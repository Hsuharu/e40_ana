#!/usr/bin/env python3.5

#____________________________________________________

__author__  = 'Y.Nakada <nakada@km.phys.sci.osaka-u.ac.jp>'
__version__ = '3.2'
__date__    = '24 July 2018'

#____________________________________________________

import os
import sys
import resource
import psutil
import shutil
import time
import copy
import shlex
import subprocess
import tempfile

import configparser
import xml.etree.ElementTree

#____________________________________________________

rsrc = resource.RLIMIT_NPROC
soft, hard = resource.getrlimit( rsrc )
resource.setrlimit( rsrc, ( hard, hard ) )
MAX_NPROC = hard

rsrc = resource.RLIMIT_NOFILE
soft, hard = resource.getrlimit( rsrc )
resource.setrlimit( rsrc, ( hard, hard ) )
MAX_NOFILE = hard

#____________________________________________________

SCRIPT_DIR = os.path.dirname( os.path.abspath( sys.argv[0] ) )
XML_NAMESPACE = 'http://www.w3.org/2001/XMLSchema-instance'
SCHEMA_LOC_ATTRIB = 'noNamespaceSchemaLocation'
BSUB_RESPONCE = 'Job <JobID> is submitted to queue <queue>'

#____________________________________________________


#__________________________________________________
#
# BJob Class
#__________________________________________________

class BJob :

    #__________________________________________________
    def __init__( self, jid ) :

        self.__jid = jid
        # 0: PEND, 1: RUN, 2: DONE, 3: EXIT, 4: killed, -1: unknown
        self.__status = None
        self.getStatus()


    #__________________________________________________
    def getJobId( self ) :

        return self.__jid

    #__________________________________________________
    def getStatus( self ) :

        if self.__status is 2 \
           or self.__status is 3 \
           or self.__status is 4 :
            return self.__status

        cmd = 'bjobs {}'.format( self.__jid )
        try :
            proc = subprocess.run( shlex.split( cmd ),
                                   stdout = subprocess.PIPE,
                                   stderr = subprocess.PIPE,
                                   check = True )
        except subprocess.CalledProcessError as e :
            sys.stderr.write( 'ERROR: command \'{}\' returned error code ({})'\
                              .format( ' '.join( e.cmd ), e.returncode ) )
            sys.stderr.write( proc.stderr )

        buff = proc.stdout.splitlines()[1].decode().split()
    
        status = None
        if int( buff[0] ) == self.__jid :
            if buff[2] ==   'PEND' :
                status = 0
            elif buff[2] == 'RUN' :
                status = 1
            elif buff[2] == 'DONE' :
                status = 2
            elif buff[2] == 'EXIT' :
                status = 3
            else :
                status = -1

            self.__status = status

        return status

    #__________________________________________________
    def kill( self ) :

        self.getStatus()
        if self.__status is 0 \
           or self.__status is 1 :

            cmd = 'bkill {}'.format( self.__jid )
            proc = subprocess.run( shlex.split( cmd ),
                                   stdout = subprocess.DEVNULL,
                                   stderr = subprocess.DEVNULL )
            self.__status = 4


    #__________________________________________________
    @staticmethod
    def readJobId( buff ) :
    
        jid = None
        fl = True

        words = buff.split()

        for i, item in enumerate( BSUB_RESPONCE.split() ) :
            if i == 1 or i == 6 : continue
            if item != words[i] :
                fl = False

        if fl is True :
            jid = int( words[1][1:-1] )
    
        return jid



#__________________________________________________
#
# Analysis Job Class
#__________________________________________________

class AnalysisJob :

    #__________________________________________________
    def __init__( self,
                  manager,
                  tag, conf, out, log ) :

        self.__mainProc = psutil.Process()
        self.__manager = manager

        self.__tag = tag

        self.__conf = conf
        self.__out  = out
        self.__log  = log

        self.__pid  = None
        self.__proc = None

        self.__jid  = None
        self.__bjob = None

        # True: success, False: failure,
        #  0: process thrown, 1: process return and bsub running, 2: killed, -1: unknown
        self.__status   = None 

        self.__statProc = None # UNIX process. True: success, False: failure, 0: processing
        self.__statBjob = None # bsub process. True: success, False: failure, 0: processing, 1: killed


    #__________________________________________________
    def getTag( self ) :

        return self.__tag


    #__________________________________________________
    def getProcessId( self ) :

        return self.__pid


    #__________________________________________________
    def getJobId( self ) :

        return self.__jid


    #__________________________________________________
    def getStatus( self ) :

        if self.__status is True \
           or self.__status is False \
           or self.__status is 2 :
            return self.__status
        elif self.__status is 0 :
            self.__updateProcessStatus()
            if self.__status is 1 :
                self.__updateJobStatus()
        elif self.__status is 1 :
            self.__updateJobStatus()
        else :                  # unknown case
            self.__updateProcessStatus()
            self.__updateJobStatus()

        return self.__status


    #__________________________________________________
    def __updateProcessStatus( self ) :

        if not self.__statProc is 0 :
            return

        if self.__proc.poll() is None :
            return
        elif self.__proc.poll() == 0 :
            self.__statProc = True
            if self.__bjob is None :
                self.__registerJob()
        elif self.__proc.poll() == 1 :
            sys.stderr.write( 'ERROR: bsub command failed at {}\n'\
                              .format( self.__tag ) )
            outs, errs = proc.communicate()
        else :
            self.__statProc = -1
            self.__status   = -1


    #__________________________________________________
    def __updateJobStatus( self ) :

        if not self.__statBjob is 0 :
            return

        status = self.__bjob.getStatus()
        if status is None :     # initial
            pass
        elif status is 0 :      # PEND
            pass
        elif status is 1 :      # RUN
            pass
        elif status is 2 :      # DONE
            self.__statBjob = True
            self.__status   = True
        elif status is 3 :      # EXIT
            self.__statBjob = False
            self.__status   = False
        elif status is 4 :      # killed
            pass
        else :                  # unknow case
            self.__statBjob = -1
            self.__status   = -1


    #__________________________________________________
    def __registerJob( self ) :

        if self.__jid is None and self.__statProc is True :
            buff  = self.__proc.communicate()[0]
            self.__jid = BJob.readJobId( buff.decode() )
            self.__bjob = BJob( self.__jid )
            self.__statBjob = 0
            self.__status   = 1


    #__________________________________________________
    def execute( self ) :

        if not self.__statProc is None :
            return

        while True :
            nfds = self.__mainProc.num_fds()
            nproc = len( self.__mainProc.children( recursive=True ) )
            if nfds < MAX_NOFILE and nproc < MAX_NPROC :
                break

        pf = self.__manager.getPreFetchPath()

        cmd = shlex.split( 'bsub' + ' ' \
                           + '-q' + ' ' + self.__manager.getQueue() + ' ' \
                           + self.__manager.getOption() + ' ' \
                           + '-o' + ' ' + self.__log + ' ' \
                           + '-a \"prefetch (' + pf + ')\"' )

        cmd.extend( [ self.__manager.getExecutingPath(),
                      self.__conf,
                      self.__manager.getDataPath(),
                      self.__out ] )

        self.__proc = subprocess.Popen( cmd,
                                        stdout = subprocess.PIPE,
                                        stderr = subprocess.PIPE )

        self.__pid = self.__proc.pid

        self.__statProc = 0
        self.__status   = 0


    #__________________________________________________
    def kill( self ) :

        self.__updateProcessStatus()
        if self.__statProc == 0 \
           or self.__statProc == -1 :
            sys.stdout.write( 'Killing process [pid: {}]\n'.format( self.__pid ) )
            self.__proc.kill()
            self.__status = 2

        self.__updateJobStatus()
        if self.__statBjob == 0 \
           or self.__statBjob == -1 :
            sys.stdout.write( 'Killing job [jid: {}]\n'.format( self.__pid ) )
            self.__bjob.kill()
            self.__status = 2



#__________________________________________________
#
# Job Manager Class
#__________________________________________________

class JobManager :

    #__________________________________________________
    def __init__( self,
                  tag,
                  key,
                  fexec_path, fconf_path, fdata_path, fout_path,
                  nproc = 1, buff_path = None,
                  queue = 's', div_unit = 0, nevents = None ) :

        # true: success, false: failure,
        # 0: bjob running, 1: bjob complete, 2: merging, 3: killed
        self.__status = None 

        # true: success, false: failure, 0: running, 1: killed
        self.__statBjob  = None
        self.__statMerge = None

        self.__tag = tag

        self.__key = key

        self.__stime = time.time()
        self.__ctime = self.__stime
        self.__diffTime = 0

        self.__baseName = self.__tag + '_' \
                          + os.path.splitext( os.path.basename( fout_path ) )[0]

        dtmp_path = '{}/tmp'.format( SCRIPT_DIR )
        if not os.path.exists( dtmp_path ) :
            os.mkdir( dtmp_path )
        self.__dDummy = tempfile.TemporaryDirectory( dir=dtmp_path )

        self.__fExecPath     = fexec_path
        self.__fConfPath     = fconf_path
        self.__fDataPath     = fdata_path
        self.__fOutPath      = fout_path
        self.__fPreFetchPath = None
        self.__fUnpackPath   = None
        self.__fSchemaPath   = None
        self.__fLogPath      = None
        self.__fMergeLogPath = None

        self.__nProc = nproc
        self.__buffPath = buff_path

        self.__nEvents = nevents
        self.__divUnit = div_unit

        self.__queue  = queue
        self.__option = ''

        self.__elemList    = list()
        self.__fConfList   = list()
        self.__fUnpackList = list()
        self.__fOutList    = list()
        self.__fLogList    = list()
        self.__bjobList    = list()

        self.__procMerge = None
        self.__jobMerge  = None

        self.__makeFLog()
        self.__makeFPreFetch()

        self.__dumpInitInfo()

        self.__makeElem()

        self.__nComplete = 0


    #__________________________________________________
    def setOption( self, option ) :

        self.__option = option


    #__________________________________________________
    def getOption( self ) :

        return self.__option


    #__________________________________________________
    def getKey( self ) :

        return self.__key


    #__________________________________________________
    def getPreFetchPath( self ) :

        return self.__fPreFetchPath


    #__________________________________________________
    def getExecutingPath( self ) :

        return self.__fExecPath


    #__________________________________________________
    def getDataPath( self ) :

        return self.__fDataPath


    #__________________________________________________
    def getQueue( self ) :

        return self.__queue


    #__________________________________________________
    def getNSegs( self ) :

        return len( self.__elemList )


    #__________________________________________________
    def getProgress( self ) :

        return self.__nComplete


    #__________________________________________________
    def getStartTime( self ) :

        return time.ctime( self.__stime )


    #__________________________________________________
    def getDiffTime( self ) :

        if not self.__status is True \
           and not self.__status is False :
            self.__ctime = time.time()
            self.__diffTime = self.__ctime - self.__stime

        return self.__diffTime


    #__________________________________________________
    def getInfo( self ) :

        info = dict()
        info['queue'] = self.__queue
        info['nproc'] = self.__nProc
        info['unit']  = self.__divUnit
        info['nev']   = self.__nEvents
        info['bin']   = self.__fExecPath
        info['conf']  = self.__fConfPath
        info['data']  = self.__fDataPath
        info['root']  = self.__fOutPath
        info['time']  = self.getDiffTime()
        info['stat']  = self.getStatus()
        info['nseg']  = self.getNSegs()
        info['prog']  = self.getProgress()

        return { format( self.__key ): info }


    #__________________________________________________
    def getStatus( self ) :

        if self.__status is None \
           or self.__status is True \
           or self.__status is False :
            return self.__status

        if self.__status is 0 :
            self.__updateJobStatus()
        elif self.__status is 1 :
            pass
        elif self.__status is 2 :
            self.__updateMergingStatus()
        elif self.__status is 3 :
            pass
        else :
            self.__updateJobStatus()
            self.__updateMergingStatus()

        return self.__status


    #__________________________________________________
    def __updateJobStatus( self ) :

        if not self.__statBjob is 0 :
            return

        n_complete = 0
        for job in self.__bjobList :

            stat = job.getStatus()
            if stat is True :
                n_complete += 1
            elif stat is False :
                self.__statBjob = False
                self.__status   = False
                self.__dumpLog( 'error', 'error at {}'.format( job.getTag() ) )
                self.__dumpLog( None,  64 * '_' )

        if len( self.__elemList ) == n_complete :
            self.__statBjob = True
            self.__status   = 1

        self.__nComplete = n_complete


    #__________________________________________________
    def mergeFOut( self ) :

        if not self.__statMerge is None :
            return

        size = 0
        for item in self.__fOutList :
            size += os.path.getsize( item )

        qOpt = '-q sx' if size > 2 * 1024**3 + 5 * 1024**2 else '-q s'
        pOpt = '-j {}'.format( self.__nProc ) if self.__nProc > 1 else ''
        bOpt = '-d {}'.format( self.__buffPath ) if not self.__buffPath is None else ''

        cmd = shlex.split( 'bsub {} -o {} hadd -ff {} {}'\
                           .format( qOpt, self.__fMergeLogPath, pOpt, bOpt ) )
        cmd.append( self.__fOutPath )
        cmd.extend( self.__fOutList )

        self.__procMerge = subprocess.run( cmd,
                                           stdout = subprocess.PIPE,
                                           stderr = subprocess.PIPE,
                                           check = True )
        buff = self.__procMerge.stdout
        self.__jobMerge = BJob( BJob.readJobId( buff.decode() ) )

        self.__dumpLog( 'jid[merge]', self.__jobMerge.getJobId() )
        self.__dumpLog( None,  64 * '_' )

        self.__statMerge = 0
        self.__status    = 2


    #__________________________________________________
    def __updateMergingStatus( self ) :

        if self.__statMerge is True \
           or self.__statMerge is False :
            return

        if self.__statMerge is 0 :
            stat = self.__jobMerge.getStatus()
            if stat == 0 or stat == 1 : # PEND or RUN
                return
            elif stat == 2 :    # DONE
                self.__statMerge = True
                self.__status    = True
            elif stat == 3 :    # EXIT
                self.__statMerge = False
                self.__status    = False
                self.__dumpLog( 'error', 'merging error' )
                self.__dumpLog( None,  64 * '_' )
            else :              # unknown
                self.__statMerge = -1
                self.__status    = -1
                

    #__________________________________________________
    def execute( self ) :

        if not self.__statBjob is None :
            return

        self.__makeFConflist()
        self.__makeFOutlist()
        self.__makeFLoglist()

        for i, elem in enumerate( self.__elemList ) :

            if os.path.exists( self.__fOutList[i] ) :
                os.remove( self.__fOutList[i] )

            job = AnalysisJob( self, elem,
                               self.__fConfList[i],
                               self.__fOutList[i],
                               self.__fLogList[i] )
            job.execute()

            self.__bjobList.append( job )

        for i, item in enumerate( self.__bjobList ) :
            self.__dumpLog( 'pid[bsub({})]'.format( i ), item.getProcessId() )
        self.__dumpLog( None,  64 * '_' )

        self.__statBjob = 0
        self.__status   = 0


    #__________________________________________________
    def killBjob( self ) :

        if self.__statBjob is True :
            return

        for job in self.__bjobList :

            stat = job.getStatus()
            if stat is 0 or stat is 1 :

                job.kill()

                self.__statBjob = 1

                jpid = job.getProcessId() if stat is 0 \
                       else job.getJobId()
                buff = 'Process was killed [jid/pid: {}]'\
                       .format( jpid )
                self.__dumpLog( 'killBjob', buff )

        if self.__statBjob is 1 :
            self.__dumpLog( None,  64 * '_' )


    #__________________________________________________
    def killMerge( self ) :

        self.__updateMergingStatus()

        if self.__statMerge is True \
           or self.__statMerge is False :
            return

        if self.__statMerge is 0 :

            sys.stdout.write( 'Killing merging job\n' )
            self.__jobMerge.kill()
            self.__statMerge = 1
            buff = 'merging job was killed [jid: {}]'\
                   .format( self.__jobMerge.getJobId() )
            self.__dumpLog( 'killMerge', buff )
            self.__dumpLog( None,  64 * '_' )


    #__________________________________________________
    def killAll( self ) :

        if self.__status is True :
            return
        elif self.__status is 0 \
             or self.__status is 1 \
             or self.__status is 2 :
            self.__status = 3

        self.killBjob()
        self.killMerge()


    #__________________________________________________
    def __makeElem( self ) :

        if self.__divUnit <= 0 :
            nsegs = 1
        else :
            nsegs = 1 if self.__nEvents is None else \
                    self.__nEvents // self.__divUnit + 1

        for i in range( nsegs ) :
            self.__elemList.append( '{}_{}'.format( self.__baseName, i ) )

        self.__dumpLog( 'elem', self.__elemList )
        self.__dumpLog( None,   64 * '_' )

        return nsegs


    #__________________________________________________
    def __makeFLog( self ) :

        dlog = SCRIPT_DIR + '/log'
        if not os.path.exists( dlog ) :
            os.mkdir( dlog )

        self.__fLogPath = dlog + '/' + self.__baseName + '.log'

        if os.path.exists( self.__fLogPath ) :
            os.remove( self.__fLogPath )


    #__________________________________________________
    def __makeFPreFetch( self ) :

        self.__fPreFetchPath = self.__dDummy.name + '/' + self.__baseName + '.pf'

        with open( self.__fPreFetchPath, 'w' ) as f :
            f.write( self.__fDataPath )


    #__________________________________________________
    def __makeFConflist( self ) :

        with open( self.__fConfPath, 'r' ) as f :
            buff = '[dummy]\n' + f.read()

        config = configparser.ConfigParser( delimiters=':', comment_prefixes='#' )
        config.optionxform = lambda option: option
        try :
            config.read_string( buff )
            tmp_unpack = config.get( 'dummy', 'UNPACK' )
        except configparser.Error as e :
            sys.stderr.write( 'ERROR: Invalid format in {}\n'\
                              .format( self.__fConfPath ) )
            self.__status = False
            return

        if os.path.exists( tmp_unpack ) :
            self.__fUnpackPath = os.path.abspath( tmp_unpack )
        else :
            sys.stderr.write( 'ERROR: Cannot find file > {}'\
                              .format( tmp_unpack ) )
            self.__status = False
            return

        for item in self.__elemList :

            path_unpack = self.__dDummy.name + '/' + item + '.xml'
            config['dummy']['UNPACK'] = path_unpack

            path_conf = self.__dDummy.name + '/' + item + '.conf'
            with open( path_conf, 'w' ) as f :
                for option in config.options( 'dummy' ) :
                    f.write( option + ':\t' + config.get( 'dummy', option ) + '\n' )
            
            self.__fConfList.append( path_conf )
            self.__fUnpackList.append( path_unpack )

        self.__dumpLog( 'conf',   self.__fConfList )
        self.__dumpLog( 'unpack', self.__fUnpackList )
        self.__dumpLog( None,     64 * '_' )

        self.__generateFUnpack()


    #__________________________________________________
    def __generateFUnpack( self ) :

        tree = xml.etree.ElementTree.parse( self.__fUnpackPath )

        self.__generateSchema( os.path.dirname( self.__fUnpackPath ),
                               tree )

        for i, item in enumerate( self.__fUnpackList ) :
            tmp = copy.deepcopy( tree )

            root = tmp.getroot()
            key = '{{{}}}{}'.format( XML_NAMESPACE, SCHEMA_LOC_ATTRIB )
            root.set( key, self.__fSchemaPath )

            for node in tmp.findall( 'control/skip' ) :
                node.text = str( i * self.__divUnit )
            for node in tmp.findall( 'control/max_loop' ) :
                node.text = str( -1 if i == len( self.__fUnpackList ) - 1 \
                                 else self.__divUnit )

            tmp.write( item )


    #__________________________________________________
    def __generateSchema( self, path, tree ) :

        root = tree.getroot()
        fsrc = root.get( '{{{}}}{}'.format( XML_NAMESPACE, SCHEMA_LOC_ATTRIB ) )
        src = path + '/' + fsrc
        
        self.__fSchemaPath = self.__dDummy.name + '/' + self.__baseName + '.xsd'
        shutil.copyfile( src, self.__fSchemaPath )


    #__________________________________________________
    def __makeFOutlist( self ) :

        for item in self.__elemList :
            path = os.path.dirname( self.__fOutPath ) + '/' + item + '.root'
            self.__fOutList.append( path )

        self.__dumpLog( 'out', self.__fOutList )
        self.__dumpLog( None,  64 * '_' )


    #__________________________________________________
    def __makeFLoglist( self ) :

        dlog = SCRIPT_DIR + '/log'
        if not os.path.exists( dlog ) :
            os.mkdir( dlog )

        for item in self.__elemList :
            path = dlog + '/' + item + '.log'
            self.__fLogList.append( path )

        self.__fMergeLogPath = dlog + '/' + self.__baseName + '_merge.log'
        if os.path.exists( self.__fMergeLogPath ) :
            os.remove( self.__fMergeLogPath )

        self.__dumpLog( 'log', self.__fLogList )
        self.__dumpLog( 'mergelog', self.__fMergeLogPath )
        self.__dumpLog( None,  64 * '_' )


    #__________________________________________________
    def finalize( self, flag = False ) :

        self.__dumpLog( 'end', time.ctime( time.time() ) )

        if self.__status is True :
            self.clearAll()
        elif 3 == self.__status :
            if flag is True :
                self.clear()
            else :
                self.clearAll()
        else :
            self.clear()


    #__________________________________________________
    def clear( self ) :

        self.clearFOut()


    #__________________________________________________
    def clearAll( self ) :

        self.clearFOut()
        self.clearAllLog()


    #__________________________________________________
    def clearFOut( self ) :

        for item in self.__fOutList :
            if os.path.exists( item ) :
                os.remove( item )


    #__________________________________________________
    def clearAllLog( self ) :

        self.clearFLog()
        self.clearMainLog()
        self.clearMergeLog()


    #__________________________________________________
    def clearFLog( self ) :

        for item in self.__fLogList :
            if os.path.exists( item ) :
                os.remove( item )


    #__________________________________________________
    def clearMainLog( self ) :

        if not self.__fLogPath is None :
            if os.path.exists( self.__fLogPath ) :
                os.remove( self.__fLogPath )


    #__________________________________________________
    def clearMergeLog( self ) :

        if not self.__fMergeLogPath is None :
            if os.path.exists( self.__fMergeLogPath ) :
                os.remove( self.__fMergeLogPath )


    #__________________________________________________
    def __dumpLog( self, key = None, buff = None ) :

        with open( self.__fLogPath, 'a' ) as flog :

            if key is None :
                if buff is None :
                    flog.write( '\n' )
                else :
                    flog.write( str( buff ) + '\n' )
            else :
                if buff is None :
                    flog.write( str( key ) + ':\n' )
                elif isinstance( buff, list ) or isinstance( buff, tuple ) :
                    for i, item in enumerate( buff ) :
                        flog.write( '{}({}):'.format( key, i ).ljust(16) )
                        flog.write( str( item ) + '\n' )
                else :
                    flog.write( '{}:'.format( key ).ljust( 16 ) )
                    flog.write( str( buff ) + '\n' )


    #__________________________________________________
    def __dumpInitInfo( self ) :

        self.__dumpLog( 'start',    time.ctime( self.__stime ) )
        self.__dumpLog( None,       64 * '_' )
        self.__dumpLog( 'key',      self.__key )
        self.__dumpLog( None,       64 * '_' )
        self.__dumpLog( 'bin',      self.__fExecPath )
        self.__dumpLog( 'conf',     self.__fConfPath )
        self.__dumpLog( 'data',     self.__fDataPath )
        self.__dumpLog( 'unit',     self.__divUnit )
        self.__dumpLog( 'nevent',   self.__nEvents )
        self.__dumpLog( 'out',      self.__fOutPath )
        self.__dumpLog( 'nproc',    self.__nProc )
        self.__dumpLog( 'buffPath', self.__buffPath )
        self.__dumpLog( 'queue',    self.__queue )
        self.__dumpLog( 'prefetch', self.__fPreFetchPath )
        self.__dumpLog( 'dirdummy', self.__dDummy.name )
        self.__dumpLog( None,       64 * '_' )

#!/usr/bin/env python3.5

#____________________________________________________

__author__  = 'Y.Nakada <nakada@km.phys.sci.osaka-u.ac.jp>'
__version__ = '3.2'
__date__    = '24 July 2018'

#____________________________________________________

import os
import sys
import time
import signal
import fcntl

import json

sys.path.append( os.path.dirname( os.path.abspath( sys.argv[0] ) )
                 + '/module' )

import utility
import RunlistManager
import JobManager

#____________________________________________________

SLEEP_TIME = 0

#____________________________________________________

def handler( num, frame ) :

    print( 'KeyboardInterrupt' )

    print( 'Terminating processes...' )

    info = dict()
    for job in joblist :
        job.killAll()
        info.update( job.getInfo() )
    with open( fJobInfo, 'w' ) as f :
        json.dump( info, f, indent=4 )

    time.sleep( 1 )             # waiting until bsub log files are generated

    fl = False
    tmp = input( 'Keep log files? [y/-] >> ' )
    if 'y' == tmp :
        print( 'Deleting intermediate files...' )
        fl = True
    else :
        print( 'Deleting files...' )

    for item in joblist :
        item.finalize( fl )

    sys.exit( 0 )

#____________________________________________________

argvs = sys.argv
argc = len( argvs )

if argc != 2 :
    print( 'USAGE: {} [ file ]'.format( argvs[0] ) )
    sys.exit( 0 )

if not os.path.exists( argvs[1] ) :
    utility.ExitFailure( 'No such file: {}'.format( argvs[1] ) )

frunlist = argvs[1]

print( 'Press \'Ctrl-C\' to terminate processes.' )

#____________________________________________________

dJobInfo = os.path.dirname( os.path.abspath( sys.argv[0] ) ) + '/stat'
if not os.path.exists( dJobInfo ) :
    os.mkdir( dJobInfo )

fJobInfo = dJobInfo + '/'\
           + os.path.splitext( os.path.basename( frunlist ) )[0]\
           + '.json'

#____________________________________________________

runMan  = RunlistManager.RunlistManager( frunlist )
runtag  = runMan.getTag()
runlist = runMan.getRunlist()

joblist = list()

info = dict()
for run in runlist :
    jobMan = JobManager.JobManager( runtag, *run )
    nsegs  = jobMan.getNSegs()
    joblist.append( jobMan )
    info.update( jobMan.getInfo() )

buff = json.dumps( info, indent=4 )
with open( fJobInfo, 'w+' ) as f :
    try :
        fcntl.flock( f.fileno(), fcntl.LOCK_EX )
        f.write( buff )
        f.truncate()
    except IOError :
        sys.stderr.write( 'ERROR: I/O error was detected.\n' )
    finally :
        fcntl.flock( f.fileno(), fcntl.LOCK_UN )

signal.signal( signal.SIGINT, handler )

njobs = len( joblist )
fl_done = [ 0 for i in range( njobs ) ]

while sum( fl_done ) != njobs :

    info = dict()

    for i, job in enumerate( joblist ) :
        status = job.getStatus()
        if status is None :
            job.execute()
        elif status is 0 :
            pass
        elif status is 1 :
            job.mergeFOut()
        elif status is 2 :
            pass
        elif status is True :
            if fl_done[i] == 0 :
                job.finalize()
                fl_done[i] = 1
        elif status is False :
            if fl_done[i] == 0 :
                job.finalize()
                fl_done[i] = 1
        else :
            sys.stderr.write( 'ERROR: unknown status was detected.\n' )
            
        info.update( job.getInfo() )

    buff = json.dumps( info, indent=4 )
    with open( fJobInfo, 'w+' ) as f :
        try :
            fcntl.flock( f.fileno(), fcntl.LOCK_EX )
            f.write( buff )
            f.truncate()
        except IOError :
            sys.stderr.write( 'ERROR: I/O error was detected.\n' )
        finally :
            fcntl.flock( f.fileno(), fcntl.LOCK_UN )

    time.sleep( SLEEP_TIME )

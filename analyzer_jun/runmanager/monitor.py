#!/usr/bin/env python3.5

#____________________________________________________

__author__  = 'Y.Nakada <nakada@km.phys.sci.osaka-u.ac.jp>'
__version__ = '3.2'
__date__    = '24 July 2018'

#____________________________________________________

import os
import sys
import time
import fcntl

import json

sys.path.append( os.path.dirname( os.path.abspath( sys.argv[0] ) )
                 + '/module' )

import utility
from utility import pycolor as cl

#____________________________________________________

SLEEP_TIME = 5

#____________________________________________________

def display( filename ) :

    buff = str()
    with open( filename, 'r' ) as f :
        try :
            fcntl.flock( f.fileno(), fcntl.LOCK_SH )
            buff = f.read()
        except IOError :
            pass
            # sys.stderr.write( 'ERROR: I/O error was detected.\n' )
        finally :
            fcntl.flock( f.fileno(), fcntl.LOCK_UN )

    info = json.loads( buff )

    os.system( 'clear' )

    buff =  cl.reverce + cl.bold\
            + 'KEY'.ljust(8)   + '  '\
            + 'STAT'.ljust(16) + '  '\
            + 'BIN'.ljust(16)  + '  '\
            + 'CONF'.ljust(16) + '  '\
            + 'DATA(#EVENT)'.ljust(24) + '  '\
            + 'ROOT'.ljust(16) + '  '\
            + 'TIME'.ljust(8)\
            + cl.end
    print( buff )


    for key, item in info.items() :

        status = utility.decodeStatus( item )
        ptime  = utility.decodeTime( item )

        buff = cl.bold + key[:8].ljust(8) + cl.end + '  ' \
               + '{}{}{}{}{}'.format( cl.reverce, cl.bold, cl.red, status, cl.end ).ljust(16 + 18) + '  ' \
               + os.path.basename( item['bin'] )[-16:].ljust(16) + '  ' \
               + os.path.basename( item['conf'] )[-16:].ljust(16) + '  ' \
               + '{} ({})'.format( os.path.basename( item['data'] ), str( item['nev'] ) )[-24:].ljust(24) + '  ' \
               + os.path.basename( item['root'] )[-16:].ljust(16) + '  '\
               + ptime.rjust(8)
        print( buff )

    buff = cl.reverce + cl.bold + 'Press \'Ctrl-C\' to exit' + cl.end
    print( buff )
    
#____________________________________________________

argvs = sys.argv
argc = len( argvs )

if argc != 2 :
    print( 'USAGE: %s [ file ]' % argvs[0] )
    sys.exit( 0 )

if not os.path.exists( argvs[1] ) :
    utility.ExitFailure( 'No such file > ' + argvs[1] )

fJobInfo = argvs[1]

#____________________________________________________


while True :

    try :
        display( fJobInfo )
        time.sleep( SLEEP_TIME )

    except KeyboardInterrupt :

        print( 'KeyboardInterrupt' )
        print( 'Exiting the process...' )
        break

    except FileNotFoundError :

        sys.stderr.write( 'Cannot find file > ' + fJobInfo + '\n' )
        sys.exit( 1 )

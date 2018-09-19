#!/usr/bin/env python3.5

#____________________________________________________

__author__  = 'Y.Nakada <nakada@km.phys.sci.osaka-u.ac.jp>'
__version__ = '3.2'
__date__    = '24 July 2018'

#____________________________________________________

import sys

#____________________________________________________

def ExitFailure( message ):
    sys.stderr.write( 'ERROR: ' + message + '\n' )
    sys.exit( 1 )
    return None


#____________________________________________________

def decodeTime( info ) :

    second = int( info['time'] )

    hour    = second // 3600
    second -= hour    * 3600
    minute  = second // 60
    second -= minute  * 60

    return '{}:{:02d}:{:02d}'.format( hour, minute, second )

#____________________________________________________

def decodeStatus( info ) :

    buff = ''

    stat = info['stat']
    nseg = info['nseg']
    prog = info['prog']

    if stat is None :
        buff = 'init({})'.format( nseg )
    elif stat is 0 :
        buff = 'running({}/{})'.format( prog, nseg )
    elif stat is 1 :
        buff = 'running({}/{})'.format( prog, nseg )
    elif stat is 2 :
        buff = 'merging({})'.format( nseg )
    elif stat is 3 :
        buff = 'terminated({})'.format( nseg )
    elif stat is True :
        buff = 'done({})'.format( nseg )
    elif stat is False :
        buff = 'error({})'.format( nseg )
    else :
        buff = 'unknown({})'.format( nseg )

    return buff

#____________________________________________________

class pycolor :

    black  = '\033[30m'
    red    = '\033[31m'
    green  = '\033[32m'
    yellow = '\033[33m'
    blue   = '\033[34m'
    purple = '\033[35m'
    cyan   = '\033[36m'
    white  = '\033[37m'

    end = '\033[0m'

    bold = '\033[1m'
    underline = '\033[4m'
    invisible = '\033[08m'
    reverce   = '\033[07m'

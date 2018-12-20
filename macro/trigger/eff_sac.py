#!/usr/bin/env python2.7

import os
import ROOT
import array

runnum = 5078

file0 = ROOT.TFile( os.path.expanduser( '~' ) + '/work/analyzer_e40/rootfile/run%05d_DstKuramaHodoscope.root' % runnum, 'read' )

tree = file0.Get( 'khodo' )

hh1 = ROOT.TH2F( 'hh1', 'track point @SAC w/o SAC hit',
                1000, -100, 500, 1000, -200, 200 )
hh2 = ROOT.TH2F( 'hh2', 'track point @SAC w/ SAC time cut',
                1000, -100, 500, 1000, -200, 200 )
hh3 = ROOT.TH1F( 'hh3', 'mass w/o SAC hit',
                 1000, -0.5, 1.5 )
hh4 = ROOT.TH1F( 'hh4', ' mass w/ SAC time cut',
                 1000, -0.5, 1.5 )

hit = 0
total = 0

for event in tree :

    if event.ntKurama != 1 :
        continue

    fl_SacGeo  = False
    fl_SacTime = False
    fl_PiPlus  = False
    fl_Kurama  = False

    ntr  = event.ntKurama
    ncmb = event.m2Combi

    for i in range( ntr ) :

        if event.chisqrKurama[i] > 100 :
            continue

        fl_Kurama = True

        hh1.Fill( event.vpx[0*ntr + i], event.vpy[0*ntr + i] )

        if event.vpx[0*ntr + i] > 30 and event.vpx[0*ntr + i] < 450 \
           and event.vpy[0*ntr + i] > -170 and event.vpx[0*ntr + i] < 140 :
            fl_SacGeo = True

        for j in range( ncmb ) :
            if event.m2[j] > 0 and event.m2[j] < 0.25 \
               and event.pKurama[i] > 0.2 and event.pKurama[i] < 1.2 \
               and event.qKurama[i] > 0 :
                fl_PiPlus = True


    if fl_Kurama is True :

        for i in range( ncmb ) :
            
            hh3.Fill( event.m2[i] )


    if event.nhSac == 0 :
        continue

    for time in event.tSac :
        if time > -15 and time < 15 :
            fl_SacTime = True

    if fl_SacTime is True :

        for i in range( ntr ) :
            hh2.Fill( event.vpx[0*ntr + i], event.vpy[0*ntr + i] )

        for i in range( ncmb ) :
            hh4.Fill( event.m2[i] )

    if fl_PiPlus is True and fl_SacGeo is True:
        total += 1
        if fl_SacTime is True :
            hit += 1

print 'total:', total
print 'hit:  ', hit
print 'eff:  ', float(hit)/float(total)


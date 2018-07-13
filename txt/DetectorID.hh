/**
 *  file: DetectorID.hh
 *  date: 2017.04.10
 *
 */

#ifndef DETECTOR_ID_HH
#define DETECTOR_ID_HH

#include <iostream>

// Counters ___________________________________________________________
const int DetIdBH1      =  1;
const int DetIdBH2      =  2;
const int DetIdSCH      =  7;
const int DetIdTOF      =  8;
const int DetIdSAC      =  9;
const int DetIdLC       = 10;
const int DetIdHtTOF    = 11; // high threshold TOF
const int NumOfSegBH1   = 11;
const int NumOfSegBH2   =  8;
const int NumOfSegSCH   = 64;
const int NumOfSegTOF   = 24;
const int NumOfSegSAC   = 4;
const int NumOfSegLC    = 28;
const int NumOfSegHtTOF = 16;

// Misc _______________________________________________________________
const int DetIdTrig       = 21;
const int DetIdScaler     = 22;
const int DetIdMsT        = 25;
const int DetIdMtx        = 26;
const int DetIdFpgaBH2Mt  = 29;
const int DetIdVmeRm      = 81;
const int DetIdMsTRM      = 82;
const int DetIdHulRM      = 83;
const int NumOfSegTrig    = 32;
const int NumOfSegScaler  = 96;
const int SpillEndFlag    = 27; // 0-based
const int NumOfPlaneVmeRm = 2;

enum eTriggerFlag
  {
    kBh21K      =  0,
    kBh22K      =  1,
    kBh23K      =  2,
    kBh24K      =  3,
    kBh25K      =  4,
    kBh26K      =  5,
    kBh27K      =  6,
    kBh28K      =  7,
    kBh2K       =  8,
    kElseOr     =  9,
    kBeam       = 10,
    kBeamTof    = 11,
    kBeamPi     = 12,
    kBeamP      = 13,
    kCoin1      = 14,
    kCoin2      = 15,
    kE03        = 16,
    kBh2KPs     = 17,
    kBeamPs     = 18,
    kBeamTofPs  = 19,
    kBeamPiPs   = 10,
    kBeamPPs    = 21,
    kCoin1Ps    = 22,
    kCoin2Ps    = 23,
    kE03Ps      = 24,
    kClock      = 25,
    kReserve2   = 26,
    kSpillEnd   = 27,
    kMatrix     = 28,
    kMstAccept  = 29,
    kMstClear   = 30,
    kTofTiming  = 31
  };

const int DetIdVmeCalib      = 999;
const int NumOfPlaneVmeCalib =   5;
const int NumOfSegVmeCalib   =  32;

// Trackers ___________________________________________________________
const int DetIdBC3  = 103;
const int DetIdBC4  = 104;
const int DetIdSDC1 = 105;
const int DetIdSDC2 = 106;
const int DetIdSDC3 = 107;
const int DetIdBFT  = 110;
const int DetIdSFT  = 111;
const int DetIdFBT1 = 131;
const int DetIdFBT2 = 132;

const int PlMinBcIn        =   1;
const int PlMaxBcIn        =  12;
const int PlMinBcOut       =  13;
const int PlMaxBcOut       =  24;
const int PlMinSdcIn       =   1;
const int PlMaxSdcIn       =   9;
const int PlMinFBT1        =  80;
const int PlMaxFBT1        =  83;
const int PlMinFBT2        =  84;
const int PlMaxFBT2        =  87;
const int PlMinSdcOut      =  31;
const int PlMaxSdcOut      =  38;
const int PlOffsBc         = 100;
const int PlOffsSdcIn      =   0;
const int PlOffsSft        =   6;
const int PlOffsSdcOut     =  30;
const int PlOffsVP         =  20;

const int NumOfLayersBc     = 6;
const int NumOfLayersSFT    = 3;
const int NumOfLayersSDC1   = 6;
const int NumOfLayersSDC2   = 4;
const int NumOfLayersSDC3   = 4;
const int NumOfLayersFBT1   = 2;
const int NumOfLayersFBT2   = 2;
const int NumOfLayersBcIn   = PlMaxBcIn   - PlMinBcIn   + 1;
const int NumOfLayersBcOut  = PlMaxBcOut  - PlMinBcOut  + 1;
const int NumOfLayersSdcIn  = PlMaxSdcIn  - PlMinSdcIn  + 1;
const int NumOfLayersFBT    = PlMaxFBT2   - PlMinFBT1   + 1;
const int NumOfLayersSdcOut = PlMaxSdcOut - PlMinSdcOut + 1;
const int NumOfLayersVP     = 5;

const int MaxWireBC3      =  64;
const int MaxWireBC4      =  64;

const int MaxWireSDC1     =  64;
const int MaxWireSDC2     = 128;
const int MaxWireSDC3X    =  96;
const int MaxWireSDC3Y    =  64;

const int MaxSegFBT1      =  48;
const int MaxSegFBT2      =  64;

const int NumOfPlaneBFT   =   2;
const int NumOfSegBFT     = 160;
// SFT X layer has U D plane.
// SFT UV layers have only U plnane.
// enum SFT_PLANE{ SFT_X1, SFT_X2, SFT_V, SFT_U };
enum SFT_PLANE{ SFT_U, SFT_V, SFT_X1, SFT_X2 };
const int NumOfPlaneSFT   =   4;
const int NumOfSegSFT_X   = 256;
const int NumOfSegSFT_UV  = 320;
const int NumOfSegCSFT    = 48;

// HulRm -----------------------------------------------
const int NumOfHulRm   = 4;

// Matrix ----------------------------------------------
const int NumOfSegSFT_Mtx = 48;

// MsT -------------------------------------------------
enum TypesMst{typeHrTdc, typeLrTdc, typeFlag, NumOfTypesMst};
const int NumOfMstHrTdc = 32;
const int NumOfMstLrTdc = 64;
const int NumOfMstFlag  = 7;
enum dTypesMst
  {
    mstClear,
    mstAccept,
    finalClear,
    cosolationAccept,
    fastClear,
    level2,
    noDecision,
    size_dTypsMsT
  };


const char*  STOF_HT[] =
  {
    "TOF Seg(1,20)",
    "TOF Seg(5,22)",
    "TOF Seg(18  )",
    "TOF Seg(4,10)",
    "TOF Seg(2,11)",
    "TOF Seg(8,24)",
    "TOF Seg(6,9 )",
    "TOF Seg(7,23)",
    "TOF Seg(12  )",
    "TOF Seg(19  )",
    "TOF Seg(13  )",
    "TOF Seg(14  )",
    "TOF Seg(15  )",
    "TOF Seg(16  )",
    "TOF Seg(3,21)",
    "TOF Seg(17  )",
  };

enum  httof_segnum
  {
    TOF1_20 =  0,
    TOF5_22 =  1,
    TOF18   =  2,
    TOF4_10 =  3,
    TOF2_11 =  4,
    TOF8_24 =  5,
    TOF6_9  =  6,
    TOF7_23 =  7,
    TOF12   =  8,
    TOF19   =  9,
    TOF13   = 10,
    TOF14   = 11,
    TOF15   = 12,
    TOF16   = 13,
    TOF3_21 = 14,
    TOF17   = 15
  };

// Scaler ----------------------------------------------
const int NumOfScaler  = 2;

#endif

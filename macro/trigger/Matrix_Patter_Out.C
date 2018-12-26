#include "DetectorID.hh"
#include <fstream>
#include <string>
#include <vector>

 const char* Month[] =
 {
   "zero",
   "jan",
   "feb",
   "mar",
   "apr",
   "may",
   "jun",
   "jly",
   "agt",
   "sep",
   "oct",
   "nov",
   "dec",
 };

void Matrix_Pattern_Out( int month){

//Matrix Patern txt file PATH -----------------------------------------------------------------------
   TString anadir=Form("%s/work/e40/ana",std::getenv("HOME")); 
   TString filein1=Form("%s/analyzer_%s/param/MATRIXSFT/SFT_table.txt.2018Jun.3_1",anadir.Data(),Month[month] ); 

// Matrix Parameter Vector Dif ----------------------------------------------------------------------
  std::vector<std::vector<int>> Mtx_prm; 




}

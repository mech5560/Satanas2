/*  Last Modified Time-stamp: <2014-06-11 17:23:32 mike_georgiou> */ 
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

void Print_Binary(double ***A, int ldx, int ldy, int ldz,
		  int time_index,const char *mike)
{


  stringstream ss;

  string directory = "./Printing/Postprocessing/";
  string format = ".bin";
  string finalName;

  ss<<directory<<mike<<time_index<<format;
  finalName = ss.str();

   ofstream  outfile;
   outfile.open(finalName,ios::out | ios::binary);



for (int k = 0; k < ldz; k++){
  for (int j = 0; j < ldy; j++){
    for (int i = 0; i < ldx; i++){
      
      outfile.write( (char*)&A[0][j][i],sizeof(double));
    }
  }	    
 }   

 
}


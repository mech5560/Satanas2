/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <>   
*
*
Print_2D_Non_Uniform.cpp -- This program will save the output of my code
for the case of a non-uniform grid. 
*
* Written on Tuesday,  3 June 2014.
********************************************/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;
void Print_2D_Non_Curve_Uniform(double*** data,
			  double dx, double* dy,
			  int ldx, int ldy, int ldz,
			  int time_index,
			  const char* mike, int index)


{
  stringstream ss;
  string out = "";

  string format = ".dat";
  string finalName;

  ss<<out<<mike<<time_index<<index<<"curve"<<format;
  finalName = ss.str();
 

  ofstream outfile;
  outfile.open(finalName);




  if(index==1)
    {
  
  double y_local = 0.;
  for (int j = 0; j < ldy; j++){
    double x_local =0.;
    y_local+= dy[j];
    for (int i = 0; i < ldx; i++){
      
      x_local += dx/2.;
      outfile<<x_local<<" "<<y_local<<" "<<data[0][j][i]<<endl;
      x_local+=dx/2.;


    }
    y_local+= dy[j];
  }	    

    }
  else if(index ==2)
    {
  
    double x_local =0.;
    for (int i = 0; i < ldx; i++){ 
      x_local+= dx/2.;
      double y_local = 0.;
      for (int j = 0; j < ldy; j++){
	y_local+= dy[j];     
	outfile<<x_local<<" "<<y_local<<" "<<data[0][j][i]<<endl;
	y_local+= dy[j];     
    }
      x_local+= dx/2.;
    }	    
    
    }

  else { cout<<"wrong input"<<endl;}


}

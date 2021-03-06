/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-16 09:23:16 mike_georgiou>
 *
 *
Initial_Reader.cpp -- This program reads the initial velocity
profiles from a number of data files that will be introduced by the
user in this folder.
*
* Written on Thursday, 15 May 2014.
********************************************/

#include "Initial_Reader.h"

using namespace std;

void Initial_Reader(double*** velocity_x, double*** velocity_y,
                    double*** velocity_z,
                    int ldx, int ldy, int ldz)
{

  // Opening the .dat file to read the necessary information
  ifstream input_x("Input_Velocity_X.txt", ifstream::in);
  //X
  if(input_x.is_open())
    {

      for (int k = 0; k < ldz; k++){
        for (int j = 0; j < ldy; j++){
          for (int i = 0; i < ldx; i++){

            input_x>>velocity_x[k][j][i];

          }
        }
      }
    }
  else {cout << "Unable to open file X\n";}

  input_x.close();
  //Y
  ifstream input_y("Input_Velocity_Y.txt", ifstream::in);
  if(input_y.is_open())
    {

      for (int k = 0; k < ldz; k++){
        for (int j = 0; j < ldy; j++){
          for (int i = 0; i < ldx; i++){

            input_y>>velocity_y[k][j][i];

          }
        }
      }
    }
  else {cout << "Unable to open file Y\n";}

  input_y.close();


  //Z
  ifstream input_z("Input_Velocity_Z.txt", ifstream::in);
  if(input_z.is_open())
    {

      for (int k = 0; k < ldz; k++){
        for (int j = 0; j < ldy; j++){
          for (int i = 0; i < ldx; i++){

            input_z>>velocity_z[k][j][i];

          }
        }
      }
    }
  else{ cout << "Unable to open file Z\n";}
  input_z.close();




}

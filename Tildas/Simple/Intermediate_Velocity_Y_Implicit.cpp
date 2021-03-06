/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-06-04 10:41:38 mike_georgiou>
 *
 *
Intermediate_Velocity_Y.cpp -- This function computes the v_tilda of my
code. Firstly  the velocity residual is computed.
*
* Written on Tuesday, 29 April 2014.
********************************************/

#include"Intermediate_Velocity.h"

void Intermediate_Velocity_Y_Implicit(double*** velocity_y_tilda,
				      double*** residual_y,
				      double*** residual_y_old,
				      double*** velocity_x, 
				      double*** velocity_y,
				      double*** velocity_z,
				      double*** flux_x, double***flux_y, 
				      double***flux_z,
				      double*** rho_new, double*** rho,
				      double*** temperature,
				      double*** pressure,
				      double Reynolds,double source,
				      double dx, double* dy,  double dz,
				      double dt, double time_total,
				      int ldx, int ldy, int ldz)
{

  //Allocating memory for the three vectors that will be used by the
  //tridiagonal solver
  double *lower_diagonal, *central_diagonal, *upper_diagonal, *rhs,
    *result, *auxiliary;

  lower_diagonal = new double [ldy+1];
  central_diagonal = new double [ldy+1];
  upper_diagonal = new double [ldy+1];
  rhs = new double [ldy+1];
  result = new double [ldy+1];
  auxiliary = new double [ldy+1];


  for (int k=0; k<ldz; k++){
    for (int i=0; i<ldx; i++){


      for (int j=0; j<ldy; j++){


        double explicit_term=0.;
        Velocity_Residual_Y_Implicit(residual_y,
                                     velocity_x, velocity_y, velocity_z,
                                     flux_x, flux_y,  flux_z,
                                     temperature, Reynolds,
                                     source,
                                     dx, dy, dz,
                                     time_total,
                                     i, j, k,
                                     &explicit_term);

        double residual_sum=
          1.5*residual_y[k][j][i] - 0.5*residual_y_old[k][j][i];



        ////////////Define the implicit methodology that I will use
        double implicit_scheme=0.5;
        explicit_term *=(1.-implicit_scheme);


        // computing the inputs of the vectors that the tridiagonal
        //solver will get
        double coefficients[3];
        Coefficient_Calculator(temperature, Reynolds,
                               coefficients,
                               dy, dt,
                               implicit_scheme,
                               i, j, k);

	// Multiplying all the coefficient with 4/3 since i am in the
	// Y-direction
	for(int vi=0; vi<3; vi++)
	  coefficients[vi] *=4./3;

        // Filling the vectors. Be cautious in the introduction of
        //the boundary conditions
        if (j==0)
          {
            lower_diagonal[j+1] = 0.;
            central_diagonal[j+1] = coefficients[1]+ rho_new[k][j][i]
	      -coefficients[0];
            
	    upper_diagonal[j+1] = coefficients[2];

            rhs[j+1] = ((rho[k][j][i]*velocity_y[k][j][i]+
			 dt*(residual_sum+explicit_term)));

              
          }
        else if (j==ldy-1)
          {


            lower_diagonal[j+1] = coefficients[0];
            
	    central_diagonal[j+1] = coefficients[1]+ rho_new[k][j][i]
	      -coefficients[2];
            
	    upper_diagonal[j+1] = 0.;

            rhs[j+1] = ((rho[k][j][i]*velocity_y[k][j][i]+
			 dt*(residual_sum+explicit_term)));


          }
        else
          {
            lower_diagonal[j+1] = coefficients[0];
            central_diagonal[j+1] = coefficients[1]+ rho_new[k][j][i];
            upper_diagonal[j+1] = coefficients[2];

            rhs[j+1] = ((rho[k][j][i]*velocity_y[k][j][i]+
			 dt*(residual_sum +explicit_term)));


          }
      }

      // Solving the tridiagonal system
      int flag=0;
      tridag(lower_diagonal,central_diagonal,upper_diagonal,
             rhs, result, ldy, auxiliary, flag, i, k);


      for (int vj = 0; vj < ldy; vj++)
        {
          velocity_y_tilda[k][vj][i] = result[vj+1];
        }


    }
  }


  //deallocating the memory for the  vectors that will be used by the
  //tridiagonal solver

  delete[] lower_diagonal;
  delete[] central_diagonal;
  delete[] upper_diagonal;
  delete[] rhs ;
  delete[] result;
  delete [] auxiliary;
}

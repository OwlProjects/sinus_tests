/*
 * sinusFuncs.h
 *
 *  Created on: 25 июл. 2023 г.
 *      Author: serviceman
 */

#ifndef INC_SINUSFUNCS_H_
#define INC_SINUSFUNCS_H_

#define SINUS_EPS (1e-9)

#define K0 ( 1 )
#define K1 ( -1 / (1*2*3) )
#define K2 (  1 / (1*2*3*4*5) )
#define K3 ( -1 / (1*2*3*4*5*6*7) )
#define K4 (  1 / (1*2*3*4*5*6*7*8*9) )
#define K5 ( -1 / (1*2*3*4*5*6*7*8*9*10*11) )
#define K6 (  1 / (1*2*3*4*5*6*7*8*9*10*11*12*13) )

double Sin_Rec(double x, int n, double precision);
double Sinus_25(double x);
double Sinus_with_acc(double rad_x);
double Sinus_with_acc_eps(double rad_x);
double Sinus_with_reduced_expr(double x);




#endif /* INC_SINUSFUNCS_H_ */

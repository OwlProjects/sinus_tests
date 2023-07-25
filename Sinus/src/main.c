/*
 * main.c
 *
 *  Created on: 24 июл. 2023 г.
 *      Author: serviceman
 */



#include <stdio.h>
#include <math.h>

#include <sinusFuncs.h>

//
int main( void ) {
	double radians[] = {
		0,
		M_PI / 6,
		M_PI / 4,
		M_PI / 3,
		M_PI / 2
	};

	for (int i = 0; i < sizeof(radians) / sizeof(radians[0]); i++) {
		printf("%d \n", i);
		printf("%.9f \n", sin(radians[i]));
		printf("%.9f \n", Sinus_25(radians[i]));
		printf("%.9f \n", Sinus_with_acc_eps(radians[i]));
		printf("%.9f \n\n", Sinus_with_reduced_expr(radians[i]));
	}

	return 0;
}












#include <stdint.h>
#include <stdlib.h>
#include <sinusFuncs.h>
#include <math.h>

static double Factorial(uint32_t num)
{
    if (num <= 1)
    {
        return 1;
    }
    return num * Factorial(num - 1);
}

static double Power(double num, int pow)
{
    if (pow == 0)
    {
        return 1;
    }
    return num * Power(num, pow - 1);
}

double Sin_Rec(double x, int n, double precision)
{
    double res = Power(-1, n) * Power(x, 2 * n + 1) / Factorial((uint32_t)(2 * n + 1));
    if (abs(res) < precision)
    {
        return res;
    }

    return res + Sin_Rec(x, n + 1, precision);
}

double Sinus_25(double x) {
  double result = 0;
  int sign = 1;
  for(int i = 1; i < 25; i += 2) {
    result += sign * pow(x, i) / Factorial(i);
    sign = -sign;
  }
  return result;
}


// Вычисление синуса с накоплением x и коэффициента
// 	x - (x3 / 3!) + (x5 / 5!) - (x7 / 7!) + (x9 / 9!) ...
double Sinus_with_acc_eps(double rad_x) {
	double result = 0;
	int signedOne = 1; // единица для передачи знака члена
	const double pow_x2 = rad_x * rad_x; // квадрат аргумента из приведенного выражения
	double cur_factor = 1.0;	// текущее значение коэффициента при x
								//	значение выражения 1 / [факториал показателя степени x],
								//	которое накапливается с каждой итерацией
	double cur_pow_x = rad_x;	// текущее значение степени x, накапливается с каждой итерацией
	for(int i = 1; ; i += 2) {
		cur_factor /= i; // накопление коэффициента при x
		double cur_member = cur_pow_x * cur_factor;
		result += signedOne * cur_member;
		if (cur_member < SINUS_EPS) {
			break;
		} else {
			cur_factor /= ( i + 1 );
			signedOne = -signedOne;
			cur_pow_x *= pow_x2;
		}
	}
	return result;
}

double Sinus_with_acc(double rad_x) {
	double result = 0;
	int signedOne = 1; // единица для передачи знака члена
	const double x_pow_2 = rad_x * rad_x; // квадрат аргумента из приведенного выражения
	double cur_factor = 1.0;	// текущее значение коэффициента при x
								//	значение выражения 1 / [факториал показателя степени x],
								//	которое накапливается с каждой итерацией
	double cur_pow_x = rad_x;	// текущее значение степени x, накапливается с каждой итерацией
	for(int i = 1; i < 11; i += 2) {
		cur_factor /= i; // накопление коэффициента при x
		result += signedOne * cur_pow_x * cur_factor;
		cur_factor /= ( i + 1 );
		signedOne = -signedOne;
		cur_pow_x *= x_pow_2;
	}
	return result;
}

// Вычисление синуса с помощью приведенного выражения
// 	x - (x3 / 3!) + (x5 / 5!) - (x7 / 7!) + (x9 / 9!) ... =
//  	x * ( 1 + x2 * ( (-1/3!) + x2 * ( (1/5!) + x2 * ( (-1/5!) + x2 * ... [1] ) ) ) )
//      Первая итерация получения занчения начинается с [1]
double Sinus_with_reduced_expr(double x) {
	uint64_t cur_factor;
	double factors[20]; // lookup-таблица коэффициентов ряда, индекс которой - число,
						//	а значение эдемента массива - факториал индекса
						// 	для точности 1е-9 нужно иметь факториал числа 13 в знаменателе (1.6059043836821613e-10),
						//	соответственно, для работы алгоритма нужно минимум 13+1=14 ячеек
						//  Таблицу желательно оформить вне функции как глобальную часть памяти (переменную или константу)
	factors[1] = 1.0; // первый коэффициент - единица
	cur_factor = 1;
	for(int i = 2; i < sizeof(factors) / sizeof(double); i++) { // заполнить таблицу факториалов
		cur_factor *= i;
		if (i % 2 > 0) {
			factors[i] = (1.0 / cur_factor) * (( (i - 2) % 4 < 2) ? -1 : 1); // учесть знак
		} else {
			factors[i] = 0;
		}
	}
	double x_pow_2 = x * x;
	double result = factors[(sizeof(factors) / sizeof(double)) - 1]; // элемент [1]
	for(int i = (sizeof(factors) / sizeof(double)) - 3; i >= 3; i -= 2) {
		result = factors[i] + x_pow_2 * result;
	}
	return x + x * x_pow_2 * result;
}




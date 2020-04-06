#include <stdio.h>
#include <math.h>

int main(){
  float x, y, e = exp(1.0);
  typedef enum {
		UNKNOWN, OTREZOK_1, OTREZOK_2, OTREZOK_3, OTREZOK_4
  } TOtrezok;
  TOtrezok otrezok = UNKNOWN;
  printf("\n Лабораторная работа №2 вариант №11");
  printf("\n\n Выполнил студент гр. ИСТбд-12 Ильмурзин П.А. \n");
  printf("\n Вычисление составной функции вида:\n\
1> y = 3 * cos(2x) + 4 * sin(10x) при    -1 <= x < -0.05\n\
2> y = e^x                        при -0.05 <= x < 1\n\
3> y = ln(x) + x^e + 1.7          при     1 <= x < 2.05\n\
4> y = 13.8 + 5 * (x - 3)^3       при  2.05 <= x <= 3\n\
\n указать отрезок, где находится аргумент \n\
 и вывести значение функции в данной точке.\n");
  printf("\n Введите значение x: ");
  scanf("%f", &x);

  if(x < -1 || x > 3) {
    printf("\n Не входит в заданные участки.\n");
    return 0;
  }
  if(x >= -1 && x < -0.05){ printf("\n Первый отрезок (-1 <= x < -0.05); \n"); otrezok = OTREZOK_1; }
  if(x >= -0.05 && x < 1){ printf("\n Второй отрезок (-0.05 <= x < 1); \n"); otrezok = OTREZOK_2; }
  if(x >= 1 && x < 2.05){ printf("\n Третий отрезок (1 <= x < 2.05); \n"); otrezok = OTREZOK_3; }
  if(x >= 2.05 && x <= 3){ printf("\n Четвёртый отрезок (2.05 <= x <= 3); \n"); otrezok = OTREZOK_4; }

  switch(otrezok){
  case OTREZOK_1: y = 3*cos(2*x)+4*sin(10*x); break;
  case OTREZOK_2: y = pow(e,x); break;
  case OTREZOK_3: y = log(x)+pow(x,e)+1.7; break;
  case OTREZOK_4: y = 13.8 + 5 * pow(x-3, 3); break;
  }

  printf("\n Значение функции: "); printf("%f\n", y);
	 
  return 0;
}

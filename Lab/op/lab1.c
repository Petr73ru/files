#include <stdio.h>
#include <math.h>

int main(){
  float x1, y1, x2, y2, x3, y3, AB, BC, CA, cosB, sinB, R;
  printf("\n Лабораторная работа №1 вариант №11");
  printf("\n\n Выполнил студент гр. ИСТбд-12 Ильмурзин П.А.\n");
  printf("\n Вычисление радиуса окружности по координатам 3-х точек.\n");
  printf("\n Введите координаты 3-х точек");
  printf("\n Введите x1 \n");
  scanf("%f", &x1);
  printf("\n Введите y1 \n");
  scanf("%f", &y1);
  printf("\n Введите x2 \n");
  scanf("%f", &x2);
  printf("\n Введите y2 \n");
  scanf("%f", &y2);
  printf("\n Введите x3 \n");
  scanf("%f", &x3);
  printf("\n Введите y3 \n");
  scanf("%f", &y3);

  AB = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  BC = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
  CA = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));

  cosB = (x1 * x2 + y1 * y2)/ (AB * BC);
  sinB = sqrt(1 - pow(cosB, 2));
  R = CA / (2 * sinB);
  
  printf("R is : ");
  printf("%f\n", R);

  return 0;
}

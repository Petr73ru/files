#include <stdio.h>
#include <math.h>

const int len = 255;
char mass[255];
char mass0[255]; // Возростающие слова
int startIndex0 = 0;
char mass1[255]; // Убывающие слова
int startIndex1 = 0;
char mass2[255]; // Прочие слова
int startIndex2 = 0;
int wordStart, wordEnd;
int status = 3; /* 0 - В порядке возростания
	           1 - В порядке убывания
	           2 - Другие
	           3 - Not set
	     */

void moveWordHelper(char targetArray[], int targetIndex){
  for(int i = wordStart; i <= wordEnd; i++){
    targetArray[targetIndex] = mass[i];
    targetIndex++;
  }
  targetArray[targetIndex] = ' ';
  targetIndex++;
}

void moveWord(){
  if(status == 0) moveWordHelper(mass0, startIndex0);
  if(status == 1) moveWordHelper(mass1, startIndex1);
  if(status == 2) moveWordHelper(mass2, startIndex2);
}

void analiseWord(){
  status = 3;
  for(int i = wordStart + 1; i <= wordEnd; i++){
    if((int)mass[i] > (int)mass[i-1] && (status == 3 || status == 0)) { status = 0; }
    if((int)mass[i] > (int)mass[i-1] && status == 1) { status = 2; }
    if((int)mass[i] < (int)mass[i-1] && (status == 3 || status == 1)) { status = 1; }
    if((int)mass[i] < (int)mass[i-1] && status == 0) { status = 2; }
    if((int)mass[i] == (int)mass[i-1]) { status = 2; }
  }
  if (status != 3) moveWord();
}

void iterate(){
  wordStart = 0;
  for(int i = 0; i < len; i++){
    if(mass[i] == ' ' || mass[i] == (char)0) {
      wordEnd = i - 1;
      analiseWord();
      wordStart = i + 1;
    }
  }
  wordEnd = len;
  analiseWord();
}

void printA(char array[], char message[]){
  printf(message);
  for(int i = 0; i < len; i++){
    printf("%c", array[i]);
  }
  printf("%c", '\n');
} 

int main(){
  printf("\n Лабораторная работа №5 вариант №11");
  printf("\n\n Выполнил студент гр. ИСТбд-12 Ильмурзин П.А.\n");
  printf("\n Обработка одномернов массивов.\n");

  printf("Введите текст: ");
  scanf("%[^\n]", &mass);
  iterate();
  printA(mass,  "Исходный массив     : ");
  printA(mass0, "Возврастающие слова : ");
  printA(mass1, "Убывающие слова     : ");
  printA(mass2, "Прочие слова        : ");

  return 0;
}


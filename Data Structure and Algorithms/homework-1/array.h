#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>
#include "patient_record.h"


/*
Name:EMRE KÖSE
Student ID:150130037
*/

struct Dizi{

int kayitsayisi;
char *dosyaadi;
FILE *dosya;
patient_record *k;
patient_record *T_ptr;
patient_record *temp;

int returnIndexFromPatientNumber(int );
int returnIndexFromBranch(char []);
int returnIndexFromPNo(int );
void sirala();   // ekleme yapildiktan sonra kullaniliyo
void sirala2(int);     // silme yapildiktan sonra kullaniliyo
void olustur();
void kapat();
void ekle(patient_record *);
int ara_brans(char []);
int ara_brans2(char []);
int ara_pNo(int);
int ara_pNo2(int);
bool kontrol_patient_number(int);
void sil(int);

void listele();


};
#endif

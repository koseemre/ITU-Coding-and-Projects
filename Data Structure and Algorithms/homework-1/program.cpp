/*
Name:EMRE KÖSE
Student ID:150130037
*/

#include <iostream>
#include <stdlib.h>
#include <iomanip>
//#include <conio.h>
#include <ctype.h>
#include <cstring>
#include <fstream>
#include "array.h"
#define NAME_LENGTH 30
#define DOCTOR_LENGTH 30
#define DIAGNOSIS_LENGTH 30
#define BRANCH_LENGTH 30

using namespace std;

typedef Dizi Veriyapisi;
Veriyapisi defter;
bool patientNumControl(int PatientNo){

double control;



control = PatientNo/1000;

if(control >= 1 && control <10 )
return true;
else
    return false;


}




void menu_yazdir();
bool islem_yap(char);


void kayit_ara_branch();
void kayit_ara_polyNo();
void kayit_ekle();
void kayit_sil();

void kayit_listele();

int main(){

defter.olustur();
string line;
char * pch;
patient_record temp;

int infoNo=1;
 ifstream fptr ("database.txt");


    while (getline(fptr,line)){
          char *a=new char[line.size()+1];
          a[line.size()]=0;
          memcpy(a,line.c_str(),line.size());
         // cout << a << endl;

     if(a[0] != ' '){
         pch = strtok (a,"\t");
  while (pch != NULL)
  {
    if(infoNo == 1){
                strcpy(temp.name,pch);
               // cout << pch<< endl;

    }

    else if(infoNo == 2)
         strcpy(temp.doctorName,pch);
    else if(infoNo == 3)
         strcpy(temp.diagnosis,pch);
    else if(infoNo == 4){
   temp.patientNumber = atoi(pch);
   // cout << temp.patientNumber << endl;
    }

    else if(infoNo == 5)    {
            temp.polyclinicNumber = atoi(pch);
         //  cout << temp.polyclinicNumber << endl;

    }
    else if(infoNo == 6)
                strcpy(temp.branchName,pch);



   // printf ("%s\n",pch);
   infoNo++;

    pch = strtok (NULL, "\t");
  }
     }
else{

             strcpy(temp.name ,         "                             ");
             strcpy(temp.doctorName ,   "                             ");
             strcpy(temp.diagnosis ,    "                             ");
             temp.patientNumber = 0;


}
infoNo =1;
  defter.ekle(&temp);
//cout << temp.branchName << " " << temp.diagnosis << temp.patientNumber << temp.polyclinicNumber << endl;
  delete [] a;

    }

defter.sirala();
fptr.close();


bool bitir = false;
char secim;
while (!bitir) {
menu_yazdir();
cin >> secim;
bitir = islem_yap(secim);
}


defter.kapat();
return EXIT_SUCCESS;

}


void menu_yazdir(){
//system("cls"); //linux'ta ekran temizleme icin system("clear"); kullaniniz
cout << endl << endl;

cout << "Choose an operation" << endl;
cout << "C: Search the data by the polyclinic number" << endl;
cout << "B: Search the data by the branch name" << endl;
cout << "I: Insert a new patient record" << endl;
cout << "R: Remove the patient record" << endl;
cout << "P: List Records" << endl;
cout << "E: Exit the program" << endl;
cout << endl;
cout << "Your selection is : ";
}


bool islem_yap(char secim){
bool sonlandir=false;
switch (secim) {
case 'B': case 'b':
    kayit_ara_branch();
break;
case 'c': case 'C':
    kayit_ara_polyNo();
break;
case 'I': case 'i':
kayit_ekle();
break;
case 'P': case 'p':
kayit_listele();
break;
case 'R': case 'r':
kayit_sil();
break;
case 'E': case 'e':
cout << "Are you sure that you want to terminate the program? (Y/N):";
cin >> secim;
if(secim=='Y' || secim=='y')
sonlandir=true;
break;
default:
cout << "Error: You have made an invalid choice" << endl;
cout << "Try again {A, E, G, S, B, C} :" ;
cin >> secim;
sonlandir = islem_yap(secim);
break;
}
return sonlandir;
}



void kayit_ara_branch(){
char brans_ad[BRANCH_LENGTH];
cout << "Please enter the name of the branch you want to search: ";
cin.ignore(1000, '\n');
cin.getline(brans_ad,BRANCH_LENGTH);
if(defter.ara_brans2(brans_ad)==0){
cout << "Record can not be found" << endl;
}
getchar();
};


void kayit_ara_polyNo(){
int polyNo;
cout << "Please enter the number of the polyclinic you want to search: ";
cin.ignore(1000, '\n');
cin >> polyNo;
if(defter.ara_pNo2(polyNo)==0){
cout << "Record can not be found" << endl;
}
getchar();
};

void kayit_ekle(){

int pNO;


patient_record yenikayit;

cout << "Please enter the information of the person you want to save ";
cout << "Name : " ;
cin.ignore(1000, '\n');
cin.getline(yenikayit.name,NAME_LENGTH);
cout << "doctorName : " ;
cin.getline(yenikayit.doctorName,NAME_LENGTH);
cout << "diagnosis : " ;
cin.getline(yenikayit.diagnosis,NAME_LENGTH);



cout << "patient number :";
cin  >> pNO;

    while(cin.fail()) {
        cout << "You did not enter integer please enter 4 digits integer: ";// integer control !!!
        cin.clear();
        cin.ignore(256,'\n');
        cin >> pNO;
    }

//while(!(patientNumControl(pNO))){               // integer 4 digit control !!!
//
//
//cout << "You did not enter integer which has 4 digits ";
//cin >> setw(4) >> pNO;
//
//}

while(!(defter.kontrol_patient_number(pNO)) || !(patientNumControl(pNO)) ){

cout << "check the patient number with these issues:  already there is a record with the same patient number or this has not 4 digits: ";
cin >> setw(4) >> pNO;


}
yenikayit.patientNumber = pNO;




cout << "polyclinic number :";
cin >> setw(2) >> yenikayit.polyclinicNumber;
cin.ignore(1000, '\n');

cout << "branchName : " ;
cin.getline(yenikayit.branchName,BRANCH_LENGTH);

//-------------------------- polyclinicNumber control
int control = defter.returnIndexFromBranch(yenikayit.branchName);


if (defter.kayitsayisi > 10 && defter.ara_brans(yenikayit.branchName) > 0 && (defter.kayitsayisi - control) > 10 &&strcmp(defter.k[control].branchName,defter.k[control+10].branchName) == 0) // o bransin birden fazla polyclinic i aciksa
{


int p1,p2;


p1 = defter.k[control].polyclinicNumber;
p2 = defter.k[control+10].polyclinicNumber;
cout << "p1:"<<p1 <<" p2:" << p2 <<endl;
while(p1 != yenikayit.polyclinicNumber && p2 != yenikayit.polyclinicNumber){

cout << "you can not enter more than 2 different polyclinicNumber on a branch"<< endl;
cout << "polyclinicNumber(you can enter( "<< p1<<" or "<<  p2 <<" ): ";
cin >> setw(2) >> yenikayit.polyclinicNumber;


}
if( yenikayit.polyclinicNumber == p1){

int num=defter.ara_pNo(p1);
cout <<"NUM:" << num << endl;
if(num < 10 ){
    defter.ekle(&yenikayit);
    cout << "record is added" << endl;

}
else
    cout << "this polyclinicNumber is full"<<endl;
}
else{

int num2=defter.ara_pNo(p2);
cout <<"NUM2:" << num2 << endl;
if(num2 < 10 ){
    defter.ekle(&yenikayit);
    cout << "added"<<endl;

}
    else
    cout << "this polyclinicNumber is full"<<endl;
}


}
else if(defter.ara_brans(yenikayit.branchName) == 0 && defter.ara_pNo(yenikayit.polyclinicNumber)>0 ) // 1 polyclinic sadece 1 brans control
{

while(defter.ara_pNo(yenikayit.polyclinicNumber)>0){
    cout << "This polyclinic Number already has branchName different from " << yenikayit.branchName << endl;
    cout << "Please enter different polyclinic Number which you entered before: ";
    cin >> setw(2) >> yenikayit.polyclinicNumber;
}
defter.ekle(&yenikayit);
}
else{

defter.ekle(&yenikayit);
//cout << "Record has been added" << endl;

}


defter.sirala();
getchar();
};


void kayit_sil(){
int pNO;

cout << "enter the patient number which you wanna delete:";
cin  >> pNO;

    while(cin.fail()) {
        cout << "You did not enter integer please enter 4 digits integer: ";// integer control !!!
        cin.clear();
        cin.ignore(256,'\n');
        cin >> pNO;
    }

while(!(patientNumControl(pNO))){               // integer 4 digit control !!!


cout << "You did not enter integer which has 4 digits ";
cin >> setw(4) >> pNO;

}

defter.sil(pNO);

getchar();
};





void kayit_listele(){
defter.listele();
getchar();
}

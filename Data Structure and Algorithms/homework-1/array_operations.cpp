/*
Name:EMRE KÖSE
Student ID:150130037
*/

#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "array.h"
#include <fstream>
using namespace std;



//--------------------------------------------------------------------------------------------------------------
void Dizi::ekle(patient_record *ykptr){


    if(ara_pNo(ykptr->polyclinicNumber) < 10 ){
        if(ara_brans(ykptr->branchName) == 0 )  {                //o brans icin ilk kayit

            if(kayitsayisi>0){
            temp = new patient_record[kayitsayisi] ;


            for(int i=0;i<kayitsayisi;i++)
            *(temp+i) = *(k+i);


            k = new patient_record[kayitsayisi+10];
            for(int i=0;i<kayitsayisi;i++)
            *(k+i) =  *(temp+i);
            delete [] temp;
}
else
        k = new patient_record[10];

        k[kayitsayisi].order = kayitsayisi;
        int sira = k[kayitsayisi].order ;

        strcpy(k[sira].branchName,ykptr->branchName);
        strcpy(k[sira].diagnosis,ykptr->diagnosis);
        strcpy(k[sira].name,ykptr->name);
        strcpy(k[sira].doctorName,ykptr->doctorName);
        k[sira].patientNumber = ykptr->patientNumber;
        k[sira].polyclinicNumber = ykptr->polyclinicNumber;
                                                        //sira olarak basladigi yer


        kayitsayisi = kayitsayisi + 10;
         for(int i = sira+1 ; i<kayitsayisi;i++  ){
            strcpy(k[i].branchName , k[sira].branchName);
            strcpy(k[i].name ,        "                             ");
            strcpy(k[i].doctorName ,  "                             ");
            strcpy(k[i].diagnosis ,   "                             ");
            k[i].polyclinicNumber = k[sira].polyclinicNumber;
            k[i].patientNumber = 0;
         }




        }
else{

        if(ara_pNo(ykptr->polyclinicNumber) == 0)  {  //ayni branch var ama ayni polyclinic den yok bi onluk daha lazim


        temp = new patient_record[kayitsayisi];

        for(int i=0;i<kayitsayisi;i++)
        *(temp+i) = *(k+i);


        k = new patient_record[kayitsayisi+10];
        for(int i=0;i<kayitsayisi;i++)
         *(k+i) =  *(temp+i);

          delete [] temp;



        k[kayitsayisi].order = kayitsayisi;
        int sira2 = kayitsayisi;

        strcpy(k[sira2].branchName,ykptr->branchName);
        strcpy(k[sira2].name,ykptr->name);
        strcpy(k[sira2].diagnosis,ykptr->diagnosis);
        strcpy(k[sira2].doctorName,ykptr->doctorName);
        k[sira2].patientNumber = ykptr->patientNumber;
        k[sira2].polyclinicNumber = ykptr->polyclinicNumber;


        kayitsayisi = kayitsayisi + 10;
     for(int i = sira2+1 ; i<kayitsayisi;i++  ){
             strcpy(k[i].branchName , k[sira2].branchName);
             strcpy(k[i].name ,         "                             ");
             strcpy(k[i].doctorName ,   "                             ");
             strcpy(k[i].diagnosis ,    "                             ");
             k[i].polyclinicNumber = k[sira2].polyclinicNumber;
             k[i].patientNumber = 0;
         }



        }
        else{   //ayni brans ve ayný poly no

        int findOrder;
        int m;
        for(m =0 ; m< kayitsayisi ; m++){
                if(k[m].polyclinicNumber == ykptr->polyclinicNumber)
                break;
                   // findOrder = k[i].order;


        }
        findOrder = m;

    int findBlankOrder;


      for(m=findOrder; m<(findOrder+10); m++)
        if(strcmp(k[m].name,"                             ") == 0 )
        break;
            findBlankOrder = m;






        strcpy(k[findBlankOrder].branchName,ykptr->branchName);
        strcpy(k[findBlankOrder].name,ykptr->name);
        strcpy(k[findBlankOrder].doctorName,ykptr->doctorName);
        strcpy(k[findBlankOrder].diagnosis,ykptr->diagnosis);

        k[findBlankOrder].patientNumber = ykptr->patientNumber;
        k[findBlankOrder].polyclinicNumber = ykptr->polyclinicNumber;


        }

        }

}
else
{
    cout << "this polyclinic is full" << endl;
}
}

//--------------------------------------------------------------------------------------------------------------
void Dizi::sirala(){
patient_record temp;
T_ptr = k;


//ikiden fazla kayit varsa(branch cinsinde) alfabetik sirala
if(kayitsayisi >= 20 ){
    for(int i=1;i<kayitsayisi;i++)
        for(int j=0;j<kayitsayisi-i;j++)

    {
        if( strcmp((T_ptr+j)->branchName,(T_ptr+j+1)->branchName)>0  )
             {
                       temp = *(T_ptr+j);
                       *(T_ptr+j) = *(T_ptr+j+1);
                       *(T_ptr+j+1) = temp;
             }
    }

}

if(kayitsayisi >= 20 ){
    for(int i=1;i<kayitsayisi;i++)
        for(int j=0;j<kayitsayisi-i;j++)

    {
        if( ((T_ptr+j)->polyclinicNumber > (T_ptr+j+1)->polyclinicNumber )  &&   strcmp((T_ptr+j)->branchName,(T_ptr+j+1)->branchName)>0 )
             {
                       temp = *(T_ptr+j);
                       *(T_ptr+j) = *(T_ptr+j+1);
                       *(T_ptr+j+1) = temp;
             }

    }
}

}

//--------------------------------------------------------------------------------------------------------------
void Dizi::olustur(){

kayitsayisi=0;

}

//--------------------------------------------------------------------------------------------------------------

void Dizi::kapat(){


dosya = fopen("database.txt","w+");   //dosyayi sil
fclose(dosya);

ofstream myfile;
  myfile.open ("database.txt");



for(int i=0;i<kayitsayisi;i++){

if(k[i].patientNumber == 0)
    myfile << " "<<'\n';
    else
myfile <<k[i].name<<'\t'<<k[i].doctorName<<'\t'<<k[i].diagnosis<<'\t'<<k[i].patientNumber<<'\t'<<k[i].polyclinicNumber<<'\t'<<k[i].branchName<<'\n';


}
myfile.close();


}
//--------------------------------------------------------------------------------------------------------------
int Dizi::ara_brans(char aranacak[]){
    int sayac=0;

    if(kayitsayisi > 0){// used in functions so there is no cout<<
    for(int i=0;i<kayitsayisi;i++){
    if(strcmp(k[i].branchName,aranacak)==0&& k[i].patientNumber !=0 )
    sayac++;
    }
    return sayac;
    }
        else
        return sayac;
}

//--------------------------------------------------------------------------------------------------------------

int Dizi::ara_brans2(char aranacak[]){
int sayac=0;
unsigned int y;


if(kayitsayisi > 0){  // used in searching so there is  cout<<
for(int i=0;i<kayitsayisi;i++){
if((strcmp(k[i].branchName,aranacak)==0) && k[i].patientNumber !=0)
{
cout<<sayac+1<<". "<<k[i].name;
for(y=0 ; y< 30- strlen(k[i].name) ; y++)
    cout << " ";

cout<<k[i].doctorName;
for(y=0 ; y< 30- strlen(k[i].doctorName) ; y++)
    cout << " ";

cout<<k[i].diagnosis;
 for(y=0 ; y< 30- strlen(k[i].diagnosis) ; y++)
    cout << " ";

cout<<k[i].patientNumber<<"\t" <<k[i].polyclinicNumber<<"\t"<<
k[i].branchName<<endl;

sayac++;

}
}
return sayac;}
else
    return sayac;
}

//--------------------------------------------------------------------------------------------------------------

int Dizi::ara_pNo(int p){ // used in functions so there is no cout<<
int sayac=0;


if(kayitsayisi > 0){
for(int i=0;i<kayitsayisi;i++){
if(  p == k[i].polyclinicNumber && k[i].patientNumber !=0)
sayac++;

}
return sayac;
}
else
    return sayac;

}
//--------------------------------------------------------------------------------------------------------------
int Dizi::ara_pNo2(int p){
int sayac=0;
unsigned int y;

if(kayitsayisi > 0)
for(int i=0;i<kayitsayisi;i++){
if(k[i].polyclinicNumber == p && k[i].patientNumber !=0)
{

cout<<sayac+1<<". "<<k[i].name;
for(y=0 ; y< 30- strlen(k[i].name) ; y++)
    cout << " ";

cout<<k[i].doctorName;
for(y=0 ; y< 30- strlen(k[i].doctorName) ; y++)
    cout << " ";

cout<<k[i].diagnosis;
 for(y=0 ; y< 30- strlen(k[i].diagnosis) ; y++)
    cout << " ";

cout<<k[i].patientNumber<<"\t" <<k[i].polyclinicNumber<<"\t"<<
k[i].branchName<<endl;
sayac++;

}
}
return sayac;
}

//--------------------------------------------------------------------------------------------------------------
int Dizi::returnIndexFromPNo(int p){

int l;
for( l=0;l<kayitsayisi;l++)
        if((k+l)->polyclinicNumber == p )
        break;



        return l;


}
//--------------------------------------------------------------------------------------------------------------

int Dizi::returnIndexFromBranch(char aranacak[]){

int m;
for( m=0;m<kayitsayisi;m++)
        if(strcmp((k+m)->branchName , aranacak) ==0 )
        break;


        cout<<  "m:" << m <<endl;
        return m;


}
//--------------------------------------------------------------------------------------------------------------
int Dizi::returnIndexFromPatientNumber(int PatientNo){


int returnPNo=-1;
int p;

for(p=0;p<kayitsayisi;p++)
        if( PatientNo == k[p].patientNumber )
            break;

        returnPNo = p;



        return returnPNo;


}
//--------------------------------------------------------------------------------------------------------------
void Dizi::sil(int patientNo){

int hold = returnIndexFromPatientNumber(patientNo);
int j=0;
if(hold == -1)
{
    cout << "there is no record " << endl;
}
else if(ara_pNo(k[hold].polyclinicNumber) == 1 )  // son kayit i silmek isterse o 10 luk u yok et
{
temp = new patient_record[kayitsayisi-10];
for (int i=0;i<kayitsayisi;i++){
if(i>=hold && i<hold+10)
    continue;
else{
   *(temp+j) =  *(k+i);
    j++;
}

}
kayitsayisi = kayitsayisi-10;

k = new patient_record[kayitsayisi];
for(int i=0; i<kayitsayisi;i++)
    *(k+i) = *(temp+i);

cout << "removed "<< endl;
}
else if(ara_pNo(k[hold].polyclinicNumber) > 1)
{

            strcpy(k[hold].name ,         "                             ");
             strcpy(k[hold].doctorName ,   "                             ");
             strcpy(k[hold].diagnosis ,    "                             ");
             k[hold].patientNumber = 0;
             sirala2(hold);
            cout << "removed "<< endl;
}




}
//--------------------------------------------------------------------------------------------------------------
void Dizi::sirala2(int in){   // sildikten sonra kullanildi

patient_record temp;
T_ptr = k;


int inStart = ((int)(in/10));
inStart = inStart * 10;
cout << "ins:"<<inStart << endl;

    for(int i=1;i<10;i++)
        for(int j=inStart;j<inStart+10-i;j++)

    {
        if( strcmp((T_ptr+j)->name,(T_ptr+j+1)->name) < 0    )
             {
                       temp = *(T_ptr+j);
                       *(T_ptr+j) = *(T_ptr+j+1);
                       *(T_ptr+j+1) = temp;
             }


    }

}


//--------------------------------------------------------------------------------------------------------------

void Dizi::listele(){

    unsigned int y;
    if(kayitsayisi>0){
for(int i=0;i<kayitsayisi;i++)
    if(k[i].patientNumber !=0){

        cout<<i+1<<". "<<k[i].name;
for(y=0 ; y< 30- strlen(k[i].name) ; y++)
    cout << " ";

cout<<k[i].doctorName;
for(y=0 ; y< 30- strlen(k[i].doctorName) ; y++)
    cout << " ";

cout<<k[i].diagnosis;
 for(y=0 ; y< 30- strlen(k[i].diagnosis) ; y++)
    cout << " ";

cout<<k[i].patientNumber<<"\t" <<k[i].polyclinicNumber<<"\t"<<
k[i].branchName<<endl;
    }
else
    cout <<i+1<<". " <<'\n';
}
else{cout << endl;
    cout << "There is no records in phone" << endl;}

}

//--------------------------------------------------------------------------------------------------------------

bool Dizi::kontrol_patient_number(int patNo){

bool control=true;

for (int i=0; i<kayitsayisi; i++ ){
        if(k[i].patientNumber == patNo )
           control = false;


}
            return control;
}

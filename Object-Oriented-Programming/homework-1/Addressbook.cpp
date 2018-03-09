#include <iostream>
#include <string.h>
#include "Instructor.h"
#include "InstructorList.h"

/*#ifndef INSTRUCTORLIST_H
#define INSTRUCTOSRLIST_H
#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H */
using namespace std;

    string temp_title;                  // temp members of the class Instructor for to get inputs and run methods
    string temp_firstName;
    string temp_lastName;
    string temp_telNumber;
    string temp_roomNumber;
    string temp_userName;
    string temp_email;
    string temp_courses;

class Adressbook {

public:
    instructorList *il_ptr;

    Adressbook(){                       //Constructor of the class Adressbook .it generates 5 constructor for first capacity
    il_ptr = new instructorList(5);
    }
    instructorList *temp_ptr;            // temp_ptr is used for delete operation


    void addOperation();
    void printOperation();
    void deleteOperation();
    void searchByName();
    void searchBySurname();
    void searchByTel();
    void searchByRoom();
    void selectOperation();


};
void Adressbook::deleteOperation(){
string a,b;
int c;
int x;
cout << "Enter the first name of the record to be deleted: " ;
cin >> a;
cout << "Enter the last name of the record to be deleted: " ;
cin >> b;
  c = Adressbook::il_ptr->findtoDelete(a,b) ;
 // cout <<"location to delete: " <<c << endl;
  //cout << " curCap : "<<Adressbook::il_ptr->curCap<<endl;

if(c == -1)
    cout << "record can not be found" <<endl;
else{
    Adressbook::temp_ptr = new instructorList((Adressbook::il_ptr->curCap)-1);
    for(int i =0 ;i<Adressbook::il_ptr->curCap ;i++)
    {
        if(i != c )
        temp_ptr->i_ptr[i] = il_ptr->i_ptr[i];
        else{
        for( ;i<Adressbook::il_ptr->curCap-1;i++)
        temp_ptr->i_ptr[i] = il_ptr->i_ptr[i+1];
        x = i+1;
        }
        if( x == il_ptr->curCap-1)
            break;

    }

    Adressbook::il_ptr->curCap--;
    int hold = Adressbook::il_ptr->curCap;


    il_ptr = new instructorList(hold);

    for(int j= 0;j<hold;j++){
 il_ptr->i_ptr[j] = temp_ptr->i_ptr[j];
 Adressbook::il_ptr->curCap++;
// cout << "cur "<<Adressbook::il_ptr->curCap <<endl;
// cout <<"max "<<Adressbook::il_ptr->maxCap<<endl;


    }
    if(Adressbook::il_ptr->maxCap == Adressbook::il_ptr->curCap)
     {
      Adressbook::il_ptr->full=true;

 }
        temp_ptr->~instructorList();
        cout << " Record has been deleted!" <<endl;

}

}

// Search Operations
void Adressbook::searchByName(){
string m;
cout << "enter the name to search : " ;
cin >> m;
 Adressbook::il_ptr->searchName(m);

}

void Adressbook::searchBySurname(){
 string n;
cout << "enter the surname to search : " ;
cin >> n;
 Adressbook::il_ptr->searchSurname(n);
}
void Adressbook::searchByTel(){
string x;
cout << "enter the tel number to search : " ;
cin >> x;
 Adressbook::il_ptr->searchTel(x);

}
void Adressbook::searchByRoom(){
string x;
cout << "enter the room number to search : " ;
cin >> x;
 Adressbook::il_ptr->searchRoom(x);

}




//PRINT OPERATION
void Adressbook::printOperation(){
    if(Adressbook::il_ptr->curCap == 0)
    return;
    else
    Adressbook::il_ptr->printAll();
}


// ADD OPERATION
void Adressbook::addOperation(){

cout << "Enter the title: ";
cin >> temp_title;

cout << "Enter the First Name: ";
cin >> temp_firstName;


cout << "Enter the Last Name: ";
cin >> temp_lastName;

if(Adressbook::il_ptr->curCap != 0)
    if(Adressbook::il_ptr->findtoDelete(temp_firstName,temp_lastName) >= 0)
    {
        cout << "there is already record named of " << temp_firstName << "  " << temp_lastName << endl;
        return;
    }

cout << "Enter the Telephone Number: ";
cin >> temp_telNumber;

cout << "Enter the Room Number: ";
cin >> temp_roomNumber;

cout << "Enter the User Name: ";
cin >> temp_userName;

cout << "Enter the email: ";
cin >> temp_email;

cout << "Enter the course: ";
cin >> temp_courses;


instructor a(temp_title,temp_firstName, temp_lastName, temp_telNumber,temp_roomNumber,temp_userName,temp_email,temp_courses);


if (Adressbook::il_ptr->curCap==0){
  Adressbook::il_ptr= new instructorList(1);
  Adressbook::il_ptr->addInstructor(a);
}
else if(Adressbook::il_ptr->full == true)
{
    int holdCurCap;

    Adressbook::temp_ptr = new instructorList(Adressbook::il_ptr->curCap);

     for(int j=0; j < il_ptr->curCap; j++ ){
      temp_ptr->i_ptr[j] =  il_ptr->i_ptr[j];
      cout << "curCap is " << il_ptr->curCap << " now" << endl;
      }

        holdCurCap=Adressbook::il_ptr->curCap;    // holdCurCap hold the current capacity because capacity will be zero after then .
                                                    // And holdCurCap will provide to not change of the curCap after new allocation
        Adressbook::il_ptr = new instructorList(2*(Adressbook::il_ptr->curCap));


     Adressbook::il_ptr->curCap = holdCurCap;
    for(int j=0;j<il_ptr->curCap;j++ )
        il_ptr->i_ptr[j] = temp_ptr->i_ptr[j];

Adressbook::temp_ptr->~instructorList();
    Adressbook::il_ptr->addInstructor(a);

    }

    else
    {
        Adressbook::il_ptr->addInstructor(a);
        cout << " record is added"<<endl;
    }

//cout <<"curcap: " <<Adressbook::il_ptr->curCap <<endl;

}

void Adressbook::selectOperation(){
    char operation;
    cout <<"1. Add a new instructor" <<endl;
    cout <<"2. Delete an instructor"<<endl;
    cout <<"3. List all instructors"<<endl;
    cout <<"4. Search by Name"<<endl;
    cout <<"5. Search by Surname"<<endl;
    cout <<"6. Search by Telephone Number"<<endl;
    cout <<"7. Search by Room Number"<<endl;
    cout <<"8. Exit"<<endl;
    cout << "Enter the number for operation you want to perform: ";
    cin >> operation;

    if(operation != '8')
    while(operation != '8'){
   switch(operation)
   {
   case '1' :
    Adressbook::addOperation();
cout << "case 1 end"<<endl;
      break;

   case '2' :
    Adressbook::deleteOperation();
    break;

   case '3' :
Adressbook::printOperation();
      break;
   case '4' :
      Adressbook::searchByName();
      break;
   case '5' :
      Adressbook::searchBySurname();
      break;
   case '6' :
      Adressbook::searchByTel();
      break;
   case '7' :
      Adressbook::searchByRoom();
      break;
   default:
       cout << "invalid character" <<endl;
    break;

   }

    cout <<"1. Add a new instructor" <<endl;
    cout <<"2. Delete an instructor"<<endl;
    cout <<"3. List all instructors"<<endl;
    cout <<"4. Search by Name"<<endl;
    cout <<"5. Search by Surname"<<endl;
    cout <<"6. Search by Telephone Number"<<endl;
    cout <<"7. Search by Room Number"<<endl;
    cout <<"8. Exit"<<endl;
    cout << "Enter the number for operation you want to perform: ";
    cin >> operation;

}

}
int main()
{

    Adressbook a;

    instructor a1("Doc. Dr.","Turgay","Altilar","02122853587","5109","altilar@itu.edu.tr","altilar","BIL105 B");
    instructor a2("Yrd.Doc.Dr.","Yusuf","Yaslan","02122856703","5309","yyaslan@itu.edu.tr","yyaslan","BLG202 b");
    instructor a3("Doc.Dr.","Mustafa","Kamasak","02122853593","3309","kamasak@itu.edu.tr","kamasak","BLG231 b");
    a.il_ptr->addInstructor(a1);
    a.il_ptr->addInstructor(a2);
    a.il_ptr->addInstructor(a3);

    a.selectOperation();


    return 0;
}
//#endif
//#endif

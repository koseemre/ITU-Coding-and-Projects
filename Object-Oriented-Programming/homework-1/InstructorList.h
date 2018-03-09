#include <iostream>
#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include <string.h>

using namespace std;

class instructorList{
friend class Adressbook;
instructor *i_ptr;
const int maxCap;
bool full;
int curCap;

public:
    instructorList(int);
    instructorList(int, const instructor*, int);
    instructorList(const instructorList&);
    bool addInstructor(instructor&);
    bool deleteInstructor(int);
    void searchName(const string ) const;                                  //search functions
    void searchSurname(const string ) const;
    void searchTel(const string) const;
    void searchRoom(const string) const;
    void printAll() const;
    int findtoDelete(const string,const string) const;                          // finds the instructor's place in array
    ~instructorList();                                                          // destructor
};



int instructorList::findtoDelete(std::string n_f,std::string s_f) const {

for(int i=0;i<curCap;i++)
    if( i_ptr[i].getfirstName().compare(n_f) == 0 && i_ptr[i].getlastName().compare(s_f) == 0 )
        return i;                                           //if there is record about searched name it return it's index

    return -1;

}


void instructorList::searchName(std::string n) const {
  int f=0;
for(int i=0;i<curCap;i++){
    if( i_ptr[i].getfirstName().compare(n) == 0  )
    {
        i_ptr[i].print();
        f++;
    }
}
if(f == 0)
    cout << "there is no record about" << n <<endl;

}

void instructorList::searchSurname(std::string m) const{
 int a=0;
for(int i=0;i<curCap;i++){
    if( i_ptr[i].getlastName().compare(m) == 0  )
    {
        i_ptr[i].print();
        a++;
    }
}
if(a == 0)
    cout << "there is no record about " << m <<endl;

}

void instructorList::searchTel(std::string b) const{
int a=0;
for(int i=0;i<curCap;i++){
    if( i_ptr[i].gettelNumber().compare(b) == 0  )
    {
        i_ptr[i].print();
        a++;
    }
}
if(a == 0)
    cout << "there is no record about tel number -> " << b <<endl;

}
void instructorList::searchRoom(std::string c) const{
int a=0;
for(int i=0;i<curCap;i++){
    if( i_ptr[i].getroomNumber().compare(c)== 0  )
    {
        i_ptr[i].print();
        a++;
    }
}
if(a == 0)
    cout << "there is no record about room number -> " << c <<endl;
}

// constructor and add function are partially taken from midterm exam and modified according to the program


instructorList::instructorList(int m_capacity): maxCap(m_capacity){
    curCap = 0;
    full = false;
    i_ptr = new instructor[m_capacity];
    }



instructorList::~instructorList(){
    delete[] i_ptr;
               }

instructorList::instructorList(const instructorList& in_i):maxCap(in_i.maxCap){
curCap = in_i.curCap;
full = in_i.full;
i_ptr = new instructor[in_i.maxCap];
for(int i=0;i<maxCap;i++)
i_ptr[i]=in_i.i_ptr[i];
}

bool instructorList::addInstructor(instructor& in_i){
     if(full)
        return false;
     i_ptr[curCap] = in_i;
     curCap++;
     if(curCap == maxCap)
        full = true;
     return true;
     }

bool instructorList::deleteInstructor(int a){
     if(full)
        full = false;

     curCap--;

     return true;
     }


void instructorList::printAll() const
         {

             cout << "----------List of all Instructors in Computer Engineering of ITU----------" << endl;
             cout << endl;
             for(int i = 0; i < curCap; i++)
             {

                i_ptr[i].print();
                cout << "---------------------------------------" << endl;

             }

             }
#endif

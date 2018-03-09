//NOTE!!!: you should compile with main.cpp which i sent because I could not all of the functions
/*
* @Author
* Student Name: !! Emre KÖSE!!
* Student ID : !! 150130037 !!
* Date:08.02.2016
*/
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
class Book{
    public:

string label;
float length,weight,width;

Book(){} // default
Book(string lbl,float wght,float lngth,float wdth){
label = lbl;
length = lngth;
weight = wght;
width =wdth ;


}


};
ostream& operator <<(ostream& out, const Book &z)  // Overloading <<
{
	out  <<"Book Label: "<<z.label<<"# "<<z.length<<"x"<<z.width<<"  "<<z.weight<<"  ";


   return out;
}

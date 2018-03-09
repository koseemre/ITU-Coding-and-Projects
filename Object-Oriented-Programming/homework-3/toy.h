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

class Toy{
public:
bool battery;
string label;
float length,weight,width;

Toy(){

length = 0;
weight = 0;
width =0 ;

} // default
Toy(string lbl,float wght,float lngth,float wdth,bool Bttry ){
label = lbl;
length = lngth;
weight = wght;
width =wdth ;
battery = Bttry;


}
void setContainsBattery(bool var){

	battery = var;
}

float getWidth(){
return width;
}

float getWeight(){
return weight;
}

float getLength(){
return length;
}



};
ostream& operator <<(ostream& out, const Toy &z)  // Overloading <<
{
	out  <<"Toy Label: "<<z.label<<"# "<<z.length<<"x"<<z.width<<"  "<<z.weight<<"  ";
        if (z.battery)
    cout<<"with Battery"<<endl;
    else
    cout<<"No Battery"<<endl;

   return out;
}

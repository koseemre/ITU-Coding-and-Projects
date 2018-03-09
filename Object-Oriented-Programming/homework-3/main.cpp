//NOTE!!!: you should compile with main.cpp which i sent because I could not all of the functions
/*
* @Author
* Student Name: !! Emre KÖSE!!
* Student ID : !! 150130037 !!
* Date:08.02.2016
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include <iostream>
#include "box.h"
#include "box.cpp"
#include "toy.h"
#include <algorithm>
#include "book.h"
using namespace std;
int main() {

  //Toy Constructor: label, weight, length, width, containsBattery
    Toy toy1("Lego: Heroes Batman",1.2,0.2,0.3,false);



    //Box Constructor: weight, length, width, maximumAllowedWeight
    Box<Toy> toyBox(0.1,1.0,1.0,7.0);


    try {
        toyBox.add(toy1);
        cout << toyBox[0]<< endl;

        // trying to get the element at(1)
        // should give an error
        cout << toyBox[1] << endl;
    } catch (const string & err_msg) {
        cout <<"### ERROR ### "<< err_msg << endl;          //DONE
    }

    Toy toy2("Lego: Star Wars Death Star",1.7,0.5,0.3,false);
    toyBox.add(toy2);
    cout<<endl<<toyBox<<endl;

    Toy *toyArray= new Toy[2];
    toyArray[0]=  Toy("Hot Wheels: Turbine Twister Track Set",1.4,0.3,0.3,false);
    toyArray[1]=  Toy("Lego: Heroes Superman",1.6,0.3,0.3,false);

    Box<Toy> toyBox2=toyBox;            //DONE

	toyBox2.add(toyArray,2);
	 cout<<endl<<toyBox2<<endl;

    delete [] toyArray;

    try {
        Toy toy3("Lego: Heroes Superman",1.0,0.7,1.1,false);
        // trying to add a toy bigger than the box
        // should give an error
        toyBox.add(toy3);
    } catch (const string & err_msg) {
        cout <<"### ERROR ### "<< err_msg << endl;
    }
    try {
        Toy toy3("Hot Wheels: Speedtropolis Playset",6,0.7,0.8,false);
        // trying to add a toy heavier than the box's remaining available weight
        // should give an error
        toyBox.add(toy3);
    } catch (const string & err_msg) {
        cout <<"### ERROR ### "<< err_msg << endl;
    }
    cout<<endl<<toyBox<<endl;
	toyBox[1].setContainsBattery(true);


   // Box<Box<Toy> > multipleBoxes(1,1,1,20);       //multiple boxes cannot be done
   // multipleBoxes.add(toyBox);
//    multipleBoxes.add(toyBox2);

//    cout<<endl<< multipleBoxes <<endl;


//Book Constructor: label, weight, length, width
    Book book("Terry Pratchett: The Colour of Magic",0.2,0.4,0.2);          //OK
    Box<Book> bookBox(0.05,0.2,0.4,2);
    bookBox.add(book);

    cout<<bookBox<<endl;
    return 0;

}

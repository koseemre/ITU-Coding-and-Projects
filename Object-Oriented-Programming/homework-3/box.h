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
#include <algorithm>

using namespace std;


template <class data_type>
class Box{

 int numOfGoods;
 float length,weight,width;
 float currentWeight,maxWeight;
public:

     class Node {
public:

    data_type data;
    Node* previous;
    Node* next;
    Node() : previous(NULL), next(NULL) {}

   void operator=(data_type a){

        this->data.label = a.label;
        this->data.length = a.length;
         this->data.weight = a.weight;
        this->data.width = a.width;
        this->data.battery = a.battery;


}

};
     Node* head;


Box(float a,float b,float c,float d) {
    a = length;
    b = weight;
    c = width;
    d = maxWeight;

    currentWeight=0.0;
    numOfGoods = 0;
    head = new Node;
    head->previous = head;
    head->next = NULL;
}



Box(){
 length =0;
     weight=0;
     width=0;
     maxWeight=0;

}
Box(Box<data_type> &objectIn) {
     length = objectIn.length;
    weight = objectIn.weight;
    width = objectIn.width;
    maxWeight= objectIn.maxWeight;

    currentWeight=0.0;
    numOfGoods = 0;

    head = new Node;
    head->previous = head;
    head->next = NULL;
    for (int i = 1; i <= objectIn.numOfGoods; i++) {
        this->add(objectIn.GetObject(i));
    }
}
data_type GetObject(unsigned int item_number) {
    Node* cur = head;
    for (unsigned i = 1; i < item_number; i++) {
        cur = cur->next;
    }
    return cur->next->data;
}

void add(data_type *objectIn,int addObj){


for(int i=0;i<addObj;i++){
    Node *temp = new Node;
    temp->data = *objectIn;
    this->add(temp->data);
    objectIn++;
}
/*
data_type* GetItemRef(unsigned int item_number) {
    Node* cur = head->next;
    for (int i = 1; i < item_number; i++) {
        cur = cur->next;
    }
    return &(cur->data);
}*/


}

int getNumOfGoods(){
return numOfGoods;
}

float getMax(){
return maxWeight;
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





data_type & operator[](int index){

if (index >= numOfGoods) throw (const string) "Index out of bounds!";


 Node* temp = head->next;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->data;

}


~Box() {
    DeleteAll();
    delete head;
    head = NULL;
    currentWeight = 0;
    numOfGoods =0;
}


void add(const data_type &dataNew) { //NOTE!!! : I wrote the codes of exceptions for dimension and weight ,but it gives error and i want to  evaluated of these two lines.


//EXCEPTIONS FOR WEIGHT AND DIMENSION LIMIT
  // if ( (data.width>=length  && data.width>=width)|| (data.length>=length && data.length>=width)  ) throw  (const string) "The dimensions of the contained object should be equal or smaller than those of the box!";

   //if(currentWeight+dataNew.weight >= maxWeight) throw (const string ) "The total weight of the contained objects including the box may not exceed the maximum allowed weight for the box!";


    Node *temp2 = head;
    while(temp2->next){
        temp2=temp2->next;
    }

    Node* newnode = temp2->next = new Node;
    newnode->previous = temp2;
    newnode->data = dataNew;

    numOfGoods++;

    currentWeight = currentWeight + dataNew.weight;

}




void DeleteAll() {
     Node *temp3 = head;
    while(temp3->next){
        temp3=temp3->next;
    }

    Node* previous = temp3->previous;

    while (previous != head) {
        delete temp3;
        temp3 = previous;
        previous = temp3->previous;
    }
    head->next = NULL;
}

friend ostream& operator <<(ostream& out,  Box &y)  // Overloading <<
{

    out<<"***** Box *****"<<endl;
    out<<"Box item count:"<< y.getNumOfGoods()<<endl;


    out << "Items:"<<endl;
    for(int i=0;i<y.getNumOfGoods();i++){
        out<<i+1<<":"<<y[i]<<endl;
        }

  return out;
}



};



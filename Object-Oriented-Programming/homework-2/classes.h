//EMRE KÖSE - 150130037
#include <iostream>
#include <memory>
#include <string>
#define CAPACITY 30
using namespace std;



class Base{
friend class HetList;                           //it was added there owing to do 'protected' compare function
protected:
        enum result{ Lose = 0, Tie = 1, Win=2 };
        char type;                                      // type is used in compare functions
        result step;                                    // holds result in every different matches
        virtual void compare(Base *)=0;
public:

        Base(){}
        char getType() const{
        return type;}

        result getStep() const{
        return step;}


        void SetStepGeneric(result r){
            this->step=r;
        }
        ~Base(){}
};

// --------------Red Class----------------
class Red: public Base{
protected:
    void compare(Base *);

public:
    Red(){type = 'R';}

    //~Red(){}
};

 void Red::compare(Base *x){

             if(x->getType() == 'R'){
                    step = Tie;
               x->SetStepGeneric(Tie);
               }

             else if(x->getType()== 'D'){
                    step=Lose;
                  x->SetStepGeneric(Win);}

            else if(x->getType()== 'B'){
                    step=Lose;
                     x->SetStepGeneric(Win);
                       }

            else if(x->getType()== 'G'){
                                step=Win;
                     x->SetStepGeneric(Lose);}

    }

 // ---------------- dark red ------------------------------------

class DarkRed: public Red{
protected:
    void compare(Base *);
public:
    DarkRed(){
    type = 'D';}


};
void DarkRed::compare(Base *x){
            if(x->getType() == 'R'){
                    step = Win;
                    x->SetStepGeneric(Lose);}

             else if(x->getType()== 'D'){
                    step=Tie;
                  x->SetStepGeneric(Tie);}

            else if(x->getType()== 'B'){
                    step=Win;
                     x->SetStepGeneric(Lose);
                       }

            else if(x->getType()== 'G'){
                                step=Lose;
                     x->SetStepGeneric(Win);}
    }

// -------------------- Blue Class -----------------------------
class Blue: public Base{
protected:
    void compare(Base *);
public:
    Blue(){
    type = 'B';}

};

 void Blue::compare(Base *x){
              if(x->getType() == 'R'){
                    step = Win;
                    x->SetStepGeneric(Lose);}

             else if(x->getType()== 'D'){
                    step=Lose;
                  x->SetStepGeneric(Win);}

             else if(x->getType()== 'B'){
                    step=Tie;
                     x->SetStepGeneric(Tie);
                       }

             else if(x->getType()== 'G'){
                                step=Lose;
                     x->SetStepGeneric(Win);}

    }


// ------------- Green Class ----------------------------------
class Green: public Base{
protected:
    void compare(Base *);
public:
    Green(){
    type = 'G';}

};

 void Green::compare(Base *x){
           if(x->getType() == 'R'){
                    step = Lose;
                    x->SetStepGeneric(Win);}

             else if(x->getType()== 'D'){
                    step=Win;
                  x->SetStepGeneric(Lose);}

            else if(x->getType()== 'B'){
                    step=Win;
                     x->SetStepGeneric(Lose);
                       }

            else if(x->getType()== 'G'){
                                step=Tie;
                     x->SetStepGeneric(Tie);}

    }



// ------------------------- ListNode Class ---------------------------------------

class ListNode{
	friend class HetList;
	public:
    Base *element;
	ListNode * next;
	ListNode(Base *);	// constructor
};

ListNode::ListNode(Base *n)
{
	element = n;
	next = 0;
}



// Heterogeneous List of Color Objects
class HetList{
    ListNode *head;
	public:

    int results[CAPACITY];
    int sumOfScore;
    int numOfWin;
     int numOfLose;
     int numOfTie;
      int lenOfMatch;
    HetList(){
     head=0;
	 lenOfMatch = 0;
	 sumOfScore=0;
	 numOfWin  =0;
	 numOfLose =0;
	 numOfTie  =0;
	 }
	 bool insert( Base *);
	 void compList(HetList *);

	 ~HetList();
};


// Insert a new object of color
// if there is no space returns false, otherwise true
bool HetList::insert(Base *n)
{
    ListNode *tem;

	if(head)
	{
    tem = new ListNode(n);
    tem->next = head;
    head = tem;

    lenOfMatch++;
    return true;

	}
	else             // if the list is empty
	{
		head = new ListNode(n);

		lenOfMatch++;
		if (!head) {
                lenOfMatch--;
                return false;	}			// If memory is full
    }
	return true;
}

//---------COMPARE THE ALL LIST ----------------------

void HetList::compList(HetList *a){

ListNode *tempp1 = head;
ListNode *tempp2 = a->head;




for(int i=0;i<lenOfMatch;i++){

        head->element->compare(a->head->element);

        results[i]=head->element->getStep();

        a->results[i]=a->head->element->getStep();

  //count the all results by their kinds
        if(results[i]== 0){
            numOfLose++;
            a->numOfWin++;
        }
            else if(results[i] == 1){
                numOfTie++;
                a->numOfTie++;
            }
                else if(results[i] == 2){
                        numOfWin++;
                        a->numOfLose++;
                    }

// sums the all of the results
        sumOfScore = sumOfScore + results[i];
        a->sumOfScore = a->sumOfScore + a->results[i];

            head = head->next;
            a->head=a->head->next;
}

head = tempp1;
a->head = tempp2;

}

HetList::~HetList()
{
	ListNode *temp;
	while(head)        // if the list is not empty
	{
		 temp=head;
		 head=head->next;
		 delete temp;
	}



}



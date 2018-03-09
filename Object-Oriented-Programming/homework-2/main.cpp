//EMRE KÖSE - 150130037
#include <iostream>
#include <string>
#include "classes.h"
#ifndef CLASSES_H
#define CLASSES_H
#include <fstream>

using namespace std;
void displayResults(int , HetList*, HetList*,char[],char []);
int main()
{
   //-----------READING CARDS FROM DECK.TXT---------------------------------------------
int matchLen1;
int matchLen2;
    string s1;
    string s2;
    ifstream myfile ("deck.txt");
    if (myfile.is_open())
    {

        getline(myfile,s1);
        getline(myfile,s2);
        myfile.close();
                            }
  else cout << "File can not be opened";


    matchLen1= (s1.length()+1)/2;
    matchLen2= (s2.length()+1)/2;
    char cards1[matchLen1];
    char cards2[matchLen2];

  // ----------------------CONTROL OF CARDS -------------------------------------
        if( matchLen1 != matchLen2)
        {
            cout << "number of cards are not equal"<<endl;
            return 0;
        }

        if(matchLen1 >=30 || matchLen2 >= 30 )
        {

        cout << "Cards number is higher than 30 So, you should increase CAPACITY from 'classes.h' "<<endl;
                    return 0;
        }
//-------------------------------------------------------------------------------------------------
//---ARRAYS OF CARDS => CARDS1 and CARDS2 for both players
  int j=0;
  for(unsigned i=0;i<s1.length()+1;i++){
        if(s1[i] != ' '  )
        {
            cards1[j]= s1[i];
            j=j+1;
        }
  }
   cards1[j] = '\0';
j=0;
 for(unsigned i=0;i<s2.length()+1;i++){
        if(s2[i] != ' '  )
        {
            cards2[j]= s2[i];
            j=j+1;
        }
  }
   cards2[j] = '\0';




    Base *r = new Red;
    Base *d = new DarkRed;
    Base *b = new Blue;
    Base *g = new Green;
    HetList *player1 = new HetList;
    HetList *player2= new HetList;

//INSERTING CLASSES TO HETLIST according to the their 'type's in own classes

    for(int i = 0; i< matchLen1;i++){
        if(cards1[i]== 'R')
        player1->insert(r);
        else if(cards1[i]== 'G')
        player1->insert(g);
         else if(cards1[i]== 'B')
        player1->insert(b);
        else if(cards1[i] == 'D')
           player1->insert(d);

    }


if(matchLen2 < 30  )
    for(int i = 0; i< matchLen2;i++){
        if(cards2[i]== 'R')
        player2->insert(r);
        else if(cards2[i]== 'G')
        player2->insert(g);
         else if(cards2[i]== 'B')
        player2->insert(b);
         else if(cards2[i] == 'D')
            player2->insert(d);

    }



    player1->compList(player2);  //'compList' function in 'HetList' Class for compare all cards in heterogeneous linked list

   displayResults(matchLen1,player1,player2,cards1,cards2); // display function for display all results and number of result types(win-lose-tie)



    return 0;

}
void displayResults(int lenList,HetList *x,HetList *y,char arrayx[],char arrayy[]){
    cout<<"Player1: ";
    for(int i=0;i<lenList;i++){
        cout << arrayx[i];
        cout<<" ";
    }
     cout<<endl;
      cout<<"Player2: ";
      for(int i=0;i<lenList;i++){
        cout << arrayy[i];
        cout<<" ";
    }
    cout<<endl;
    cout<<"Score1:  ";
    for(int i=0;i<lenList;i++){
        cout<<x->results[i];
        cout<<" ";
    }
    cout<<endl;
    cout<<"Score2:  ";
    for(int i=0;i<lenList;i++){
        cout<<y->results[i];
        cout<<" ";
    }
    cout<<endl;

    cout << "Total Score1: "<< "Lose: "<<x->numOfLose<<" Tie: "<<x->numOfTie<<" Win: "<<x->numOfWin<< "  => "<< x->sumOfScore<<endl;
    cout << "Total Score2: "<< "Lose: "<<y->numOfLose<<" Tie: "<<y->numOfTie<<" Win: "<<y->numOfWin << "  => "<< y->sumOfScore<<endl;


    if(x->sumOfScore>y->sumOfScore)
    cout<<"Winner: Player1"<<endl;
        else if(x->sumOfScore<y->sumOfScore)
        cout<<"Winner: Player2"<<endl;
            else
            cout<< "Tie"<<endl;


}

#endif // CLASSES_H

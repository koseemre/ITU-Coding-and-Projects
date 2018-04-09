#include <string>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
//#include <ctype.h>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;


class Card{
public:
    string name,className,rarity, set,type;
    int cost;
	// Constructor
    Card(const string &name, const string &className, const string &rarity, const string &set, const string &type,
         int cost) : name(name), className(className), rarity(rarity), set(set), type(type), cost(cost) {
        cout<< "card is created" << endl;
    }

    Card() { //Default Constructor
        name = "noName";
        className = "noClassName";
        rarity = "noRarity";
        set = "noSet";
        type = "noType";
        cost = 0;
    }

};

void Merge_Sort(Card *cards, int Start, int End); //Merge for full sort
void Merge_Sort_2(Card *cards, int Start, int End); //Merge for filter sort
void MergeForFull(Card *cards, int Start, int Middle, int End); //Merging Func 
void MergeForFilter(Card *cards, int Start, int Middle, int End); //Merging Func
void Insertion_SortForFull(Card *cards, int length); //Insertion Sort for fully sorting 
void Insertion_SortForFilter(Card *cards,int length); //Insertion Sort for filter sorting
class CardManager{

public:

    Card *cards;
    int indexOfCardList;
    int numberOfLine;
    clock_t time;
    float timeInSeconds;
	//Constructor which handles file and sorting operations
    CardManager(char *inputFileName, char *outputFileName, char *algorithmType,
                char *procedure)  {


        string line;
        numberOfLine=0;
        char * pch;
        Card *temp = new Card();
        int infoNo=1;
        indexOfCardList = 0;
        cout << "number of cards >> " << indexOfCardList << endl;
        ifstream ptrForLineNumber(inputFileName);

        while (getline(ptrForLineNumber,line)){	//Determining the size of file
            numberOfLine++;
        }
        ptrForLineNumber.close();

        if(numberOfLine>0){

            cards = new Card[numberOfLine];	//Allocating memory for card list
			
            ifstream fptr(inputFileName);
            while (getline(fptr,line)){		//Reading file and filling the card list

                char *a=new char[line.size()+1];
                a[line.size()]= '\0';
                memcpy(a,line.c_str(),line.size());

                pch = strtok (a,"\t");

                    while (pch != NULL)
                    {
                        if(infoNo == 1)
                            temp->name = pch;
                        else if(infoNo == 2)
                            temp->className = pch;
                        else if(infoNo == 3)
                            temp->rarity = pch;
                        else if(infoNo == 4)
                            temp->set = pch;
                        else if(infoNo == 5)
                            temp->type = pch;
                        else if(infoNo == 6)
                            temp->cost = atoi(pch);

                        infoNo++;
                        pch = strtok (NULL, "\t");
                    }

                infoNo =1;
                cards[indexOfCardList].cost = temp->cost;
                cards[indexOfCardList].type = temp->type;
                cards[indexOfCardList].set = temp->set;
                cards[indexOfCardList].name = temp->name;
                cards[indexOfCardList].className = temp->className;
                cards[indexOfCardList].rarity = temp->rarity;

                indexOfCardList++;

                delete [] a;

            }

            fptr.close();
        }
//According to the console inputs, determining and handling sorting operation and then writing these sorted list to new file
        if(strcmp(procedure,("full")) == 0 && strcmp(algorithmType,("merge")) == 0){	
            time = clock();
            Merge_Sort(cards,0,numberOfLine-1);
            time = clock() - time;
            timeInSeconds = (float)time/CLOCKS_PER_SEC;

            ofstream myfile;
            myfile.open (outputFileName);
                for(int i =0; i< numberOfLine;i++){
                    myfile<<cards[i].name; myfile<<'\t';  myfile<<cards[i].className; myfile<<'\t';
                    myfile<<cards[i].rarity; myfile<<'\t';  myfile<<cards[i].set; myfile<<'\t';
                    myfile<<cards[i].type; myfile<<'\t';  myfile<<cards[i].cost; myfile<<'\n';
                }
            myfile.close();
        }
        else if(strcmp(procedure,("filter")) == 0 && strcmp(algorithmType,("merge")) == 0){

            time = clock();
            Merge_Sort_2(cards,0,numberOfLine-1);
            time = clock() -time;
            timeInSeconds = (float)time/CLOCKS_PER_SEC;

            ofstream myfile;
            myfile.open (outputFileName);
                for(int i =0; i< numberOfLine;i++){
                    myfile<<cards[i].name; myfile<<'\t';  myfile<<cards[i].className; myfile<<'\t';
                    myfile<<cards[i].rarity; myfile<<'\t';  myfile<<cards[i].set; myfile<<'\t';
                    myfile<<cards[i].type; myfile<<'\t';  myfile<<cards[i].cost; myfile<<'\n';
                }
            myfile.close();
        }
        else if(strcmp(procedure,("filter")) == 0 && strcmp(algorithmType,("insertion")) == 0){

            time = clock();
            Insertion_SortForFilter(cards,numberOfLine);
            time = clock() -time;
            timeInSeconds = (float)time/CLOCKS_PER_SEC;
            ofstream myfile;
            myfile.open (outputFileName);
                for(int i =0; i< numberOfLine;i++){
                    myfile<<cards[i].name; myfile<<'\t';  myfile<<cards[i].className; myfile<<'\t';
                    myfile<<cards[i].rarity; myfile<<'\t';  myfile<<cards[i].set; myfile<<'\t';
                    myfile<<cards[i].type; myfile<<'\t';  myfile<<cards[i].cost; myfile<<'\n';
                }
            myfile.close();
        }
        else if(strcmp(procedure,("full")) == 0 && strcmp(algorithmType,("insertion")) == 0){

            time = clock();
            Insertion_SortForFull(cards,numberOfLine);
            time = clock() -time;
            timeInSeconds = (float)time/CLOCKS_PER_SEC;
            ofstream myfile;
            myfile.open (outputFileName);

                for(int i =0; i< numberOfLine;i++){
                    myfile<<cards[i].name; myfile<<'\t';  myfile<<cards[i].className; myfile<<'\t';
                    myfile<<cards[i].rarity; myfile<<'\t';  myfile<<cards[i].set; myfile<<'\t';
                    myfile<<cards[i].type; myfile<<'\t';  myfile<<cards[i].cost; myfile<<'\n';
                }

            myfile.close();
        }

    }
	//Deallocation of memory 
     ~CardManager() {
        if(cards != NULL)
            delete []cards;
    }


};
//Insertion sort with Full Procedure
void Insertion_SortForFull(Card *cards, int length){

    int j;
    Card temp;
    for (int i = 0; i < length; i++){
        j = i;
        while (j > 0 ){

            if(cards[j].className.compare(cards[j-1].className) < 0){
                temp = cards[j];
                cards[j] = cards[j-1];
                cards[j-1] = temp;

            }
            else if(cards[j].className.compare(cards[j-1].className) == 0){
                    if(cards[j].cost < cards[j-1].cost){
                        temp = cards[j];
                        cards[j] = cards[j-1];
                        cards[j-1] = temp;
                    }
                else if(cards[j].cost == cards[j-1].cost){
                        if(cards[j].name.compare(cards[j-1].name) < 0){
                            temp = cards[j];
                            cards[j] = cards[j-1];
                            cards[j-1] = temp;
                        }
                    }

            }

            j= j-1;
        }
    }
}
//Insertion sort with Filter Procedure
void Insertion_SortForFilter(Card *cards, int length){

    int j;
    Card temp;
    for (int i = 0; i < length; i++){
        j = i;
        while (j > 0 && cards[j].type.compare(cards[j-1].type) < 0 ){
            temp = cards[j];
            cards[j] = cards[j-1];
            cards[j-1] = temp;
            j= j-1;
        }
    }
}
//Merge sort with Full Procedure
void Merge_Sort(Card *cards, int Start, int End) // Merge sort recursive function
{
    int Middle;
    if (Start < End)
    {
        Middle = (Start + End) / 2;
        Merge_Sort(cards,Start,Middle);
        Merge_Sort(cards, Middle + 1, End);
        MergeForFull(cards, Start, Middle, End);
    }
}
//Merge sort with Filter Procedure
void Merge_Sort_2(Card *cards,int Start, int End) // Merge sort recursive function
{
    int Middle;
    if (Start < End)
    {
        Middle = (Start + End) / 2;
        Merge_Sort_2(cards,Start,Middle);
        Merge_Sort_2(cards,Middle + 1, End);
        MergeForFilter(cards, Start, Middle, End);
    }
}
//Merging according to the Full Procedure
void MergeForFull(Card *cards,int Start, int Middle, int End) // Merge(A, p, q, r)
{
    int N1 = (Middle - Start) + 1;
    int N2 = (End - Middle);
    Card *Temp_Results_L = new Card[N1];
    Card *Temp_Results_R = new Card[N2];

    int i, j, k;

        for (i = 0; i < N1; i++)  {
            Temp_Results_L[i] = cards[Start + i];
        }

        for (j = 0; j < N2; j++)    {
            Temp_Results_R[j] = cards[Middle+j+1];
        }

    i = 0;
    j = 0;
    k=Start;

   while( i<N1 && j< N2)
    {
        if (Temp_Results_L[i].className.compare( Temp_Results_R[j].className)  < 0)
        {
            cards[k] = Temp_Results_L[i];
            i++;
        }
        else if(Temp_Results_L[i].className.compare(Temp_Results_R[j].className)  == 0){
            if(Temp_Results_L[i].cost < Temp_Results_R[j].cost){
                cards[k] = Temp_Results_L[i];
                i++;
            }
            else if(Temp_Results_L[i].cost == Temp_Results_R[j].cost){
                if(Temp_Results_L[i].name.compare(Temp_Results_R[j].name) <= 0){
                    cards[k] = Temp_Results_L[i];
                    i++;
                }
                else{
                    cards[k] = Temp_Results_R[j];
                    j++;
                }
            }
            else{
                cards[k] = Temp_Results_R[j];
                j++;
            }
        }
        else {
            cards[k] = Temp_Results_R[j];
            j++;
        }
             k++;
    }

    while (i < N1) {
        cards[k] = Temp_Results_L[i];
        i++;
        k++; }


    while (j < N2)
    {
        cards[k] = Temp_Results_R[j];
        j++;
        k++;
    }

    delete []Temp_Results_L;
    delete []Temp_Results_R;
}
//Merging according to the Filter Procedure
void MergeForFilter(Card *cards,int Start, int Middle, int End) {
    int N1 = (Middle - Start) + 1;
    int N2 = (End - Middle);
    Card *Temp_Results_L2 = new Card[N1];
    Card *Temp_Results_R2 = new Card[N2];
    string holdType;

    int i, j, k;

    for (i = 0; i < N1; i++) {
        Temp_Results_L2[i] = cards[Start + i];
    }
    for (j = 0; j < N2; j++) {
        Temp_Results_R2[j] = cards[Middle+j+1];
    }
    i = 0;
    j = 0;
    k=Start;
    while( i<N1 && j< N2) {
        if (Temp_Results_L2[i].type.compare( Temp_Results_R2[j].type)  <= 0) {
            cards[k] = Temp_Results_L2[i];
            i++;
        }
        else {
            cards[k] = Temp_Results_R2[j];
            j++;
        }
        k++;
    }

    while (i < N1) {
        cards[k] = Temp_Results_L2[i];
        i++;
        k++;  }


    while (j < N2){
        cards[k] = Temp_Results_R2[j];
        j++;
        k++; }

    delete []Temp_Results_L2;
    delete []Temp_Results_R2;
}



//Handling of console inputs and creating CardManager object according to the these inputs
int main(int argc, char **argv)
{
    CardManager *cardManager;


        if(argc == 5){

            if(strcmp(*(argv+1),"-full")==0 && strcmp(*(argv+2),"-i")==0)
                cardManager = new CardManager(*(argv+3),*(argv+4),"insertion","full"); //inputfile,outputfile,algo,procedure
            else if(strcmp(*(argv+1),"-filter")==0 && strcmp(*(argv+2),"-i")==0)
                cardManager = new CardManager(*(argv+3),*(argv+4),"insertion","filter");
            else if(strcmp(*(argv+1),"-full")==0 && strcmp(*(argv+2),"-m")==0)
                cardManager = new CardManager(*(argv+3),*(argv+4),"merge","full");
            else if(strcmp(*(argv+1),"-filter")==0 && strcmp(*(argv+2),"-m")==0)
                cardManager = new CardManager(*(argv+3),*(argv+4),"merge","filter");

            cout << "time for this algorithm is: " << cardManager->timeInSeconds << endl;
        }
        else{
            cout << "invalid parameters for program" << endl;
        }



    return 0;

}

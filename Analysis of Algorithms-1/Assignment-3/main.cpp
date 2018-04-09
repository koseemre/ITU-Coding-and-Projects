#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <string>
#include <math.h>

#include <vector>

#define M 131070
using namespace std;

class Book_Character{
public:
    int page;
    int line;
    int index;
    char character;
    unsigned long  key;

    Book_Character();
    Book_Character(int p, int l, int i, char c);
    unsigned long  generateKey();
};

Book_Character::Book_Character(int p, int l, int i, char c)
{
    page = p;
    line = l;
    index = i;
    character = c;
    key = 0;

}
Book_Character::Book_Character()
{
    page = 0;
    line = 0;
    index = 0;
    character = '/';
    key = 0;

}

unsigned long  Book_Character::generateKey(){
    unsigned long k;
    k = (page*10000+line*100+index);
    return k;
}


class Dictionary{
public:

    int collision;
    int collisionSearch;
    Dictionary(int);
    ~Dictionary();
    void insert(Book_Character b_c);
    bool lookup(Book_Character b_c, ofstream &myfile);
    int hashFunc(unsigned long key);
    Book_Character *myHashTable;
    int totalEntries;
    int totalFound;
    int countTotal; // counts the number of running of insert function
    Book_Character homeless_Char[50];
    int count;//counts homeless objects


};
Dictionary::Dictionary(int tableSize)
{

    collision=0;
    totalEntries=0;
    totalFound= 0;
    myHashTable = new Book_Character[tableSize];
    collisionSearch=0;
    count = 0;
    countTotal = 0;
}

Dictionary::~Dictionary(){
    delete [] myHashTable;
}
int Dictionary::hashFunc(unsigned long  key)
{

    double A = (sqrt(5)-1)/2;
    double v=  fmod((key*A),1);
    int h = round(M * v);
    return h;

}
void Dictionary::insert(Book_Character b_c)
{
    long  h = hashFunc(b_c.key);
    long  probed_value = h;
    int current_collision;
    countTotal++;
    for(current_collision=0; current_collision<M; current_collision++){

        probed_value= (probed_value + 7*current_collision + 3*(current_collision*current_collision))%M;
        if(probed_value < 0){
            probed_value = probed_value+M;
        }


        if(myHashTable[probed_value].character == '/'){
            myHashTable[probed_value].key = b_c.key;
            myHashTable[probed_value].page=b_c.page;
            myHashTable[probed_value].index=b_c.index;
            myHashTable[probed_value].character=b_c.character;
            totalEntries++;
            break;
        }
       if(current_collision == M -1 )
        {
            homeless_Char[count] = b_c; // holds the book_characters which not found any appropriate probed_value(hash value)
            count++;
        }

        collision++;
    }
    if(totalEntries == 1000 || totalEntries == 10000 || totalEntries == 100000 || M == countTotal ){
        if(countTotal == M)
            cout << "Average number of Collisions(overall) |" << ((double)collision/(double)totalEntries) << endl;
        else
            cout << "Average number of Collisions(" << totalEntries<< ") |" << ((double)collision/(double)totalEntries) << endl;

    }

}


bool Dictionary::lookup(Book_Character b_c,ofstream &myfile) {


    int predictedIndex;
    int current_collision;
    predictedIndex=hashFunc(b_c.key);

    // control the Book_Characters which will be searched for it is in the homeless Book_Characters set or not?
    for(int i=0;i<count;i++){
        if(b_c.key == homeless_Char[i].key){   // if it is in homeless Book_Characters set, update with the one of the random free object in hashTable
            for(int j=0;j<M;j++){
                if(myHashTable[j].key== 0){
                    myHashTable[j]= homeless_Char[i];
                    //  cout<< myHashTable[j].key<<endl;
                    // cout << "updated"  <<endl;
                    return true;

                }
            }
            break;
        }
    }

    for( current_collision =0 ;current_collision < M ; current_collision++){

        predictedIndex = (predictedIndex + 7*current_collision + 3*(current_collision*current_collision))%M;
        if(predictedIndex < 0){
            predictedIndex = predictedIndex+M;
        }

        if( myHashTable[predictedIndex].key == b_c.key){
            totalFound++;
            myfile<<b_c.page<<'\t'<<b_c.line<<'\t'<<b_c.index<<'\t'<< myHashTable[predictedIndex].character<<'\n';
            return true;
        }
        collisionSearch++;
    }


    return false;
}

int main(int argc, char **argv) {

    clock_t time;
    string line;
    int page,p_line,index;
    char character;
    unsigned long  key;
    double timeInSecondsDicInsert=0;
    double timeInSecondsListInsert=0;

    vector <Book_Character> g1;
    vector <Book_Character> :: iterator i;
    vector <Book_Character> :: reverse_iterator ir;

    ifstream fptr("ds-set-input.txt");

    if(!fptr.is_open())
        cout << "error when file is opening"<<endl;

    char *pch;
    int infoNo=1;
    Dictionary *dictionary = new Dictionary(M);

    if (fptr.is_open())
    {
        while ( getline (fptr,line)  )
        {
            char *a=new char[line.size()+1];
            a[line.size()]= '\0';
            memcpy(a,line.c_str(),line.size());

            pch = strtok (a,"\t");

            while (pch != NULL)
            {
                if(infoNo == 1)
                    page = atoi(pch);
                else if(infoNo == 2)
                    p_line= atoi(pch);
                else if(infoNo == 3)
                    index= atoi(pch);
                else if(infoNo == 4)
                    character = *pch;

                infoNo++;
                pch = strtok (NULL, "\t");
            }
            Book_Character b_c;
            b_c.page = page;
            b_c.line= p_line;
            b_c.index= index;
            b_c.character = character;
           // cout << "counter: " << counter++ << " ";
            key = b_c.generateKey();
            b_c.key = key;

            time = clock();
            g1.push_back(b_c);
            time = clock() - time;
            timeInSecondsListInsert = timeInSecondsListInsert + (double)time/CLOCKS_PER_SEC;

            time = clock();
            dictionary->insert(b_c);
            time = clock() - time;
            timeInSecondsDicInsert = timeInSecondsDicInsert + (double)time/CLOCKS_PER_SEC;

            delete []a;
            infoNo =1;

        }
        fptr.close();
    }


    vector <Book_Character> g2;
    vector <Book_Character> :: iterator j;
    vector <Book_Character> :: reverse_iterator jr;
    ofstream myfile3;
    myfile3.open ("ds-set-output-dict.txt");
    ofstream myfile4;
    myfile4.open ("ds-set-output-list.txt");


    ifstream fptr2("ds-set-lookup.txt");
    if(!fptr2.is_open())
        cout << "error when file is opening"<<endl;
    infoNo=1;
    if (fptr2.is_open())
    {
        while (getline(fptr2,line))
        {
            char *a=new char[line.size()+1];
            a[line.size()]= '\0';
            memcpy(a,line.c_str(),line.size());

            pch = strtok (a,"\t");

            while (pch != NULL)
            {
                if(infoNo == 1)
                    page = atoi(pch);
                else if(infoNo == 2)
                    p_line= atoi(pch);
                else if(infoNo == 3)
                    index= atoi(pch);

                infoNo++;
                pch = strtok (NULL, "\t");
            }

            Book_Character b_c_2;
            b_c_2.page = page;
            b_c_2.line= p_line;
            b_c_2.index= index;
            b_c_2.character = '/';
            key = b_c_2.generateKey();
            b_c_2.key = key;
            g2.push_back(b_c_2);
           // dictionary->lookup(b_c_2);

            delete []a;
            infoNo =1;

        }
        fptr2.close();
    }


    double timeInSecondsDicLookUp=0;
    double timeInSecondsListLookUp=0;

    time = clock();
    // Dictionary look-up
    for (j = g2.begin(); j != g2.end(); ++j)
        dictionary->lookup((*j),myfile3);
    time = clock() - time;
    timeInSecondsDicLookUp = (double)time/CLOCKS_PER_SEC;

    //List Lookup
    time = clock();
    for (int i=0;i<M ; i++){
        for(int j=0;j<M ; j++){
            if(g1[i].key == g2[j].key ){
                myfile4<<g1[i].page<<'\t'<<g1[i].line<<'\t'<<g1[i].index<<'\t'<< g1[i].character<<'\n';
                break;
            }

        }
    }
    time = clock() - time;
    timeInSecondsListLookUp = (double)time/CLOCKS_PER_SEC;

    cout << "Look up for Dictionary:" << timeInSecondsDicLookUp << endl;
    cout << "Look up for List:" << timeInSecondsListLookUp << endl;
    cout << "Inserting for Dictionary:" << timeInSecondsDicInsert << endl;
    cout << "Inserting for List:" << timeInSecondsListInsert << endl;

   /* cout << "total found:" << dictionary->totalFound << endl;
    cout << "total Entries:" << dictionary->totalEntries<< endl;
    cout << "total collisionSearch:" << dictionary->collisionSearch << endl;
    cout << "total collision:" << dictionary->collision << endl;*/

   /* for(int i=0 ;i < M ; i++)
        if(dictionary->myHashTable[i].character =='/')
            cout << "i:" <<i<< "  "<<dictionary->myHashTable[i].key<< endl;

    for(int i=0 ;i<50;i++)
        cout<< dictionary->homeless_Char[i].key << endl;*/

    myfile3.close();
    myfile4.close();

    return 0;
}

/*
Name:EMRE KÖSE
Student ID:150130037
*/
//NOT SORTED list icin fonk. yazildi ancak anlayamadigim bir nedenden dolayi isme gore sort edemiyor

#include <iostream>
#include <stdlib.h>
#include <iomanip>
//#include <conio.h>
#include <ctype.h>
#include <cstring>
#include <fstream>
#include "List.h"
#include "Song.h"
#include <time.h>

using namespace std;

typedef list Veriyapisi;
Veriyapisi defter;

bool islem_yap(char);
void menu_yazdir();
void play();
void printList();
void createList();
void addSong();
void removeSong();
void deleteList();
void writeToFile();
void exit();

int main(){

int sayac=0;
defter.create();
defter.create_list_for_default("SORTED");
defter.create_list_for_default("CHRONOLOGICAL");

string line;
char * pch;
song temp;
bool control= true;
int infoNo=1;
int songNumber=0;
 ifstream fptr ("songbook.txt");
char list_name[50];
char *a;

    while (getline(fptr,line)){

          a=new char[line.size()+1];
          a[line.size()]=0;
          memcpy(a,line.c_str(),line.size());

    if(strcmp(a,"*****") != 0  && control == true){

        songNumber++;
         pch = strtok (a,"\t");
  while (pch != NULL)
  {
    if(infoNo == 1){
                strcpy(temp.name,pch);
               // cout << pch<< endl;

    }

    else if(infoNo == 2)
         strcpy(temp.singer,pch);
    else if(infoNo == 3)
        temp.year = atoi(pch);

    else if(infoNo == 4){
    strcpy(temp.style,pch);

    }

    infoNo++;
    pch = strtok (NULL, "\t");
  }

    infoNo =1;
    defter.add_song(&temp,"SORTED");
    defter.add_song(&temp,"CHRONOLOGICAL");



    delete [] a;
    }
    else{

    control = false;
        if(strcmp(a,"*****") == 0){

        sayac++;
        delete []a;
        getline(fptr,line);
        int j;

            for( int i=0;i<50;i++)
            list_name[i] = '0';


            for( j=0;j<line.size();j++)
                list_name[j] = line[j];
                list_name[j] = '\0';


                defter.create_list(list_name);


         getline(fptr,line);
         a=new char[line.size()+1];
         a[line.size()]=0;
         memcpy(a,line.c_str(),line.size());


  pch = strtok (a,"\t");
  while (pch != NULL)
  {
    if(infoNo == 1){
                strcpy(temp.name,pch);
               // cout << pch<< endl;

    }

    else if(infoNo == 2)
         strcpy(temp.singer,pch);
    else if(infoNo == 3)
        temp.year = atoi(pch);

    else if(infoNo == 4){
    strcpy(temp.style,pch);

    }

    infoNo++;
    pch = strtok (NULL, "\t");
  }

        infoNo =1;
        defter.add_to_list(list_name,&temp);
        delete [] a;

    }
    else{

         pch = strtok (a,"\t");
        while (pch != NULL) {
    if(infoNo == 1)
        strcpy(temp.name,pch);
    else if(infoNo == 2)
         strcpy(temp.singer,pch);
    else if(infoNo == 3)
        temp.year = atoi(pch);
    else if(infoNo == 4)
    strcpy(temp.style,pch);

    infoNo++;
    pch = strtok (NULL, "\t");
  }

        infoNo =1;

        defter.add_to_list(list_name,&temp);
        delete [] a;
    }
    }

        }


    defter.createRandomList(songNumber); // default random list created

    fptr.close();


bool bitir = false;
char secim;
while (!bitir) {
menu_yazdir();
cin >> secim;
bitir = islem_yap(secim);
}



return EXIT_SUCCESS;

}


void menu_yazdir(){
//system("cls"); //linux'ta ekran temizleme icin system("clear"); kullaniniz
cout << endl << endl;

cout << "Choose an operation" << endl;
cout << "P: play" << endl;
cout << "L: printList" << endl;
cout << "C: createList" << endl;
cout << "A: addSong" << endl;
cout << "R: removeSong" << endl;
cout << "D: deleteList" << endl;
cout << "W: writeToFile" << endl;
cout << "E: exit" << endl;

cout << endl;
cout << "Your selection is : ";
}

//----------------------------------------------------------------------------------------------------------------------
bool islem_yap(char secim){
bool sonlandir=false;
switch (secim) {
case 'P': case 'p':
    play();
break;
case 'L': case 'l':
    printList();
break;
case 'C': case 'c':
createList();
break;
case 'A': case 'a':
addSong();
break;
case 'R': case 'r':
removeSong();
break;
case 'D': case 'd':
deleteList();
break;
case 'W': case 'w':
writeToFile();
break;
case 'E': case 'e':
cout << "Are you sure that you want to terminate the program? (Y/N):";
cin >> secim;
if(secim=='Y' || secim=='y'){
   sonlandir=true;
   exit();
}

break;
default:
cout << "Error: You have made an invalid choice" << endl;
cout << "Try again {A, E, G, S, B, C} :" ;
cin >> secim;
sonlandir = islem_yap(secim);
break;
}
return sonlandir;
}
//--------------------------------------------------------------------------------------------------------
void play(){
char input;
char list_name[50];
cout << "PLAY > " << endl;
cout << "Choose an operation: " << endl;
cout << "L: Play a play list" << endl;
cout << "S: Play a play list starting from specific song" << endl;
cout << "P: Playing a single song " << endl;
cout << "E: Exit " << endl;
cout << "Enter a choice(L,S,P,E):";
cin >> input;

while(input != 'E'){
    if(input == 'L' || input == 'l'){
          playlist *traverse = defter.last->next;
          char input2;

            cout << "Enter the name of the list you want to play:  ";
            cin >> list_name;

        for(int i=0;i < defter.playlist_count ; i++){
        if(strcmp(traverse->name,list_name) ==0)
            break;
        else
            traverse = traverse->next;
        }

        if(strcmp(traverse->name,list_name) ==0 ){
            song_node *traverse_node = traverse->last->next;


    cout << "playing song name: "<<traverse_node->data->name << " singer: "<< traverse_node->data->singer << "  year:  "<< traverse_node->data->year<< "  style:  "<< traverse_node->data->style<< endl;
    cout << "N(NEXT) - P(PREVIOUS) - E(EXIT):";

    cin >> input2;

    while(input2 != 'E' && input2 != 'e'){

        if(input2 == 'N' || input2 == 'n' )
        {
            traverse_node = traverse_node->next;
            cout << "playing song name: "<<traverse_node->data->name << " singer: "<< traverse_node->data->singer << "  year:  "<< traverse_node->data->year<< "  style:  "<< traverse_node->data->style<< endl;
        }
        else if(input2 == 'P' || input2 == 'p'){
        traverse_node = traverse_node->prev;
        cout << "playing song name: "<<traverse_node->data->name << " singer: "<< traverse_node->data->singer << "  year:  "<< traverse_node->data->year<< "  style:  "<< traverse_node->data->style<< endl;
        }
        cout << "N(NEXT) - P(PREVIOUS) - E(EXIT):";
        cin >> input2;

    }
        }
        else{
            cout << "this list is not in the current lists" << endl;
            return;
        }

    return;
    }
    else if(input == 'S' || input == 's'){
        playlist *traverse;
        traverse = defter.last->next;
        song_node *traverse_node;
        int in;
        int in2;

        for(int i= 0 ; i< defter.playlist_count ; i++){
            cout << i+1<< ". "<<traverse->name << endl;
            traverse= traverse->next;
        }
        cout << "choose one of index of them to play any song in it:";
        cin >> in;
        if(in > 0 && in <=defter.playlist_count ){
        traverse = defter.last->next;
        for(int i= 1 ; i< in ; i++)
                traverse = traverse->next;


        traverse_node = traverse->last->next;
         for(int i= 0 ; i< traverse->songnumber ; i++)
         {
        cout << i+1<<". Name: "<<traverse_node->data->name << " singer: "<< traverse_node->data->singer << "  year:  "<< traverse_node->data->year<< "  style:  "<< traverse_node->data->style<< endl;
        traverse_node = traverse_node->next;
         }

        cout << "Selection is : ";
        cin >> in2;
        traverse_node = traverse->last->next;
        if(in2 > 0 && in2 <=traverse->songnumber ){
            for(int i=1;i<in2;i++)
                traverse_node = traverse_node->next;

        cout << "playing song name: "<<traverse_node->data->name << " singer: "<< traverse_node->data->singer << "  year:  "<< traverse_node->data->year<< "  style:  "<< traverse_node->data->style<< endl;
        return;
        }


        }
        else{
            cout << "wrong index" << endl;
            return;
        }

    }
    else if(input == 'P' || input == 'p'){

    playlist *traverse;
    traverse = defter.last->next;
    song_node *traverse_node;
    int in2;

    for(int i=0 ; i< defter.playlist_count; i++){
    if(strcmp(traverse->name,"SORTED"))
        break;
    else
        traverse = traverse->next;
    }

    if(strcmp(traverse->name,"SORTED")){
            traverse_node = traverse->last->next;

         for(int i= 0 ; i< traverse->songnumber ; i++)
         {
        cout << i+1<<". Name: "<<traverse_node->data->name << " singer: "<< traverse_node->data->singer << "  year:  "<< traverse_node->data->year<< "  style:  "<< traverse_node->data->style<< endl;
        traverse_node = traverse_node->next;
         }
        cout << "Selection is : ";
        cin >> in2;
        traverse_node = traverse->last->next;
        if(in2 > 0 && in2 <=traverse->songnumber ){
            for(int i=1;i<in2;i++)
                traverse_node = traverse_node->next;

        cout << "playing song name: "<<traverse_node->data->name << " singer: "<< traverse_node->data->singer << "  year:  "<< traverse_node->data->year<< "  style:  "<< traverse_node->data->style<< endl;
        return;


        }else
        {
            cout << "wrong index" << endl;
            return;
        }


    }
    else
        return;
    }
    else {
    cout << "invalid input" << endl;
    return;

    }





}



}

//-----------------------------------------------------------------------------------------------------
void printList(){

    playlist *traverse = defter.last->next;



    cout << "All lists:" << endl;
    for(int i=0 ;i < defter.playlist_count ; i++){

        cout << i+1 <<". "  << traverse->name << endl;
        traverse = traverse->next;
    }


    traverse = defter.last->next;
    song_node *traverse_node = traverse->last->next;


    cout << traverse->name<<":" << endl;                //ilk ekranda sadece ilk listeyi goruntule
    for(int i=0 ; i< traverse->songnumber; i++ ){
        cout << i+1<< ". name: " << traverse_node->data->name << "   singer: "<< traverse_node->data->singer<< "      year: " << traverse_node->data->year<< "   style: "<< traverse_node->data->style<< endl;
        traverse_node = traverse_node->next;
    }


        char input;
        cout << " N (NEXT), P (PREVIOUS) , S (SELECT) , E (EXIT) : ";
        cin >> input;


        while(input != 'E' && input != 'e'){

        if(input == 'N' || input == 'n' ){
        traverse = traverse->next;
        traverse_node = traverse->last->next;
        cout << traverse->name<<":" << endl;
        for(int i=0 ; i< traverse->songnumber ; i++){

        cout << i+1<<".song name: " << traverse_node->data->name << "  singer name:  " <<  traverse_node->data->singer << "  year:  " << traverse_node->data->year << "  style:  " << traverse_node->data->style << endl;
        traverse_node = traverse_node->next;
        }

        }

        else if(input == 'P' || input == 'p'){
             traverse = traverse->prev;
        traverse_node = traverse->last->next;
        cout << traverse->name<<":" << traverse->songnumber<<endl;
         for(int i=0 ; i< traverse->songnumber ; i++){

        cout << i+1<<".song name: " << traverse_node->data->name << "  singer name:  " <<  traverse_node->data->singer << "  year:  " << traverse_node->data->year << "  style:  " << traverse_node->data->style << endl;
        traverse_node = traverse_node->next;
        }

        }
        else if(input == 'S' || input == 's'){
            cout << "select one of the following commands:"<<endl;
            cout << " D (delete the playlist), A (add song), R (remove song) , P (play the songs in the playlist): , E(Exit)";
            char inpt;
            cin >> inpt ;


            while(inpt == 'D' || inpt == 'A' || inpt == 'R' || inpt == 'P' || inpt == 'd' || inpt == 'a' ||inpt == 'r'|| inpt == 'p' ||inpt == 'E'|| inpt == 'e'){

            if(inpt == 'D' || inpt == 'd'){
                playlist *t= defter.last->next;
                int c=0;
                for(int i = 0; i < defter.playlist_count ; i++)
                {
                    if(traverse == t){
                      c = i+1;
                        break;
                    }
                        else
                        t = t->next;
                }

                if(c > 0){
                    defter.delete_list(c,traverse);
                    cout << "current list is deleted" << endl;
                    return;
                }

                else
                {
                    cout << "list can not be deleted" << endl;
                    return;
                }
            }
            else if(inpt == 'A' || inpt == 'a'){ // print in icinde ekleme yapma
                int in;
                playlist *traverse2;
                song_node *traverse_node;
                traverse2 = defter.last->next;

                      for(int i=0 ;i < defter.playlist_count ; i++)
                            {
                                if(strcmp(traverse2->name,"SORTED")==0)
                                    break;
                                traverse2= traverse2->next;
                            }

     if(strcmp(traverse2->name,"SORTED")==0)
     {
         traverse_node = traverse2->last->next;

                        for(int i=0 ;i < traverse2->songnumber ; i++){
                            cout << i+1<<".song name: " << traverse_node->data->name << endl;
                            traverse_node = traverse_node->next;
                        }

            cout << "enter the index of song which you add to this play list(!!to complete press -1): ";
            cin>> in;

            while(in != -1){
                defter.add_non_default_song(in,traverse->name);
                traverse_node = traverse2->last->next;
                        for(int i=0 ;i < traverse2->songnumber ; i++){
                            cout << i+1<<".song name: " << traverse_node->data->name << endl;
                            traverse_node = traverse_node->next;
                        }

                cout << "enter the index of song which you add to this play list(!!to complete press -1): ";
                cin>> in;
            }

            }
            else
            {
                cout << "adding can  not be done" << endl;

            }
             }
             else if(inpt == 'R' ||inpt == 'r'){
        char song_name[50];
        int in;
        song_node *traverse_node;
         traverse_node = traverse->last->next;

        for(int i=0 ;i < traverse->songnumber ; i++){
            cout << i+1<<". Song name: " << traverse_node->data->name << endl;
            traverse_node = traverse_node->next;
        }

            cout << "enter the index of song which you delete from "<< traverse->name<< " play list(!! to complete press -1): ";
            cin>> in;

            while(in != -1){
                defter.delete_from_given_list(in,traverse);
                traverse_node = traverse->last->next;
                        for(int i=0 ;i < traverse->songnumber ; i++){
                            cout << i+1<<".song name: " << traverse_node->data->name << endl;
                            traverse_node = traverse_node->next;
                        }

                cout << "enter the index of song which you add to this play list(!!to complete press -1): ";
                cin>> in;
            }
            }
            else if(inpt == 'P' || inpt == 'p'){
            song_node *traverse_node;
            traverse_node = traverse->last->next;

            cout << "Playing list... " <<endl;
             for(int i=0;i<traverse->songnumber;i++){
            cout << i+1<<".song name: " << traverse_node->data->name << "  singer name:  " <<  traverse_node->data->singer << "  year:  " << traverse_node->data->year << "  style:  " << traverse_node->data->style << endl;
            traverse_node = traverse_node->next;
            }



            }
            else if(inpt == 'E' || inpt == 'e')
            break;


            cout << " D (delete the playlist), A (add song), R (remove song) , P (play the songs in the playlist) ,E(Exit):";
            char inpt;
            cin >> inpt ;

            if(inpt == 'E' || inpt == 'e'  )
                break;

            }

        }
        cout << " N (NEXT), P (PREVIOUS) , S (SELECT) , E (EXIT) : ";
        cin >> input;

        }


}
//---------------------------------------------------------------------------------------------------------------------------
void createList(){

    int select;


    cout << "Create list types:" << endl;
    cout << "1) songs of a specific style" << endl;
    cout << "2) songs of a specific singer" << endl;
    cout << "3) a combination of existing playlists" << endl;
    cout << "4) a combination of existing songs" << endl;

    cout << "Select one type(press 1 to 4): " ;
    cin >> select;
    if(select >= 1 && select <= 4)
    {
        if(select == 1)
            {
                 char style[30];
                 cout << "enter the style name of songs:";
                 cin >> style;
                 defter.create_list_by_style(style);

                                        }
                else if(select == 2)
            {    char singer[30];
                 cout << "enter the singer name of songs:";

                 cin.ignore(1000, '\n');
                 cin.getline(singer,30);
                 defter.create_list_by_singer(singer); }
                    else if(select == 3)
                    {
                        char name[50];
                        cout << "enter specific name of list for a combination of existing play  lists:";
                        cin.ignore(1000, '\n');
                        cin.getline(name,50);
                        playlist *merged_list;
                        playlist *hold_head = defter.last->next;
                        playlist *traverse = defter.last->next;
                        playlist *traverse2 = defter.last->next;
                        playlist *traverse3;
                        int selectList;
                        for(int i=0 ; i< defter.playlist_count ; i++){
                            cout << i+1 << ").  " << traverse->name << endl;
                            traverse = traverse->next;
                        }
                        cout << "select one of the play lists and press enter one by one ( !! to complete press (-1) ): ";
                        cin >> selectList;
                        if(selectList >=1 && selectList <= defter.playlist_count){  //ilk isteneni ekle
                            for(int i=1 ;i < selectList ; i++)
                                traverse2 = traverse2->next;

                            merged_list = new playlist;

                            merged_list->last= NULL;
                            merged_list->next= NULL;
                            merged_list->prev= NULL;
                            strcpy(merged_list->name,name);
                            merged_list->songnumber=0;
                            defter.add_for_merged(merged_list,traverse2);




                              while(selectList != -1){
                            traverse = defter.last->next;

                            for(int i=0 ; i< defter.playlist_count ; i++){
                            cout << i+1 << ").  " << traverse->name << endl;
                            traverse = traverse->next;
                        }
                        cout << "select one of the play lists and press enter one by one: to complete press (-1): ";
                        cin >> selectList;

                        if(selectList >=1 && selectList <= defter.playlist_count){

                              traverse3 =  hold_head;
                            for(int i=1 ;i < selectList ; i++)
                                traverse3 = traverse3->next;

                            defter.add_for_merged(merged_list,traverse3);
                            cout << traverse3->songnumber << endl;

                        }
                        else{
                            cout << "invalid input " << endl;
                            break;
                        }

                        }

                        defter.playlist_count++;

                        }
                        else if(selectList == -1 )
                            return;
                            else
                        {
                            cout <<  "invalid input " << endl;
                            return;

                        }


                                                        }
                            else if(select ==4)
                            {
                        playlist *traverse;
                        song_node *traverse_node;
                        song *new_song;
                        traverse = defter.last->next;
                        char name[50];
                        int ind;
                        cout << "enter specific name of list for a combination of existing songs which you will select:";
                        cin.ignore(1000, '\n');
                        cin.getline(name,50);
                     //   for(int i = 0; i< defter.playlist_count;i++)
                     for(int i = 0; i< defter.playlist_count;i++){
                        if(strcmp(traverse->name,"SORTED") ==0)
                            break;
                        else
                            traverse= traverse->next;
                     }
                     if(strcmp(traverse->name,"SORTED") ==0){
                        defter.create_list(name);
                        traverse_node = traverse->last->next;

                        for(int i=0 ; i< traverse->songnumber;i++)
                                {
    cout << i+1<<".song name: " << traverse_node->data->name << "  singer name:  " <<  traverse_node->data->singer << "  year:  " << traverse_node->data->year << "  style:  " << traverse_node->data->style << endl;
                traverse_node = traverse_node->next;
                                }
                            cout << "enter the index you want to add to " << name <<" list (to complete press -1)"<<endl;
                            cin>>ind;
                            while(ind != -1){
                            traverse_node = traverse->last->next;
                            for(int i=1 ; i< ind;i++)
                                traverse_node = traverse_node->next;

                            new_song = new song;
                            strcpy(new_song->name,traverse_node->data->name);
                            strcpy(new_song->singer,traverse_node->data->singer);
                            strcpy(new_song->style,traverse_node->data->style);
                            new_song->year = traverse_node->data->year;

                            defter.add_to_list(name,new_song);

                            cout << "enter the index you want to add to " << name <<" list (to complete press -1)"<<endl;
                            cin>>ind;
                            if(ind == -1)
                                return;
                            }

                     }
                     else
                     {
                         cout << "sorted can not be found"<<  endl;
                         return;
                     }


                                                            }
                            else{
                                cout << "invalid selection" <<endl;
                                return;
                            }
    }
    else
    {
        cout << "incorrect input" << endl;
        return;
    }


}
//----------------------------------------------------------------------------------------------------------
void addSong(){
        char song_name[50];
        char list_name[50];
        int in;
        playlist *traverse = defter.last->next;
        song_node *traverse_node;
            for(int i=0 ;i < defter.playlist_count ; i++)
        {
            if(strcmp(traverse->name,"RANDOM") != 0)
            cout << i+1 <<". " << traverse->name << endl;
            traverse= traverse->next;
        }

         cout << "enter the name of play list which you would add to:";
          cout << "(you can add to one of the default lists(SORTED,CHRONOLOGICAL) or other specific list name )";
         cin.ignore(1000, '\n');
         cin.getline(list_name,50);
         traverse = defter.last->next;
                for(int i=0 ;i < defter.playlist_count ; i++)
    {
        if(strcmp(traverse->name,list_name)==0)
            break;
        traverse= traverse->next;
    }
     if(strcmp(traverse->name,list_name)!=0)
     {
         cout << "there is no list name like " << list_name << endl;
         return;
     }


         traverse = defter.last->next;
          for(int i=0 ;i < defter.playlist_count ; i++)
    {
        if(strcmp(traverse->name,"SORTED")==0)
            break;
        traverse= traverse->next;
    }
     if(strcmp(traverse->name,"SORTED")==0)
     {
         traverse_node = traverse->last->next;

        for(int i=0 ;i < traverse->songnumber ; i++){
            cout << i+1<<".song name: " << traverse_node->data->name << endl;
            traverse_node = traverse_node->next;
        }

            cout << "enter the index of song which you add to this play list(!!to complete press -1): ";
            cin>> in;

            while(in != -1){
                defter.add_non_default_song(in,list_name);
                traverse_node = traverse->last->next;
                        for(int i=0 ;i < traverse->songnumber ; i++){
                            cout << i+1<<".song name: " << traverse_node->data->name << endl;
                            traverse_node = traverse_node->next;
                        }

                cout << "enter the index of song which you add to this play list(!!to complete press -1): ";
                cin>> in;
            }

     }
     else{
        cout << "there is no SORTED list which help help you to add songs . It can be deleted" << endl;
        return;
     }

}

//-------------------------------------------------------------------------------------------
void removeSong(){
        char song_name[50];
        char list_name[50];
        int in;
        playlist *traverse = defter.last->next;
        song_node *traverse_node;
            for(int i=0 ;i < defter.playlist_count ; i++)
        {

            cout << i+1 <<". " << traverse->name << endl;
            traverse= traverse->next;
        }
         cout << "(you can delete to one of the default lists or other specific list name )"<<endl;;
         cout << "enter the name of play list which you would delete songs from :";

         cin.ignore(1000, '\n');
         cin.getline(list_name,50);
         traverse = defter.last->next;
                for(int i=0 ;i < defter.playlist_count ; i++)
    {
        if(strcmp(traverse->name,list_name)==0)
            break;
        traverse= traverse->next;
    }


     if(strcmp(traverse->name,list_name)==0)
     {
         traverse_node = traverse->last->next;

        for(int i=0 ;i < traverse->songnumber ; i++){
            cout << i+1<<". Song name: " << traverse_node->data->name << endl;
            traverse_node = traverse_node->next;
        }

            cout << "enter the index of song which you delete from "<< list_name<< " play list(!! to complete press -1): ";
            cin>> in;

            while(in != -1){
                defter.delete_from_given_list(in,traverse);
                traverse_node = traverse->last->next;
                        for(int i=0 ;i < traverse->songnumber ; i++){
                            cout << i+1<<".song name: " << traverse_node->data->name << endl;
                            traverse_node = traverse_node->next;
                        }

                cout << "enter the index of song which you add to this play list(!!to complete press -1): ";
                cin>> in;
            }

     }
     else{
        cout << "there is no list like  " << list_name<< endl;
        return;
     }
}
//-----------------------------------------------------------------------
void deleteList(){
    char list_name[50];
    playlist *traverse = defter.last->next;

    for(int i = 0; i< defter.playlist_count ; i++ )
    {
            cout << i+1<< ". " << traverse->name << endl;
            traverse = traverse->next;
    }

    cout << "enter the name of the list which you want to delete: ";
    cin.ignore(1000, '\n');
    cin.getline(list_name,50);
    int control=0;
    traverse = defter.last->next;
    for(int i = 0 ; i< defter.playlist_count ; i++)
    {
        if(strcmp(traverse->name,list_name) ==0){
            control = i+1;
            break;
        }
        else
            traverse = traverse->next;
    }

        if(control > 0){
            defter.delete_list(control,traverse);
            cout << list_name <<" list is deleted" << endl;
            return;
        }
        else{
            cout << list_name << " can not be found in the list" << endl;
            return;
        }


}
//----------------------------------------------------------------------------------------
void writeToFile(){

    defter.write();

}
//--------------------------------------------------------------------------------------------
void exit(){
    writeToFile();
    defter.close();

     }











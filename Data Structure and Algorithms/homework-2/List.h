
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include "play_list.h"

using namespace std;
struct list {
  FILE *file_ptr;
  int playlist_count;
  playlist* last;
  void create_list_for_default(char *);
  void create_list(char *);
  void add_to_list(char * , song *);
  void write();
  void delete_list(int , playlist *);
  void create_list_by_style(char *);
  void create_list_by_singer(char *);
  void add_for_merged(playlist *, playlist *);
  void add_non_default_song(int  , char *);
  void delete_from_given_list(int  , playlist *);
  void print();
  void create();
  void close();
  void add_song(song *,char *);
  void createRandomList(int);
  void shuffle(int * , size_t);
  playlist * create_new_list(song *,char*);


};

 playlist * list::create_new_list(song *add_song, char *name){   // RANDOM list icin kullanildi

    song_node *new_node = new song_node;
    new_node->data = new song;

            strcpy(new_node->data->name,add_song->name);
            strcpy(new_node->data->singer,add_song->singer);
            strcpy(new_node->data->style,add_song->style);
            new_node->data->year = add_song->year;


    playlist *new_list = new playlist;



    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->parent = new_list;

    new_list->last = new_node;
    new_list->last->next = new_node;
    new_list->last->prev = new_node;
    new_list->songnumber = 1;

    strcpy(new_list->name,name);
    new_list->next = NULL;
    new_list->prev = NULL;


    return new_list;


}

//-----------
void list::add_song(song *new_song, char *type){


        song_node *new_node;



        playlist *traverse = last->next;  // head



        while(strcmp(traverse->name,type) != 0 && traverse != last){
            traverse = traverse->next;
        }


        if(traverse == last) {  // ismi bulamadi sonuncuyla ayni mi ?

            if(strncmp(traverse->name,type,strlen(type))==0){     // sonuncuyla ayniysa sonuncuya node ekle

            traverse->songnumber++;

            if(strcmp(type,"CHRONOLOGICAL")==0){        // CHRONOLOGICAL listesine gore ekle

            song_node *end_node = traverse->last;
            new_node = new song_node;
            new_node->data = new song;
            strcpy(new_node->data->name,new_song->name);
            strcpy(new_node->data->singer,new_song->singer);
            strcpy(new_node->data->style,new_song->style);
            new_node->data->year = new_song->year;
            new_node->parent = traverse;

             if(traverse->last == NULL){ //1

            traverse->last= new_node;
            traverse->last->next = new_node;
            traverse->last->prev = new_node;
            return;
          }

            song_node *traverse_node = traverse->last->next; // baslangici
            if(new_song->year < traverse_node->data->year) // CHRONOLOGICAL da basa ekle
            {
                traverse->last->next = new_node;
                new_node->next = traverse_node;
                traverse_node->prev = new_node;

                traverse->last->next = new_node;
                new_node->prev = traverse->last;


                return;
            }




            while(traverse_node->data->year < new_song->year  && traverse_node != end_node ) // sonuncusuna esit degilken
                 traverse_node = traverse_node->next;                                    //traverse_node bi sonrakini gosteriyor

            if(traverse_node == end_node){
                    if(traverse_node->data->year >= new_song->year ) // CHRONOLOGICAL da sona ekle
            {
                    end_node->next = new_node;
                    new_node->prev = end_node;
                    traverse->last = new_node;          // sonuncuya atandi


                return;
            }
            else{
                  new_node->next=end_node;
                new_node->prev = end_node->prev;
                end_node->prev->next = new_node;
                end_node->prev = new_node;

                return;

            }


            }
            else{       // araya ekle

                new_node->next=traverse_node;
                new_node->prev = traverse_node->prev;
                traverse_node->prev->next = new_node;
                traverse_node->prev = new_node;

                return;

            }
            }
            else if(strcmp(type,"SORTED")==0){ // SORTED listesine gore  ekle

            song_node *end_node = traverse->last;
            new_node = new song_node;
            new_node->data = new song;
            strcpy(new_node->data->name,new_song->name);
            strcpy(new_node->data->singer,new_song->singer);
            strcpy(new_node->data->style,new_song->style);
            new_node->data->year = new_song->year;
            new_node->parent = traverse;

             if(traverse->last == NULL){ //1

            traverse->last= new_node;
            traverse->last->next = new_node;
            traverse->last->prev = new_node;
            return;
          }

            song_node *traverse_node = traverse->last->next; // baslangici

            if(strcmp(new_song->singer,traverse_node->data->singer) < 0) // sorted da basa ekle
            {
                traverse->last->next = new_node;
                new_node->next = traverse_node;
                traverse_node->prev = new_node;

                traverse->last->next = new_node;
                new_node->prev = traverse->last;


                return;
            }




            while(strcmp(traverse_node->data->singer,new_song->singer ) < 0 && traverse_node != end_node ) // sonuncusuna esit degilken
                 traverse_node = traverse_node->next;                                    //traverse_node bi sonrakini gosteriyor

            if(traverse_node == end_node){
                    if(strcmp(new_song->singer,end_node->data->singer) > 0) // sorted da sona ekle
            {
                    end_node->next = new_node;
                    new_node->prev = end_node;
                    traverse->last = new_node;          // sonuncuya atandi


                return;
            }
            else{
                  new_node->next=end_node;
                new_node->prev = end_node->prev;
                end_node->prev->next = new_node;
                end_node->prev = new_node;

                return;

            }


            }
            else{       // araya ekle

                new_node->next=traverse_node;
                new_node->prev = traverse_node->prev;
                traverse_node->prev->next = new_node;
                traverse_node->prev = new_node;

                return;

            }

            }

            else{

                return;
            }



            }


        }
        else { // ismi buldu ve traverse o playlist i gosteriyor

            traverse->songnumber++;

            if(strcmp(type,"CHRONOLOGICAL")==0){


            song_node *end_node = traverse->last;
            new_node = new song_node;
            new_node->data = new song;
            strcpy(new_node->data->name,new_song->name);
            strcpy(new_node->data->singer,new_song->singer);
            strcpy(new_node->data->style,new_song->style);
            new_node->data->year = new_song->year;
            new_node->parent = traverse;

          if(traverse->last == NULL){ //1

            traverse->last= new_node;
            traverse->last->next = new_node;
            traverse->last->prev = new_node;
            return;
          }

          song_node *traverse_node = traverse->last->next; // baslangici
             if(traverse_node->data->year < new_song->year ) // CHRONOLOGICAL da basa ekle
            {
                traverse->last->next = new_node;
                new_node->next = traverse_node;
                traverse_node->prev = new_node;

                traverse->last->next = new_node;
                new_node->prev = traverse->last;


                return;
            }




            while(traverse_node->data->year < new_song->year && traverse_node != end_node ) // sonuncusuna esit degilken
                 traverse_node = traverse_node->next;                                    //traverse_node bi sonrakini gosteriyor

            if(traverse_node == end_node){
                    if(traverse_node->data->year < new_song->year ) // CHRONOLOGICAL da sona ekle
            {
                    end_node->next = new_node;
                    new_node->prev = end_node;
                    traverse->last = new_node;          // sonuncuya atandi

                    return;
            }
            else{           //sonuncudan bi onceki
                new_node->next=end_node;
                new_node->prev = end_node->prev;
                end_node->prev->next = new_node;
                end_node->prev = new_node;
                  return;

            }

            }
            else{       // araya ekle

                new_node->next=traverse_node;
                new_node->prev = traverse_node->prev;
                traverse_node->prev->next = new_node;
                traverse_node->prev = new_node;
                  return;
            }

            }
            else if(strcmp(type,"SORTED")==0){ // daha once var olan sorted list e ekle


            song_node *end_node = traverse->last;
            new_node = new song_node;
            new_node->data = new song;
            strcpy(new_node->data->name,new_song->name);
            strcpy(new_node->data->singer,new_song->singer);
            strcpy(new_node->data->style,new_song->style);
            new_node->data->year = new_song->year;
            new_node->parent = traverse;

            if(traverse->last == NULL){ //2

            traverse->last= new_node;
            traverse->last->next = new_node;
            traverse->last->prev = new_node;
            return;
          }

            song_node *traverse_node = traverse->last->next; // baslangici

             if(strcmp(traverse_node->data->singer,new_node->data->singer) < 0) // sorted da basa ekle
            {
                traverse->last->next = new_node;
                new_node->next = traverse_node;
                traverse_node->prev = new_node;

                new_node->prev = traverse->last;


                return;
            }




            while(strcmp(traverse_node->data->singer,new_song->singer ) < 0 && traverse_node != end_node ) // sonuncusuna esit degilken
                 traverse_node = traverse_node->next;                                    //traverse_node bi sonrakini gosteriyor

            if(traverse_node == end_node){
                    if(strcmp(new_song->singer,end_node->data->singer) > 0) // sorted da sona ekle
            {
                    end_node->next = new_node;
                    new_node->prev = end_node;
                    traverse->last = new_node;          // sonuncuya atandi

                    return;
            }
            else{           //sonuncudan bi onceki
                new_node->next=end_node;
                new_node->prev = end_node->prev;
                end_node->prev->next = new_node;
                end_node->prev = new_node;
                  return;

            }


            }
            else{       // araya ekle

                new_node->next=traverse_node;
                new_node->prev = traverse_node->prev;
                traverse_node->prev->next = new_node;
                traverse_node->prev = new_node;
                  return;
            }
            }
                else
                    return;


        }



}

//------------
void list::create(){
    playlist_count =0;
    last = NULL;



}
void list::close(){

playlist *traverse = last->next;
song_node *traverse_node;


while(traverse != last){

        traverse_node=traverse->last->next; // icindeki nodelarin basi
        while(traverse_node !=  traverse->last){
            delete traverse_node->data->name;
            delete traverse_node->data->singer;
            delete traverse_node->data->style;
            delete traverse_node->data;

            song_node *temp_node = traverse_node;
            traverse_node = traverse_node->next;
            delete temp_node;
        }
        if(traverse_node ==  traverse->last){
            delete traverse_node->data->name;
            delete traverse_node->data->singer;
            delete traverse_node->data->style;
            delete traverse_node->data;

            delete traverse_node;
        }
        delete traverse->name;
        playlist *temp_list = traverse;
        traverse= traverse->next;
        delete temp_list;


}
        if(traverse == last){
            traverse_node=traverse->last->next; // icindeki nodelarin basi
        while(traverse_node !=  traverse->last){
            delete traverse_node->data->name;
            delete traverse_node->data->singer;
            delete traverse_node->data->style;
            delete traverse_node->data;

            song_node *temp_node = traverse_node;
            traverse_node = traverse_node->next;
            delete temp_node;
        }
        if(traverse_node ==  traverse->last){
            delete traverse_node->data->name;
            delete traverse_node->data->singer;
            delete traverse_node->data->style;
            delete traverse_node->data;


            delete traverse_node;
        }
          delete traverse->name;
          delete traverse;  //sonuncu list de silindi

        }
        playlist_count = 0;
}

 void list::print(){


    playlist *traverse_list = last->next;
    song_node *traverse_node;
   // song_node *traverse_node = traverse_list->last->next;

    while(traverse_list != last){

    traverse_node = traverse_list->last->next;
    cout << "list name: " <<traverse_list->name << endl;
    while(traverse_node != traverse_list->last){
        cout << "song name: " << traverse_node->data->name << "  singer name:  " <<  traverse_node->data->singer << "  year:  " << traverse_node->data->year << "  style:  " << traverse_node->data->style << endl;
        traverse_node = traverse_node->next;

    }
     if(traverse_node == traverse_list->last)
           cout << "song name: " << traverse_node->data->name << "  singer name:  " <<  traverse_node->data->singer << "  year:  " << traverse_node->data->year << "  style:  " << traverse_node->data->style << endl;


    traverse_list= traverse_list->next;


    }

        traverse_list= last;
    if(traverse_list == last){
            traverse_node = traverse_list->last->next;
    cout << "list name: " <<traverse_list->name << endl;
        while(traverse_node != traverse_list->last){
        cout << "song name x: " << traverse_node->data->name << "  singer name:  " <<  traverse_node->data->singer << "  year:  " << traverse_node->data->year << "  style:  " << traverse_node->data->style << endl;
        traverse_node = traverse_node->next;

    }
    if(traverse_node == traverse_list->last)
        cout << "song name y: " << traverse_node->data->name << "  singer name:  " <<  traverse_node->data->singer << "  year:  " << traverse_node->data->year << "  style:  " << traverse_node->data->style << endl;


    }






 }

 void list::createRandomList(int songNum){

     playlist *temp= last->next;
     playlist *randomList;
     song_node * holdFirstListFirstSong = last->next->last->next;
     song_node *temp_node;
     song_node *new_node;
     song *temp_song;

     int i;
    int songList[songNum];
    for( i = 0 ; i< songNum ; i++)
        songList[i] = i;

    int randomnumber;
    srand( time( NULL ) ); // initializes the pseudo-random number generator

    shuffle(songList, songNum);



    if(strcmp(temp->name,"SORTED")==0 || strcmp(temp->name,"CHRONOLOGICAL")==0 )
    {
        for(i=0;i<songNum ; i++){

        temp_node= holdFirstListFirstSong; //ilk play list den sarkilar cekilecek

            for(int j=1;j< songList[i]  ; j++)
            temp_node = temp_node->next;



            if(i==0){

            temp_song = new song;
            strcpy(temp_song->name,temp_node->data->name);
            strcpy(temp_song->singer,temp_node->data->singer);
            strcpy(temp_song->style,temp_node->data->style);
            temp_song->year= temp_node->data->year;
            randomList = create_new_list(temp_song,"RANDOM");
            playlist_count++;
            playlist *holdhead = last->next;

            last->next = randomList;
            randomList->prev = last;

            last = randomList;

            last->next = holdhead;
            holdhead->prev = last;


            }

                else{

                new_node = new song_node;
                new_node->data = new song;
                strcpy(new_node->data->name,temp_node->data->name);
                strcpy(new_node->data->singer,temp_node->data->singer);
                strcpy(new_node->data->style,temp_node->data->style);
                new_node->data->year= temp_node->data->year;
                new_node->parent = randomList;

                song_node *hold_head = randomList->last->next;

                randomList->last->next = new_node;
                new_node->prev = randomList->last;

                randomList->last = new_node;
                new_node->next = hold_head;
                hold_head->prev = new_node;

                randomList->songnumber++;

                }



        }

    }
    else
        cout << "random list can not be created because there is no SORTED or CHRONOLOGICAL play list" << endl;





 }

 void list::shuffle(int *arr, size_t n)
{
    if (n > 1)
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}


void list::create_list_by_style(char *style)
{


    playlist *temp= last->next;
    for(int i=0 ; i< playlist_count; i++)
    {
        if(strcmp(temp->name,"SORTED")==0 || strcmp(temp->name,"CHRONOLOGICAL")==0 )
            break;
        else
            temp = temp->next;
    }


    if(strcmp(temp->name,"SORTED")==0 || strcmp(temp->name,"CHRONOLOGICAL")==0 ){

     playlist *style_list = new playlist;
     style_list->songnumber =0;
     style_list->last =NULL;
     style_list->prev =NULL;
     style_list->next=NULL;

     strcpy(style_list->name,style);
     song_node *traverse = temp->last->next;

     while(traverse != temp->last ){

        if(strcmp(traverse->data->style,style)==0){
                style_list->songnumber++;
            if(style_list->last == NULL){

            song_node *new_node = new song_node;
            new_node->parent = style_list;
            new_node->data = new song;

            strcpy(new_node->data->name,traverse->data->name);
            strcpy(new_node->data->singer,traverse->data->singer);
            strcpy(new_node->data->style,traverse->data->style);
            new_node->data->year = traverse->data->year;
            style_list->last = new_node;
            style_list->last->next = new_node;
            style_list->last->prev= new_node;

            }
            else{       // sona ekle

            song_node *new_node = new song_node;
            new_node->parent = style_list;
            new_node->data = new song;

            strcpy(new_node->data->name,traverse->data->name);
            strcpy(new_node->data->singer,traverse->data->singer);
            strcpy(new_node->data->style,traverse->data->style);
            new_node->data->year = traverse->data->year;

            song_node *hold_head = style_list->last->next;

            style_list->last->next = new_node;
            new_node->prev = style_list->last;
            new_node->next = hold_head;
            hold_head->prev = new_node;

            style_list->last = new_node;
            }


        }
        traverse = traverse->next;
     }
     if(traverse == temp->last){
        if(strcmp(traverse->data->style,style)==0){
                style_list->songnumber++;

             if(style_list->last == NULL){

            song_node *new_node = new song_node;
            new_node->parent = style_list;
            new_node->data = new song;

            strcpy(new_node->data->name,traverse->data->name);
            strcpy(new_node->data->singer,traverse->data->singer);
            strcpy(new_node->data->style,traverse->data->style);
            new_node->data->year = traverse->data->year;
            style_list->last = new_node;
            style_list->last->next = new_node;
            style_list->last->prev= new_node;

            }
            else{       // sona ekle

            song_node *new_node = new song_node;
            new_node->parent = style_list;
            new_node->data = new song;

            strcpy(new_node->data->name,traverse->data->name);
            strcpy(new_node->data->singer,traverse->data->singer);
            strcpy(new_node->data->style,traverse->data->style);
            new_node->data->year = traverse->data->year;

            song_node *hold_head = style_list->last->next;

            style_list->last->next = new_node;
            new_node->prev = style_list->last;
            new_node->next = hold_head;
            hold_head->prev = new_node;

            style_list->last = new_node;
            }
        }
     }
        if(style_list->songnumber ==0){
            cout << "there is no song like this style" << endl;
            delete style_list;
        }
        else{
            playlist_count++;
            playlist *holdheadoflists = last->next;
            last->next = style_list;
            style_list->prev= last;
            last = style_list;
            last->next = holdheadoflists;
            holdheadoflists->prev = last;
        }

    }
    else{
        cout << "because there is no SORTED or CHRONOLOGICAL play list in  lists you can not create style list " << endl;
        return;
    }



}




//------------------------------------------------------------------------------------------------
void list::create_list_by_singer(char *singer)
{




     playlist *temp= last->next;
    for(int i=0 ; i< playlist_count; i++)
    {
        if(strcmp(temp->name,"SORTED")==0 || strcmp(temp->name,"CHRONOLOGICAL")==0 )
            break;
        else
            temp = temp->next;
    }

    if(strcmp(temp->name,"SORTED")==0 || strcmp(temp->name,"CHRONOLOGICAL")==0 ){

     playlist *singer_list = new playlist;
     singer_list->songnumber =0;
     singer_list->last =NULL;
     singer_list->prev =NULL;
     singer_list->next=NULL;

     strcpy(singer_list->name,singer);
     song_node *traverse = temp->last->next;

     while(traverse != temp->last ){

        if(strcmp(traverse->data->singer,singer)==0){
                singer_list->songnumber++;
            if(singer_list->last == NULL){

            song_node *new_node = new song_node;
            new_node->parent = singer_list;
            new_node->data = new song;

            strcpy(new_node->data->name,traverse->data->name);
            strcpy(new_node->data->singer,traverse->data->singer);
            strcpy(new_node->data->style,traverse->data->style);
            new_node->data->year = traverse->data->year;
            singer_list->last = new_node;
            singer_list->last->next = new_node;
            singer_list->last->prev= new_node;

            }
            else{       // sona ekle

            song_node *new_node = new song_node;
            new_node->parent = singer_list;
            new_node->data = new song;

            strcpy(new_node->data->name,traverse->data->name);
            strcpy(new_node->data->singer,traverse->data->singer);
            strcpy(new_node->data->style,traverse->data->style);
            new_node->data->year = traverse->data->year;

            song_node *hold_head = singer_list->last->next;

            singer_list->last->next = new_node;
            new_node->prev = singer_list->last;
            new_node->next = hold_head;
            hold_head->prev = new_node;

            singer_list->last = new_node;
            }


        }
        traverse = traverse->next;
     }
     if(traverse == temp->last){
        if(strcmp(traverse->data->singer,singer)==0){
            singer_list->songnumber++;
             if(singer_list->last == NULL){

            song_node *new_node = new song_node;
            new_node->parent = singer_list;
            new_node->data = new song;

            strcpy(new_node->data->name,traverse->data->name);
            strcpy(new_node->data->singer,traverse->data->singer);
            strcpy(new_node->data->style,traverse->data->style);
            new_node->data->year = traverse->data->year;
            singer_list->last = new_node;
            singer_list->last->next = new_node;
            singer_list->last->prev= new_node;

            }
            else{       // sona ekle

            song_node *new_node = new song_node;
            new_node->parent = singer_list;
            new_node->data = new song;

            strcpy(new_node->data->name,traverse->data->name);
            strcpy(new_node->data->singer,traverse->data->singer);
            strcpy(new_node->data->style,traverse->data->style);
            new_node->data->year = traverse->data->year;

            song_node *hold_head = singer_list->last->next;

            singer_list->last->next = new_node;
            new_node->prev = singer_list->last;
            new_node->next = hold_head;
            hold_head->prev = new_node;

            singer_list->last = new_node;
            }
        }
     }
        if(singer_list->songnumber ==0){
            cout << "there is no song like this singer" << endl;
            delete singer_list;
        }
        else{
            playlist_count++;
            playlist *holdheadoflists = last->next;
            last->next = singer_list;
            singer_list->prev= last;
            last = singer_list;
            last->next = holdheadoflists;
            holdheadoflists->prev = last;
        }

    }
    else{
        cout << "because there is no SORTED or CHRONOLOGICAL play list in  lists you can not create singer list " << endl;
        return;
    }



}



void list::add_for_merged(playlist * will_merge , playlist *resource){

    song_node *hold_head_of_resource = resource->last->next;
    song_node *traverse_nodes = hold_head_of_resource;


    if(will_merge->last == NULL){       //merge list in ilk node u

            playlist *hold_head = last->next;
            last->next = will_merge;
            will_merge->prev = last;

            last = will_merge;
            last->next = hold_head;
            hold_head->prev = last;
            song_node *new_node = new song_node;
            new_node->parent = will_merge;
            new_node->data = new song;
            will_merge->songnumber++;
            strcpy(new_node->data->name,hold_head_of_resource->data->name);
            strcpy(new_node->data->singer,hold_head_of_resource->data->singer);
            strcpy(new_node->data->style,hold_head_of_resource->data->style);
            new_node->data->year = hold_head_of_resource->data->year;
            will_merge->last = new_node;
            will_merge->last->next = new_node;
            will_merge->last->prev= new_node;


               for(int i=1 ; i< resource->songnumber ; i++){

            traverse_nodes = traverse_nodes->next;

            song_node *new_node = new song_node;
            new_node->parent = will_merge;
            new_node->data = new song;
            will_merge->songnumber++;
            strcpy(new_node->data->name,traverse_nodes->data->name);
            strcpy(new_node->data->singer,traverse_nodes->data->singer);
            strcpy(new_node->data->style,traverse_nodes->data->style);
            new_node->data->year = traverse_nodes->data->year;

            song_node *hold_head = will_merge->last->next;

            will_merge->last->next = new_node;
            new_node->prev = will_merge->last;
            new_node->next = hold_head;
            hold_head->prev = new_node;

            will_merge->last = new_node;

            }

            }
            else{       // sonrakileri ekle
            for(int i=0 ; i< resource->songnumber ; i++){

            traverse_nodes = traverse_nodes->next;

            song_node *new_node = new song_node;
            new_node->parent = will_merge;
            new_node->data = new song;
            will_merge->songnumber++;
            strcpy(new_node->data->name,traverse_nodes->data->name);
            strcpy(new_node->data->singer,traverse_nodes->data->singer);
            strcpy(new_node->data->style,traverse_nodes->data->style);
            new_node->data->year = traverse_nodes->data->year;

            song_node *hold_head = will_merge->last->next;

            will_merge->last->next = new_node;
            new_node->prev = will_merge->last;
            new_node->next = hold_head;
            hold_head->prev = new_node;

            will_merge->last = new_node;

            }

            }


}

void list:: add_non_default_song(int index , char *list_name){


playlist *traverse = last->next;
playlist *traverse2 = last->next;
//song_node* traverse_nodes ;

    for(int i=0 ; i< playlist_count ; i++){
            if(strcmp(traverse->name,"SORTED") ==0)
                break;
            else
                traverse= traverse->next;

    }

    if(strcmp(traverse->name,"SORTED") ==0){


        for(int i=0 ; i< playlist_count ; i++){
            if(strcmp(traverse2->name,list_name) ==0)
                break;
            else
                traverse2= traverse2->next;
        }
        if(strcmp(traverse2->name,list_name) ==0 ){  //SORTED ve istenilen liste(RANDOM  disindakiler) bulunuyor ise ekle

            song_node *traverse_sorted = traverse->last->next;
              for(int i=1; i< index ; i++)                                          //traverse -> sorted i traverse2 de eklenecek list i gosteriyor
              traverse_sorted = traverse_sorted->next; // eklenilecek node a ulasildi

              if(strcmp(list_name,"SORTED") ==0   )
              {
                  song *new_song = new song;
                  strcpy(new_song->name,traverse_sorted->data->name);
                  strcpy(new_song->singer,traverse_sorted->data->singer);
                  strcpy(new_song->style,traverse_sorted->data->style);
                  new_song->year = traverse_sorted->data->year;
                  add_song(new_song,"SORTED");
                  cout << "aaaaa" << endl;
                  return;

              }
              else if( strcmp(list_name,"CHRONOLOGICAL") ==0){
                song *new_song = new song;
                  strcpy(new_song->name,traverse_sorted->data->name);
                  strcpy(new_song->singer,traverse_sorted->data->singer);
                  strcpy(new_song->style,traverse_sorted->data->style);
                  new_song->year = traverse_sorted->data->year;
                  add_song(new_song,"CHRONOLOGICAL");
                  cout << "aaaaa" << endl;
                  return;

              }
              else {//digerleri icin bi kural olmadigindan sonuna eklendi

           // song_node *add_to_last = traverse2->last;

            song_node *new_node = new song_node;
            new_node->parent = traverse2;
            new_node->data = new song;
            traverse2->songnumber++;
            strcpy(new_node->data->name,traverse_sorted->data->name);
            strcpy(new_node->data->singer,traverse_sorted->data->singer);
            strcpy(new_node->data->style,traverse_sorted->data->style);
            new_node->data->year = traverse_sorted->data->year;

            song_node *hold_head = traverse2->last->next;

            traverse2->last->next = new_node;
            new_node->prev = traverse2->last;
            new_node->next = hold_head;
            hold_head->prev = new_node;

            traverse2->last = new_node;
            traverse2->songnumber++;
            return;


              }

        }
        else
            return;

    }


    else{
        cout << "SORTED list can not be found" << endl;
        return;
    }

}



//-------------------------------------------------------------------------------------------------------------------------
void list:: delete_from_given_list(int index , playlist *ptr){


        song_node *traverse_nodes;

    if(index == 1)                                  //bastan sil
    {
            traverse_nodes = ptr->last->next;
            song_node *hold_second = traverse_nodes->next;
            ptr->last->next = hold_second;
            hold_second->prev = ptr->last;

            delete traverse_nodes->data->name;
            delete traverse_nodes->data->singer;
            delete traverse_nodes->data->style;
            delete traverse_nodes;
            ptr->songnumber--;
            return;
    }
    else if(index == ptr->songnumber)               // sondan sil
    {
        traverse_nodes = ptr->last->next;
        song_node *temp = ptr->last;
        song_node *hold_last_before = ptr->last->prev;
        hold_last_before->next = traverse_nodes;
        traverse_nodes->prev = hold_last_before;

        ptr->last = hold_last_before;

            delete temp->data->name;
            delete temp->data->singer;
            delete temp->data->style;
            delete temp;
            ptr->songnumber--;

        return;
    }
    else if(index > 1 && index <ptr->songnumber){                                           //aradan sil
            song_node *temp;
            traverse_nodes = ptr->last->next;
            for(int i=1 ; i< index ; i++)
                traverse_nodes = traverse_nodes->next; //silinecek olan traverse_nodes ile gosteriliyor


            traverse_nodes->prev->next= traverse_nodes->next;
            traverse_nodes->next->prev = traverse_nodes->prev;

            delete traverse_nodes->data->name;
            delete traverse_nodes->data->singer;
            delete traverse_nodes->data->style;
            delete traverse_nodes;
            ptr->songnumber--;
            return;  }
                                else
                                { cout << "invalid index " << endl;
                                    return;                             } }

//---------------------------------------------------------------------------------------------------------------
void list::delete_list(int control , playlist *ptr){

    playlist *traverse;
    playlist *temp;
    song_node * traverse_nodes;


    if(control == 1){           // ilk list i sil
        traverse = last->next;      //ilk list
        temp = traverse->next;      //ikinci list

        last->next = temp;
        temp->prev = last;          // traverse bosa cikti

        traverse_nodes = traverse->last->next;
        for(int i = 0 ; i < traverse->songnumber ; i++){
            delete traverse_nodes->data->name;
            delete traverse_nodes->data->singer;
            delete traverse_nodes->data->style;
            delete traverse_nodes;
            traverse_nodes = traverse_nodes->next;
        }
        delete traverse->name;
        delete traverse;
        playlist_count--;
        return;

    }
    else if (control == playlist_count){            // son list i sil
        playlist *hold = last;
        traverse = last->next;
        temp = traverse->prev;

        temp->next = traverse;
        traverse->prev = temp;

        last = temp;

        traverse_nodes = hold->last->next;
        for(int i = 0 ; i < hold->songnumber ; i++){
            delete traverse_nodes->data->name;
            delete traverse_nodes->data->singer;
            delete traverse_nodes->data->style;
            delete traverse_nodes;
            traverse_nodes = traverse_nodes->next;
        }
        delete hold->name;
        delete hold;
        playlist_count--;
        return;



    }
    else{                                       // aradan sil

        traverse = last->next;
        for(int i = 1 ; i < control ; i++)
            traverse = traverse->next;  //traverse silinecek list i gosteriyor

            traverse->prev->next = traverse->next;
            traverse->next->prev = traverse->prev;


            traverse_nodes = traverse->last->next;
        for(int i = 0 ; i < traverse->songnumber ; i++){
            delete traverse_nodes->data->name;
            delete traverse_nodes->data->singer;
            delete traverse_nodes->data->style;
            delete traverse_nodes;
            traverse_nodes = traverse_nodes->next;
        }
        delete traverse->name;
        delete traverse;
        playlist_count--;
        return;


    }

}

void list::write() {

    playlist *traverse;
    traverse = last->next;
    song_node *traverse_node;
    file_ptr = fopen("songbook.txt","w" );
    fclose(file_ptr);


    ofstream myfile;
    myfile.open ("songbook.txt");

    for(int i=0 ; i<playlist_count; i++ )
    {
        if(strcmp(traverse->name,"CHRONOLOGICAL") ==0)
            break;
        else
            traverse= traverse->next;
    }
    if(strcmp(traverse->name,"CHRONOLOGICAL") ==0){
            traverse_node = traverse->last->next;
        for(int i=0;i<traverse->songnumber;i++){
            myfile << traverse_node->data->name << '\t' << traverse_node->data->singer << '\t' << traverse_node->data->year << '\t' << traverse_node->data->style << '\n' ;
            traverse_node= traverse_node->next;
        }
    }
    traverse = last->next;
    for(int i=0 ; i< playlist_count ; i++){
       if(strcmp(traverse->name,"CHRONOLOGICAL") !=0 && strcmp(traverse->name,"SORTED") !=0 && strcmp(traverse->name,"RANDOM") !=0){
        traverse_node = traverse->last->next;
        myfile << "*****" << '\n';
        myfile << traverse->name << '\n';
        for(int i=0;i<traverse->songnumber;i++){
        if(i < traverse->songnumber-1)
        myfile << traverse_node->data->name << '\t' << traverse_node->data->singer << '\t' << traverse_node->data->year << '\t' << traverse_node->data->style << '\n' ;
        else if(i == traverse->songnumber-1)
            myfile << traverse_node->data->name << '\t' << traverse_node->data->singer << '\t' << traverse_node->data->year << '\t' << traverse_node->data->style;
        traverse_node = traverse_node->next;
        }
       }
       traverse = traverse->next;
    }

myfile.close();


}

void list::create_list(char *list_name){
    playlist *hold_head = last->next;
    playlist *new_list = new playlist;
    strcpy(new_list->name,list_name);
    new_list->songnumber =0;
    new_list->last = NULL;
    new_list->next = NULL;
    new_list->prev = NULL;
    playlist_count++;

    if(last != NULL){
    last->next = new_list;
    new_list->prev = last;

    last = new_list;

    last->next = hold_head;
    hold_head->prev = last;


    return;
    }




}
void list::add_to_list(char *list_name, song *add){

    song_node *new_node = new song_node;
    new_node->data = new song;
    strcpy(new_node->data->name,add->name);
    strcpy(new_node->data->singer,add->singer);
    strcpy(new_node->data->style,add->style);
    new_node->data->year = add->year;
    playlist *traverse;
    traverse = last->next;


    for(int i=0; i< playlist_count ; i++)
    {
        if(strcmp(traverse->name,list_name) == 0 )
            break;
        else
            traverse = traverse->next;
    }
    new_node->parent = traverse;


    if(traverse->last == NULL){

    traverse->last = new_node;
    traverse->last->next= new_node;
    traverse->last->prev = new_node;
    traverse->songnumber++;
    return;
    }
    else {
    song_node *hold_head_node = traverse->last->next;

    traverse->last->next = new_node;
    new_node->prev = traverse->last;

    traverse->last = new_node;

    traverse->last->next = hold_head_node;
    hold_head_node->prev = traverse->last;

    traverse->songnumber++;
    return;
    }

}

//--------------------------------

void list::create_list_for_default(char *list_name){

    playlist *new_list = new playlist;
    strcpy(new_list->name,list_name);
    new_list->songnumber =0;
    new_list->last = NULL;
    new_list->next = NULL;
    new_list->prev = NULL;
    playlist_count++;

    if(last == NULL){
        last= new_list;
        last->next = new_list;
        last->prev = new_list;

    }
    else if(last != NULL){
            playlist *hold_head = last->next;
    last->next = new_list;
    new_list->prev = last;

    last = new_list;

    last->next = hold_head;
    hold_head->prev = last;


    return;
    }

}
//----------------------------------



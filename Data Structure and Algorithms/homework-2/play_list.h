#define LNAME_LENGTH 50
#include "Node.h"
struct playlist {
  int songnumber;
  char* name = new char[LNAME_LENGTH];
  //song_node* head;
  song_node *last;
  playlist* next;
  playlist* prev;
};


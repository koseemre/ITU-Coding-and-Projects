#include "Song.h"
//#include "play_list.h"
struct playlist;
struct song_node {
  song* data;
  song_node* next;
  song_node* prev;
  playlist* parent;
};


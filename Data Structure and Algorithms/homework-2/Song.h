#ifndef SONG_H
#define SONG_H

#define SNAME_LENGTH 50
#define STYLE_LENGTH 30
#define SINGER_LENGTH 50


struct song {
  char* name   = new char[SNAME_LENGTH];
  char* singer = new char[SINGER_LENGTH];
  char* style  = new char[STYLE_LENGTH];
  int year;
};

#endif // SONG_H

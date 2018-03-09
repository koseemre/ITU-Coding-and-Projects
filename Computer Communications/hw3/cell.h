#ifndef CELL_H
#define CELL_H

struct cell{


    int control;
    int sending_time[15];
    int time[15];
    char sender[15],receiver[15];
    int row_num,column_num;

}typedef c;
#endif

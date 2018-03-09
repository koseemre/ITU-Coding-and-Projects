#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "station.h"
#include "transmission.h"
#include "cell.h"




int find_index(char c , s *st , int station_number){

int i;
int hold=0;
 for(i=0;i<station_number;i++){

    if(c == st[i].station_name)
        hold = i;
 }

return hold;

}

void calculate_end_time_for_transmission_Of_Station(char sender, s *st,int station_number,t *tr,int i){
    int index = find_index(sender,st,station_number);
    tr[i].end_time_of_emitting = st[index].range + tr[i].start_time-1;


}


void oor(t *transmissions ,int index,FILE *linkfile){

    fputs("OOR:", linkfile);
    fputc(transmissions[index].sender, linkfile);
    fputs("=>", linkfile);
    fputc(transmissions[index].receiver, linkfile);
    fprintf(linkfile, "(%d,%d)\n", transmissions[index].start_time,transmissions[index].end_time_of_emitting);
    printf("oor %c => %c (%d,%d)\n",transmissions[index].sender,transmissions[index].receiver,transmissions[index].start_time, transmissions[index].end_time_of_emitting );

 }


 void send_to_cell(t *transmissions, int index, int real_time, c **cells,s *stations,int station_number){

    int index_target = find_index(transmissions[index].receiver,stations,station_number);
    int row = stations[index_target].origin_row -1 ;
    int column = stations[index_target].origin_column -1 ;

    cells[row][column].sender[cells[row][column].control] = transmissions[index].sender;
    cells[row][column].receiver[cells[row][column].control] = transmissions[index].receiver;
    cells[row][column].time[cells[row][column].control] = real_time;
    cells[row][column].sending_time[cells[row][column].control] = transmissions[index].start_time;
    printf("control: %d-%d%d\n",cells[row][column].control,row,column);
    cells[row][column].control++;

 }


void control_target(int index,t *transmissions , int real_time, s *stations, int station_number, int N ,c **cells,FILE *linkfile){



    int index_of_sender = find_index(transmissions[index].sender,stations,station_number);
    int index_of_receiver = find_index(transmissions[index].receiver,stations,station_number);
    int in_row1,in_row2,in_column1,in_column2;

    // finds the estimated coordinates of transmission
    if((stations[index_of_sender].origin_row - transmissions[index].reach_target_time)  > 0 )
        in_row1 = stations[index_of_sender].origin_row - transmissions[index].reach_target_time;
    else
        in_row1= -1;

    if((stations[index_of_sender].origin_row + transmissions[index].reach_target_time)  <=  N )
        in_row2 = stations[index_of_sender].origin_row + transmissions[index].reach_target_time;
    else
        in_row2= -1;

      if((stations[index_of_sender].origin_column - transmissions[index].reach_target_time)  > 0 )
        in_column1 = stations[index_of_sender].origin_column - transmissions[index].reach_target_time;
    else
        in_column1= -1;

    if((stations[index_of_sender].origin_column + transmissions[index].reach_target_time)  <=  N )
        in_column2 = stations[index_of_sender].origin_column + transmissions[index].reach_target_time;
    else
        in_column2= -1;
    printf("ins: %d %d %d %d \n", in_column1,in_column2,in_row1,in_row2);



    if(  stations[index_of_sender].range < transmissions[index].duration) // OOR
    {
        oor(transmissions,index,linkfile);
        transmissions[index].is_end =1;
         printf("transmission %d is finished\n",index);
    }
    else if(transmissions[index].reach_target_time == real_time) // collision or success, it will be controlled in control_cells() function
    {


                send_to_cell(transmissions,index,real_time,cells,stations,station_number);
                transmissions[index].is_end =1;
                }
            else if(transmissions[index].end_time_of_emitting > real_time && transmissions[index].reach_target_time < real_time)
                printf("still propagate after collision or success \n");



}



void progress(t *transmissions, int real_time,int index_of_transmission , s *stations , int station_number,int N, c **cells,FILE *linkfile){

    if(transmissions[index_of_transmission].is_end  !=  1 ){

        if(transmissions[index_of_transmission].start_time == real_time){
            transmissions[index_of_transmission].is_start =1;
            transmissions[index_of_transmission].current_time = real_time;
            control_target(index_of_transmission,transmissions,real_time,stations,station_number,N,cells,linkfile);
           // if(transmissions[index_of_transmission].current_time == transmissions[index_of_transmission].end_time_of_emitting)
              //      transmissions[index_of_transmission].is_end = 1;
        }
        else if(real_time <= transmissions[index_of_transmission].end_time_of_emitting && transmissions[index_of_transmission].current_time >0   && transmissions[index_of_transmission].is_start ==1 ){

                 transmissions[index_of_transmission].current_time = real_time;
                 control_target(index_of_transmission,transmissions,real_time,stations,station_number,N,cells,linkfile);
               //  if(transmissions[index_of_transmission].current_time == transmissions[index_of_transmission].end_time_of_emitting)
                   // transmissions[index_of_transmission].is_end = 1;

        }

    }
//    else if(transmissions[index_of_transmission].is_end  ==  1)
//    {
//        printf("transmission %d is finished\n",index_of_transmission);
//    }


}






 void control_cells(c **cells,int N,FILE *linkfile){

 int i,j,k,l;
 int hold,hold2=-1;
     for(i=0 ; i< N; i++)
        for(j=0;j<N;j++){

    if(cells[i][j].control == 1){
         printf("success: %c,%c   =>  (%d,%d)\n",cells[i][j].sender[0],cells[i][j].receiver[0],cells[i][j].sending_time[0],cells[i][j].time[0]);

    fputs("SUCCESS:", linkfile);
    fputc(cells[i][j].sender[0], linkfile);
    fputs("=>", linkfile);
    fputc(cells[i][j].receiver[0], linkfile);
    fprintf(linkfile, " (%d,%d)\n", cells[i][j].sending_time[0],cells[i][j].time[0]);

    }

         else if(cells[i][j].control>=2)
        for(k=0 ; k<cells[i][j].control;k++){
                        for(l=0;l<cells[i][j].control;l++){
                hold=k;
                if(cells[i][j].time[k] == cells[i][j].time[l] && k != l)
                    hold2++;
            }
            if(hold2 == -1)
                fprintf(linkfile,"SUCCESS:%c=>%c (%d,%d)\n",cells[i][j].sender[k],cells[i][j].receiver[k],cells[i][j].sending_time[k],cells[i][j].time[k]);
            else
                fprintf(linkfile,"COLLISION:%c=>%c (%d,%d)\n",cells[i][j].sender[k],cells[i][j].receiver[k],cells[i][j].sending_time[k],cells[i][j].time[k]);
            hold2=-1;
        }

        }

    }


//---------------------------------MAIN STARTS HERE ----------------------------------------------------------------------------------------
int main(int argc , char *argv[])
{
    if(argc ==2){
            int N, hold_value ;
    char line[255];
    FILE *fptr;
    char *pch;
    int counter=0;
    int counter2 =0;
    int count_stations =0;



    N = atoi(argv[1]);

    printf("nn :%d",N);
    fptr = fopen("stations.txt", "r");
    while(fgets(line, 255, fptr)) //learning how many stations are there in the stations.txt file
    counter++;
    fclose(fptr);


    fptr = fopen("stations.txt", "r");
    s stations[counter];


     while(fgets(line, 255, fptr)){
        printf("strlen : %d\n",strlen(line));
        pch = strtok (line," ");
        while (pch != NULL)
  {
        if(counter2 ==0)
        {
            stations[count_stations].station_name = pch[0];

        }
        else if(counter2 == 1){

            hold_value = atoi(pch);
            stations[count_stations].origin_row = hold_value;
        }
        else if(counter2 == 2){
            hold_value = atoi(pch);
            stations[count_stations].origin_column = hold_value;
        }
        else{

            hold_value = atoi(pch);
            stations[count_stations].range = hold_value;
        }
        counter2++;

       pch = strtok (NULL, " ");
  }
        count_stations++;
        counter2 =0;
    }

     //calculating coverage limits of stations
    int i;
    for(i=0; i< counter ; i++)
       {
           if(stations[i].origin_row + stations[i].range <= N )
                stations[i].end_ranged_rows = stations[i].origin_row + stations[i].range;
           else
            stations[i].end_ranged_rows = N;

           if(stations[i].origin_column + stations[i].range <= N )
                stations[i].end_ranged_columns = stations[i].origin_column + stations[i].range;
           else
            stations[i].end_ranged_columns = N;

             if(stations[i].origin_row - stations[i].range >= 1 )
                stations[i].start_ranged_rows = stations[i].origin_row - stations[i].range;
             else
             stations[i].start_ranged_rows = 1;

              if(stations[i].origin_column - stations[i].range >= 1 )
                stations[i].start_ranged_columns = stations[i].origin_column - stations[i].range;
             else
             stations[i].start_ranged_columns = 1;

       }

        for(i=0; i< counter ; i++){
        printf("column:  %d-%d ,row:  %d-%d \n",stations[i].start_ranged_columns, stations[i].end_ranged_columns,stations[i].start_ranged_rows,stations[i].end_ranged_rows);

        }
        //so far , stations.txt file is read and struct station array is created which has number of 'count_stations'.
        //so , transmissions.txt file will be read now.
        char line2[255];
        int counter3=0;
        FILE *fptr2;

        fptr2 = fopen("transmissions.txt", "r");

        while(fgets(line2, 255, fptr2)) //learning how many transmissions are there in the transmissions.txt file
        counter3++;
        fclose(fptr2);
        t transmissions[counter3];

        fptr2 = fopen("transmissions.txt", "r");
        counter2=0;
        int count_transmissions =0,first_time_of_all_transmissions,last_time_of_all_transmissions;

           while(fgets(line2, 255, fptr2)){

        pch = strtok (line2," ");
        while (pch != NULL)
  {
        if(counter2 == 0)
        {
             transmissions[count_transmissions].sender = pch[0];

        }

        else if(counter2 == 1)
            transmissions[count_transmissions].receiver = pch[0];
        else {
            hold_value = atoi(pch);
            transmissions[count_transmissions].start_time = hold_value;
        }
        counter2++;

       pch = strtok (NULL, " ");
  }
        if(count_transmissions == 0){
            first_time_of_all_transmissions = transmissions[count_transmissions].start_time;
            last_time_of_all_transmissions   = transmissions[count_transmissions].start_time;  }

        if(count_transmissions > 0){  // in there first and last transmission time is found
                if(transmissions[count_transmissions].start_time<first_time_of_all_transmissions)
                    first_time_of_all_transmissions = transmissions[count_transmissions].start_time;
                if(transmissions[count_transmissions].start_time>last_time_of_all_transmissions)
                    last_time_of_all_transmissions = transmissions[count_transmissions].start_time;
        }

        count_transmissions++;
        counter2 =0;
    }

    fclose(fptr2);
    int the_last_start = transmissions[0].start_time;

    int the_max_ending_emission_time;
    for(i=0; i < counter3 ; i++){
         //   printf("sender: %c,receiver: %c,start time: %d \n",transmissions[i].sender,transmissions[i].receiver,transmissions[i].start_time);
            if(transmissions[i].start_time  > the_last_start)
                the_last_start = transmissions[i].start_time;

    }
    the_max_ending_emission_time = the_last_start + N - 1;


    printf("all first :%d,all last :  %d",first_time_of_all_transmissions,last_time_of_all_transmissions);

    int index,index2,row_distance,column_distance;
    for(i=0;i<counter3;i++){

       index = find_index(transmissions[i].sender,stations,counter);
       index2 = find_index(transmissions[i].receiver,stations,counter);

       if(stations[index].origin_row >= stations[index2].origin_row)
            row_distance = stations[index].origin_row - stations[index2].origin_row;
       else
            row_distance =  stations[index2].origin_row-stations[index].origin_row;

       if(stations[index].origin_column >= stations[index2].origin_column)
            column_distance = stations[index].origin_column - stations[index2].origin_column;
       else
            column_distance =  stations[index2].origin_column-stations[index].origin_column;



        if(row_distance > column_distance)
            transmissions[i].duration =row_distance;
        else
            transmissions[i].duration =column_distance;

    }




     for(i=0; i < counter3 ; i++)
        printf("duration: %d\n",transmissions[i].duration);

     for(i=0; i < counter3 ; i++){
        calculate_end_time_for_transmission_Of_Station(transmissions[i].sender, stations,counter,transmissions,i);
        transmissions[i].reach_target_time =transmissions[i].start_time + transmissions[i].duration-1;
     }


     for(i=0; i < counter3 ; i++)
        printf("end_times: %d\n",transmissions[i].reach_target_time);






    c** cells = malloc (sizeof(c)*N);
    for(i = 0; i < N; ++i)
    cells[i] = malloc (sizeof(c)*N);

    c **traverse = cells;
    int p,l;


for(p =0; p<N; p++){
    for(i =0; i<N; i++){
        traverse[p][i].row_num = p+1;
        traverse[p][i].column_num = i+1;
        traverse[p][i].control = 0;
        for(l=1;l<16;l++)
            traverse[p][i].time[l] = -l;
    }

}


    for(p =0; p<N; p++){
    for(i =0; i<N; i++)
      printf("start: %d , %d , %d\n",traverse[p][i].row_num,traverse[p][i].column_num,traverse[p][i].control);

}



       for(i=0; i < counter3 ; i++){
        printf("duration: %d\n",transmissions[i].duration);
        transmissions[i].is_start=0;
        transmissions[i].is_end=0;
       }

          FILE *linkfile;
         linkfile = fopen("150130037.txt", "w");

        int real_time;
        for(real_time=1; real_time< the_max_ending_emission_time;real_time++){
        for(i=0;i<counter3 ;i++)                                                //counter3 is the number of transmissions
            progress(transmissions,real_time,i,stations,counter,N,cells,linkfile);

        }

         control_cells(cells,N,linkfile);





         for(i = 0; i < N; ++i)   //deallocations of cells struct  array
            free(cells[i]);

            free(cells);

    fclose(linkfile);
    return 0;
    }
    else
    {
        printf("argument fault\n");
    }


}

/*
Name: Emre
Surname: KÖSE
Student ID:150130037
Development Environment: Code::Blocks 16.01
*/
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

char *decimal_to_binary(int);

int main(int argc , char *argv[]){

if(argc == 3){


int i;
int frame_sayac = 0;
double ber = atof(argv[2]);
int calculatedRange=2;

FILE *data_file;
FILE *linkfile;
FILE *sent_frames_file;
FILE *receiver_file;
FILE *rcvd_frames_file;



 time_t t;
 srand((unsigned) time(&t));


//-------BER range belirleme -------------------------------------------------------------

 if( ber >= 0.0001 && ber < 0.001)
    calculatedRange = 10000;
 else if (ber >= 0.001 && ber < 0.01)
    calculatedRange = 1000;
    else if(ber == 0.01)
        calculatedRange = 100;
    else
    calculatedRange = 2;

 printf("cal_range: %d\n",calculatedRange);


 if(calculatedRange < 100)
    ber = 0.0;
 else
 ber = ber * calculatedRange;





    int c;
    int control=1;
    char frameData[8];
    char *pointer;              //once 10 luk tabanda azaltiliyor sonra o da decimal_to_binary fonksiyonu nu ile binary ye cevriliyor
    char frameSequence[8];

    data_file = fopen(argv[1], "r");

    sent_frames_file = fopen("150130037_sent_frames.txt","w");
    linkfile = fopen("150130037_NRZ_L.txt", "w");

     if(data_file == NULL)
   {
      perror("Error in opening file");
      return(-1);
   }
   else
    fputc('|', linkfile);

    int j=0;

   do
   {
       c = fgetc(data_file);
       frameData[j] = c;
        j++;

       if( feof(data_file) || c == '\0')
      {
         break ;
      }




      if(control%7 == 0){       //frame olusturma
        fputc('|', sent_frames_file);


         pointer = decimal_to_binary(frame_sayac);

        int parity_kontrol=0;
         for( i=0;i<8;i++){
            if(pointer[i] == '1')
                parity_kontrol++;
         }


         frame_sayac++;

         for(i=0;i<7;i++){

            if(frameData[i] == '1')
                parity_kontrol++;
}
        char parity;
        if(parity_kontrol%2 ==0)
         parity = '0';
         else
            parity = '1';

      for( i=0;i<8;i++){
        int range;
           range  =  rand() % calculatedRange;


            if((float)range < ber )
            {
                if(pointer[i]=='0'){
                    printf("error occured\n");
                    fputc('1' ,sent_frames_file);
                    pointer[i] = '1';
                }

                else
                {   printf("error occured\n");
                    fputc('0' ,sent_frames_file);
                    pointer[i] = '0';
                }


            }
            else
            fputc(pointer[i] ,sent_frames_file);


         }
            fputc('|', sent_frames_file);
            for(i=0;i<7;i++){
                      int range2;
                      range2 =  rand() % calculatedRange;


                            if((float)range2 < ber )        // olasilik hesaplamasi
                            {
                                if(frameData[i]=='0'){
                                    printf("error occured\n");
                                    fputc('1' ,sent_frames_file);
                                    frameData[i] = '1';
                                }

                                else{
                                    printf("error occured\n");
                                    fputc('0' ,sent_frames_file);
                                     frameData[i] = '0';
                                }


                            }
                                    else
                                    fputc(frameData[i] ,sent_frames_file);
            }

                      int range3;
                      range3 =  rand() % calculatedRange;


                            if((float)range3 < ber ){  // parity biti de hata olasiligina katiliyor
                                if(parity == '1')
                                {
                                    parity = '0';
                                     fputc(parity, sent_frames_file);
                                }
                                 else
                                {
                                    parity = '1';
                                    fputc(parity, sent_frames_file);
                                }
                            }
                            else
                                fputc(parity, sent_frames_file);

                    fputc('|', sent_frames_file);
                    fputc('\n', sent_frames_file);


                     //frameler olusurken ayni anda birer frameden NRZ-L coding ile link_file olusturuluyor

           for( i=0;i<8;i++){

         if(frame_sayac > 1 && i ==0)
           fputc('|', linkfile);

            if(pointer[i] == '0'){
                fputc('P', linkfile);
                fputc('|', linkfile);
            }
            else{
                fputc('N', linkfile);
                fputc('|', linkfile);
            }

         }
          for(i=0;i<7;i++){

            if(frameData[i] == '0'){
                fputc('P', linkfile);
                fputc('|', linkfile);
            }
            else{
                fputc('N', linkfile);
                fputc('|', linkfile);
            }
          }

          if(parity == '0'){
            fputc('P', linkfile);
            fputc('|', linkfile);
          }

          else{
              fputc('N', linkfile);
              fputc('|', linkfile);
          }
          fputc('\n', linkfile);

        free(pointer);
        if(frame_sayac == 256)      //255 frame gonderildiginde basa don ve gondermeye devam et
            frame_sayac=0;

        control =0;
        j=0;
      }

        control++;
      printf("%c", c);
   }while(1);



        fclose(data_file);
        fclose(sent_frames_file);
        fclose(linkfile);

        linkfile = fopen("150130037_NRZ_L.txt", "r");
        receiver_file = fopen("150130037_rcv_data.txt","w");
        rcvd_frames_file = fopen("150130037_rcvd_frames.txt","w");



        int d;
        int frame_to_data_control = 0;
        int number_of_ones = 0;
        char hold_frame[16];


   do
   {
      d = fgetc(linkfile);
   if(d == 'N'){
     hold_frame[frame_to_data_control] = '1';
     if(frame_to_data_control != 15)
     number_of_ones++;
   }
   else if(d == 'P')
        hold_frame[frame_to_data_control] = '0';




if(d == 'P' || d == 'N')                    // '|' karakteri disindakiler kactane var ?
      frame_to_data_control++;


      if(frame_to_data_control == 16){
        fputc('|', rcvd_frames_file);
        if(number_of_ones % 2 ==0 && hold_frame[15] == '0')  //parity bit kontrolu => TRUE
        {
            for(i = 8;i<15;i++)
                fputc(hold_frame[i], receiver_file);
            for(i=0;i<8;i++)
                   fputc(hold_frame[i], rcvd_frames_file);
                   fputc('|', rcvd_frames_file);
             for(i=8;i<16;i++)
                   fputc(hold_frame[i], rcvd_frames_file);
                   fputc('|', rcvd_frames_file);
                   fputc('\n', rcvd_frames_file);

        }
        else if(number_of_ones % 2 ==0 && hold_frame[15] == '1'){  //parity bit kontrolu => FALSE
             printf("parity bit error");
              printf("\n");
               for(i=0;i<8;i++)
                   fputc(hold_frame[i], rcvd_frames_file);
                   fputc('|', rcvd_frames_file);
                for(i=8;i<16;i++)
                   fputc(hold_frame[i], rcvd_frames_file);
                   fputc('|', rcvd_frames_file);
                   fputc('P', rcvd_frames_file);
                   fputc('E', rcvd_frames_file);
                   fputc('\n', rcvd_frames_file);
        }
        else if(number_of_ones % 2 == 1  && hold_frame[15] == '1'){ //parity bit kontrolu => TRUE
            for(i = 8;i<15;i++)
                fputc(hold_frame[i], receiver_file);
                   for(i=0;i<8;i++)
                       fputc(hold_frame[i], rcvd_frames_file);

                           fputc('|', rcvd_frames_file);
                    for(i=8;i<16;i++)
                       fputc(hold_frame[i], rcvd_frames_file);

                           fputc('|', rcvd_frames_file);
                           fputc('\n', rcvd_frames_file);
        }
        else if(number_of_ones % 2 ==1  && hold_frame[15] == '0'){ //parity bit kontrolu => FALSE
              printf("parity bit error");
              printf("\n");
                 for(i=0;i<8;i++)
                   fputc(hold_frame[i], rcvd_frames_file);
                   fputc('|', rcvd_frames_file);
                for(i=8;i<16;i++)
                   fputc(hold_frame[i], rcvd_frames_file);
                   fputc('|', rcvd_frames_file);
                   fputc('P', rcvd_frames_file);
                   fputc('E', rcvd_frames_file);
                   fputc('\n', rcvd_frames_file);


        }



        frame_to_data_control = 0 ;
        number_of_ones =0;
      }


         if( feof(linkfile))
      {
         break ;
      }

   }while(1);


        fclose(receiver_file);
        fclose(linkfile);
        fclose(rcvd_frames_file);


}
        else{
            printf("too many or too less parameter  \n");
        }


        return 0;
}

char *decimal_to_binary(int n)  // decimal olarak artirilan sayi binary ye cevriliyor
{
   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(8+1);

   if ( pointer == NULL )
      exit(EXIT_FAILURE);

   for ( c = 7 ; c >= 0 ; c-- )
   {
      d = n >> c;

      if ( d & 1 )
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';

      count++;
   }
   *(pointer+count) = '\0';

   return  pointer;
}


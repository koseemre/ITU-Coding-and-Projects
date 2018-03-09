/*
Name: Emre
Surname: KÖSE
Student ID:150130037
Development Environment: Code::Blocks 16.01
*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main(int argc , char *argv[]){


int i;
char line[255];
char line2[255];
FILE *Inputfile;
FILE *encoderFile;
FILE *link;
FILE *decoderFile;


if(argc > 1){
    Inputfile = fopen(argv[1], "r");

fgets(line, 255, Inputfile);
for( i=0;line[i] != '\0' ; i++ )
printf("%c ", line[i]);
printf("\n");
fclose(Inputfile);

}






if(argc > 1)
if(strcmp(argv[3],"NRZ_L" ) == 0 ){


    printf("your selection is %s\n",argv[3]);
    encoderFile = fopen("150130037_NRZ_L.txt", "w");
    int j;
    fputc('|', encoderFile);

        for(j=0; line[j] != '\0' ; j++ ){
            if(line[j] == '0'){
                fputc('P', encoderFile);
                fputc('|', encoderFile);
            }
            else{
                fputc('N', encoderFile);
                fputc('|', encoderFile);
            }

        }

fclose(encoderFile);//buraya kadar encode edildi simdi link ile decode edilerek receiver_file_name olusturulacak
link = fopen("150130037_NRZ_L.txt", "r");
fgets(line2,255,link);
fclose(link);




decoderFile = fopen(argv[2],"w");

for(j=0; line2[j] != '\0' ; j++ ){

    if(line2[j] == 'N')
        fputc('1', decoderFile);
    if(line2[j] == 'P')
        fputc('0', decoderFile);

}



fclose(decoderFile);

}
else if(strcmp(argv[3],"NRZ_I" ) == 0){

        printf("your selection is %s\n",argv[3]);
        encoderFile = fopen("150130037_NRZ_I.txt", "w");

char blackWhite[255];

if(line[0] == '1')
    blackWhite[0] = 'N';
else
    blackWhite[0] = 'P';

    // GERI KALANLAR ICIN SIYAH YA DA BEYAZ ANLAMINDA 'b' ya da 'w' koyuldu  Pbwwbb olacak
for(i=1; line[i] != '\0'; i++)
if(line[i] == '1')
    blackWhite[i] = 'b';
else
    blackWhite[i] = 'w';
    blackWhite[i] = '\0';




for(i=0;blackWhite[i]!= '\0' ; i++){
    if(blackWhite[i+1] == 'b')
{
    if(blackWhite[i] == 'N')
    blackWhite[i+1] = 'P';
        else
        blackWhite[i+1] = 'N';
}
else if(blackWhite[i+1] == 'w'){
    if(blackWhite[i] == 'N')
    blackWhite[i+1] = 'N';
            else
            blackWhite[i+1] = 'P';

}
}
// BURAYA KADAR YINE BLACK AND WHITE DIZISININ ICINE P VE N CINSINDEN KODLAMA YAPILDI
//SIMDI BUNLAR '|' EKLENEREK DOSYAYA YAZILACAK
fputc('|', encoderFile);

for(i=0;blackWhite[i] != '\0' ; i++)
{
    fputc(blackWhite[i], encoderFile);
    fputc('|', encoderFile);
}
fclose(encoderFile); // encoder yapilarak dosyaya yazildi simdi link uzerinden receiver_file_name.txt dosyasina decode edilerek yazilacak

link = fopen("150130037_NRZ_I.txt", "r");
fgets(line2,255,link);
fclose(link);

decoderFile = fopen(argv[2],"w");
for(i=0; line2[i] != '\0' ; i++){
        if(i == 1 ){
                if(line2[1] == 'P')
                  fputc('0',decoderFile);
                        else
                         fputc('1',decoderFile);
        }
                if(i>1 && i%2 ==1 )
                {
                    if(line2[i] == line2[i-2])
                        fputc('0',decoderFile);
                    else
                        fputc('1',decoderFile);

                }

}



fclose(decoderFile);

}
else if(strcmp(argv[3],"MANCH" ) == 0){
        int j;
        printf("your selection is %s\n",argv[3]);
        encoderFile = fopen("150130037_MANCH.txt", "w");

fputc('|', encoderFile);
for(j=0; line[j] != '\0' ; j++ ){
    if(line[j] == '0'){
        fputc('P', encoderFile);
        fputc('N', encoderFile);
        fputc('|', encoderFile);
    }
    else{
        fputc('N', encoderFile);
        fputc('P', encoderFile);
        fputc('|', encoderFile);
    }

}

fclose(encoderFile);// encoder yapilarak dosyaya yazildi simdi link uzerinden receiver_file_name.txt dosyasina decode edilerek yazilacak

link = fopen("150130037_MANCH.txt", "r");
fgets(line2,255,link);
fclose(link);

decoderFile = fopen(argv[2],"w");

    for(j=1 ; line2[j] != '\0' ;){
    if(line2[j] == 'P')
        fputc('0' , decoderFile);
    if(line2[j] == 'N')
        fputc('1' , decoderFile);

        j = j+3;
    }


fclose(decoderFile);



}
else if(strcmp(argv[3],"D_MANCH") == 0){
int i;
        printf("your selection is %s\n",argv[3]);
        encoderFile = fopen("150130037_D_MANCH.txt", "w");

char blackWhite[255];

if(line[0] == '1'){
    blackWhite[0] = 'P';
    blackWhite[1] = 'N';
}

else{
    blackWhite[0] = 'N';
    blackWhite[1] = 'P';
}


    // GERI KALANLAR ICIN SIYAH YA DA BEYAZ ANLAMINDA 'b' ya da 'w' koyuldu  Pbwwbb olacak
for(i=1; line[i] != '\0'; i++)
if(line[i] == '1'){
    blackWhite[2*i] = 'w';
    blackWhite[2*i+1] = 'x';
}

else{
     blackWhite[2*i] = 'b';
     blackWhite[2*i+1] = 'x';
}
blackWhite[2*i] = '\0';




for(i=1;blackWhite[i]!= '\0' ; i++ ){
    if(blackWhite[2*i] == 'b')
{
     if(blackWhite[2*i-1] == 'N'){
        blackWhite[2*i] = 'P';
        blackWhite[2*i+1] = 'N';
    }

            else{
                blackWhite[2*i] = 'N';
                blackWhite[2*i+1] = 'P';
            }
}
else if(blackWhite[2*i] == 'w'){
    if(blackWhite[2*i-1] == 'N'){
        blackWhite[2*i] = 'N';
        blackWhite[2*i+1] = 'P';
    }

            else{
                blackWhite[2*i] = 'P';
                blackWhite[2*i+1] = 'N';
            }


}

}
// BURAYA KADAR YINE BLACK AND WHITE DIZISININ ICINE P VE N CINSINDEN ENCODE YAPILDI
//SIMDI BUNLAR '|' EKLENEREK DOSYAYA YAZILACAK
fputc('|', encoderFile);

for(i=0;blackWhite[i] != '\0' ; i++)
{
    fputc(blackWhite[i], encoderFile);
    if(i%2 == 1)
    fputc('|', encoderFile);

}

fclose(encoderFile);
//encode edilen bilgi dosyaya yazildi simdi bu dosyadan decode edilerek receiver_file_name.txt dosyasi olusturulacak
link = fopen("150130037_D_MANCH.txt","r");
fgets(line2, 255, link);
fclose(link);

decoderFile = fopen(argv[2],"w");
for (i=0; line2[i] != '\0';)
{
    if(i == 1 ){          // ilk biti tahmin etme
        if(line2[i] == 'N' )
            fputc('0',decoderFile);
        else
            fputc('1',decoderFile);
    }
    if(i>=2 && i%3 != 0 ){
    if(line2[i] == line2[i+2])
         fputc('1',decoderFile);
    else
         fputc('0',decoderFile);
    i = i+2;  // bu if yapisi yapildi cunku encode ettigimiz dizideki karsilastirilmasi gereken indexler su sekilde =>(2,4),(5,7),(8,10),(11,13), ........
    }
if(line2[i+3] == '\0')
    break;
i++;
}


fclose(decoderFile);

}
else if(strcmp(argv[3],"AMI") == 0  ){
printf("your selection is %s\n",argv[3]);
encoderFile = fopen("150130037_AMI.txt", "w");
char positiveNegative[100]= "PNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNPNP";
fputc('|', encoderFile);
int i;
int k=0;
for(i=0; line[i] != '\0' ; i++){ //encoding AMI ----------------------------------------------------------------
        if(line[i] == '0')
        {
            fputc('Z', encoderFile);
            fputc('|', encoderFile);
        }
                else
                {
                    fputc(positiveNegative[k], encoderFile);
                     fputc('|', encoderFile);
                     k++;
                }


}//---------------------------------------------------------------------------------------------------------------------------
fclose(encoderFile);
// buraya kadar encode edildi, simdi link den receiver_file_name dosyasi olusturalacak.
link = fopen("150130037_AMI.txt","r");
fgets(line2, 255, link);
fclose(link);



//alinan bilgi decode edilerek receiver_file_name.txt ye yaziliyor

decoderFile = fopen(argv[2], "w");
for(i=0;line2[i] != '\0' ; i++){
if(line2[i] == 'Z')
    fputc('0',decoderFile);
else if(line2[i] == 'P')
    fputc('1',decoderFile);
else if( line2[i] == 'N')
    fputc('1',decoderFile);

}


fclose(decoderFile);

}



return 0;
}


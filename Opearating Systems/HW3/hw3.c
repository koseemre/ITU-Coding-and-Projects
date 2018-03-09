
//emre kose - 150130037


#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>







void prosesOku(void *ptr);
void prosesYaz(void *ptr);
int *hafiza;
char *hafiza2;
sem_t sem;


int main()
{

	int shmBoyut = 2;
	int shmBoyut2 = 2;
	int shmid,shmid2;

	shmid = shmget(IPC_PRIVATE, shmBoyut, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	shmid2 = shmget(IPC_PRIVATE, shmBoyut2, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	key_t key;
    pthread_t process[50]; // max. sayıda kullanılacak proses sayısı


	hafiza = shmat(shmid, 0, 0); //  çalışan okuyucu ve yazıcıların sayısını tutmak için	(int değerinde)
	hafiza2 =   shmat(shmid2, 0, 0); // çalışan okuyucunun olup olmadığını kontrol etmek için (char değerinde)

	*hafiza2 = 'Y'; // çalışan okuyucu var mı yok mu
	*(hafiza2+1) = 'Y';// çalışan yazıcı var mı yok mu

	*(hafiza) = 0; // okuyucu sayısı
	*(hafiza+1) = 0; // yazıcı sayısı


    int prosesSira = 0;
	char devamTamam;
	char prosesTip;
	int komutSuresi;


	setlinebuf(stdout);
	sem_init(&sem, 0, 1);

	for(;;){
		if(prosesSira != 0){
			printf("devam etmek ister misiniz?(E/H) :");
			scanf(" %c", &devamTamam);

			if(devamTamam == 'H')
				break;
		}

		printf("Proses tipini(W ya da R) ve çalışma süresini giriniz:");
		scanf(" %c", &prosesTip);
        scanf(" %d", &komutSuresi);



		if(prosesTip== 'R' ){
			pthread_create(&process[prosesSira], NULL, (void *) &prosesOku,(void*)&komutSuresi);
			prosesSira = prosesSira+1;
		}else if(prosesTip == 'W' ){
			pthread_create(&process[prosesSira], NULL, (void *) &prosesYaz,(void*)&komutSuresi);
			prosesSira = prosesSira+1;
		}

	}



	for(;;){
		if(*(hafiza) == 0 && *(hafiza+1) == 0 && *(hafiza2) == 'Y' && *(hafiza2+1) == 'Y' ) {
			printf("\n");
			printf("Tum prosesler sonlandı\n");
			sem_destroy(&sem);
			break;
		}
	}



	return 0;
}




void prosesYaz(void *ptr){


	*(hafiza+1) = *(hafiza+1) + 1;


	int prosesSira = *(hafiza + 1); // yazıcı sayısı
	char komutSuresi  = *((char *)ptr);

	 if(*(hafiza2+1) == 'V'){
		 printf("\n");
		 printf("çalışmakta olan yazıcı var...\n");
		 }

	else if(*hafiza2 == 'V'){
		printf("\n");
		printf("okuyucu çalışmakta...\n");
		}




	for(;;){
		if(*hafiza2 == 'Y'  && *(hafiza+1) <=1){
			printf("\n");
			printf("W%d çalışmaya başladı \n", prosesSira);
			break;
			}


	}


	prosesSira = *(hafiza+1);
	if(prosesSira== 1)
		*(hafiza2+1) = 'V';
	if(prosesSira == 0)
		*(hafiza2+1) = 'Y';


	sleep(komutSuresi);
	//yazma işlemleri...
	*(hafiza+1) = prosesSira  - 1;
	printf("\n");
	printf("yazma islemi bitti\n");
	prosesSira = *(hafiza+1);

	if(prosesSira== 1)
		*(hafiza2+1) = 'V';
	if(prosesSira == 0)
		*(hafiza2+1) = 'Y';

	sem_post(&sem);
	pthread_exit(0);
}

void prosesOku(void *ptr){


	*(hafiza) = *(hafiza)+1; // OKUCU sayısını bir artır
	char komutSuresi  = *((char *)ptr); // komut süresini thread fonksiyonundan çek
	int prosesSira = *(hafiza);	// güncel proses sayısını çek

	 if(*(hafiza) > 5)		// okuyucu sayısı kontrol
	 {
		 printf("\n");
		 printf("\n R%d beklemekte 5 den fazla okuyucu var\n", prosesSira);
		 }

	else if(*(hafiza2+1) == 'V') //yazıcı kontrol
	{	printf("\n");
		printf("yazma islemi devam etmekte  R%d beklemekte\n", prosesSira);
		}



	for(;;){
		if(*(hafiza2+1) == 'Y' && *(hafiza) <= 5){
			printf("\n");
			printf("\nR%d başladı\n", prosesSira); // yazıcı ya da okuyucu yoksa okuyucuyu başlat
			break;
			}


		sleep(1);
	}


	if(*(hafiza) == 1)
		*(hafiza2) = 'V';
		else if(*(hafiza) == 0)
		*(hafiza2) = 'Y';


	// okuma işlemleri ....
	sleep(komutSuresi);
	*(hafiza) =*(hafiza) -1;
	printf("\nR%d bitti\n", prosesSira);


		if(*(hafiza) == 1)
			*(hafiza2) = 'V';
				else if(*(hafiza) == 0)
				*(hafiza2) = 'Y';


	sem_post(&sem);
	pthread_exit(0);
}



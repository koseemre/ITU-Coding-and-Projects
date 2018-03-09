// EMRE KÖSE - 150130037
#define MAX 100
#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <signal.h>

#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SHM_K1 1

#define Semafor_K1 8
#define Semafor_K2 9
#define Semafor_K3 10

void sem_signal(int semid, int val){
	struct sembuf semaphore;
	semaphore.sem_num = 0;
	semaphore.sem_op = val;
	semaphore.sem_flg = 1;
	semop(semid, &semaphore, 1);
	}

void sem_wait(int semid, int val){
	struct sembuf semaphore;
	semaphore.sem_num = 0;
	semaphore.sem_op = (-1*val);
	semaphore.sem_flg = 1;
	semop(semid, &semaphore, 1);
	}



void mysignal(int signum){
printf("Received signal  = %d. \n",signum);
}

void mysigset(int num){
	struct sigaction mysigaction;
	mysigaction.sa_handler = (void*) mysignal;
	mysigaction.sa_flags = 0;
	sigaction(num, &mysigaction, NULL);
}

int main(int argc, char *argv[]){



    srand (time(NULL));
    mysigset(10);

    int i,order=0;
    int n, M,f=1;



    printf("A dizisinin eleman sayısını(n) giriniz: ");

    scanf("%d",&n);


   	int *ptr_n = NULL;
	int memory_id1;
	int x=0;
	int y=0;



	int senk_var=0;
	int senk_var2=0;
	int senk_var3=0;


		for(i=0; i<2; i++){


		f = fork();		//create child process
		order = i;
		if(f == -1){
			printf("Fork Error....\n");
			exit(1);
		}
		if(f == 0)
            break;	//because need only two child processes, no more


		}

        if(f!=0) // semaphores and memory allocations are handled in mother process
        {


		senk_var = semget(Semafor_K1,1,0700|IPC_CREAT);
		semctl(senk_var,0,SETVAL,0);



		senk_var3 = semget(Semafor_K3,1,0700|IPC_CREAT);
		semctl(senk_var2,0,SETVAL,0);


		memory_id1 = shmget(SHM_K1, sizeof(int)*(2*n+4),0700|IPC_CREAT);
		ptr_n = (int *)shmat(memory_id1, 0, 0);
		ptr_n[0] = n;

		int j=4;

		while(j<n+4){
			   ptr_n[j] = rand()%MAX;
			    j++;
		}

		printf("Olusturulan A dizisi:");
		j=0;
		printf("%d",ptr_n[4+j]);

		while(j+1<n){
		printf(",%d ",ptr_n[5+j]);
		j++;
		}
		printf("\n");

		printf("A dizisinin başlangıç adresi:%li \n",(long int)ptr_n);

		printf("M değerini giriniz(maksimum range 100 olarak ayarlandı): ");

   		scanf("%d",&M);
		sleep(1);
		printf("\n");
		ptr_n[1] = M;




		sem_signal(senk_var3,2);    // to wait to finish of child processes
		sem_wait(senk_var,2);






		shmdt(ptr_n);


		// Deallocations
		semctl(senk_var, 0, IPC_RMID, 0);
		semctl(senk_var2, 0, IPC_RMID, 0);
		semctl(senk_var3, 0, IPC_RMID, 0);

		shmctl(memory_id1, IPC_RMID, 0);


        }
        else{ // Child processes work


            senk_var3 = semget(Semafor_K3,1,0);
    	    sem_wait(senk_var3,1);

            senk_var = semget(Semafor_K1,1,0);



    if(order ==0 ){ // First child


		senk_var2 = semget(Semafor_K2,1,0700|IPC_CREAT);
		semctl(senk_var2,0,SETVAL,0);

		memory_id1 = shmget(SHM_K1, sizeof(int)*(2*n+4),0);
		ptr_n = (int *)shmat(memory_id1, 0, 0);



                int temp_n = ptr_n[0];
                int temp_M = ptr_n[1];



                int j,k =0;
		j=0;
                while(j<ptr_n[0]){
                        if(ptr_n[j+4]<=  ptr_n[1]){
                            ptr_n[n+4+k]=ptr_n[j+4];


                            k++;
                        }

                    j++;
                }
                    ptr_n[2] = k;
                    int te = ptr_n[0];

		    printf("Çocuk_1 %c<= M%c olan eleman sayısı: %d\n",'"','"',k);
		    printf("Çocuk_1 dizisinin başlangıç adresi:%li \n",(long int)&ptr_n[te+4]);

		printf("Cocuk 1 :B =");
		printf("%d",ptr_n[te+4]);
		j=1;
		while(j<ptr_n[2]){
		printf(",%d",ptr_n[te+4+j]);
		j++;
		}
		printf("\n");
                    sem_signal(senk_var2,1);   // To start 2. child
                    sem_signal(senk_var,1);     //   to inform mother process of finishing of 1. child

            }
    else {  // Second child

		senk_var2 = semget(Semafor_K2,1,0);
		sem_wait(senk_var2,1);
		//printf("1 bittiii \n");
		memory_id1 = shmget(SHM_K1, sizeof(int)*(2*n+4),0);
		ptr_n = (int *)shmat(memory_id1, 0, 0);


               int temp_n =ptr_n[0], temp_x =ptr_n[2];

                int m=0,l=0;
                while(l<ptr_n[0]){
                   if(ptr_n[l+4]> ptr_n[1]){
                                 ptr_n[n+ptr_n[2]+4+m] = ptr_n[l+4] ;
                                 m++;
                            }

                        l++;
                }

                   ptr_n[3] = m;
                   printf("Çocuk_2 %c> M%c olan eleman sayısı: %d\n",'"','"',m);
		   printf("Çocuk_2 dizisinin başlangıç adresi:%li \n",(long int)&ptr_n[temp_x+temp_x+4]);
		int j;
		printf("Cocuk 2 :C =");
		printf("%d",ptr_n[temp_x+temp_n+4]);
		j=1;
		while(j<m){
		printf(",%d",ptr_n[temp_x+temp_n+4+j]);
		j++;
		}
		printf("\n");
                 sem_signal(senk_var,1);
            }


        }


        return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_t thr1;
pthread_t thr2;
char player1[101],player2[101];
int peta1[20],peta2[20];
int ranjau,petak,tebak;
int stock1=16,stock2=16;
int nilai1=0,nilai2=0;
int status=0;

void* play1(void *arg){
	while(1){
		while(status!=0){};
		printf("player 1 : %s\nnilai : %d\nplayer 2 : %s\nnilai : %d\n", player1, nilai1, player2, nilai2);
		printf("ranjau pemain 1 (max 4) : ");
		scanf("%d", &ranjau);
		for(int i=0;i<ranjau;i++){
			printf("masukkan ranjau ke petak : ");
			scanf("%d",&petak);
			if(peta1[petak]==0){
				stock1--;
				peta1[petak]=1;
			}
		}
		printf("pemain 2 tebak : ");
		scanf("%d", &tebak);
		if(peta1[tebak]==1){
			printf("benar! pemain 2 +1\n");
			nilai2++;
		}
		else{
			printf("salah! pemain 1 +1\n");
			nilai1++;
		}
		status=1;
		return NULL;
	}
}

void* play2(void *arg){
	while(1){
		while(status!=1){};
		printf("player 1 : %s\nnilai : %d\nplayer 2 : %s\nnilai : %d\n", player1, nilai1, player2, nilai2);
		printf("ranjau pemain 2 (max 4) : ");
		scanf("%d", &ranjau);
		for(int i=0;i<ranjau;i++){
			printf("masukkan ranjau ke petak : ");
			scanf("%d",&petak);
			if(peta2[petak]==0){
				stock2--;
				peta2[petak]=1;
			}
		}
		printf("pemain 1 tebak : ");
		scanf("%d", &tebak);
		if(peta2[tebak]==1){
			printf("benar! pemain 1 +1\n");
			nilai1++;
		}
		else{
			printf("salah! pemain 2 +1\n");
			nilai2++;
		}
		status=0;
		return NULL;
	}
}

int main(){
	printf("Player 1 : ");
	scanf("%s", player1);
	printf("Player 2 : ");
	scanf("%s", player2);
	for(int i=1;i<=16;i++){
		peta1[i]=0;
		peta2[i]=0;
	}
	while(1){
		pthread_create(&(thr1),NULL,&play1,NULL);
		pthread_create(&(thr2),NULL,&play2,NULL);
		pthread_join(thr1,NULL);
		pthread_join(thr2,NULL);
	}
}

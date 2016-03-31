#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> 

#define DIM 4

pthread_mutex_t mtx[DIM][DIM];

void *simulator(int id){
	while(1){
		int xsrc,ysrc,xdes,ydes,xold,yold;
		xsrc=rand()%DIM;
		ysrc=rand()%DIM;
		//xsrc=0;
		//ysrc=0;
		while(1){
			xdes=rand()%DIM;
			ydes=rand()%DIM;
			if(xdes==xsrc&&ydes==ysrc)
				continue;
			else
				break;
		} 
		int xcur=xsrc;
		int ycur=ysrc;
		printf("Thread %d: New Source Position [%d,%d], Destination position [%d,%d]\n",id,xsrc,ysrc,xdes,ydes);
		//pthread_mutex_lock(&mtx[xcur][ycur]);
		while(xcur!=xdes||ycur!=ydes){
			// Packet generate
			// Calculate next position
			pthread_mutex_lock(&mtx[xcur][ycur]);
			xold=xcur;
			yold=ycur;
			if(xcur!=xdes)
				xcur=xcur>xdes?xcur-1:xcur+1;
			else
				ycur=ycur>ydes?ycur-1:ycur+1;
			pthread_mutex_lock(&mtx[xcur][ycur]);
			//Transfer Packet
			printf("Thread %d: Current position [%d,%d], Next position [%d,%d], Destination position [%d,%d]\n",id,xold,yold,xcur,ycur,xdes,ydes);
			//for(int i=0;i<100000000;i++);
			pthread_mutex_unlock(&mtx[xold][yold]);
			// Level original location
			pthread_mutex_unlock(&mtx[xcur][ycur]);
			// Arrive new location
			// Transfer Finish
		}
	}
}

int main(){
	pthread_t p[2];
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++){
			pthread_mutex_init(&mtx[i][j],NULL);
		}
	}
	pthread_create(&p[0], NULL, simulator, 1);
	pthread_create(&p[1], NULL, simulator, 2);
	pthread_join(p[0],NULL);
	pthread_join(p[1],NULL);
}

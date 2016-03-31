/*
 * barrier.c
 *
 *  Created on: Mar 16, 2016
 *      Author: gaohan
 */

#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>

#define BARRIER_MAX_THREADS 10
struct barrier_t {
	int count;
	int reached[BARRIER_MAX_THREADS];
	pthread_mutex_t mutex;
	pthread_cond_t cond[BARRIER_MAX_THREADS];
};

void barrier_init(struct barrier_t *barrier, int count);
void barrier_wait(struct barrier_t *barrier, int id);

void barrier_init(struct barrier_t *barrier, int count) {
	barrier->count = count;
	for (int i = 0; i < count; i++) {
		barrier->reached[i] = 0;
	}
	int rc = pthread_mutex_init(&barrier->mutex, NULL);
	assert(rc == 0);
	for (int i = 0; i < count; i++) {
		int rc = pthread_cond_init(&barrier->cond[i], NULL);
		assert(rc == 0);
	}
}

void barrier_wait(struct barrier_t *barrier, int id) {
	//printf("thread id is %d\n", gettid());
	barrier->reached[id] = 1;
	for (int i = 0; i < barrier->count; i++) {
		if (barrier->reached[i] != 1) {
			//printf("I am %d, thread %d is != 1 \n",id, i);
			pthread_mutex_lock(&barrier->mutex);
			int rc = pthread_cond_wait(&barrier->cond[id], &barrier->mutex);
			assert(rc == 0);
			pthread_mutex_unlock(&barrier->mutex);
			return;
		}
	}
	//printf("flag = %d\n", flag);
	for (int i = 0; i < barrier->count; i++) {
		if (i != id) {
			//printf("wake up thread %d\n", i);
			pthread_mutex_lock(&barrier->mutex);
			int rc = pthread_cond_signal(&barrier->cond[i]);
			assert(rc == 0);
			pthread_mutex_unlock(&barrier->mutex);
		}
	}
}

#endif

struct barrier_t barrier;

void *thread(int i) {
	printf("Thread %d do some work \n", i);
	sleep(rand() % 5);
	printf("Thread %d finish work and waiting others \n", i);
	barrier_wait(&barrier, i);
	printf("Thread %d keep going \n", i);
}

int main() {
	int i;
	int num=5;
	pthread_t p[num];
	barrier_init(&barrier, num);
	for (i = 0; i < num; i++) {
		pthread_create(&p[i], NULL, thread, (void *) i);
	}
	for (i = 0; i < num; i++) {
		pthread_join(p[i], NULL);
	}
	return 0;
}

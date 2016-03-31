/*
 * q1.c
 *
 *  Created on: Mar 16, 2016
 *      Author: gaohan
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define DIM 5
int A[DIM * DIM];
int B[DIM * DIM];
int C[DIM * DIM];

void InitializeMatrix(int *X) {
	int i, j;
	for (i = 0; i < DIM; i++)
		for (j = 0; j < DIM; j++)
			X[i * DIM + j] = random() % 10;
}
void PrintMatrix(int *X) {
	int i, j;
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++)
			printf("%3d ", X[i * DIM + j]);
		printf("\n");
	}
	printf("\n");
}
void MultiplyMatrices() {
	int i, j, k;
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			int sum = 0;
			for (k = 0; k < DIM; k++)
				sum += A[i * DIM + k] * B[k * DIM + j];
			C[i * DIM + j] = sum;
		}
	}
}
void *partialMultilply(int i) {
	//printf("begin\n");
	int j, k;
	for (j = 0; j < DIM; j++) {
		int sum = 0;
		for (k = 0; k < DIM; k++)
			sum += A[i * DIM + k] * B[k * DIM + j];
		C[i * DIM + j] = sum;
	}
	//sleep(DIM-i);
	//printf("finish\n");
	return NULL;
}
void MultiplyMatricesParallel() {
	pthread_t p[DIM];
	int i;
	for (i = 0; i < DIM; i++) {
		pthread_create(&p[i], NULL, partialMultilply, (void *)i);
	}
	for (i = 0; i < DIM; i++) {
		pthread_join(p[i], NULL);
	}
}
void Verify() {
	int i, j, k;
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			int sum = 0;
			for (k = 0; k < DIM; k++)
				sum += A[i * DIM + k] * B[k * DIM + j];
			if(C[i * DIM + j] != sum){
				printf("Verify: Two metrics are not equal\n");
				return;
			}
		}
	}
	printf("Verify: Two metrics are equal\n");
}
int main() {
	InitializeMatrix(A);
	InitializeMatrix(B);
	MultiplyMatricesParallel();
	PrintMatrix(A);
	PrintMatrix(B);
	PrintMatrix(C);
	Verify();
	return 0;
}

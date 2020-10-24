#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFERSIZE 10

void *producer(void *arg);
void *consumer(void *arg);

sem_t empty;
sem_t full;
//sem_t mutex;
pthread_mutex_t mutex;

int buffer[BUFFERSIZE], in = 0, out = 0;

int main() 
{

	int res, i, np, nc, *arg;
	pthread_t tp, tc;

	printf("\n-------------------------------------------\n");
	printf("Enter the number of producers :\n");
	scanf("%d", &np);
	printf("Enter the number of consumers :\n");
	scanf("%d", &nc);
	printf("\n-------------------------------------------\n");

	res = sem_init(&empty, 0, BUFFERSIZE);
	if(res != 0) 
	{
		printf("\nEmpty semaphore initialization failed.\n");
		exit(EXIT_FAILURE);
	}

	res = sem_init(&full, 0, 0);
	if(res != 0) 
	{
		printf("\nFull semaphore initialization failed.\n");
		exit(EXIT_FAILURE);
	}


	for(i=1; i<=np; i++)
	{
		arg = (int*)malloc(sizeof(int));
		*arg = i;
		
		res = pthread_create(&tp, NULL, producer, arg);
		if(res != 0)
		{
			printf("\nThread initialization failed\n");
			exit(EXIT_FAILURE);
		}
	}

	for(i=0; i<nc; i++)
	{
		arg = (int*)malloc(sizeof(int));
		*arg = i;
		
		res = pthread_create(&tc, NULL, consumer, arg);
		if(res != 0)
		{
			  printf("\nThread initialization failed\n");
			  exit(EXIT_FAILURE);
		}
	}

	res = pthread_join(tp, NULL);
	if(res != 0)
	{
		printf("\nThread join failed\n");
		exit(EXIT_FAILURE); 
	}

	res = pthread_join(tc, NULL);
	if(res != 0)
	{
		printf("\nThread join failed\n");
		exit(EXIT_FAILURE); 
	}
}

void *producer(void *arg) 
{
	int i;
	int *num = (int *)arg;

	while(1) 
	{
		sem_wait(&empty);
		//sem_wait(&mutex);
		pthread_mutex_lock(&mutex);
		printf("\nEntered producer: %d\n", *num);
		buffer[in] = *num;

		printf("Produced %d on position %d.\n", buffer[in], in+1);
		for(int i=0; i<BUFFERSIZE; i++)
		{
			printf(" %d ", buffer[i]);
		}
		printf("\nExiting producer: %d\n", *num);
		printf("-------------------------------------------\n");
		
		in = (in + 1) % BUFFERSIZE;
		//sem_post(&mutex);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		sleep(2);
	}
	pthread_exit(NULL);
}

void *consumer(void *arg) 
{
	int n;
	int *num = (int *)arg;

	while(1) 
	{
		sem_wait(&full);
		//sem_wait(&mutex);
		pthread_mutex_lock(&mutex);
		printf("\nEntered consumer: %d\n", *num);
		
		printf("Consumed %d on position %d.\n", buffer[out], out+1);
		buffer[out] = 0;
		
		for(int i=0; i<BUFFERSIZE; i++)
		{
			printf(" %d ", buffer[i]);
		}
		printf("\nExiting consumer: %d\n", *num);
		printf("-------------------------------------------\n");
		
		out = (out + 1) % BUFFERSIZE;
		//sem_post(&mutex);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		sleep(2);
	}
	pthread_exit(NULL);
}

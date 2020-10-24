#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *reader(void *arg);
void *writer(void *arg);

sem_t wrt;
pthread_mutex_t mutex;

int count = 1, readCount = 0;

int main() 
{

	int res, i, nr, nw, *arg;
	pthread_t tr, tw;

	printf("\n-------------------------------------------\n");
	printf("Enter the number of readers :\n");
	scanf("%d", &nr);
	printf("Enter the number of writers :\n");
	scanf("%d", &nw);
	printf("\n-------------------------------------------\n");

	res = sem_init(&wrt, 0, 1);
	if(res != 0) 
	{
		printf("\nWrite semaphore initialization failed.\n");
		exit(EXIT_FAILURE);
	}

	for(i=1; i<=nw; i++)
	{
		arg = (int*)malloc(sizeof(int));
		*arg = i;
		
		res = pthread_create(&tw, NULL, writer, arg);
		if(res != 0)
		{
			printf("\nThread initialization failed\n");
			exit(EXIT_FAILURE);
		}
	}

	for(i=0; i<nr; i++)
	{
		arg = (int*)malloc(sizeof(int));
		*arg = i;
		
		res = pthread_create(&tr, NULL, reader, arg);
		if(res != 0)
		{
			  printf("\nThread initialization failed\n");
			  exit(EXIT_FAILURE);
		}
	}

	res = pthread_join(tw, NULL);
	if(res != 0)
	{
		printf("\nThread join failed\n");
		exit(EXIT_FAILURE); 
	}

	res = pthread_join(tr, NULL);
	if(res != 0)
	{
		printf("\nThread join failed\n");
		exit(EXIT_FAILURE); 
	}
}

void *writer(void *arg) 
{
	int *num = (int *)arg;

	sem_wait(&wrt);
	printf("\nEntered writer: %d\n", *num);
	count++;
	printf("Writer %d modified count to %d\n", *num, count);
	sem_post(&wrt);
	sleep(2);
	
	pthread_exit(NULL);
}

void *reader(void *arg) 
{
	int *num = (int *)arg;

	pthread_mutex_lock(&mutex);
	readCount++;
	if(readCount == 1)
	{
		sem_wait(&wrt);
	}
	pthread_mutex_unlock(&mutex);
	
	printf("\nEntered reader: %d\n", *num);
	printf("Reader %d read count = %d\n", *num, count);
	
	pthread_mutex_lock(&mutex);
	readCount--;
	if(readCount == 0)
	{
		sem_post(&wrt);
	}
	pthread_mutex_unlock(&mutex);
	sleep(2);
	
	pthread_exit(NULL);
}

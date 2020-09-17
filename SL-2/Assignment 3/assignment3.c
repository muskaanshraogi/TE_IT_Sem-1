#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void *multiply(void *arg)
{
	int *data = (int *)arg;
	int x, k = 0;
	
	x = data[0];
	for(int i = 1; i <= x; i++)
		k += data[i]*data[i+x];
		
	int *p = (int *)malloc(sizeof(int));
	*p = k;
	
	pthread_exit(p);
}


int main()
{
	int res, r1, c1, r2, c2, max, count = 0;
	pthread_t *threads;
	
	printf("\nEnter the number of rows of columns for matrix A:\n");
	scanf("%d %d", &r1, &c1);
	
	int A[r1][c1];
	
	printf("\n");
	for(int i=0; i<r1; i++)
	{
		for(int j=0; j<c1; j++)
		{
			printf("Enter the [%d][%d] element of matrix A:", i, j);
			scanf("%d", &A[i][j]);
		}
	}
	
	
	printf("\nEnter the number of rows of columns for matrix B:\n");
	scanf("%d %d", &r2, &c2);
	
	int B[r2][c2];
	
	printf("\n");
	for(int i=0; i<r2; i++)
	{
		for(int j=0; j<c2; j++)
		{
			printf("Enter the [%d][%d] element of matrix B:", i, j);
			scanf("%d", &B[i][j]);
		}
	}
	
	max = r1 * c2;
	threads = (pthread_t *)malloc(max*sizeof(pthread_t));
	
	int *data = NULL;
	for(int i=0; i<r1; i++)
	{
		for(int j=0; j<c2; j++)
		{
			data = (int *)malloc((c1+r2+1)*sizeof(int));
			data[0] = c1;
			
			for(int k=0; k<c1; k++)
				data[k+1] = A[i][k];
			
			for(int k=0; k<r2; k++)
				data[k+c1+1] = B[k][j];
				
			res = pthread_create(&threads[count++], NULL, multiply, (void *)data);
			
			if (res != 0) 
			{
				perror("\nThread creation failed!\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	
	printf("\n---------------------------------------------------------\n");
	printf("\nThe resultant matrix is:\n\n");
	
	for(int i=0; i<max; i++)
	{
		void *k;
		res = pthread_join(threads[i], &k);
		
		if (res != 0) 
		{
			perror("\nThread joining failed!\n");
			exit(EXIT_FAILURE);
		}
		
		printf("%d ", *(int *)k);
		if((i+1) % c2 == 0)
			printf("\n");
	}
	
	return 0;
}

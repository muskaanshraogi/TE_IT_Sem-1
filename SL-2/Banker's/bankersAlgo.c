#include<stdio.h>
#include<stdlib.h>

int safeSequence(int p, int r, int available[r], int need[p][r], int allocation[p][r]) 
{
	int flag, index = 0, unsafe = 0;
	int finish[p], work[r], safe[p];
	
	printf("\nInitializing the finish matrix....\n");
	for(int i=0; i<p; i++)
	{
		finish[i] = 0;
	}
	
	printf("\nInitializing the work matrix....\n");
	for(int i=0; i<r; i++)
	{
		work[i] = available[i];
	}
	
	printf("\nCalculating safe sequence....\n");
	do
	{
		flag = 1;
		for(int i=0; i<p; i++)
		{
			if(finish[i] == 0)
			{
				flag = 0;
				for(int j=0; j<r; j++)
				{
					if(available[j] < need[i][j])
					{
						flag = 1;
						break;
					}
				}
				
				if(flag == 0)
				{
					safe[index++] = i;
					for(int j=0; j<r; j++)
					{
						available[j] += allocation[i][j];
					}
					finish[i] = 1;
				}
			}
		}
	} while(index != p && flag != 1);
		
	for(int i=0; i<p; i++)
	{
		if(!finish[i])
		{
			unsafe = 1;
			break;
		}
	}
	
	if(unsafe)
	{
		printf("\nThe given allocation is in unsafe state.\n");
		return 0;
	}
	else
	{
		printf("\nThe safe sequence is :\n");
		for(int i=0; i<p; i++)
		{
			printf("P%d\t", safe[i]);
		}
		printf("\n");
		return 1;
	}
}

void resourceAllocation(int p, int r, int available[r], int need[p][r], int allocation[p][r])
{
	int pi, request[r], flag = 1;
	
	printf("\nEnter the process which is requesting resources (0 - %d):\n", p);
	scanf("%d", &pi);
	
	printf("\nEnter its request matrix:\n");
	for(int i=0; i<r; i++)
	{
		printf("Resource %d:", i+1);
		scanf("%d", &request[i]);
	}
	
	for(int i=0; i<r; i++)
	{
		if(request[i] > need[pi][i] || request[i] > available[i])
			flag = 0;
	}
	
	if(flag)
	{
		for(int i=0; i<r; i++)
		{
			available[i] -= request[i];
			allocation[pi][i] += request[i];
			need[pi][i] -= request[i];
		}
		
		int safe = safeSequence(p, r, available, need, allocation);
		
		if(safe)
		{
			printf("\nThe requested resources can be immediately allocated to P%d\n", pi);
		}
		else 
		{
			printf("\nThe requested resources cannot be allocated to P%d\n", pi);
			for(int i=0; i<r; i++)
			{
				available[i] += request[i];
				allocation[pi][i] -= request[i];
				need[pi][i] += request[i];
			}
		}
	}
	else 
	{
		printf("\nThe requested resources cannot be allocated to P%d\n", pi);
	}
}

int main()
{
	int p, r, choice;
	
	printf("\nEnter the number of processes:\n");
	scanf("%d", &p);
	
	printf("\nEnter the number of resources:\n");
	scanf("%d", &r);
	
	int max[p][r], allocation[p][r], need[p][r], available[r];
	
	printf("\nEnter the maximum matrix:\n");
	for(int i=0; i<p; i++)
	{
		printf("\nProcess %d:\n", i+1);
		for(int j=0; j<r; j++)
		{
			printf("Resource %d:", j+1);
			scanf("%d", &max[i][j]);
		}
	}
	
	printf("\nMaximum matrix:\n");
	for(int i=0; i<p; i++)
	{
		for(int j=0; j<r; j++)
		{
			printf("%d ", max[i][j]);
		}
		printf("\n");
	}
	
	printf("\nEnter the allocation matrix:\n");
	for(int i=0; i<p; i++)
	{
		printf("\nProcess %d:\n", i+1);
		for(int j=0; j<r; j++)
		{
			printf("Resource %d:", j+1);
			scanf("%d", &allocation[i][j]);
		}
	}
	
	printf("\nAllocation matrix:\n");
	for(int i=0; i<p; i++)
	{
		for(int j=0; j<r; j++)
		{
			printf("%d ", allocation[i][j]);
		}
		printf("\n");
	}
	
	printf("\nEnter the available matrix:\n");
	for(int i=0; i<r; i++)
	{
		printf("Resource %d:", i+1);
		scanf("%d", &available[i]);
	}
	
	printf("\nAvailable resources:\n");
	for(int i=0; i<r; i++)
	{
		printf("%d ", available[i]);
	}
	printf("\n");
	
	printf("\nCalculating the need matrix....\n");
	for(int i=0; i<p; i++)
	{
		for(int j=0; j<r; j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	
	printf("\nNeed matrix:\n");
	for(int i=0; i<p; i++)
	{
		for(int j=0; j<r; j++)
		{
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}
	
	do 
	{
		printf("\n****MENU****\n");
		printf("1) Safe sequence\n2) Resource allocation\n3) Exit\n");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
				safeSequence(p, r, available, need, allocation);
				break;
				
			case 2:
				resourceAllocation(p, r, available, need, allocation);
				break;
				
			default:
				exit(0);
		}
	}while(1);
	
	
	return 0;
}

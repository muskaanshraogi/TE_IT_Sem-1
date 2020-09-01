#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

void quicksort(int array[], int n, int left, int right)
{
	int i, j, k, pivot, temp;
	
	if(left < right)
	{
		i = left;
		j= right + 1;
		
		pivot = array[left];
		
		do
		{
			do 
			{
				i++;
			}while(pivot > array[i]);
			
			do
			{
				j--;
			}while(pivot < array[j]);
			
			if(i < j)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			
		}while(i < j);
		
		temp = array[j];
		array[j] = array[left];
		array[left] = temp;
		
		quicksort(array, n, left, j-1);
		quicksort(array, n, j+1, right);
	}
}

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    i = 0; 
    j = 0; 
    k = l;
    
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
   while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
   while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void mergesort(int arr[], int left, int right) 
{ 
    if (left < right) 
    { 
        int middle = left + (right - left) / 2; 
  
        mergesort(arr, left, middle); 
        mergesort(arr, middle + 1, right); 
  
        merge(arr, left, middle, right); 
    } 
} 


int main()
{
	pid_t pid;
	int i, j, n, array[30], choice;
	
	printf("\n****Demostration*****\n");
	printf("Enter your choice :\n");
	printf("1. Zombie\n");
	printf("2. Orphan\n");
	scanf("%d", &choice);
	
	printf("Enter the total number of numbers :\n");
	scanf("%d", &n);
	
	printf("\nEnter the %d numbers to be sorted :\n", n);
	for(i=0; i<n; i++)
	{
		scanf("%d", &array[i]);
	}
	
	printf("\nExecuting fork now...\n");
	pid = fork();
	
	switch(pid)
	{
		case -1:
			printf("\nFork failed. Exiting program...\n");
			exit(0);
			
		case 0:
			printf("\nChild process active now...\n");
			printf("\nCHILD:: My PID is %d.\n", getpid());
			printf("CHILD:: My PPID is %d.\n", getppid());
			
			quicksort(array, n, 0, n-1);
			
			printf("\nCHILD:: My sorted array is using quicksort:\n");
			for(i=0; i<n; i++)
			{
				printf("%d ", array[i]);
			}
			
			
			if(choice == 2)
			{
				printf("\nChild process sleeping now...\n");
				sleep(10);
				
				printf("\nChild is awake again...\n");
				printf("\nCHILD:: My PID is %d.\n", getpid());
				printf("CHILD:: My PPID is %d.\n", getppid());
			}
			
			system("ps -elf| grep a.out");
			printf("\nExiting child...\n");
			printf("\n");
			break;
		
		default:
			system("wait");
			printf("\nParent process active...\n");
			printf("\nPARENT:: My child's ID is %d.\n", pid);
			
			mergesort(array, 0, n-1);
			
			printf("\nPARENT:: My sorted array using merge sort is:\n");
			for(i=0; i<n; i++)
			{
				printf("%d ", array[i]);
			}
			
			if(choice == 1)
			{
				printf("\nParent process sleeping now...\n");
				sleep(10);
			}
			if(choice == 2)
			{
				printf("\nParent process dying now...\n");
				exit(0);
			}
			
			system("ps -elf| grep a.out");
			printf("\nExiting parent...\n");
			printf("\n");
			break;
	}
	
	return 0;
}

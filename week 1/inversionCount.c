/*
 ============================================================================
 Name        : inversionCount.c
 Author      : Somnath Saha 
 Description : Count no. of inversions in a file
 ============================================================================
*/

#include<stdio.h>

#define MAX 100000

double count=0;


void displayArray(int*, int);
void merge(int*, int, int, int);

void mergeSort(int a[], int start, int end)
{
	int mid=(start+end)/2;
	if(start<end)
	{
		mergeSort(a, start, mid);
		mergeSort(a, mid+1, end);
		merge(a, start, mid, end); 
	}	
}

void merge(int *a, int start, int mid, int end)
{
	int b[MAX], p=start, q=mid+1, i=0, flg=0;

	while(i<=(end-start+1))
	{
		if(a[p]<=a[q])
		{
			b[i++]=a[p++];
			if(p==mid+1) 
			{
				flg=1;
				break;
			}
			
		}
		else
		{
			b[i++]=a[q++];
			count=count+mid-p+1;
			//printf("\np=%d, mid=%d.", p, mid);
			if(q==end+1)
			{
				flg=2;
				break;
			}
		}			
	}
	if(flg==1)
	{
		while(q<=end)
		{
			b[i++]=a[q++];
		}
	}
	if(flg==2)
	{
		while(p<=mid)
		{
			b[i++]=a[p++];
		}
	}
	int j, k;
	for(j=start, k=0; k<i; k++, j++)
	{
		a[j]=b[k];
	}
}

void displayArray(int a[], int size)
{
	int i;
	for(i=0; i<size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main()
{
	int a[MAX], i, n;
	
	printf("Count no. of inversions in a file:\n\n");
	printf("Loading File...\n");
	FILE * fp;
	fp=fopen("IntegerArray.txt", "r");
	
	for(i=0; i<MAX; ++i)
	{
		fscanf(fp, "%d", &n);
		a[i]=n;	
	}
	
	printf("\nFile succesfully loaded.");
	printf("\na[0]=%d; a[max]=%d.", a[0], a[MAX-1]);
	
	mergeSort(a, 0, MAX-1);
		
	printf("\nSorted Array:  ");
	printf("\na[0]=%d; a[max]=%d.", a[0], a[MAX-1]);
	printf("\ncount=%lf.", count);
	
	fclose(fp);
	
	
	return 0;
}

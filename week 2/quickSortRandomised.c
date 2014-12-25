/*
 ============================================================================
 Introduction to Algorithms - I | Stanford University | Tim Roughgarden
 Name        : QuickSort.c
 Author      : Somnath Saha 
 Description : Quick Sort in the prescribed format
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000
double count=0;
void displayArray(int*,int);

int Random (int _iMin, int _iMax) 
{ 
return (_iMin + (rand () % (_iMax-_iMin+1))); 
} 


int partition(int a[], int start, int end)
{
	int pivot, temp, iRandom;
	 
	iRandom = Random (start,end); 
	
	temp=a[start];
	a[start]=a[iRandom];
	a[iRandom]=temp;
		
	pivot=a[start];
	int j=start+1;
	int i=j;
	for(; j<=end; ++j)
	{
		if(a[j]<pivot)
		{
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;			
			i++;		
		}
	}
	temp=a[start];
	a[start]=a[i-1];
	a[i-1]=temp;
	return (i-1);			
}
void quickSort(int a[], int start, int end)
{
	if(start<end)
	{
		int n=partition(a,start,end);
		count+=end-start;
		quickSort(a,start,n-1);
		quickSort(a,n+1,end);
	}
}

int main()
{
	int a[10000]={5,1,4,2,6,3,7,0,8,9}, i=0, k=0;
	double sum=0;
	int cnt[500];
	
	srand (time (NULL));
	for(k=0; k<500; ++k)
	{	
		FILE * fp=fopen("QuickSort.txt", "r");
		count=0;
		for(i=0; i<MAX; ++i)
			fscanf(fp, "%d", &a[i]);
		quickSort(a,0,MAX-1);
		cnt[k]=count;
		fclose(fp);
	}
	for(k=0; k<500; ++k)
	{
		printf("\n%d: %d", k+1, cnt[k]);
		sum+=cnt[k];
	}
	printf("\nAverage: %.0lf", sum/500);
	
	//displayArray(a, MAX);	
	return 0;
}

void displayArray(int a[], int size)
{
	printf("\nArray: ");
	int i=0;
	for(i=0; i<size; ++i)
	{
		printf("%d ", a[i]);
	}
}

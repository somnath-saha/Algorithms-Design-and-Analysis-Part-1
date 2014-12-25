/*
 ============================================================================
 Introduction to Algorithms - I | Stanford University | Tim Roughgarden
 Name        : sum.c
 Author      : Somnath Saha 
 Description : Find no. of pairs that generate a sum
 ============================================================================
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>   //_getch*/
#include <termios.h>  //_getch*/

#define MAX 1000000
void displayArray(long long*,int);
char getch();
int split(long long a[], int start, int end);
void QuickSort(long long a[], int start, int end);
int BSearch(long long a[], int start, int end, long long item);

int main()
{
	long long a[MAX];
	int i=0;
	
	FILE * fp=fopen("list_sorted", "r");
	for(i=0; i<MAX; ++i)
	{
		fscanf(fp, "%Ld", &a[i]);
	}
	fclose(fp);
	printf("Reading done...Press any key to sort and find answer...\n");
	getch();
	
	//QuickSort(a, 0, MAX-1);
	//printf("Sorting done...Press any key to write to file...\n");
	//getch();
	
	long t0=time(NULL);
	int p, q;
	long count=0;
	for(i=-10000; i<=10000; ++i)
	{
		p=0;
		q=MAX-1;
		while(p<q)
		{
			if(a[p]+a[q]==i)
			{
				count++;
				//printf("%Ld+%Ld=%d\n", a[p], a[q], i);
				//getch();
				break;
			}
			else if((a[p]+a[q])<i)
			{
				p++;
			}
			else
				q--;
		}		
	}
	printf("Count=%ld\n", count);
	printf("Time taken to calculate = %lds.", time(NULL)-t0);
	return 0;
}


int BSearch(long long a[], int start, int end, long long item)
{
	if(start<end)
	{
		int mid=(start+end)/2;
		if(a[mid]==item)
		{
			return 1;
		}
		else if(a[mid]<item)
		{
			return BSearch(a, mid+1, end, item);
		}
		else
		{
			return BSearch(a, start, mid-1, item);
		}
	}
	return 0;
}

void displayArray(long long a[], int size)
{
	printf("\nArray: \n");
	long i=0;
	for(i=0; i<size; ++i)
	{
		printf("%Ld \n", a[i]);
	}
}

int split(long long a[], int start, int end)
{
	long long temp;
	int p, q;
	p=start+1;
	q=end;
	temp=a[p];
	while(p<q)
	{
		while(a[p]<=a[start])
		{
				p++;
		}
		while(a[q]>a[start])
		{
				q--;
		}
		if (p<q)
		{
			temp=a[p];
			a[p]=a[q];
			a[q]=temp;
		}
	}
	if(a[q]<a[start])
	{
		temp=a[start];
		a[start]=a[q];
		a[q]=temp;
	}
	return q;
}

void QuickSort(long long a[], int start, int end)
{
	if(start<end)
	{
		int i;
		i=split(a, start, end);
		QuickSort(a, start, i-1);
		QuickSort(a, i+1, end);
	}
}

char getch()
{
    /*#include <unistd.h>   //_getch*/
    /*#include <termios.h>  //_getch*/
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
 }

/*
 =======================================================================
 Introduction to Algorithms - I | Stanford University | Tim Roughgarden
 Name        : kargerMinCut.c
 Author      : Somnath Saha 
 Description : Karger's Minimum Contraction in the prescribed format
 =======================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>   
#include <termios.h> 

#define N 200
#define VERTICES 200

void createGraph(int g[200][400]);
void setEdges(int g[200][400]);
void displayGraph(int g[200][400]);
long int countEdge(int g[200][400]);
int countVertices(int g[200][400]);
//Random Number Generator (lower and upper included)
long int Random (long int, long int);
long int kargerMinCut(int g[200][400]);
char getch();

int main()
{
	long x=time(NULL), y=0;
	clock_t start, end;
	double cpu_time_used;
	while(1)
	{
		

		start = clock();
		getch();//... /* Do the work. */
		end = clock();
		cpu_time_used = ((double) (end - start)) ;/// CLOCKS_PER_SEC;
		//x=time(NULL);
		//y=time(NULL)-x;
		printf("\n%lf %ld", cpu_time_used,CLOCKS_PER_SEC);
	}
	//printf("\nMinimum cut for %d iterations: %ld\n", i, min);	
	return 0;
}

long int kargerMinCut(int g[200][400])
{
	long int r, s, i=0, pos;
	while(countVertices(g)>2)
	{
		long int z=countEdge(g);
		printf(", Edges=%ld, ",z);
		//srand(time(NULL));
		//r=Random(1, (2*z)); 	
		r=1 + (rand () % (2*z));
		printf("random:%ld ",r);
		i=0;
		s=g[0][399];
		while(r>s)
		{
			i++;
			s+=g[i][399];
		}
		pos=r-(s-g[i][399]);
		//g[i][pos]
		//Replace all occurences of i+1 in the graph with g[i][pos]
		int j=1, k=0, row, col;
		while(g[i][j]!=0)
		{
			k=1;
			while(g[g[i][j]-1][k]!=0)
			{
				if(g[g[i][j]-1][k]==(i+1))
					g[g[i][j]-1][k]=g[i][pos];				
				k++;
			}
			j++;
		}	
		//Add all edges of vertex value i+1 to in row no. (g[i][pos]-1)
		j=1;
		row=g[i][pos]-1;
		col=g[row][399]+1;
		while(g[i][j]!=0)
		{
			g[row][col++]=g[i][j++];
			g[row][399]++;
		}
		//Remove all self loops
		j=1;
		while(g[row][j]!=0)
		{
			if(g[row][j]==row+1)
			{
				g[row][j]=g[row][g[row][399]];
				g[row][g[row][399]]=0;
				g[row][399]--;
				j--;
			}
			j++;
		}
		if(!g[row][399])
		{
			displayGraph(g);
			printf("\nrow=%d, i=%ld, ", row, i);
			getch();
			
		}
		//setEdges not required, vertex removed and its edge length nullified
		g[i][0]=0;
		g[i][399]=0;
		printf(" ...Done\n");
	}	
	return countEdge(g);
}

long int Random (long int _iMin, long int _iMax) 
{ 
	return (_iMin + (rand () % (_iMax-_iMin+1))); 
}

void createGraph(int g[200][400])
{
	int i, j, count;
	char ch, s[5];
	long int pos=0;	
	for(i=0; i<200; ++i)
	{
		for(j=0; j<400; ++j)
		{
			g[i][j]=0;
		}
	}
	//FILE * fp=fopen("file", "r");
	FILE * fp=fopen("kargerMinCut.txt", "r");
	for(i=0; i<VERTICES; ++i)
	{
		pos=ftell(fp);
		count=0;
		while((ch=fgetc(fp))!='\n')
		{
			if(ch=='\t')
				count++;
		}
		fseek(fp, pos, SEEK_SET);
		for(j=0; j<count; ++j)
		{
			fscanf(fp, "%d", &g[i][j]);
		}
		fgets(s,5,fp);	
	}
	printf("File successfully loaded.\n");
	
	fclose(fp);	
}

void setEdges(int g[200][400])
{
	//Set no. of edges in end
	int edges=0, i=0, j=0;
	for(i=0; i<200; ++i)
	{
		edges=0;
		for(j=1; j<400; ++j)
		{
			if(g[i][j]==0)
				break;
			edges++;
		}
		g[i][399]=edges;
	}
	printf("Edges set.\n");
}

void displayGraph(int g[200][400])
{
	printf("Graph:\n");
	int i=0, j;
	for(i=0; i<N; ++i)
	{
		if (g[i][0]==0) continue;
		for(j=0; ; ++j)
		{
			if(g[i][j]==0)
			{
				break;
			}
			if (j==0)
			{
				printf("%d -> ", g[i][j]);
				continue;
			}
			printf("%d ", g[i][j]);
		}
		printf("e= %d", g[i][399]);
		printf("\n");
	}		
}

int countVertices(int g[200][400])
{
	int n=0, i;
	for(i=0; i<N; ++i)
	{
		if(g[i][399]>0)
			n++;
	}
	printf("\nReturning n=%d, ", n);
	if(n==20||n==19||n==21) 
	{
		//int x;
		//scanf("%d", &x);
		//displayGraph(g);	
		//scanf("%d", &x);
	}
	return n;		
}

long int countEdge(int g[200][400])
{
	int i=0;
	long int t_edges=0;
	for(i=0; i<N; ++i)
	{
		if(g[i][0]==0) 
			continue;
		else
			t_edges+=g[i][399];
	}
	return (t_edges/2);		
}

char getch(){
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
    printf("%c\n",buf);
    return buf;
 }

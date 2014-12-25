/*
 =======================================================================
 Introduction to Algorithms - I | Stanford University | Tim Roughgarden
 Name        : graphSCC.c
 Author      : Somnath Saha 
 Description : Finding strongly connected components of a directed graph
 =======================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <termios.h> 
#include <limits.h> 
#include <time.h> 

char getch();
void display();
void createGraph();
void DFS(int,int);
void DFS_Loop(int);


#define NO_OF_VERTICES 875714
#define NO_OF_ENTRIES 5105043


/*875714 vertices => 17.538MB RAM by nodes
 *5105043 edges => 77.90MB RAM by 5105043x2 edges
 *95.43MB RAM at least for maintaining the graph
 */
 
typedef struct node
{
	int x;
	char status;
	int leader;
	int ft;
	struct edge *link;
	struct edge *link2;
}node;

typedef struct edge
{
	int x;
	struct edge *link;
}edge;

node g[NO_OF_VERTICES+1];
int m[NO_OF_VERTICES+1];
int count[NO_OF_VERTICES+1];
edge *tempEdge=NULL;
int t=0, s=0;

void DFS_Loop(int rev)
{
	if(rev==0)
	{
		int i;
		for(i=NO_OF_VERTICES; i>=1; --i)
		{
			if(g[m[i]].status==0)
			{
				s=i;
				DFS(i, rev);
			}
		}
	}
	else
	{
		int i;
		for(i=NO_OF_VERTICES; i>=1; --i)
		{
			if(g[i].status==0)
			{
				s=i;
				DFS(i, rev);
			}
		}		
	}
}
void DFS(int i, int rev)
{
	if(rev==0)
	{
		g[m[i]].status=1;
		g[m[i]].leader=s;
		count[s]++;
		edge* tmpEdge=g[m[i]].link;
		while(tmpEdge!=NULL)
		{
			int k=tmpEdge->x;
			if(g[k].status==0)
			{
				DFS(g[k].x, rev);
			}
			tmpEdge=tmpEdge->link;
		}	
	}
	else
	{
		g[i].status=1;
		g[i].leader=s;
		edge* tmpEdge=g[i].link2;
		while(tmpEdge!=NULL)
		{
			int k=tmpEdge->x;
			if(g[k].status==0)
			{
				DFS(k, rev);
			}
			tmpEdge=tmpEdge->link;
		}		
		t++;
		g[i].ft=t;
		m[t]=i;
	}
}

void scc()
{
	int i;
	DFS_Loop(1);
	printf("\nDFS_Loop(1) done! To do second pass...");
	for(i=1; i<=NO_OF_VERTICES; ++i)
	{
		g[i].status=0;
		g[i].x=g[i].ft;
		count[i]=0;
	}
	DFS_Loop(0);
	printf("\nDFS_Loop(0) done! To count SCCs...\n\n");
	printf("Format - Leader:Components\n");
	int t;
	for(t=1; t<=5; ++t)
	{
		int max=0, k=0, c=0;
		for(i=1; i<=NO_OF_VERTICES; ++i)
		{
			if(max<count[i])
			{
				max=count[i];
				c=i;
			}
			if(max==count[i])
				k++;
		}
		printf("\nMax %d: %d [i=%d, k=%d]", t, max, c, k);
		count[c]=0;
	}
}

int main()
{
	long t0=time(NULL);
	createGraph();
	printf("\nTime taken = %lds. Starting SCC subroutine...", time(NULL)-t0);
	scc();	
	printf("\nTotal Time taken = %lds.", time(NULL)-t0);
	return 0;
}

void createGraph()
{
	int i=1, x=-1, e;
	FILE* fp=fopen("SCC.txt", "r");
	
	for(i=1; i<=NO_OF_VERTICES; i++)
	{
		g[i].x=i;
		g[i].status=0;
		g[i].leader=0;
		g[i].ft=0;
		g[i].link=NULL;
		g[i].link2=NULL;
	}
	
	printf("\nAll vertices set.");
	fseek(fp, 0, SEEK_SET);
	i=1;
	
	while(i<=NO_OF_ENTRIES)
	{	
		fscanf(fp, "%d %d", &x, &e);		
		tempEdge=g[x].link;
		if(tempEdge==NULL)
		{
			tempEdge=(edge *)malloc(sizeof(edge));
			tempEdge->x=e;
			tempEdge->link=NULL;
			g[x].link=tempEdge;			
		}
		else
		{
			while(tempEdge->link!=NULL)
			{
				tempEdge=tempEdge->link;
			}
			tempEdge->link=(edge *)malloc(sizeof(edge));
			tempEdge->link->x=e;
			tempEdge->link->link=NULL;
		}		
		
		tempEdge=g[e].link2;
		if(tempEdge==NULL)
		{
			tempEdge=(edge *)malloc(sizeof(edge));
			tempEdge->x=x;
			tempEdge->link=NULL;
			g[e].link2=tempEdge;			
		}
		else
		{
			while(tempEdge->link!=NULL)
			{
				tempEdge=tempEdge->link;
			}
			tempEdge->link=(edge *)malloc(sizeof(edge));
			tempEdge->link->x=x;
			tempEdge->link->link=NULL;
		}	
		i++;	
	}
	printf("\nEdges read from file.");
	fclose(fp);
}

void display()
{
	int i=1, j=NO_OF_VERTICES;
	while(i<=j)
	{
		printf("\n%d [s(%d), l(%d), ft(%d)] -> ", g[i].x, g[i].status, g[i].leader, g[i].ft);
		tempEdge=g[i].link;
		while(tempEdge!=NULL)
		{
			printf("%d ", tempEdge->x);
			tempEdge=tempEdge->link;
		}
		printf("| ");
		tempEdge=g[i].link2;
		while(tempEdge!=NULL)
		{
			printf("%d ", tempEdge->x);
			tempEdge=tempEdge->link;
		}
		i++;
	}	
	printf("\n");
	for(i=1; i<=NO_OF_VERTICES; i++)
	{
		printf("%d:%d ",i, m[i]);
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

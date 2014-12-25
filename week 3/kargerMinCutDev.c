/*
 ============================================================================
 Introduction to Algorithms - I | Stanford University | Tim Roughgarden
 Name        : kargerMinCut.c
 Author      : Somnath Saha 
 Description : Karger's Minimum Contraction in the prescribed format
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 200
#define VERTICES 4

void createGraph(int g[200][200]);
void displayGraph(int g[200][200]);
int countEdge(int g[200][200]);
int countVertices(int g[200][200]);
int Random (int, int);//Random Number Generator (lower and upper included)
void kargerMinCut(int g[200][200]);
void setEdges(int g[200][200]);

int g[200][200];

int main()
{
	createGraph(g);
	setEdges(g);
	displayGraph(g);
	kargerMinCut(g);	
	displayGraph(g);	
	return 0;
}

void kargerMinCut(int g[200][200])
{
	int r, s, i=0, pos;
	srand(time(NULL));
	while(countVertices(g)>2)
	{
		/*if (flg==0)
		{
			flg++;
			r=7;
		}
		else
			r=2;*/
		
		int z=countEdge(g);
		r=Random(1, (2*z)); 	
		printf("\nr=%d, edges=%d", r, z);
		
		//r=6;
		i=0;
		s=g[0][199];
		while(r>s)
		{
			i++;
			s+=g[i][199];
		}
		pos=r-(s-g[i][199]);
		printf("for g[i][pos] i=%d, pos=%d. \n", i, pos);
		//g[i][pos]
		//Replace all occurences of i+1 in the graph with g[i][pos]
		printf("Replace all occurences of i+1 in the graph with g[i][pos]\n");
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
		displayGraph(g);
		printf("\nAdd all edges of vertex value i+1 to in row no. (g[i][pos]-1)\n");
		//Add all edges of vertex value i+1 to in row no. (g[i][pos]-1)
		j=1;
		row=g[i][pos]-1;
		col=g[row][199]+1;
		while(g[i][j]!=0)
		{
			g[row][col++]=g[i][j++];
			g[row][199]++;
		}
		displayGraph(g);
		printf("\nRemoving Self loops: ");
		//Remove all self loops
		j=1;
		while(g[row][j]!=0)
		{
			if(g[row][j]==row+1)
			{
				g[row][j]=g[row][g[row][199]];
				g[row][g[row][199]]=0;
				g[row][199]--;
				j--;
			}
			j++;
		}
		displayGraph(g);
		//setEdges not required
		printf("\nFinal: ");
		g[i][0]=0;
		g[i][199]=0;
		displayGraph(g);

		
	}
}

int Random (int _iMin, int _iMax) 
{ 
	return (_iMin + (rand () % (_iMax-_iMin+1))); 
}

void createGraph(int g[200][200])
{
	int i, j, count;
	char ch, s[5];
	long int pos=0;	
	for(i=0; i<N; ++i)
	{
		for(j=0; j<200; ++j)
		{
			g[i][j]=0;
		}
	}
	FILE * fp=fopen("file", "r");
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
	fclose(fp);	
}

void setEdges(int g[200][200])
{
	//Set no. of edges in end
	int edges=0, i=0, j=0;
	for(i=0; i<N; ++i)
	{
		edges=0;
		for(j=1; j<N; ++j)
		{
			if(g[i][j]==0)
				break;
			edges++;
		}
		g[i][199]=edges;
	}
}

void displayGraph(int g[200][200])
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
		printf("e= %d", g[i][199]);
		printf("\n");
	}		
}

int countVertices(int g[200][200])
{
	int n=0, i;
	for(i=0; i<N; ++i)
	{
		if(g[i][199]>0)
			n++;
	}
	return n;		
}

int countEdge(int g[200][200])
{
	int i=0, t_edges=0;
	for(i=0; i<N; ++i)
	{
		//edges=0;
		if(g[i][0]==0) 
			continue;
		else
			t_edges+=g[i][199];
		/*
		for(j=1; j<N; ++j)
		{
			printf("\ng[%d][%d]=%d", i, j, g[i][j]);
			if(g[i][j]==0)
				break;
			edges++;
		}*/
		//printf(" thus, Adding %d to %d=total for i=%d", edges, t_edges, i);
	}
	return (t_edges/2);		
}

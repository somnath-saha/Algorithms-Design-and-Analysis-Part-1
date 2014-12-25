#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

int Random (int _iMin, int _iMax) 
{ 
return (_iMin + (rand () % (_iMax-_iMin+1))); 
} 

int main (void) 
{ 
	int iRandom, i=0; 

	srand (time (NULL)); 
	for(i=0; i<10; ++i)
	{
		iRandom = Random (0,10); 
		printf ("\nRandom : %d", iRandom); 
	}
	return 0; 
}

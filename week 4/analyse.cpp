/*
 * analyse.cpp
 * 
 * Copyright 2013 T-Virus <t-virus@tvirus-virtual-machine>
 * 
 */


#include <iostream>
#include <stdio.h>

using namespace std;
struct node
{
	unsigned long x;
	unsigned long y;
	} s[875714];

int main(int argc, char **argv)
{
	FILE *fm;
	unsigned long i=0,j,l,a,b,c,d;
	while(i<875714)
	{
		s[i].x=i+1;
		s[i].y=0;
		i++;
		}
	fm=fopen("leader.txt","r");
	i=0;
	while(!feof(fm))
	{
		fscanf(fm,"%ld",&j);
		s[j-1].y++;
		}
	l=s[i].y;
	while(i<875714)
	{
		if(l<s[i].y)
		{
			l=s[i].y;
			}
		i++;
		}
		cout<<l<<"\n";
	i=0;	
	a=s[i].y;
	while(i<875714)
	{
		if(a<s[i].y && s[i].y<l)
		{
			a=s[i].y;
			}
		i++;
		}
		cout<<a<<"\n";
		i=0;	
	b=s[i].y;
	while(i<875714)
	{
		if(b<s[i].y && s[i].y<a)
		{
			b=s[i].y;
			}
		i++;
		}
		cout<<b<<"\n";
		i=0;	
	c=s[i].y;
	while(i<875714)
	{
		if(c<s[i].y && s[i].y<b)
		{
			c=s[i].y;
			}
		i++;
		}
		cout<<c<<"\n";
		i=0;	
	d=s[i].y;
	while(i<875714)
	{
		if(d<s[i].y && s[i].y<c)
		{
			d=s[i].y;
		}
		i++;
	}
		cout<<d;
	
	
	
	return 0;
}


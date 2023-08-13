//Link.cpp

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;
#include "Link.h"  // Class definition

BOOL Free_Array(char s[], int size)
{
	int j;
	for(j=0; j < size; j++)
	{
		s[j] = '\0';
	}
	return TRUE;
}

Link::Link(void)
{
}


Link::~Link(void)
{
}

void Link::fill(char s[])
{
	int  Field, k, flag, j;
	char c1[] = ";" ;
	char c2[20];

	Field = flag = j = 0;
	From_Node = 0;
	To_Node	  = 0;
	Length	  = 0.0;

	for (k = 0; (k < 200) && (s[k] != '\0') ; k++)
	{
		if (s[k] == c1[0])
				flag = 1;

		if (flag == 0) // Fill c2
		{
			c2[j] = s[k];
			j++;
		}

		if (flag == 1) // ";" catched
		{
			switch(Field)
			{
				case 0:
					From_Node = atoi(c2);
				break;

				case 1:
					To_Node = atoi(c2);
				break;
			}		
			Free_Array(c2, 20);
			flag = 0;
			j = 0;
			Field++;
		}
	}
	if (From_Node == To_Node) 
	{
		Length = INFINITY;
		return;	
	}
	Length = atof(c2);
	return ;
}

void Link::write(char ff[20])
{
	ofstream fn;	
	fn.open(ff,ios::app); // open file in append mode

	fn.setf(ios::right);
	fn.width(10);
	fn  << From_Node;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);	
	fn  << To_Node;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);	
	fn  << Length << '\n';	

	fn.close();
};

int Link::get_From_Node()
{
	return From_Node;
};

int Link::get_To_Node()
{
	return To_Node;
};

double Link::get_Length()
{
	return Length;
};
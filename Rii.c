#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned int u32; 

struct vertex
{
	u32 name;
	u32 color; //Structure type declarations do not support initializers
	u32 grade;
	u32 a_pos; //position in neighbour array
};

int main()
{
	unsigned int n = 0;
	unsigned int m = 0;
	int c = 0;
	char prev = 'a';
	char edge[50] = {0};
	int i = 0;
	while(true) //module to ignore comments
	{
		prev = (char)c;
		c = fgetc(stdin);
		if((char)c == 'p' && (prev == '\n' || prev == '\r') )
		{	
			break;
		}
	}
	scanf("%s",edge);// %s\n breaks my inputs
	scanf("%d",&n);
	scanf("%d",&m);
	printf("el valor de n es: %d\n", n);
	printf("el valor de m es: %d\n", m);
}
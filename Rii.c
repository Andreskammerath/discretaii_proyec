#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


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
	scanf("%s\n",edge);
	scanf("%d\n",&n);
	scanf("%d\n",&m);
	printf("%s\n",edge);
	printf("el valor de n es: %d\n", n);
	printf("el valor de m es: %d\n", m);

}
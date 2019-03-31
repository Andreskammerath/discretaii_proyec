#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


int main()
{
	unsigned int n = 0;
	unsigned int m = 0;
	int c = 0;
	char edge[50] = {0};
	int i = 0;
	while(true) //module to ignore comments
	{
		++i;
		c = 0;
		c = fgetc(stdin);
		if((char)c == 'p' )
		{	
			printf("entró en el if \n");
			break;
		}
		// int len = strlen(line);

		// while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
  //           line[--len] = 0;    /* strip newline or carriage rtn    */


  //       while (*p == ' ')     advance to first non-whitespace  
  //           p++;

  //       /* skip lines beginning with 'c' or blank lines  */
  //       if (*p == 'c' || !*p)
  //           continue;

  //       if(*p == 'p')
  //       	break;
	}

	scanf("%s\n",edge);
	scanf("%d\n",&n);
	scanf("%d\n",&m);
	printf("%s\n",edge);
	printf("el valor de n es:%d\n", n);
	printf("el valor de m es:%d\n", m);
	//como crear un string char por char ó scanf los numeros n y m en el string line(ver mejor opción)
	// while(true) //looking for n value
	// {
	// 	if(*p > 47 && *p < 72) 
	// }



}
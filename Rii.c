#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAXS 256 //¿cuantos caracteres como maximo puede tener una linea? 

int main()
{
	unsigned int n,m = 0;
	char line[MAXS] = {0};
	while(fgets (line, MAXS, stdin) != NULL) //module to ignore comments
	{
		char *p = line;
		int len = strlen(line);

		while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
            line[--len] = 0;    /* strip newline or carriage rtn    */


        while (*p == ' ')    /* advance to first non-whitespace  */
            p++;

        /* skip lines beginning with 'c' or blank lines  */
        if (*p == 'c' || !*p)
            continue;

        if(*p == 'p')
        	break;
	}

	printf("%s\n",line);
	//como crear un string char por char ó scanf los numeros n y m en el string line(ver mejor opción)
	// while(true) //looking for n value
	// {
	// 	if(*p > 47 && *p < 72) 
	// }



}
#include "Rii.h"

#include <stdlib.h>

void cambiar(u32* array, u32* array2, u32* array3, u32* array4)
{
 	u32* a = array;
 	u32* b = array2;
 	u32 tmp = *array2; 
 	*b = *a;
 	*a = tmp;
 	a = array3;
 	b = array4;
 	tmp = *array4; 
 	*b = *a;
 	*a = tmp;
}
// void quick_sort(u32* array, u32* array2, u32 com, u32 fin, u32* array3, u32* array4)
// {
// 	if(com >= fin)
// 	{
// 		return;
// 	}
// }
Grafostv* ConstruccionDelGrafo()
{
	Grafostv* G = (Grafostv*)malloc(sizeof(Grafostv));
	u32 n = 0; //number of vertexs
	u32 m = 0; //number of edges
	u32 v = 0; //vertex name
	u32 w = 0; // vertex name
	int c = 0; //auxiliar char needed for fgetc function
	char prev = 'a';
	char edge[50] = {0};
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
	// printf("%u %u\n", n, m );
	G->color = (u32*)malloc(sizeof(u32) * n);
	G->orden = (u32*)malloc(sizeof(u32) * n);
	G->grado = (u32*)malloc(sizeof(u32) * n);
	G->vecinos = (u32**)(malloc(sizeof(u32*) * 2));
	for (int i = 0; i < 2; ++i)
	{
		G->vecinos[i] = (u32*)malloc(sizeof(u32)*2*m);
	}
	for (int i = 0; i < 2*m; i += 2)
	{	
		if(scanf(" %c %u %u",&prev, &v, &w) != 3 || prev != 'e')
		{
			free(G->color);
			free(G->orden);
			free(G->grado);
			return NULL;
		}
		G->vecinos[0][i] = v;
		G->vecinos[1][i] = w;
		G->vecinos[0][i+1] = w;
		G->vecinos[1][i+1] = v;
	}
	cambiar(&G->vecinos[0][1],&G->vecinos[0][3],&G->vecinos[1][1],&G->vecinos[1][3]);
	return G;
}
int main()
{
	// begin of create graph
	Grafostv* ptr = ConstruccionDelGrafo();
	for (int j = 0; j < 14; ++j)
	{
		printf("%u ------ %u\n",ptr->vecinos[0][j], ptr->vecinos[1][j] );
	}
	return 0;
}
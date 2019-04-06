#include "Rii.h"

Grafost* ConstruccionDelGrafo()
{
	Grafost* G = malloc(sizeof(Grafost));
	u32 n = 0; //number of vertexs
	u32 m = 0; //number of edges
	u32 v = 0;
	u32 w = 0;
	int c = 0; //auxiliar char needed for fgetc function
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
	G->vertices = malloc(sizeof(u32) * n);
	G->color = malloc(sizeof(u32) * n);
	G->orden = malloc(sizeof(u32) * n);
	G->grado = malloc(sizeof(u32) * n);
	G->ocupado = malloc(sizeof(u32) * n);
	memset(G->ocupado,0,sizeof(u32) * n);
	G->vecinos = malloc(sizeof(vector) * n);
	for (int i = 0; i < m; ++i)
	{
		if(scanf("%c %u %u",&prev, &v, &w) != 3 || prev != 'e')
		{
			free(G->vertices);
			free(G->color);
			free(G->orden);
			free(G->grado);
			free(G->vecinos);
			return NULL;
		}


	}
}

int main()
{
	// begin of create graph
	Grafost* ptr = ConstruccionDelGrafo();
}
#include "Rii.h"

u32 binarySearch(u32* arr, u32 l, u32 r, u32 x) 
{ 
	if (r >= l) { 
		u32 mid = l + (r - l) / 2; 
		if (arr[mid] == x) 
			return mid; 
      	if (arr[mid] > x) 
        	return binarySearch(arr, l, mid - 1, x);
     	return binarySearch(arr, mid + 1, r, x); 
  	} 
  	return 0; 
}

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
void quick_sort(u32* array, u32 com, u32 fin, u32* array3)
{
	if (com >= fin) return;
  	u32 pivot = array[fin];
  	u32 cnt = com;
  	for (u32 i = com; i <= fin; i++)
  	{
    	if (array[i] <= pivot)
     	{
          cambiar(&array[cnt], &array[i], &array3[cnt], &array3[i]);
          cnt++;
      	}
  	}
  	quick_sort(array, com, cnt-2, array3); // Recursively sort the left side of pivot
  	quick_sort(array, cnt, fin, array3);   // Recursively sort the right side of pivot
}

void copiarAVertice(u32* vertices, u32* vecinos, u32* grados, u32* orden, u32* indEnVecinos, u32 m)
{
	u32 j = 0;
	u32 grado = 0;
	for (u32 i = 0; i < m; ++i)
	{
    	if(vecinos[i] == vertices[j])
      		grado++;
    	else
    	{
			grados[j] = grado;
			++j;
			indEnVecinos[j] = i;
			vertices[j] = vecinos[i];
			grado = 1;
			orden[j] = j;
		}
  	}
  	grados[j] = grado;
}

u32 Greedy(Grafostv* G)
{
    u32 max_color = 0;
    u32 nVer = G->n;
    u32 indice = binarySearch(G->vertices,0,nVer-1,G->orden[0]);
  	G->color[indice] = 0;
  	G->visitados[indice] = 1;
    u32 indice2 = 0; 
  	for (u32 i = 1; i < nVer; ++i)
  	{
	    indice = binarySearch(G->vertices,0,nVer-1,G->orden[i]);
	    G->visitados[indice] = 1;
	    u32 color = 0;
	    u32 rompelo = 0;
	    u32 flag = 1;
	    while(flag)
    	{
        	rompelo = 0;
        	for (u32 i = 0; i < G->grados[indice]; ++i)
        	{
            	indice2 = binarySearch(G->vertices,0,nVer-1,G->vecinos[1][G->indEnVecinos[indice]+i]);
                if(G->color[indice2] == color && G->visitados[indice2]) color++;
                else
                {
                    rompelo++;
                    if(rompelo == G->grados[indice]) flag = 0;
                }
        	}
    	}
    	G->color[indice] = color;
    	if(color > max_color) max_color = color;
  	}
  	return max_color+1;
}

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
      		break;
  	}
  	if (scanf("%s" "%u" "%u", edge, &n, &m))
  		printf("Vertices: %u. Aristas: %u\n", n, m);

	G->m = m;
	G->n = n;
	G->color = (u32*)malloc(sizeof(u32) * n);
	G->orden = (u32*)malloc(sizeof(u32) * n);
	G->grados = (u32*)malloc(sizeof(u32) * n);
	G->indEnVecinos = (u32*)malloc(sizeof(u32) * n);
	G->vecinos = (u32**)malloc(sizeof(u32*) * 2);
	G->vertices = (u32*)malloc(sizeof(u32*) * n);
	G->visitados = (u32*)malloc(sizeof(u32*) * n);
  	for (u32 i = 0; i < 2; ++i)
  	{
    	G->vecinos[i] = (u32*)malloc(sizeof(u32)*2*m);
  	}
  	for (u32 i = 0; i < 2*m; i += 2)
  	{ 
    	if(scanf(" %c %u %u",&prev, &v, &w) != 3 || prev != 'e')
    	{
	      free(G->color);
	      free(G->orden);
	      free(G->grados);
	      return NULL;
    	}
	    G->vecinos[0][i] = v;
	    G->vecinos[1][i] = w;
	    G->vecinos[0][i+1] = w;
	    G->vecinos[1][i+1] = v;
  	} 
	quick_sort(G->vecinos[0], 0, 2*m-1, G->vecinos[1]);
	G->vertices[0] = G->vecinos[0][0];
	copiarAVertice(G->vertices,G->vecinos[0],G->grados, G->orden, G->indEnVecinos, 2*m);
	memset(G->visitados,0,n*sizeof(u32));
	memcpy(G->orden,G->vertices,n*sizeof(u32)); 
	G->max = Greedy(G);
	return G;
}

int main()
{
	// begin of create graph
	Grafostv* G = ConstruccionDelGrafo();
	// u32 color = Greedy(ptr);
	//u32 m = ptr->m;
	// for (int j = 0; j < 2*m; ++j)
	// {
	//  printf("%u ------ %u\n",ptr->vecinos[0][j], ptr->vecinos[1][j] );
	// }
	u32 n = G->n;
	for (u32 i = 0; i < n; ++i)
	{
		// printf("%u\n", G->indEnVecinos[i]);
		printf("el vertice es:%u ", G->vertices[i]);
		// printf("el indEnVecino es:%u ", ptr->indEnVecinos[i]);
		printf("el color es:%u \n", G->color[i]);
	}
	printf("el color máximo es: %u\n",G->max);
	// u32 x = binarySearch(ptr->vertices,0,n-1,7);
	return 0;
}
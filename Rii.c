#include "Rii.h"

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
        // Base case: No need to sort arrays of length <= 1
        if (com >= fin)
        {
            return;
        }
        // Choose pivot to be the last element in the subarray
        u32 pivot = array[fin];

        // Index indicating the "split" between elements smaller than pivot and 
        // elements greater than pivot
        u32 cnt = com;

        // Traverse through array from l to r
        for (u32 i = com; i <= fin; i++)
        {
            // If an element less than or equal to the pivot is found...
            if (array[i] <= pivot)
            {
                // Then swap arr[cnt] and arr[i] so that the smaller element arr[i] 
                // is to the left of all elements greater than pivot
                cambiar(&array[cnt], &array[i], &array3[cnt], &array3[i]);

                // Make sure to increment cnt so we can keep track of what to swap
                // arr[i] with
                cnt++;
            }
        }
        // NOTE: cnt is currently at one plus the pivot's index 
        // (Hence, the cnt-2 when recursively sorting the left side of pivot)
        quick_sort(array, com, cnt-2, array3); // Recursively sort the left side of pivot
        quick_sort(array, cnt, fin, array3);   // Recursively sort the right side of pivot
}

void copiarAVertice(u32* vertices, u32* vecinos,u32 m)
{
	u32 j = 0;
	for (u32 i = 0; i < m; ++i)
	{
		if(vecinos[i] != vertices[j])
		{
			++j;
			vertices[j] = vecinos[i];
		}
	}
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
		{	
			break;
		}
	}
	scanf("%s",edge);// %s\n breaks my inputs
	scanf("%d",&n);
	scanf("%d",&m);
	// printf("%u %u\n", n, m );
	G->n = n;
	G->color = (u32*)malloc(sizeof(u32) * n);
	G->orden = (u32*)malloc(sizeof(u32) * n);
	G->grado = (u32*)malloc(sizeof(u32) * n);
	G->vecinos = (u32**)malloc(sizeof(u32*) * 2);
	G->vertices = (u32*)malloc(sizeof(u32*) * n);
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
			free(G->grado);
			return NULL;
		}
		G->vecinos[0][i] = v;
		G->vecinos[1][i] = w;
		G->vecinos[0][i+1] = w;
		G->vecinos[1][i+1] = v;
	}	
	quick_sort(G->vecinos[0], 0, 2*m-1, G->vecinos[1]);
	G->vertices[0] = G->vecinos[0][0];
	copiarAVertice(G->vertices,G->vecinos[0],2*m); 

	return G;
}
int main()
{
	// begin of create graph
	Grafostv* ptr = ConstruccionDelGrafo();
	//u32 m = ptr->m;
	/*for (int j = 0; j < 2*m; ++j)
	{
		printf("%u ------ %u\n",ptr->vecinos[0][j], ptr->vecinos[1][j] );
	}
	u32 n = ptr->n;
	for (int i = 0; i < n; ++i)
	{
		printf("%u\n", ptr->vertices[i]);
	}*/
	return 0;
}
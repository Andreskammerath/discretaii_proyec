#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Rii.h"

int compare ( const void *pa, const void *pb ) {
    const u32 *a = *(const u32 **)pa;
    const u32 *b = *(const u32 **)pb;
    if(a[0] == b[0])
        return a[1] - b[1];
    else
        return a[0] - b[0];
}

int comOrdenNat (const void * a, const void * b) //what is it returning?
{
   u32 val1 = *(u32*)a;
   u32 val2 = *(u32*)b;
   return ( val1 - val2 ); 
}

/*int compare_vertices(const void *v1, const void *v2) {
    u32 *vert_degree;
    u32 degree1 = vert_degree[*(const u32 *)v1 - 1];
    u32 degree2 = vert_degree[*(const u32 *)v2 - 1];
    if (degree1 > degree2) {
        return -1;
    } else if (degree1 < degree2) {
        return 1;
    } else {
        return 0;
    }
}*/

void DestruccionDelGrafo (Grafostv* G)//anda perfecto
{
    u32 m = G->m;
    for (u32 i = 0; i < 2*m; i++) {
        free (G->vecinos[i]);
    }
    free(G->color);
    free(G->grados);
    free(G->orden);
    free(G->indEnVecinos);
	free(G->vecinos);
	free(G->vertices);
    free(G->visitados);
    free(G);
    G = NULL;
}
u32 NumeroDeVertices (Grafostv* G)//anda bien
{
    return G->n;
}

u32 NumeroDeLados (Grafostv* G)//anda bien
{
    return G->m;
}

/*u32 NumeroDeColores (Grafostv* G){
    return G->color; //DUDAAAAAAAAAAAA
}
*/
u32 NombreDelVertice (Grafostv* G, u32 i)//anda perfecto
{
    return G->orden[i];
}

u32 ColorDelVertice (Grafostv* G, u32 i)//anda perfecto
{
    if (i >= NumeroDeVertices(G))
    {
        return 4294967295;
    }
    u32 indice = binarySearch(G->vertices,0,(G->n)-1,G->orden[i]);
    return G->color[indice];
}

u32 GradoDelVertice (Grafostv* G, u32 i)
{
if (i >= NumeroDeVertices(G))
    {
        return 4294967295;
    }
    u32 indice = binarySearch(G->vertices,0,(G->n)-1,G->orden[i]);
    return G->grados[indice];
}

u32 ColorJotaesimoVecino(Grafostv* G, u32 i,u32 j) //vecino num j
{
    if (i >= NumeroDeVertices(G) || j >= GradoDelVertice(G,i))
    {
        return 4294967295; //2^32-1
    }
    u32 indice = binarySearch(G->vertices,0,(G->n)-1,G->orden[i]);
    u32 indice2 = binarySearch(G->vertices,0,(G->n)-1,G->vecinos[G->indEnVecinos[indice]+j][1]);
    return ColorDelVertice(G, indice2);
}

u32 NombreJotaesimoVecino(Grafostv* G, u32 i,u32 j)
{
    if (i >= NumeroDeVertices(G) || j >= GradoDelVertice(G,i))
    {
        return 4294967295; //2^32-1
    }
    u32 indice = binarySearch(G->vertices,0,(G->n)-1,G->orden[i]);
    u32 indice2 = binarySearch(G->vertices,0,(G->n)-1,G->vecinos[G->indEnVecinos[indice]+j][1]);
    return NombreDelVertice(G, indice2);
}

char OrdenNatural(Grafostv* G)
{
    qsort(G->orden, G->n, sizeof(u32), comOrdenNat);
    return 0;
}
char SwitchVertices(Grafostv* G, u32 i, u32 j)
{
    if (i < NumeroDeVertices(G) || j < NumeroDeVertices(G))
    {
        u32 tmp = G->orden[i];
        G->orden[i] = G->orden[j];
        G->orden[j] = tmp;
        return 0;
    }
    else
        return 1;
}
/*
char OrdenWelshPowell(Grafostv* G)
{
    u32 *vert_degree;
    vert_degree = G->grados;
    qsort(G->orden, G->n, sizeof(G->orden[0]), compare_vertices);

    return 0;
}*/
/*
char RMBCnormal(Grafostv* G)
{

}*/
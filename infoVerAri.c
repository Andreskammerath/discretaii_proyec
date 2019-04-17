#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Rii.h"

void DestruccionDelGrafo (Grafostv* G){
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
u32 NumeroDeVertices (Grafostv* G){
    return G->n;
}

u32 NumeroDeLados (Grafostv* G){
    return G->m;
}

/*u32 NumeroDeColores (Grafostv* G){
    return G->color; //DUDAAAAAAAAAAAA
}*/

u32 NombreDelVertice (Grafostv* G, u32 i){
    return G->vertices[i];
}

u32 ColorDelVertice (Grafostv* G, u32 i){
    return G->color[i];
}

u32 GradoDelVertice (Grafostv* G, u32 i){
    return G->grados[i];
}
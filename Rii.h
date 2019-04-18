#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "vector.h"

typedef unsigned int u32; 

typedef struct Grafost
{
	u32** vecinos;
	u32* vertices;  // Posicion de los vertices
	u32* color; //Structure type declarations do not support initializers
	u32* grados;
	u32* orden; //it has the index of the vertex array not the name of vertex
	u32* visitados;
	u32 m; //number of edges
	u32 n; // number of vertex
	u32 max; // number of colors
	u32* indEnVecinos;
} Grafostv;


void cambiar(u32* array, u32* array2, u32* array3, u32* array4);

void quick_sort(u32* array, u32 com, u32 fin, u32* array3);

void DestruccionDelGrafo (Grafostv* G);

u32 NumeroDeVertices (Grafostv* G);

u32 NumeroDeLados (Grafostv* G);

//u32 NumeroDeColores (Grafostv* G);


//Los nombres van a estar odenados de menor a mayor. 
u32 NombreDelVertice (Grafostv* G, u32 i);

u32 ColorDelVertice (Grafostv* G, u32 i);

u32 GradoDelVertice (Grafostv* G, u32 i);

u32 ColorJotaesimoVecino(Grafostv * G, u32 i,u32 j);

u32 NombreJotaesimoVecino(Grafostv* G, u32 i,u32 j);

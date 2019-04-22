#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "vector.h"

typedef unsigned int u32; 

typedef struct GrafoSt
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
	// u32* orden_indice;//order of vertex by index
} GrafoSt;

typedef GrafoSt* Grafo;
struct Node{
	int data;
	struct Node *next;
};
 
typedef struct Queue {
	struct Node *front;
	struct Node *last;
	unsigned int size;
} Queue;


int compare ( const void *pa, const void *pb );

int comp_grados(const void *v1, const void *v2);

int compColoresRevierte(const void *v1, const void *v2);

int comOrdenNat (const void * a, const void * b);

void DestruccionDelGrafo (Grafo G);

u32 NumeroDeVertices (Grafo G);

u32 NumeroDeLados (Grafo G);

u32 NumeroDeColores (Grafo G);

u32 binarySearch(u32* arr, u32 l, u32 r, u32 x);

u32 NombreDelVertice (Grafo G, u32 i);

u32 ColorDelVertice (Grafo G, u32 i);

u32 GradoDelVertice (Grafo G, u32 i);

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j);

u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j);

char OrdenWelshPowell(Grafo G);

char OrdenNatural(Grafo G);

char SwitchVertices(Grafo G,u32 i,u32 j);

void init(Queue *q);

int front(Queue *q);

void pop(Queue *q);

u32 empty(Queue* q);

void push(Queue *q, u32 data);

int Bipartito(Grafo G);

Grafo CopiarGrafo(Grafo G);

char RMBCrevierte(Grafo G);

char RMBCnormal(Grafo G);
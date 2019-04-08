#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "vector.h"

typedef unsigned int u32; 

typedef struct Grafost
{
	u32** vecinos;
	u32* vertices;  // Posicion de los vertices
	u32* color; //Structure type declarations do not support initializers
	u32* grado;
	u32* orden;
	u32* ocupado;
	u32 n;
} Grafostv;

void cambiar(u32* array, u32* array2, u32* array3, u32* array4);

void quick_sort(u32* array, u32 com, u32 fin, u32* array3);

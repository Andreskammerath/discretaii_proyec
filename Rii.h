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
	u32* color; //Structure type declarations do not support initializers
	u32* grado;
	u32* orden;
	u32* ocupado;
} Grafostv;

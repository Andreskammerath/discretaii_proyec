#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "vector.h"

typedef unsigned int u32; 

struct Grafost
{
	vector* vecinos;
	u32* color; //Structure type declarations do not support initializers
	u32* grado;
	u32* orden;
	u32* ocupado;
} Grafost;
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Rii.h"

u32* vert_grados;
u32* vert_color;
int comp_grados(const void *v1, const void *v2) {
    u32 degree1 = vert_grados[*(const u32 *)v1 - 1];
    u32 degree2 = vert_grados[*(const u32 *)v2 - 1];
    if (degree1 > degree2)
    {
        return -1;
    }
    else if (degree1 < degree2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int compColoresRevierte(const void *v1, const void *v2) {
    u32 color1 = vert_color[*(const u32 *)v1 - 1];
    u32 color2 = vert_color[*(const u32 *)v2 - 1];
    if (color1 > color2)
    {
        return -1;
    }
    else if (color1 < color2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int compColoresNormal(const void *v1, const void *v2) {
    u32 color1 = vert_color[*(const u32 *)v1 - 1];
    u32 color2 = vert_color[*(const u32 *)v2 - 1];
    if (color1 < color2)
    {
        return -1;
    }
    else if (color1 > color2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int compare ( const void *pa, const void *pb ) {
    const u32 *a = *(const u32 **)pa;
    const u32 *b = *(const u32 **)pb;
    if(a[0] == b[0])
        return a[1] >= b[1] ? 1 : -1;
    else
        return a[0] >= b[0] ? 1 : -1;
}

int comOrdenNat (const void * a, const void * b) //what is it returning?
{
   u32 val1 = *(u32*)a;
   u32 val2 = *(u32*)b;
   return ( val1 - val2 ); 
}

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

char OrdenWelshPowell(Grafostv* G)
{
    vert_grados = G->grados;
    qsort(G->orden, G->n, sizeof(u32), comp_grados);
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


char RMBCrevierte(Grafostv* G)
{
    vert_color = G->color;
    qsort(G->orden, G->n, sizeof(u32), compColoresRevierte);
    return 0;
}

char RMBCnormal(Grafostv* G)
{
    vert_color = G->color;
    qsort(G->orden, G->n, sizeof(u32), compColoresNormal);
    return 0;
}

void init(Queue *q) {
    q->front = NULL;
    q->last = NULL;
    q->size = 0;
}
 
int front(Queue *q) {
    return q->front->data;
}
 
void pop(Queue *q) {
    if(q->size)
    {
        q->size--;   
        struct Node *tmp = q->front;
        q->front = q->front->next;
        free(tmp);
    }

}
u32 not_empty(Queue* q)
{
    return q->size;
}
void push(Queue *q, u32 data) {
    q->size++;
 
    if (q->front == NULL) {
        q->front = (struct Node *) malloc(sizeof(struct Node));
        q->front->data = data;
        q->front->next = NULL;
        q->last = q->front;
    } else {
        q->last->next = (struct Node *) malloc(sizeof(struct Node));
        q->last->next->data = data;
        q->last->next->next = NULL;
        q->last = q->last->next;
    }
}

int Bipartito(Grafostv* G)
{
    u32* visitados = G->visitados;
    u32** aux = G->vecinos;
    Queue* hijos = (Queue*)malloc(sizeof(Queue));
    init(hijos);
    push(hijos,G->vertices[0]);
    u32 nVer = G->n;
    u32* color_vertices = (u32*)malloc(sizeof(u32) * nVer);
    memset(color_vertices,0,nVer*sizeof(u32));//arreglo auxiliar por si es Bi
    memset(visitados,0,nVer*sizeof(u32));
    u32* bip = (u32*)malloc(sizeof(u32) * 2);
    bip[0] = 0;
    bip[1] = 0;
    u32 indice2 = 0;
    u32 i = 0;
    while(not_empty(hijos) && i < 200)
    {
        u32 v = hijos->front->data;
        pop(hijos);
        u32 indice = binarySearch(G->vertices,0,nVer-1,v);
        visitados[indice] = 1;
        for (u32 i = 0; i < G->grados[indice]; ++i)
        {
            indice2 = binarySearch(G->vertices,0,nVer-1,aux[G->indEnVecinos[indice]+i][1]);
            if(G->visitados[indice2])
            {
                bip[color_vertices[indice2]] = 1;
                if(bip[0] && bip[1])
                {
                    while(not_empty(hijos))
                    {
                        pop(hijos);
                    }
                    free(hijos);
                    free(color_vertices);
                    free(bip);
                    return 0;
                }
            }
            else
            {
                push(hijos, G->vertices[indice2]);
            }
        }
        for (int i = 0; i < 2; ++i)
        {
            if(!bip[i])
            {
                color_vertices[indice] = i;
            }
        }
        memset(bip,0,2*sizeof(u32));
    }
    free(hijos);
    memcpy(G->color,color_vertices,nVer*sizeof(u32));
    free(color_vertices);
    free(bip);
    return 1;
}

/* 
// Driver code.
int main(void) {
    Queue q;
    init(&q);
    push(&q, 1);
    push(&q, 2);
    printf("%d\n", front(&q));
    pop(&q);
    printf("%d\n", front(&q));
}*/
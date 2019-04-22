#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Rii.h"

u32* vert_grados;
u32* vert_color;
u32* vertices;
u32 nr;
int comp_grados(const void *v1, const void *v2) {
    u32 degree1 = vert_grados[binarySearch(vertices,0,nr-1,*(const u32 *)v1)];
    u32 degree2 = vert_grados[binarySearch(vertices,0,nr-1,*(const u32 *)v2)];
    // printf("degreeuno: %u ", *(const u32 *)v1-1);
    // printf("degreedos: %u\n", *(const u32 *)v2-1);
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
    u32 color1 = vert_color[binarySearch(vertices,0,nr-1,*(const u32 *)v1)];
    u32 color2 = vert_color[binarySearch(vertices,0,nr-1,*(const u32 *)v2)];
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
    u32 color1 = vert_color[binarySearch(vertices,0,nr-1,*(const u32 *)v1)];
    u32 color2 = vert_color[binarySearch(vertices,0,nr-1,*(const u32 *)v2)];
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

int comOrdenNat (const void * a, const void * b)
{
    u32 val1 = *(u32*)a;
    u32 val2 = *(u32*)b;
    return val1 > val2 ? 1 : -1;
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

u32 NumeroDeColores (Grafostv* G)
{
    return G->max;
}

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
    nr = G->n;
    vert_grados = G->grados;
    vertices = G->vertices;
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
    nr = G->n;
    vert_color = G->color;
    vertices = G->vertices;
    qsort(G->orden, G->n, sizeof(u32), compColoresRevierte);
    return 0;
}

char RMBCnormal(Grafostv* G)
{
    nr = G->n;
    vert_color = G->color;
    vertices = G->vertices;
    qsort(G->orden, G->n, sizeof(u32), compColoresNormal);
    return 0;
}

Queue* init_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->last = NULL;
    q->size = 0;
    return q;
}
 
int front(Queue *q) {
    return q->front->data;
}
 
void pop(Queue *q) {
    if(q->size)
    {
        q->size--;   
        struct Node *tmp = q->front;
        if(q->size)q->front = q->front->next;
        else
        {
            q->front = NULL;
            q->last = NULL;
        }
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
    Queue* hijos = init_queue();
    push(hijos,G->vertices[0]);
    u32 nVer = G->n;
    u32* color_vertices = (u32*)malloc(sizeof(u32) * nVer);
    u32* vert_encolados = (u32*)malloc(sizeof(u32) * nVer);
    memset(color_vertices,0,nVer*sizeof(u32));//arreglo auxiliar por si es Bi
    memset(visitados,0,nVer*sizeof(u32));
    u32* bip = (u32*)malloc(sizeof(u32) * 2);
    bip[0] = 0;
    bip[1] = 0;
    u32 indice2 = 0;
    while(not_empty(hijos))
    {
        u32 v = hijos->front->data;
        pop(hijos);
        u32 indice = binarySearch(G->vertices,0,nVer-1,v);
        visitados[indice] = 1;
        for (u32 j = 0; j < G->grados[indice]; ++j)
        {
            indice2 = binarySearch(G->vertices,0,nVer-1,aux[G->indEnVecinos[indice]+j][1]);
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
                if(!vert_encolados[indice2])
                {
                    push(hijos, G->vertices[indice2]);
                    vert_encolados[indice2] = 1;
                }
            }
        }
        for (int j = 0; j < 2; ++j)
        {
            if(!bip[j])
            {
                color_vertices[indice] = j;
            }
        }
        memset(bip,0,2*sizeof(u32));
    }
    free(hijos);
    memcpy(G->color,color_vertices,nVer*sizeof(u32));
    free(color_vertices);
    free(bip);
    free(vert_encolados);
    return 1;
}

Grafostv* CopiarGrafo(Grafostv* G)
{
    u32 n = G->n;
    u32 m = G->m;
    Grafostv* G2 = (Grafostv*)malloc(sizeof(Grafostv));
    G2->m = m;
    G2->n = n;
    G2->color = (u32*)malloc(sizeof(u32) * n);
    G2->orden = (u32*)malloc(sizeof(u32) * n);
    G2->grados = (u32*)malloc(sizeof(u32) * n);
    G2->indEnVecinos = (u32*)malloc(sizeof(u32) * n);
    G2->vecinos = (u32**)malloc(sizeof(u32*) * 2*m);
    G2->vertices = (u32*)malloc(sizeof(u32*) * n);
    G2->visitados = (u32*)malloc(sizeof(u32*) * n);
    for (u32 i = 0; i < 2*m; ++i)
        G2->vecinos[i] = (u32*)malloc(sizeof(u32)*2);
    memcpy(G2->color,G->color,n*sizeof(u32));
    memcpy(G2->orden,G->orden,n*sizeof(u32));
    memcpy(G2->grados,G->grados,n*sizeof(u32));
    memcpy(G2->indEnVecinos,G->indEnVecinos,n*sizeof(u32));
    memcpy(G2->vertices,G->vertices,n*sizeof(u32));
    memcpy(G2->visitados,G->visitados,n*sizeof(u32));
    for (u32 i = 0; i < 2 * G->m; ++i)
    {
        memcpy(G2->vecinos[i],G->vecinos[i],2*sizeof(u32));
        // G2->vecinos[i][0] = G->vecinos[i][0];
        // G2->vecinos[i][1] = G->vecinos[i][1];
    }
    return G2;
}

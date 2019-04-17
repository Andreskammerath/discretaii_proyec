#include "Rii.h"

u32 binarySearch(u32* arr, u32 l, u32 r, u32 x) 
{ 
    if (r >= l) { 
        u32 mid = l + (r - l) / 2;
        if (arr[mid]  == x) 
            return mid;
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x);
    return binarySearch(arr, mid + 1, r, x); 
  }
  return 0; 
}

int compare ( const void *pa, const void *pb ) {
    const u32 *a = *(const u32 **)pa;
    const u32 *b = *(const u32 **)pb;
    if(a[0] == b[0])
        return a[1] - b[1];
    else
        return a[0] - b[0];
}

void copiarAVertice(u32* vertices, u32** vecinos1, u32* grados, u32* indEnVecinos, u32 m)
{
    u32** aux = vecinos1;
    u32 j = 0;
    u32 grado = 0;
    for (u32 i = 0; i < m; ++i)
    {
        if(aux[i][0] == vertices[j])
        grado++;
    else
    {
        grados[j] = grado;
        ++j;
        indEnVecinos[j] = i;
        vertices[j] = aux[i][0];
        grado = 1;
    }
}
    grados[j] = grado;
    printf("terminé copiarAVertice\n");
}

u32 Greedy(Grafostv* G)
{
    u32** aux = G->vecinos; 
    u32 max_color = 0;
    u32 nVer = G->n;
    u32 indice = binarySearch(G->vertices,0,nVer-1,G->orden[0]);
    G->color[indice] = 0;
    G->visitados[indice] = 1;
    u32 indice2 = 0; 
    for (u32 i = 1; i < nVer; ++i)
    {
        indice = binarySearch(G->vertices,0,nVer-1,G->orden[i]);
        G->visitados[indice] = 1;
        u32 color = 0;
        u32 rompelo = 0;
        u32 flag = 1;
        while(flag)
        {
            rompelo = 0;
            for (u32 i = 0; i < G->grados[indice]; ++i)
            {
                indice2 = binarySearch(G->vertices,0,nVer-1,aux[G->indEnVecinos[indice]+i][1]);
                if(G->color[indice2] == color && G->visitados[indice2]) color++;
                else
                {
                    rompelo++;
                    if(rompelo == G->grados[indice]) flag = 0;
                }
            }
        }
        G->color[indice] = color;
        if(color > max_color) max_color = color;
    }
    return max_color + 1;
    printf("terminé Greedy\n");
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
        if((char)c == 'p' && (prev == '\n' || prev == '\r') ) break;
    }
    if (scanf("%s" "%u" "%u", edge, &n, &m))
        printf("Vertice: %u  Arista %u\n", n, m);

    G->m = m;
    G->n = n;
    G->color = (u32*)malloc(sizeof(u32) * n);
    G->orden = (u32*)malloc(sizeof(u32) * n);
    G->grados = (u32*)malloc(sizeof(u32) * n);
    G->indEnVecinos = (u32*)malloc(sizeof(u32) * n);
    G->vecinos = (u32**)malloc(sizeof(u32*) * 2*m);
    G->vertices = (u32*)malloc(sizeof(u32*) * n);
    G->visitados = (u32*)malloc(sizeof(u32*) * n);
  
    for (u32 i = 0; i < 2*m; ++i)
        G->vecinos[i] = (u32*)malloc(sizeof(u32)*2);

    for (u32 i = 0; i < 2*m; i += 2)
    { 
        if(scanf(" %c %u %u",&prev, &v, &w) != 3 || prev != 'e')
        {
            free(G->color);
            free(G->orden);
            free(G->grados);
            return NULL;
        }
            G->vecinos[i][0] = v;
            G->vecinos[i][1] = w;
            G->vecinos[i+1][0] = w;
            G->vecinos[i+1][1] = v;
    } 
    qsort(G->vecinos, 2*m, 2*sizeof(u32), compare);
    printf("terminé el qsort\n");
    G->vertices[0] = G->vecinos[0][0];
    copiarAVertice(G->vertices,G->vecinos,G->grados, G->indEnVecinos, 2*m);
    memset(G->visitados,0,n*sizeof(u32));
    memcpy(G->orden,G->vertices,n*sizeof(u32)); 
    G->max = Greedy(G);
    printf("terminé\n");
    return G;

}
int main()
{
    // begin of create graph
    Grafostv* G = ConstruccionDelGrafo();
    //u32 color = Greedy(ptr);
    //u32 m = ptr->m;
    //for (int j = 0; j < 2*m; ++j)
    //{
    //  printf("%u ------ %u\n",ptr->vecinos[0][j], ptr->vecinos[1][j] );
    //}
    // u32 n = G->n;
    // for (int i = 0; i < n; ++i)
    // {
        //printf("los vertices son:%u\n", G->vertices[i]);
        //printf("%u ------ %u \n", G->vecinos[i][0],G->vecinos[i][1]);
        //printf("el indEnVecino es:%u ", G->indEnVecinos[i]);
        //printf("el color del vertice %u es:%u  \n", G->vertices[i], G->color[i]);
    // }
    printf("el numero de colores es: %u\n",G->max);
  // u32 x = binarySearch(ptr->vertices,0,n-1,7);
  return 0;
}
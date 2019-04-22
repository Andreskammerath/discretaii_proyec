#include "Rii.h"

u32 binarySearch(u32* arr, u32 l, u32 r, u32 x) 
{ 
    if (r >= l) 
    { 
        u32 mid = l + (r - l) / 2;
        if (arr[mid]  == x) 
            return mid;
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x);
    return binarySearch(arr, mid + 1, r, x); 
    }
    return 0; 
}

void copiarAVertice(u32* vertices, u32** vecinos1, u32* grados, u32* indEnVecinos, u32 m, u32 n)
{
    u32** aux = vecinos1;
    u32 j = 0;
    u32 grado = 0;
    u32 cont = 1;
    for (u32 i = 0; i < m; ++i)
    {
        if(aux[i][0] == vertices[j])
        {
            grado++;
        }
        else
        {
            grados[j] = grado;
            ++j;
            indEnVecinos[j] = i;
            cont++;
            vertices[j] = aux[i][0];
            grado = 1;
        }
    }  
    grados[j] = grado;
    if (cont < n) printf("es no conexo\n");
    if (cont > n) printf("TENES MAS VERTICES\n");

}

u32 Greedy(Grafostv* G)
{
    printf("entré a Greedy\n");
    u32** aux = G->vecinos; 
    u32 max_color = 0;
    u32 nVer = G->n;
    memset(G->color,0,nVer*sizeof(u32));
    memset(G->visitados,0,nVer*sizeof(u32));
    u32* color_vecinos = (u32*)malloc(sizeof(u32) * nVer);
    memset(color_vecinos,0,nVer*sizeof(u32));
    u32 indice = binarySearch(G->vertices,0,nVer-1,G->orden[0]);
    G->color[indice] = 0;
    G->visitados[indice] = 1;
    u32 indice2 = 0;
    u32 reset = 0; 
    for (u32 i = 1; i < nVer; ++i)
    {
        memset(color_vecinos,0,(reset+1)*sizeof(u32));
        indice = binarySearch(G->vertices,0,nVer-1,G->orden[i]);
        G->visitados[indice] = 1;
        u32 color = 0;
        reset = 0;
        for (u32 i = 0; i < G->grados[indice]; ++i)
        {
            indice2 = binarySearch(G->vertices,0,nVer-1,aux[G->indEnVecinos[indice]+i][1]);
            if(G->visitados[indice2])
            {
                color_vecinos[G->color[indice2]] = 1;
                if(reset < G->color[indice2]) reset = G->color[indice2];
            }
        }
        for (u32 i = 0; i < nVer; ++i)
        {
            if(!color_vecinos[i])
            {
                color = i; 
                break;
            }
        }
        G->color[indice] = color;
        if(color > max_color) max_color = color;
        if(reset < color) reset = color;
        if(reset == nVer) reset--;
    }
    free(color_vecinos);
    return max_color + 1;
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
        printf("Verti  ce: %u  Arista %u\n", n, m);

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
            for (u32 i = 0; i < 2*m; i++) 
            {
                free (G->vecinos[i]);
            }
            free(G->vecinos);
            free(G->vertices);
            free(G->visitados);
            free(G->indEnVecinos);
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
    copiarAVertice(G->vertices,G->vecinos,G->grados, G->indEnVecinos, 2*m,n);
    memset(G->visitados,0,n*sizeof(u32));
    memcpy(G->orden,G->vertices,n*sizeof(u32));
    G->max = Greedy(G);
    // printf("terminé Greedy\n");
    return G;

}
int main()
{
    // begin of create graph
    Grafostv* G = ConstruccionDelGrafo();
    Grafostv* G2 = CopiarGrafo(G);
    //u32 color = Greedy(ptr);
    //u32 m = ptr->m;
    //for (int j = 0; j < 2*m; ++j)
    //{
    //  printf("%u ------ %u\n",ptr->vecinos[0][j], ptr->vecinos[1][j] );
    //}
     
    //u32 n = G->n;
     /*
     //qsort(G->orden, n, sizeof(ParGradoOrden), comGrado);
     for (u32 i = 0; i < n; ++i)
     {
        //printf("los vertices son:%u\n", G->vertices[i]);
        //printf("%u ------ %u \n", G->vecinos[i][0],G->vecinos[i][1]);
        //printf("el indEnVecino es:%u ", G->indEnVecinos[i]);
        //printf("el color del vertice %u es:%u  \n", G->vertices[i], G->color[i]);
        //printf("Orden natural (Vertices ordenados):  %c\n", OrdenNatural(G));
        //printf("los vertices son %u\n: ", G->grados[G->orden[n]-1]);
     }
     */
//G->vecinos[G->indEnVecinos[0]][1]
    // printf("\n\n---Greedy---  Número máximo de colores con Greedy: %u\n",G->max);
    // OrdenNatural(G);
    // printf("---Orden Natural---   Número máximo con Orden Natural: %u\n", Greedy(G));
    //u32 min = 999999999;
    //u32 x = 0;
    // RMBCnormal(G);
    // for (int i = 0; i < G->n; ++i)
    // {
    //     printf("vertice:%u  color:%u\n",G->orden[i],G->color[binarySearch(G->vertices,0,(G->n)-1,G->orden[i])]);        
    // }    
    //printf("---SwitchVertices---   Número máximo con SwitchVertices: %u\n", min);
    // for (u32 i = 0; i < 2*G->m; ++i)
    // {
    RMBCrevierte(G2);
    for (int i = 0; i < G->n; ++i)
    {
        printf("%u %u\n",G2->orden[i],G2->color[binarySearch(G->vertices,0,(G->n)-1,G2->orden[i])]);
    }
      printf("Greedy:%u %u\n",Greedy(G2),Bipartito(G2));
    // }
    // printf("%u \n\n",NombreJotaesimoVecino(G,1,1));
    // for (u32 i = 0; i < G->n; ++i)v
    // {
    //   printf("vertice:%u ------- color:%u \n",G->orden[i],G->color[i]);
    // }
    /*printf("El número de vertices es %u\n", NumeroDeVertices(G));
    printf("El núumero de lados es %u\n", NumeroDeLados(G));
    printf("El nombre del vértice es 4 es %u\n", NombreDelVertice(G, 4));
    printf("El color del vértice 8 es %u\n", ColorDelVertice(G, 8));
    printf("El grado del vértice 8 es %u\n", GradoDelVertice(G,8));
    printf("El color del segundo vecino del vértice 2 es %u\n", ColorJotaesimoVecino(G,1,1));
    printf("El nombre del segundo vecino del vértice 2 es %u\n", NombreJotaesimoVecino(G, 1, 1));*/
    DestruccionDelGrafo(G);
  return 0;
}
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct Grafo
{
    int arestas;
    int vertices;
    int **matriz;
}Grafo;

int **IniciarMatriz (int quantidade)
{
    int **matriz = malloc(sizeof (int*) * quantidade);
    int i, j;

    for(i = 0; i < quantidade; i++)
        matriz[i] = malloc(sizeof(int) * quantidade);

    for(i = 0; i < quantidade; i++)
        for(j = 0; j < quantidade; j++)
            matriz[i][j] = 0;

    return matriz; 
}

Grafo *IniciarGrafo (int quantidade)
{
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->arestas = 0;
    grafo->vertices = quantidade;
    grafo->matriz = IniciarMatriz(quantidade);

    return grafo;
}

//Essa função adapta a função do exercício de converter direcionado para não direcionado
//A maioria das funções para criar o grafo foram feitas com adaptação daquela função
Grafo *CriarGrafoDirecionado (int quantidade)
{
   Grafo *grafo = IniciarGrafo(quantidade);
   int i, j, x;

    for(i = 0; i < quantidade; i++)
            for(j = 0; j < quantidade; j++)
            {
                scanf ("%d", &x);
                if(grafo->matriz[i][j] == 0)
                {
                    grafo->matriz[i][j] = x;
                }
                grafo->arestas++;
            }

    return grafo;
}

void VerificarLaco(Grafo *grafo, int quantidade)
{
    int cont = 0;

    printf("Laco no vertice");

    //Esse "for" para percorrer apenas os vértices do grafo, as arestas serão verificadas dentro dele
    //Como o objetivo não é percorrer a matriz, serve um "for" simples
    for(int i = 0; i < quantidade; i++)
        //Para haver um laço, a matriz deve ser 1 quando a linha for igual à coluna
        if(grafo->matriz[i][i] == 1)
        {
            printf("\n%d", i);
            //A variável cont serve para verificar no "if" de fora do "for"
            cont++;
        }

    //Se não houver laços, cont continuará igual à 0 
    if(cont == 0)
        printf("\n-");
}

int main() {

    int quantidade;
    scanf("%d", &quantidade);

    Grafo *grafo = CriarGrafoDirecionado (quantidade);

   VerificarLaco(grafo, quantidade);
    

    return 0;
}

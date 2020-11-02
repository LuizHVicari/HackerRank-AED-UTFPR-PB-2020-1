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

void VerificarRegularidade(Grafo *grafo, int quantidade)
{
    int cont[quantidade], aux, i, j, verificador = 0;

    for(i = 0; i < quantidade; i++)
        cont[i] = 0;

    for(i = 0; i < quantidade; i++)
        for(j = 0; j < quantidade; j++)
            if(grafo->matriz[i][j] > 0)
                cont[i]++;

    aux = cont[0];

    for(i = 1; i < quantidade; i++)
    {
        if (aux != cont[i])
            verificador++;
    }

    if(verificador > 0)
        printf("nao");

    else
        printf("sim");
    
}

int main() {

    int quantidade, num1 = 0, num2;
    scanf("%d", &quantidade);

    Grafo *grafo = CriarGrafoDirecionado (quantidade);

    VerificarRegularidade(grafo, quantidade);
    

    return 0;
}

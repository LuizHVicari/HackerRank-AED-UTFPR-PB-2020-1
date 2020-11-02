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

void VerificarAdjacencia(Grafo *grafo, int num1, int num2, int quantidade)
{
    //Verifica se os dois nós eistem no grafo, se não pertencerem, imprime não
    if(num1 < quantidade && num2 < quantidade && num1 >= 0 && num2 >= 0)
    {
        //Verifica a adjacência, se existir, em qualquer direção, imprime 1
        //Alteração em relação à função anterior: na anterior, o grafo funcionava como um não direcionado, transformando-o na função de criar 
        if(grafo->matriz[num1][num2] == 1 || grafo->matriz[num2][num1] == 1)
            printf("sim\n");
        else
            printf("nao\n");
    }
    
    else
        printf("nao\n");
}

int main() {

    int quantidade, num1 = 0, num2;
    scanf("%d", &quantidade);

    Grafo *grafo = CriarGrafoDirecionado (quantidade);

    do
    {
        scanf("%d %d", &num1, &num2);
        if(num1 != -1)
            VerificarAdjacencia(grafo, num1, num2, quantidade);
    } while (num1 != -1);
    

    return 0;
}

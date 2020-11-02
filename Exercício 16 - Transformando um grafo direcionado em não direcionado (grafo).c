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
    //Essa função inicia a matriz com todos os números sendo 0
    //É importante para o meu esquema na função que coloca os valores no grafo
    int **matriz = malloc(sizeof (int*) * quantidade);
    int i, j;

    //Esse "for" faz a segunda parte da alocação da matriz, já que ela é um ponteiro
    for(i = 0; i < quantidade; i++)
        matriz[i] = malloc(sizeof(int) * quantidade);

    //Esse "for" inicia todos os valores como 0 na matriz, para não ter lixo de memória,
    //e para funcionar corretamente na função CriarGrafoDirecionado
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

//O nome dessa função deveria ser CriarGrafoNaoDirecionado, só um erro de nomenclatura
Grafo *CriarGrafoDirecionado (int quantidade)
{
    Grafo *grafo = IniciarGrafo(quantidade);
    int i, j, x;

    //Os "for" percorrem recebendo os valores na matriz
    for(i = 0; i < quantidade; i++)
        for(j = 0; j < quantidade; j++)
        {
            scanf ("%d", &x);
            //Esse "if" serve para evitar que zere uma aresta que já estava iniciada como 0
            if(grafo->matriz[i][j] == 0)
            {
                //Em vez de fazer uma função separada para a conversão, achei que seria mais eficiente
                //Transformar diretamente na inserção, portanto, aqui ela insere as duas arestas de uma vez
                grafo->matriz[i][j] = x;
                grafo->matriz[j][i] = x;
            }
            //Aumenta o número de arestas no grafo
            grafo->arestas++;
        }

    return grafo;
}

void PrintarGrafo (Grafo *grafo, int quantidade)
{
    int i, j;

    for(i = 0; i < quantidade; i++)
    {
        for (j = 0; j < quantidade; j++)
            printf("%d ", grafo->matriz[i][j]);
        
        printf("\n");
    }
}

int main() {

    int quantidade;
    scanf("%d", &quantidade);

    Grafo *grafo = CriarGrafoDirecionado (quantidade);
    PrintarGrafo(grafo, quantidade);

    return 0;
}

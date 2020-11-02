#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define branco 0
#define cinza 1
#define preto 2
#define verdadeiro 1
#define falso 0

typedef struct Grafo
{
    int arestas;
    int vertices;
    int **matriz;
} Grafo;

int **IniciarMatriz(int quantidade)
{
    int **matriz = malloc(sizeof(int *) * quantidade);
    int i, j;

    for (i = 0; i < quantidade; i++)
        matriz[i] = malloc(sizeof(int) * quantidade);

    for (i = 0; i < quantidade; i++)
        for (j = 0; j < quantidade; j++)
            matriz[i][j] = 0;

    return matriz;
}

Grafo *IniciarGrafo(int quantidade)
{
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->arestas = 0;
    grafo->vertices = quantidade;
    grafo->matriz = IniciarMatriz(quantidade);

    return grafo;
}

Grafo *CriarGrafoDirecionado(int quantidade)
{
    Grafo *grafo = IniciarGrafo(quantidade);
    int i, j, x;

    for (i = 0; i < quantidade; i++)
        for (j = 0; j < quantidade; j++)
        {
            scanf("%d", &x);
            if (grafo->matriz[i][j] == 0)
            {
                grafo->matriz[i][j] = x;
            }
            grafo->arestas++;
        }

    return grafo;
}

int Visitar(Grafo *grafo, int i, int quantidade, int cor[], int tempo, int d[], int *f, int *pai)
{
    int j, k, l = 0;
    cor[i] = cinza;
    tempo++;
    d[i] = tempo;

    for(k = i; k < quantidade; k++)
    {
        for (j = 0; j < quantidade; j++)
            if ((grafo->matriz[k][j] == cinza) && (k <= quantidade) && (k >= 0) && (j <= quantidade) && (j >= 0) && (grafo != NULL))
            {
                if(pai[i] != j)
                {
                    if (cor[j] == branco)
                    {
                        pai[j] = i;
                        l = Visitar(grafo, j, quantidade, cor, tempo, d, f, pai);
                    }
                }
                
                else if (cor[j] == cinza)
                    return verdadeiro;
            } 
    }
    
    cor[i] = preto;
    f[i] = tempo = tempo + 1;
    if(l == verdadeiro)
        return verdadeiro;
    
    else
        return falso;
}

int VerificarCiclidade(Grafo *grafo, int quantidade, int *pai, int *f)
{
    int *cor = malloc(sizeof(int)*quantidade), d[quantidade], i, tempo;

    for (i = 0; i < quantidade; i++)
    {
        cor[i] = branco;
        pai[i] = -1;
        tempo = 0;
    }

    for (i = 0; i < quantidade; i++)
    {
        if (cor[i] == branco)
        
            if(Visitar(grafo, i, quantidade, cor, tempo, d, f, pai) == verdadeiro)
                return verdadeiro;
    }
    
    return falso;
}

void PrintarMatriz (Grafo *grafo, int quantidade)
{
    int i, j;
    for(i = 0; i < quantidade; i++)
    {
        for(j = 0; j < quantidade; j++)
            printf("%d ", grafo->matriz[i][j]);
        
        printf("\n");
    }
}

int main()
{

    int quantidade;
    scanf("%d", &quantidade);
    int *pai = calloc(quantidade, sizeof(int*)) , *f  = calloc(quantidade, sizeof(int**));
    
    Grafo *grafo = CriarGrafoDirecionado(quantidade);
    
    //PrintarMatriz(grafo, quantidade);

    if(VerificarCiclidade(grafo, quantidade, pai, f) == verdadeiro)
        printf("ciclico");
    
    else
        printf("aciclico");
    

    return 0;
}
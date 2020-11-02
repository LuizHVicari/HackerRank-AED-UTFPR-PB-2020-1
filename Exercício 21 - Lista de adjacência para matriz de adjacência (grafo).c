#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZE 5

typedef struct Node Node;
typedef struct Lista Lista;
typedef struct Matriz Matriz;
typedef struct Grafo Grafo;

struct Node
{
    int key;
    Node *next;
};

struct Lista
{
    Node *head;
};

struct Grafo
{
    int n_arestas;
    int n_vertices;
    Lista **matriz_adj;
};

Node *CriarNo(int key)
{
    Node *no = malloc(sizeof(Node));
    no->next = NULL;
    no->key = key;
    return no;
}

void InserirNo(int key, Lista *lista)
{
    Node *no = lista->head;

    if (lista->head == NULL)
        lista->head = CriarNo(key);

    else
    {
        while (no->next != NULL)
            no = no->next;

        no->next = CriarNo(key);
    }
}

//Essa função é uma padrão para trabalhar com matriz esparsa
Lista **CriarMatriz(int quantidade)
{
    Lista **matriz = malloc(sizeof(Lista *) * quantidade);

    for (int i = 0; i < quantidade; i++)
    {
        matriz[i] = malloc(sizeof(Lista));
        matriz[i]->head = NULL;

    }
    
    return matriz;
}

Grafo *IniciarGrafo(int quantidade)
{
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->matriz_adj = CriarMatriz(quantidade);
    grafo->n_vertices = quantidade;
    grafo->n_arestas = 0;
    return grafo;
}

//Nessa função recebi ajuda do Daniel sobre usar o getchar para pegar o enter
//As outras funções que essa função chama, porém, são minhas
Grafo *CriarGrafo(int quantidade)
{
    Grafo *grafo = IniciarGrafo(quantidade);
    int i, key;
    char vertice;
    
    scanf("%c", &vertice);

    i = 0;
        
    while(i < quantidade)
    {
        do
        {
            vertice = (char)getchar();
            key = (int)(vertice - '0');
                
            if(key >= 0 && key <= 9)
            {
                InserirNo(key, grafo->matriz_adj[i]);
                grafo->n_arestas++;
            }
                
        }
        while(vertice != '\n' && vertice != EOF);
        i++;
    }
    
    return grafo;
}

//Essa função apenas zera os valores da matriz para ela funcionar corretamente na função ConverterMatriz
void ZerarMatriz(int quantidade, int matriz[quantidade][quantidade])
{
    int i, j;

    for (i = 0; i < quantidade; i++)
        for (j = 0; j < quantidade; j++)
            matriz[i][j] = 0;
}

void PrintarMatriz(int quantidade, int matriz[quantidade][quantidade])
{
    int i, j;

    for (i = 0; i < quantidade; i++)
    {
        for (j = 0; j < quantidade; j++)
            printf("%d ", matriz[i][j]);

        printf("\n");
    }
}

void ConverterMatriz(Grafo *grafo, int quantidade)
{
    int matriz[quantidade][quantidade], i;
    Node *aux;

    //Chama a função para deixar todos os valores da matriz como 0
    ZerarMatriz(quantidade, matriz);

    //Sequência de repetições para passar os valores da matriz esparsa para a matriz normal
    for (i = 0; i < quantidade; i++)
    {
        //O auxiliar serve para percorrer a matriz
        //Ele recebe a cabeça da lista na linha indicada por i
        aux = grafo->matriz_adj[i]->head;
        while (aux != NULL)
        {
            //Passa o valor da matriz esparsa para a matriz norma
            //aux->key representa a coluna na matriz esparsa
            //Se aux não for nulo, então a matriz tem um valor na posição apontada pela chave
            matriz[i][aux->key] = 1;
            //Percorre a linha da matriz esparsa
            aux = aux->next;
        }
    }

    PrintarMatriz(quantidade, matriz);
}

int main()
{
    int quantidade;
    
    scanf("%d", &quantidade);
    
    Grafo *grafo = CriarGrafo(quantidade);
    
    ConverterMatriz(grafo, quantidade);
    
    return 0;
}
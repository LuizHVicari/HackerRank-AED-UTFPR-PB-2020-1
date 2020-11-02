//Esse código usa as mesmas funções do exercício anterior, mas cria uma nova para verificar o direcionado ou não
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
    int quantidade;
};

struct Grafo
{
    int n_arestas;
    int n_vertices;
    int *pai;
    int *visitado;
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

Grafo *CriarGrafo(int quantidade)
{
    Grafo *grafo = IniciarGrafo(quantidade);
    int i, key;
    char vertice;
    
    scanf("%c", &vertice);
    if(grafo != NULL)
    {
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
                }
                
            }
            while(vertice != '\n' && vertice != EOF);
            i++;
        }
    }
    
    return grafo;
}

void ZerarMatriz(int quantidade, int matriz[quantidade][quantidade])
{
    int i, j;

    for (i = 0; i < quantidade; i++)
        for (j = 0; j < quantidade; j++)
            matriz[i][j] = 0;
}

int VerificarDirecionado(int quantidade, int matriz[quantidade][quantidade])
{
    int i, j;

    //Os dois "for" servem para percorrer a matriz e verificar os valores dentro dela
    for(i = 0; i < quantidade; i++)
        for(j = 0; j < quantidade; j++)
            //Se em qualquer momento, um valor na matriz na linha x e coluna y for
            //diferente de na linha y e coluna x, significa que ele é direcionado
            if(matriz[i][j] != matriz[j][i])
            {
                printf("direcionado");
                //Já retorna o valor aqui para não correr o risco de sair e informar errado
                return 0;
            }

    //Se a função terminar o "for" anterior e continuar para cá, significa que o grafo é não direcionado
    printf("nao direcionado");
    return 1;
}

void ConverterMatriz(Grafo *grafo, int quantidade)
{
    int matriz[quantidade][quantidade], i;
    Node *aux;

    ZerarMatriz(quantidade, matriz);

    for (i = 0; i < quantidade; i++)
    {
        aux = grafo->matriz_adj[i]->head;
        while (aux != NULL)
        {
            
            matriz[i][aux->key] = 1;
            aux = aux->next;
        }
    }

   VerificarDirecionado(quantidade, matriz);
}

int main()
{
    int quantidade;
    
    scanf("%d", &quantidade);
    
    Grafo *grafo = CriarGrafo(quantidade);
    
    ConverterMatriz(grafo, quantidade);
    
    return 0;
}
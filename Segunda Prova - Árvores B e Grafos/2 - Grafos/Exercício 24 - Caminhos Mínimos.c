//Nessa atividade, utilizei as mesmas funções do algoritmo de Prim, com algumas alteraçoes nas funções, a maioria relativamente pequena
//Alguns comentários são do primeiro envio do exercício anterior
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define infinito 1000

typedef struct Node Node;

struct Node
{
    Node *next;
    int coluna;
    int peso;
};

typedef struct Lista
{
    Node *head;
} Lista;

typedef struct Cell Cell;

struct Cell
{
    int key;
    Cell *next;
};

typedef struct Fila
{
    Cell *topo;

} Fila;

typedef struct Grafo
{
    int n_arestas;
    int n_vertices;
    Lista **matriz_esparsa;
} Grafo;

//Funções para conferir
void PrintarMatriz(int quantidade, int** matriz)
{
    int i, j;

    for (i = 0; i < quantidade; i++)
    {
        for (j = 0; j < quantidade; j++)
            printf("%d ", matriz[i][j]);

        printf("\n");
    }
}

void PrintarMEsparsa (int tamanho, Grafo *grafo)
{
    Node *aux;
    for(int i = 0; i < tamanho; i++)
    {
        aux = grafo->matriz_esparsa[i]->head;
        
        while(aux != NULL)
        {
            printf("%d (%d)\t", aux->coluna, aux->peso);
            aux = aux->next;
        }
        printf("\n");
    }
}

void PrintarVetor(int vet[], int quantidade)
{
    for (int i = 0; i < quantidade; i++)
        if (vet[i] == -1)
            printf("%d: -\n", i);
        else
            printf("%d: %d\n", i, vet[i]);
}

//Funções para manipular a fila
Cell *CriarNo(int key)
{
    Cell *no = malloc(sizeof(Node));
    no->next = NULL;
    no->key = key;

    return no;
}

Fila *CriarFila()
{
    Fila *fila = malloc(sizeof(Fila));
    fila->topo = NULL;

    return fila;
}

Cell *CriarCell(int key)
{
    Cell *no = malloc(sizeof(Node));
    no->next = NULL;
    no->key = key;

    return no;
}

void InserirNaFila(int key, Fila *fila)
{
    Cell *percorrer, *novo = CriarCell(key);

    if (fila == NULL)
        fila = CriarFila();
    
    if (fila->topo == NULL)
        fila->topo = novo;
    else
    {
        percorrer = fila->topo;

        while (percorrer->next != NULL)
            percorrer = percorrer->next;

        percorrer->next = novo;
    }
}

int Procurar(Fila *fila, int key)
{
    Cell *percorrer;

    if (fila != NULL || fila->topo != NULL)
    {
        percorrer = fila->topo;

        while (percorrer != NULL)
        {
            if (percorrer->key == key)
                return 1;

            percorrer = percorrer->next;
        }
    }

    return 0;
}

int MenorPeso(Fila *fila, int *peso, int quantidade)
{
    int posicao = 0, peso_atual = infinito, i;

    if (fila != NULL || fila->topo != NULL)
    {

        for (i = 1; i < quantidade; i++)

            if (Procurar(fila, i) && peso[i] < peso_atual)
            {
                posicao = i;
                peso_atual = peso[i];
            }
        
        return posicao;
    }

    return -1;
}

int Extrair(Fila *fila, int *peso, int quantidade)
{
    Cell *aux1, *aux2;
    int key, menor_key = MenorPeso(fila, peso, quantidade);

    if (fila != NULL && fila->topo != NULL)
    {
        aux2 = aux1 = fila->topo;
        
        while (aux1->key != menor_key && aux1 != NULL)
        {
                aux2 = aux1;
                aux1 = aux1->next;
        }
        
        if(aux1 == aux2)
            fila->topo = fila->topo->next;
        else
            aux2->next = aux1->next;

        //if (aux1 != NULL)
        {
            key = aux1->key;
            free(aux1);
            return key;
        }
    }

    return -1;
}

//Funções para manipular o Grafo
Lista **IniciarLista(int quantidade)
{
   Lista **matriz = malloc(sizeof(Lista *) * quantidade);

    for (int i = 0; i < quantidade; i++)
    {
        matriz[i] = malloc(sizeof(Lista));
        matriz[i]->head = NULL;
    }
    
    return matriz;
}

Node *CriarNoL(int peso, int coluna)
{
    Node *no = malloc(sizeof(Node));
    no->next = NULL;
    no->peso = peso;
    no->coluna = coluna;
    return no;
}

Node *InserirNo(int peso, int coluna,  Lista *lista)
{
     Node *no = lista->head;

    if (lista->head == NULL)
        lista->head = CriarNoL(peso, coluna);

    else
    {
        while (no->next != NULL)
            no = no->next;

        no->next = CriarNoL(peso, coluna);
    }

    return no;
}

Grafo *IniciarGrafo(int quantidade)
{
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->n_arestas = 0;
    grafo->n_vertices = quantidade;
    grafo->matriz_esparsa = IniciarLista(quantidade);

    return grafo;
}

Grafo *CriarGrafo(int quantidade)
{
    Grafo *grafo = IniciarGrafo(quantidade);
    int i, j, x;

    for(i = 0; i < quantidade; i++)
            for(j = 0; j < quantidade; j++)
            {
                scanf ("%d", &x);

                if(x != 0)
                {
                    InserirNo(x, j, grafo->matriz_esparsa[i]);
                    grafo->n_arestas++;
                }
            }

    return grafo;
}

int **IniciarMatriz (int quantidade)
{
    int **matriz = malloc(sizeof (int*) * quantidade);
    int i, j;

    for(i = 0; i < quantidade; i++)
        matriz[i] = malloc(sizeof(int) * quantidade);

    for(i = 0; i < quantidade; i++)
        for(j = 0; j < quantidade; j++)
            matriz[i][j] = 0;
    
    //PrintarMatriz(quantidade, matriz);

    return matriz; 
}

int **ConverterMatriz(Grafo *grafo)
{
    int **matriz = IniciarMatriz(grafo->n_vertices), i;
    Node *aux;

    for (i = 0; i < grafo->n_vertices; i++)
    {
        aux = grafo->matriz_esparsa[i]->head;
        while (aux != NULL)
        {
            matriz[i][aux->coluna] = aux->peso;
            aux = aux->next;
        }
    }
    
    //PrintarMatriz(grafo->n_vertices, matriz);

    return matriz;
}

void Relaxar (Grafo *grafo, int *distancia, int *pai, int v1, int v2, int **matriz)
{
    //Se a possível nova distância for menor que a atual, atualiza a distância e o vetor de pai
    if(distancia[v2] > distancia[v1] + matriz[v1][v2])
    {
        distancia[v2] = distancia[v1] + matriz[v1][v2];
        pai[v2] = v1;
    }
}

int *Dijkstra(Grafo* grafo)
{
    //Essa função é quase igual à de Prim, muda no "while", em que estará indicado
    int i, *pai = (int*)malloc(sizeof(int) * grafo->n_vertices), *key = (int*)malloc(sizeof(int) * grafo->n_vertices), aux;
    Fila *fila = CriarFila();
    Node *no;
    
    int **matriz = ConverterMatriz(grafo);

    for(i = 0; i < grafo->n_vertices; i++)
    {
        pai[i] = -1;
        key[i] = infinito;
        InserirNaFila(i, fila);
    }

    key[0] = 0;

    while(fila->topo != NULL)
    {
        aux = Extrair(fila, key, grafo->n_vertices);
        no  = grafo->matriz_esparsa[aux]->head;

        //Mudança em relação a Prim
        //Chama a função de relaxamento
        while(no != NULL)
        {
            Relaxar(grafo, key, pai, aux, no->coluna, matriz);
            no = no->next;
        }
    }

    return pai;
}

int main()
{

    int quantidade;
    scanf("%d", &quantidade);

    Grafo *grafo = CriarGrafo(quantidade);

    int *vetor = Dijkstra(grafo);

    PrintarVetor(vetor, quantidade);

    return 0;
}

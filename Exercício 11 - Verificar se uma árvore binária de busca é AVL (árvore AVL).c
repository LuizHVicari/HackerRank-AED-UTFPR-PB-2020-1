#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct Node
{
    int item;
    struct Node *left;
    struct Node *right;
} Node;

Node *CriarNo(int key)
{
    Node *novo = malloc(sizeof(Node));
    novo->left = NULL;
    novo->right = NULL;
    novo->item = key;

    return novo;
}

Node *Inserir(Node *tree, int value)
{
    if (tree == NULL)
    {
        tree = CriarNo(value);
    }
    else if (value < tree->item)
    {
        tree->left = Inserir(tree->left, value);
    }
    else
        tree->right = Inserir(tree->right, value);

    return tree;
}

//Essa função é a mesma do exercício anterior
int AlturaDaArvore(Node *tree)
{
    if (tree == NULL)
        //Uma árvore com n elementos, tem n - 1 de altura, logo uma arvore com 0 elementos tem -1 elementos
        return -1;
    else
    {
        int altura_esquerda, altura_direita;

        altura_esquerda = AlturaDaArvore(tree->left);
        altura_direita = AlturaDaArvore(tree->right);

        if(altura_esquerda > altura_direita)
            return AlturaDaArvore(tree->left) + 1;
        
        else
            return AlturaDaArvore(tree->right) + 1;
    }
}

int VerificarBalanceamento (Node* tree)
{
    //Uma árvore vazia é sempre uma árvore AVL
    if(tree == NULL)
    {
        return 1;
    }
    
    //A variável altura recebe a chamada da função de obter altura para os dois lados da árvore
    //Se o módulo da diferença de alturas for > 1, então ela não é balanceada, logo não é AVL 
    int altura = AlturaDaArvore(tree->left) - AlturaDaArvore(tree->right);
    int aux;
    //Chama recursivamente essa mesma função para a esquerda, e aux recebe o retorno dela para comparar
    aux = VerificarBalanceamento(tree->left);
    if(aux == 0)
        return  aux;

    //Mesma coisa que anteriormente, porém para a direita
    aux = VerificarBalanceamento(tree->right);
    if(aux == 0)
        return aux;
    
    //Compara a primeira condição discutida na função, se a árvore estiver balanceada, entra aqui e retorna 1 (verdadeiro)
    if (altura >= -1 && altura <= 1)
        return 1;

    //Se chegar aqui, é falso
    return 0;
}


int main(void)
{
    int n, x;
    Node *tree = NULL;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf ("%d", &x);
        tree = Inserir (tree, x);
    }

   printf("%d", VerificarBalanceamento(tree));
    
    return 0;
}
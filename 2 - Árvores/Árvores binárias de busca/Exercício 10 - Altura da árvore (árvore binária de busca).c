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
    novo->item = key;
    novo->left = NULL;
    novo->right = NULL;

    return novo;
}

Node *Inserir(Node *tree, int value)
{
    if (tree == NULL)
        tree = CriarNo(value);
    else if (value < tree->item)
        tree->left = Inserir(tree->left, value);
    else
        tree->right = Inserir(tree->right, value);

    return tree;
}

int AlturaDaArvore(Node *tree)
{
    if (tree == NULL)
        //Uma árvore com n elementos, tem n - 1 de altura, logo uma arvore com 0 elementos tem -1 elementos
        return -1;
    else
    {
        int altura_esquerda, altura_direita;

        //As variáveis de altura chamam a função para seus respectivos lados (esquerda e direita) recursivamente
        altura_esquerda = AlturaDaArvore(tree->left);
        altura_direita = AlturaDaArvore(tree->right);

        //Compara qual a maior altura, e retorna ela somando 1 para esse nó
        if(altura_esquerda > altura_direita)
            return AlturaDaArvore(tree->left) + 1;
        
        else
            return AlturaDaArvore(tree->right) + 1;
    }
}

int main(void)
{
    int n, x;
    Node *tree = NULL;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        tree = Inserir(tree, x);
    }
    
    printf("%d", AlturaDaArvore(tree));

    return 0;
}

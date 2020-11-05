#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define preto 1
#define vermelho 0

typedef struct Node Node;

struct Node
{
    int key;
    int cor;
    Node *left;
    Node *right;
    Node *pai;
};

Node* CriarNo()
{
        Node *novo = malloc(sizeof(Node));
        novo->left = NULL;
        novo->right = NULL;
        novo->pai = NULL;
        novo->cor = vermelho;

        return novo;
}
Node *ObterAvo(Node *tree)
{
    if (tree == NULL || tree->pai == NULL)
        return NULL;

    return tree->pai->pai;
}

Node *ObterTio(Node *tree)
{
    if(tree != NULL && tree->pai != NULL && tree->pai->pai != NULL)
    {
        if (tree->pai == tree->pai->pai->right)
            return tree->pai->pai->left;

        else
            return tree->pai->pai->right;
    }
    
    return NULL;
}

/*Todas as funções de retação são correções feitas pelo João Henrique*/

Node *rotacionarDir(Node *tree)
{
    Node *aux_pai = tree->pai;
    Node *avo = aux_pai->pai;
    
    avo->left = aux_pai->right;
    aux_pai->right = avo;
    
    if (avo->pai != NULL)
    {
        if(avo->pai->left == avo)
            avo->pai->right = aux_pai;

        else
            avo->pai->left = aux_pai;
    }

    aux_pai->pai = avo->pai;
    avo->pai = aux_pai;

    tree = aux_pai;
    
    return tree;
}

Node *rotacionarEsq(Node *tree)
{
    Node *aux_pai = tree->pai;
    Node *avo = aux_pai->pai;

    avo->right = aux_pai->left;
    aux_pai->left = avo;
    if (avo->pai != NULL)
    {
        if(avo->pai->right == avo)
            avo->pai->right = aux_pai;
        else
            avo->pai->left = aux_pai;
    }

    
    aux_pai->pai = avo->pai;
    avo->pai = aux_pai;

    tree = aux_pai;

    return tree;
}

Node *rotacionarDirEsq(Node *tree)
{
    Node *aux_pai = tree->pai;
    Node *avo = aux_pai->pai;

    aux_pai->left = tree->right;
    tree->right = aux_pai;

    if (avo->left == aux_pai)
        avo->left = tree;
    else
        avo->right = tree;

    tree->pai = aux_pai->pai;
    aux_pai->pai = tree;

    return rotacionarEsq(aux_pai);
}

Node *rotacionarEsqDir(Node *tree)
{
    Node *aux_pai = tree->pai;
    Node *avo = aux_pai->pai;

    aux_pai->right = tree->left;
    tree->left = aux_pai;

    if (avo->left == aux_pai)
        avo->left = aux_pai;
    else
        avo->right = tree;

    tree->pai = aux_pai->pai;
    aux_pai->pai = tree;

    return rotacionarDir(aux_pai);
}

Node* Balancear(Node *tree)
{
    Node *aux_pai, *tio;

    if (tree->pai == NULL)
        tree->cor = preto;
    else
    {
        aux_pai = tree->pai;

        if (aux_pai->cor == vermelho)
        {
            tio = ObterTio(tree);

            if (tio != NULL && tio->cor == vermelho)
            {
                aux_pai->cor = preto;
                tio->cor = preto;

                tree = ObterAvo(tree);

                if (tree->pai != NULL)
                    tree->cor = vermelho;
            }

            else
            {
                if (aux_pai->left == tree)
                {
                    if (aux_pai->pai->right == aux_pai)
                        tree = rotacionarDirEsq(tree);

                    else
                        tree = rotacionarDir(tree);
                }

                else
                {
                    if (aux_pai->pai->left == aux_pai)
                        tree = rotacionarEsqDir(tree);

                    else
                        tree = rotacionarEsq(tree);
                }

                tree->cor = preto;
                if(tree->right != NULL)
                    tree->right->cor = vermelho;

                if(tree->left != NULL)
                    tree->left->cor = vermelho;
            }
        }
    }

    return tree;
}

Node* InserirNo(Node *tree, int value)
{
    if (tree == NULL)
    {
        tree = CriarNo();
        tree->cor = preto;
        tree->key = value;
        return tree;
    }

    else
    {
        Node *pai = tree;
        Node *filho = tree;

        while (filho != NULL)
        {
            pai =  filho;

            if (value < pai->key)
            {
                filho = filho->left;
                
            }
            else
            {
                filho = filho->right;
            }
        }

        filho = CriarNo();
        filho->key = value;
        filho->pai = pai;

        if (filho->key < pai->key)
            pai->left = filho;
        else
            pai->right = filho;

        while ((filho->pai != NULL) && (filho->cor == vermelho) && (filho->pai->cor == vermelho))
        {
            filho = Balancear(filho);
        }

        while(filho->pai != NULL)
            filho = filho->pai;

        return filho;
    }
}

int CalcularAltura (Node* tree)
{
    //Inicia a variável cont com 0
    int cont = 0;

    //O "while" percorre a árvore enquanto ela for diferente de nula
    while(tree != NULL)
    {
        //Segundo a teoria de árvores rubro negras, em qualquer caminho que sigamos, a altura negra vai ser a mesma
        //Por isso, nesse caso, escolhemos seguir o caminho para a extrema esquerda
        if(tree->cor == preto)
            //Quando encontra o um nó preto, aumenta o valor de cont, e ignora os nós vermelhos
            cont++;

        tree = tree->left;
    }

    return cont;
}

int main()
{
    int tamanho, n;
    Node *tree = NULL;

    scanf("%d", &tamanho);

    for(int i = 0; i < tamanho; i++)
    {
        scanf("%d", &n);

        tree = InserirNo(tree, n);
    }

    printf("%d", CalcularAltura(tree));

    return 0;
}

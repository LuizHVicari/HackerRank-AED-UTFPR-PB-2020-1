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
//Eu comentei os códigos de estrutura de dados, ou seja, todos a partir desses, nos últimos dias antes da entrega
//por isso eles tem tantas submissões
//Foi só uma ideia que eu achei interessante fazer, até para relembrar os conceitos antes da prova de árvore B e grafos
//Comentei (em maioria), as funções que eram pedidas para o algoritmo (deixando de lado as que funcionam por exemplo para inserir o valor)
void PercorrerSimetrica (Node* tree)
{
    //Essa função percorre simétricamente a árvore (foi apresentada nos slides do professor)
    //Contudo, há uma alteração nela, que será discutida
    if(tree != (NULL))
    {
        //Quando o nó não possui nenhum filho, ele entra nesse if, assim, a função imprime quais são os nó folha 
        //(apontando os valores armazenados neles)
        if (tree->left == NULL && tree->right == NULL)
        {
            printf(" %d", tree->item);
        }
        PercorrerSimetrica (tree->left);
        PercorrerSimetrica (tree->right);
    }
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

    PercorrerSimetrica (tree);
    
    return 0;
}
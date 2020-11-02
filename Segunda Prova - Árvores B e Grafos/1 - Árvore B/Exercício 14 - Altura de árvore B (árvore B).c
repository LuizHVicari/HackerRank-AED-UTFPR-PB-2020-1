#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 5

typedef struct NodeB NodeB;


NodeB* criar();

int liberar(NodeB *tree);

int pesquisar(int key, NodeB *tree);

int pesquisaSequencial(int key, NodeB *tree);

NodeB* inserir(NodeB *tree, int key);


struct NodeB
{
    int nro_chaves;
    int chaves[N - 1];
    NodeB *filhos[N];
    int eh_no_folha;
};

NodeB *criar()
{
    NodeB *tree = malloc(sizeof(NodeB));
    int i;

    tree->eh_no_folha = 1;
    tree->nro_chaves = 0;

    for (i = 0; i < N; i++)
        tree->filhos[i] = NULL;

    return tree;
}

int liberar(NodeB *tree)
{
    if (tree != NULL)
    {
        free(tree);
        return 1;
    }

    return 0;
}

static int busca_binaria(int key, NodeB *tree)
{
    int ini, fim, meio;

    if (tree != NULL)
    {
        ini = 0;
        fim = tree->nro_chaves - 1;

        while (ini <= fim)
        {
            meio = (ini + fim) / 2;

            if (tree->chaves[meio] == key)
                return meio;
            else if (tree->chaves[meio] < key)
                ini = meio + 1;
            else
                fim = meio - 1;
        }

        return ini;
    }

    return -1;
}

int pesquisaSequencial(int key, NodeB *tree)
{
    int i;

    if (tree != NULL)
    {
        for (i = 0; i < tree->nro_chaves && key < tree->chaves[i]; i++);

        if (key == tree->chaves[i])
            return 1;
        else
            return pesquisaSequencial(key, tree->filhos[i]);
    }

    return 0;
}

int pesquisar(int key, NodeB *tree)
{
    int pos = busca_binaria(key, tree);

    if (pos >= 0)
    {
        if (tree->chaves[key] == key)
            return 1;
        else
            return pesquisar(key, tree->filhos[pos]);
    }

    return 0;
}

static NodeB *split_pag(NodeB *pai, int posF_cheio)
{
    int i, keyUp;

    NodeB *pagEsq = pai->filhos[posF_cheio];
    NodeB *pagDir = criar();
    pagDir->eh_no_folha = pagEsq->eh_no_folha;
    pagDir->nro_chaves = round((N - 1) / 2);
    keyUp = pagEsq->chaves[pagDir->nro_chaves];

    for(i = 1; i < pagDir->nro_chaves; i++)
        pagDir->chaves[i - 1] = pagEsq->chaves[i + pagDir->nro_chaves];
    
    if(!pagEsq->eh_no_folha)
        for(i = 0; i < pagDir->nro_chaves; i++)
            pagDir->filhos[i] = pagEsq->filhos[i + pagDir->nro_chaves];
    
    pagEsq->nro_chaves = (N - 1) / 2;
    pagDir->nro_chaves--;

    for(i = pai->nro_chaves + 1; i > posF_cheio + 1; i--)
        pai->filhos[i + 1] = pai->filhos[i];

    pai->filhos[posF_cheio + 1] = pagDir;
    pai->filhos[posF_cheio] = pagEsq;
    pai->chaves[posF_cheio] = keyUp;
    pai->nro_chaves++;

    return pai;
}

/*static NodeB *split_pag(NodeB *pai, int posF_cheio)
{
    int i;
    NodeB *pag_esq = pai->filhos[posF_cheio];
    NodeB *pag_dir;

    pag_dir = criar();

    pag_dir->eh_no_folha = pag_esq->eh_no_folha;

    pag_dir->nro_chaves = round((N - 1) / 2);

    for (i = 0; i < pag_dir->nro_chaves; i++)
        pag_dir->chaves[i] = pag_esq->chaves[i + pag_dir->nro_chaves];

    if (!pag_esq->eh_no_folha)
        for (i = 0; i <= pag_dir->nro_chaves; i++)
            pag_dir->filhos[i] = pag_esq->filhos[i + pag_dir->nro_chaves];

    pag_esq->nro_chaves = (N - 1) / 2;

    for (i = pai->nro_chaves + 1; i > posF_cheio + 1; i--)
        pai->filhos[i + 1] = pai->filhos[i];

    pai->filhos[posF_cheio + 1] = pag_dir;

    for (i = pai->nro_chaves + 1; i > posF_cheio; i--)
        pai->chaves[i + 1] = pai->chaves[i];

    pai->chaves[posF_cheio] = pag_dir->chaves[0];

    for(i = 0; i < pag_dir->nro_chaves - 1; i++)
        pag_dir->chaves[i] = pag_dir->chaves[i + 1];

    pag_dir->nro_chaves--;
    pai->nro_chaves++;

    return pai;
}*/


static NodeB *inserir_pagina_nao_cheia(NodeB *tree, int key)
{
    int i;
    int pos = busca_binaria(key, tree);

    if (tree->eh_no_folha)
    {
        for (i = tree->nro_chaves; i > pos; i--)
            tree->chaves[i] = tree->chaves[i - 1];

        tree->chaves[i] = key;
        tree->nro_chaves++;
    }
    else
    {
        if (tree->filhos[pos]->nro_chaves == N - 1)
        {
            tree = split_pag(tree, pos);

            if (key > tree->chaves[pos])
                pos++;
        }

        tree->filhos[pos] = inserir_pagina_nao_cheia(tree->filhos[pos], key);
    }
    return tree;
}

NodeB *inserir(NodeB *tree, int key)
{
    NodeB *aux = tree;
    NodeB *nova_pag;

    if (aux->nro_chaves == N - 1)
    {
        nova_pag = criar();

        nova_pag->eh_no_folha = 0;

        nova_pag->filhos[0] = aux;

        tree = split_pag(nova_pag, 0);

        nova_pag = inserir_pagina_nao_cheia(nova_pag, key);
    }
    else
        tree = inserir_pagina_nao_cheia(aux, key);

    return tree;
}

int AlturaDaArvore(NodeB *tree)
{
    //Essa função adpta as fnunções de calcular altura para árvore binária de busca, as mudanças estão nos comentários posteriores
    if (tree == NULL)
        return -1;
    
    else
    {
        int altura[tree->nro_chaves], i, maior, controle;
        
        //Como existem vários nós, usamos eles como vetores aqui para percorrer, ao chamar a função recursivamente para cada nó
        for(i = 0; i < tree->nro_chaves; i++)
            altura[i] = AlturaDaArvore(tree->filhos[i]);
        
        maior = altura[0];
        controle = 0;
        
        for(i = 1; i < tree->nro_chaves; i++)
            if(altura[i] > maior)
            {
                //Recebe a maior altura de todos os nós
                maior = altura[i];
                controle = i;
            }
        
        return AlturaDaArvore(tree->filhos[controle]) + 1;
    }
}

int main(void)
{

    NodeB *tree = criar();
    int quantidade, x;
    scanf("%d", &quantidade);

    for (int i = 0; i < quantidade; i++)
    {
        scanf("%d", &x);
        tree = inserir(tree, x);
    }

    printf("%d", AlturaDaArvore(tree));

    return 0;
}

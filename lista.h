#ifndef LISTA
#define LISTA
#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

//Definicao de char com valores de 0 a 255 - Tamanho da Tabela ASCII
typedef unsigned char byte;

//Estrutura da Lista
struct nodeLista{
    nodeArvore *no;
    struct nodeLista *proximo;
    struct nodeLista *anterior;
};

//Estrutura do No Descritor
struct lista{
    struct nodeLista *head;
    int elementos;
};

//Definicao da Estrutura dos Nos da Lista
typedef struct nodeLista nodeLista;

//Definicao da Estrutura do No Descritor
typedef struct lista lista;

//Inicia/Cria a Lista
lista* cria_lista();

//Cria um novo No para a Lista
nodeLista *novoNodeLista(nodeArvore *nArv);

//Insere o No na lista de acordo com a Frequencia
void insereLista(nodeLista *n, lista *l);

//Remove No da Lista
nodeArvore *removeMenorLista(lista *l);

#endif
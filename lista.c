#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arvore.h"

//Inicia/Cria a Lista
lista* cria_lista(){
    lista* li = (lista*) malloc(sizeof(lista));
    if(li != NULL){
        li->head = NULL;
        li->elementos = 0;
    }
    return li;
}

//Cria um novo No para a Lista
nodeLista *novoNodeLista(nodeArvore *noArv){
    nodeLista *novo;
    if((novo = malloc(sizeof(*novo))) == NULL) return NULL;

    novo->no = noArv;

    novo->proximo = NULL;
    novo->anterior = NULL;

    return novo;
}

//Insere o No na lista de acordo com a Frequencia
void insereLista(nodeLista *no, lista *l){
    if(!l->head){
        l->head = no;
    }
    else if(no->no->frequencia < l->head->no->frequencia){
        no->proximo = l->head;
        l->head->anterior = no;
        l->head = no;
    }
    else{
        nodeLista *aux = l->head->proximo;
        nodeLista *aux2 = l->head;
        while(aux && aux->no->frequencia <= no->no->frequencia){
            aux2 = aux;
            aux = aux2->proximo;
        }
        aux2->proximo = no;
        no->anterior = aux2;
        no->proximo = aux;
    }
    l->elementos++;
}

//Remove No da Lista
nodeArvore *removeMenorLista(lista *l){
    nodeLista *aux = l->head;
    nodeArvore *aux2 = aux->no;
    l->head = aux->proximo;
    free(aux);
    aux = NULL;
    l->elementos--;
    return aux2;
}

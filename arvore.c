#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "codigo.h"

//Inicia/Cria a Arvore
arvore* cria_Arvore(){
    arvore* raiz = (arvore*) malloc(sizeof(arvore));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

//Libera a Arvore a partir da Raiz usando tambem a libera_Node
void libera_Huffman(arvore* raiz){
    if(raiz == NULL)
        return;
    libera_Node(*raiz); //Libera cada no
    free(raiz); //Libera a raiz
}

//Libera a Arvore a partir de determinado no
void libera_Node(struct nodeArvore* node){
    if(node == NULL)
        return;
    libera_Node(node->esquerda);
    libera_Node(node->direita);
    free(node);
    node = NULL;
}

//Cria um novo No na Arvore
nodeArvore *novoNodeArvore(byte letra, int frequencia, nodeArvore *esquerda, nodeArvore *direita){
    nodeArvore *novo;

    if((novo = malloc(sizeof(*novo))) == NULL) return NULL;

    novo->letra = letra;
    novo->frequencia = frequencia;
    novo->esquerda = esquerda;
    novo->direita = direita;

    return novo;
}

//Funcao que Cria a Arvore de acordo com algoritmo de Huffman usando uma Lista de Frequencia de Caracteres
nodeArvore *HuffmanArvore(unsigned *listaBytes){
    int i;
    lista *l = cria_lista();
    //Cria a lista de frequencia de caracteres do menor para o maior
    for(i = 0; i <= 255; i++){
        if(listaBytes[i]>=1){
            insereLista(novoNodeLista(novoNodeArvore(i, listaBytes[i], NULL, NULL)), l);
        }
    }
    //Remove os dois elementos com menores frequencia, cria um novo no com a soma e insere na lista ate formar a arvore
    while(l->elementos > 1){
        nodeArvore *nodeEsquerdo = removeMenorLista(l);
        nodeArvore *nodeDireito = removeMenorLista(l);
        nodeArvore *soma = novoNodeArvore('#', nodeEsquerdo->frequencia + nodeDireito->frequencia, nodeEsquerdo, nodeDireito);

        insereLista(novoNodeLista(soma), l);
    }
    nodeArvore *ultimo = removeMenorLista(l);
    free(l);
    return ultimo;
}

//Funcao que Insere na Arvore de Huffman que eh utilizada para Descomprimir
int insere_ArvoreDescomprime(arvore* raiz, char letra, char posicao[], int tamanho){
    int i;

    if(raiz == NULL)
        return 0;

    struct nodeArvore* novo;
    novo = (struct nodeArvore*) malloc(sizeof(struct nodeArvore));
    if(novo == NULL)
        return 0;

    novo->letra = letra;
    novo->direita = NULL;
    novo->esquerda = NULL;
    //Se a Arvore estiver vazia, insere como a raiz da Arvore
    if(*raiz == NULL){
        *raiz = novo;
    }
    else{
        //Percorre a arvore de acordo com a string 'posicao', caso no nao exista, insere, caso ja exista e seja a ultima posicao, libera o no criado
        struct nodeArvore* atual = *raiz;
        struct nodeArvore* ant = NULL;
        for(i = 0; i < tamanho; i++){
            if(posicao[i] == '1'){
                if(atual->direita == NULL){
                    atual->direita = novo;
                }
                else if((i == tamanho-1) && (atual->direita)){
                    free(novo);
                }
                else if((i != tamanho-1) && (atual->direita)){
                    atual = atual->direita;
                }
            }
            if(posicao[i] == '0'){
                if(atual->esquerda == NULL){
                    atual->esquerda = novo;
                }
                else if((i == tamanho-1) && (atual->esquerda)){
                    free(novo);
                }
                else if((i != tamanho-1) && (atual->esquerda)){
                    atual = atual->esquerda;
                }
            }
        }
    }
    return 1;
}

//Cria a Arvore de Huffman a partir da tabela criada no programa de compressao
arvore* HuffmanDescomprime(FILE *tabela){
    int i, tamCodigo = 0, node, tamanhoArq = 0, cont = 0;
    char codigo[9];
    char letra;

    tamanhoArq = tamanhoArquivo(tabela,"tabela.txt");

    tabela = fopen("tabela.txt","r");

    arvore* raiz = cria_Arvore();
    //Insere a raiz da arvore
    node = insere_ArvoreDescomprime(raiz, '#', "###", 0);
    //Insere nodes na Arvore seguindo o 'caminho' do codigo até chegar no final para inserir a letra
    while(cont != tamanhoArq){
        fscanf(tabela,"%c: %s\n",&letra,codigo);
        tamCodigo = strlen(codigo);

        for(i = 0; i < tamCodigo; i++){
            if(i == tamCodigo-1)
                node = insere_ArvoreDescomprime(raiz, letra, codigo, i+1);
            else
                node = insere_ArvoreDescomprime(raiz, '*', codigo, i+1);
        }
        cont = ftell(tabela);
    }
    //Retorna a Raiz da Arvore Criada
    return raiz;
}

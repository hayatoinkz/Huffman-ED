#ifndef ARVORE
#define ARVORE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BITS 8

//Definicao de char com valores de 0 a 255 - Tamanho da Tabela ASCII
typedef unsigned char byte;

//Estrutura da Arvore
struct nodeArvore{
    int frequencia;
    byte letra;
    char codigo[9];
    struct nodeArvore *esquerda;
    struct nodeArvore *direita;
};

//Definicao da Estrutura de Arvore com Ponteiro
typedef struct nodeArvore* arvore;

//Definicao da Estrutura de Arvore
typedef struct nodeArvore nodeArvore;

//Inicia/Cria a Arvore
arvore* cria_Arvore();

//Libera a Arvore a partir da Raiz usando tambem a libera_Node
void libera_Huffman(arvore* raiz);

//Libera a Arvore a partir de determinado no
void libera_Node(struct nodeArvore* node);

//Cria um novo No para a Arvore
nodeArvore *novoNodeArvore(byte letra, int frequencia, nodeArvore *esquerda, nodeArvore *direita);

//Funcao que Cria a Arvore de acordo com algoritmo de Huffman usando uma Lista de Frequencia de Caracteres
nodeArvore *HuffmanArvore(unsigned *listaBytes);

//Funcao que Insere na Arvore de Huffman que eh utilizada para Descomprimir
int insere_ArvoreDescomprime(arvore* raiz, char letra, char posicao[], int tamanho);

//Cria a Arvore de Huffman a partir da tabela criada no programa de compressao
arvore *HuffmanDescomprime(FILE *tabela);

#endif

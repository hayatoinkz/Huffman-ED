#ifndef CODIGO
#define CODIGO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#define BITS 8

//Definicao de char com valores de 0 a 255 - Tamanho da Tabela ASCII
typedef unsigned char byte;

//Le o arquivo de Texto e Cria uma lista com a Frequencia de Caracteres
void getFrequencyAscii(FILE *entrada, const char *nome, unsigned *listaBytes);

//Percorre a arvore para criar o codigo que vai ser gravado na tabela
int criaCodigo(nodeArvore *no, byte letra, byte *codigo, int tamanho);

//Gera a tabela com os codigos de acordo com  a Arvore
void gerarTabela(FILE *saidatxt, unsigned *listaBytes, nodeArvore *raiz);

//Codifica o Texto no Arquivo Binario
void escreverBinario(FILE *entrada, FILE *saidatxt, const char *nomeArq);

//Busca o Codigo na Tabela para conseguir gravar no Arquivo Binario
void buscarTabela(FILE *saidatxt, byte letra, unsigned short *codigo, unsigned short *tamCodigo);

//Verifica o tamanho do Arquivo
int tamanhoArquivo(FILE *arqv, const char *nomeArq);

//Verifica o tamanho do Arquivo Binario
int tamanhoArquivoBin(FILE *arqv, const char *nomeArq);

//Descomprime o Arquivo Binario de acordo com Arvore criada com a Tabela recebida nos argumentos
void descomprimeArquivo(FILE *entradaBin, arvore* raiz);

//Percorre a Arvore para achar a letra para determinado Codigo
int achaLetra(arvore* raiz, char codigo[], int tamanho, char* letra);

#endif
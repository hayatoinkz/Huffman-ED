#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "codigo.h"

int main(int argc, char *argv[]){
    FILE *tabela;
    FILE *entradaBin;
    //Variaveis para verificar o tamanho dos argumentos e em seguida verificar a extensao dos arquivos
    int name1, name2;

    if(argc == 3){
        name1 = strlen(argv[1]);
        name2 = strlen(argv[2]);
        if( (argv[1][name1-1] != 't') || (argv[1][name1-2] != 'x') || (argv[1][name1-3] != 't') || (argv[1][name1-4] != '.') || 
            (argv[2][name2-1] != 'f') || (argv[2][name2-2] != 'f') || (argv[2][name2-3] != 'u') || (argv[2][name2-4] != 'h') || (argv[2][name2-5] != '.') ){
            printf("Argumentos ou Arquivos Invalidos\n");
        }
        else{
            if((tabela = fopen(argv[1],"r")) == NULL){
                printf("Nao eh possivel abrir o arquivo de texto ou nao foi encontrado\n");
            }
            if((entradaBin = fopen(argv[2],"rb")) == NULL){
                printf("Nao eh possivel abrir o arquivo binario ou nao foi encontrado\n");
            }
            else{
                //Cria a Arvore de acordo com a tabela
                arvore *raiz = HuffmanDescomprime(tabela); 
                //Descomprime o arquivo binario com a Arvore
                descomprimeArquivo(entradaBin,raiz);

                libera_Huffman(raiz);
            }
        }
    }
    else{
        printf("Execute de forma correta os argumentos:\n./descomprime tabela.txt myfile.huff\n"); 
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "codigo.h"

int main(int argc, char *argv[]){
    FILE *entrada;
    FILE *saidatxt;
    //Variavel para verificar o tamanho do argumento e em seguida verificar a extensao do arquivo
    int name;

    if(argc == 2){
        name = strlen(argv[1]);
        if( (argv[1][name-1] != 't') || (argv[1][name-2] != 'x') || (argv[1][name-3] != 't') || (argv[1][name-4] != '.') ){
            printf("Argumento ou Arquivo Invalido\n");
        }
        else{
            if((entrada = fopen(argv[1],"r")) == NULL){
                printf("Nao eh possivel abrir o arquivo de texto ou nao foi encontrado\n");
            }
            else{
                //Cria uma Lista de Frequencia de Caracteres
                unsigned listaBytes[256] = {0};
                getFrequencyAscii(entrada,argv[1],listaBytes);
                //Cria a Arvore
                nodeArvore* raiz = HuffmanArvore(listaBytes);
                //Cria a Tabela com os Codigos da Arvore
                gerarTabela(saidatxt,listaBytes,raiz);
                //Libera a Arvore Criada
                libera_Node(raiz);
                
                entrada = fopen(argv[1],"r");
                saidatxt = fopen("tabela.txt","r");
                //Cria o Arquivo Binario do Arquivo de Texto
                escreverBinario(entrada,saidatxt,argv[1]);
            }
        }
    }
    else{
        printf("Execute de forma correta os argumentos:\n./comprime [nomedoarquivo].txt\n"); 
    }
    return 0;
}
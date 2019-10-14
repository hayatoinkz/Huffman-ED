#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codigo.h"
#include "arvore.h"
#define BITS 8

//Le o arquivo de Texto e Cria uma lista com a Frequencia de Caracteres
void getFrequencyAscii(FILE *entrada, const char *nomeArq, unsigned int *listaBytes){
    byte c;
    fopen(nomeArq,"r");
    while(fread(&c, 1, 1, entrada) >= 1){
        listaBytes[(int)c]++;
    }
}

//Percorre a arvore para criar o codigo que vai ser gravado na tabela
int criaCodigo(nodeArvore *no, byte letra, byte *codigo, int tamanho){
    int achou;
    //Caso seja uma Folha, Fim do Codigo
    if (!(no->esquerda || no->direita) && no->letra == letra){
        achou = 1;
        codigo[tamanho] = '\0';
        return achou;
    }
    else{
        achou = 0;
        //Percorre a Arvore Recursivamente para Prencher com os galhos utilizados para achar a letra
        if (no->esquerda){
            codigo[tamanho] = '0';
            achou = criaCodigo(no->esquerda, letra, codigo, tamanho + 1);
        }
        if ((achou == 0) && no->direita){
            codigo[tamanho] = '1';
            achou = criaCodigo(no->direita, letra, codigo, tamanho + 1);
        }
        if (achou == 0){
            codigo[tamanho] = '\0';
        }
        return achou;
    }
}

//Gera a tabela com os codigos de acordo com  a Arvore
void gerarTabela(FILE *saidatxt, unsigned *listaBytes, nodeArvore *raiz){
    int i, j, achou;
    byte letra;
    saidatxt = fopen("tabela.txt","w");
    for(i = 0; i <= 255; i++){
        if(listaBytes[i] >= 1){
            char codigo[9] = {0};
            letra = (byte)i;
            achou = criaCodigo(raiz,letra,codigo,0);
            //Escreve a letra depois o codigo
            fprintf(saidatxt,"%c: ",letra);
            j = 0;
            while(codigo[j] != '\0'){
                fprintf(saidatxt,"%c",codigo[j]);
                j++;
            }
            fprintf(saidatxt,"\n");
        }
    }
    fclose(saidatxt);
}

//Codifica o Texto no Arquivo Binario
void escreverBinario(FILE *entrada, FILE *saidatxt, const char *nomeArq){
    static int bit_count=0;
    static unsigned short buffer = 0U, aux_buffer = 0U;
    unsigned short codigo, contTam = 0, tamCodigo, tamanho, auxTam;
    unsigned char c;

    FILE *saidabin = fopen("myfile.huff","wb");
    //Gravar o Primeiro Byte com 0000 0000
    fwrite(&buffer, 1, 1, saidabin);

    tamanho = tamanhoArquivo(entrada,nomeArq);

    entrada = fopen(nomeArq,"r");

    while(fread(&c, 1, 1, entrada) >= 1){
        //Busca na Tabela o codigo e escreve no Arquivo Binario
        buscarTabela(saidatxt,c,&codigo,&tamCodigo);
        buffer |= codigo << (16-bit_count-tamCodigo);
        bit_count+=tamCodigo;
        if(bit_count >= BITS){
            aux_buffer = buffer << (16-BITS);
            bit_count-= BITS;
            buffer >>= BITS;
            fwrite(&buffer, 1, 1, saidabin);
            buffer = 0U;
            buffer |= aux_buffer;
        }
        contTam++;
        //Quando chega no Final do Arquivo >> com os bits restantes e Grava no Primeiro Byte quantos bits foram necessarios para terminar o ultimo Byte
        if(contTam == tamanho){
            auxTam = BITS - bit_count;
            buffer >>= BITS;
            if(bit_count != 0){
                fwrite(&buffer, 1, 1, saidabin);
                rewind(saidabin);
                fwrite(&auxTam, 1, 1, saidabin);
            }
        }
    }
    fclose(saidabin);
}

//Busca o Codigo na Tabela para conseguir gravar no Arquivo Binario
void buscarTabela(FILE *saidatxt, byte letra, unsigned short *codigo, unsigned short *tamCodigo){
    int i, achou = 0, linha;
    unsigned short bitLetra1 = 0U, bitLetra2 = 0U;
    byte letraBusca, codeChar[9];

    saidatxt = fopen("tabela.txt","r");

    while(achou != 1){
        linha = fscanf(saidatxt, "%c: %s\n",&letraBusca,codeChar);
        if(letraBusca == letra){
            *tamCodigo = strlen(codeChar);
            //Eh usado uma Subtracao de 48 para chegar ao numero 1 ou 0
            for(i = 0; i < *tamCodigo; i++){
                bitLetra1 = ((unsigned short)codeChar[i]-48) << (*tamCodigo-i)-1;
                bitLetra2 |= bitLetra1;
            }
            *codigo = bitLetra2;
            achou = 1;
        }
    }
}

//Verifica o tamanho do Arquivo
int tamanhoArquivo(FILE *arqv, const char *nomeArq){
    int tamanho;
    arqv = fopen(nomeArq,"a");
    tamanho = ftell(arqv);
    fclose(arqv);
    return tamanho;  
}

//Verifica o tamanho do Arquivo Binario
int tamanhoArquivoBin(FILE *arqv, const char *nomeArq){
    int tamanho;
    arqv = fopen(nomeArq,"ab");
    tamanho = ftell(arqv);
    fclose(arqv);
    return tamanho;  
}

//Descomprime o Arquivo Binario de acordo com Arvore criada com a Tabela recebida nos argumentos
void descomprimeArquivo(FILE *entradaBin, arvore* raiz){
    FILE *saidatxt = fopen("myfile-descompressed.txt","w");

    int i, cont, contTam = 2, finalBits, achou, tamanhoArquivo;
    static unsigned short byteAtual = 0U, byteAux = 0U, byteAux2 = 0U, byteAux3 = 0U, bitsDontCount = 0U;
    char codigo[9], letra;

    tamanhoArquivo = tamanhoArquivoBin(entradaBin,"myfile.huff");

    entradaBin = fopen("myfile.huff","rb");
    //Primeiro Byte contem os bits que foram necessarios para preencher o ultimo Byte
    fread(&bitsDontCount, 1, 1, entradaBin);
    finalBits = 9-bitsDontCount;
    i = 0;

    while(fread(&byteAtual, 1, 1, entradaBin) >= 1){
        cont = 1;
        byteAux3 = 0U;
        byteAux2 = 0U;

        while(cont != 9){
            //Usa operacoes logicas para preencher o buffer do codigo, bit a bit, com 0 ou 1 de acordo com Byte Atual
            byteAux = byteAtual>>BITS-cont;
            byteAux3 = byteAux;
            byteAux ^= (byteAux2 << 1);

            codigo[i] = (char)(byteAux+48);
            //Envia o Buffer Atual do Codigo e tenta achar alguma letra
            achou = achaLetra(raiz,codigo,(i+1),&letra);

            byteAux2 = byteAux3;
            byteAux = 0U;
            cont++;
            i++;
            //Caso encontre, esvazia o buffer codigo, zera o indice do buffer, grava no novo Arquivo de Texto e coloca achou = 0;
            if(achou == 1){
                i = 0;
                codigo[9] = '\0';
                fwrite(&letra,1,1,saidatxt);
            }
            achou = 0;
            //Caso esteja no final do arquivo e o contador do while seja igual ao da diferenca 
            //Dos bits que foram utilizados para gravar o ultimo Bytes, Terminar a Descompressao
            if(contTam == tamanhoArquivo){
                if(cont == finalBits){
                    cont = 9;
                }
            }
        }
        contTam++;
    }
}

//Percorre a Arvore para achar a letra para determinado Codigo
int achaLetra(arvore* raiz, char codigo[], int tamanho, char* letra){
    int i, achou = 0;
    struct nodeArvore* atual = *raiz;
    for(i = 0; i < tamanho; i++){
        if(codigo[i] == '1'){
            //Caso seja uma Folha, Achou uma letra e sai da Funcao
            if( (i == tamanho-1) && (atual->direita->esquerda == NULL) && (atual->direita->direita == NULL) ){
                atual = atual->direita;
                *letra = atual->letra;
                achou = 1;
                return 1;
            }
            else{
            //Caso Contrario, Faz o ponteiro auxiliar apontar para a arvore da direita
                atual = atual->direita;
            }
        }
        if(codigo[i] == '0'){
            //Caso seja uma Folha, Achou uma letra e sai da Funcao
            if( (i == tamanho-1) && (atual->esquerda->esquerda == NULL) && (atual->esquerda->direita == NULL) ){
                atual = atual->esquerda;
                *letra = atual->letra;
                achou = 1;
                return 1;
            }
            else{
            //Caso Contrario, Faz o ponteiro auxiliar apontar para a arvore da esquerda
                atual = atual->esquerda;
            }
        }
    }
    return achou;
}
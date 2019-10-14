# Projeto 2 Estrutura de Dados

### Turma D - 2/2018

---

Este projeto visa implementar uma compressão usando a codificação de Huffman, um método que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo.

## Execução:

_Compilação do programa_

```bash
make all
```

_Comprime_

```bash
./comprime [nomedoseuarquivo].txt
```

Recomendo escrever o texto em um editor como [Visual Studio Code](https://code.visualstudio.com/), pois outros editores podem apresentar caracteres como `Espaço` ou `Enter`.

Esse programa ira gerar um arquivo codificado chamado `myfile.huff` e uma tabela com os símbolos e seus respectivos caminhos na Árvore de Huffman no formato `.txt` para a descompressão.

_Descomprime_

```bash
./descomprime tabela.txt myfile.huff
```

Esse programa ira gerar um arquivo de texto chamado `myfile-descompressed.txt`.

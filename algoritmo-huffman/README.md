# Algoritmo de compactação - Huffman
A implementação aqui do algoritmo de compactação huffman, é implementado para arquivos de texto, mas especificamente na extensão .txt.
Já existe um arquvio de texto salvo na pasta junto com o algoritmo para teste. Para testar o algoritmo em outro arquivo, crie um arquivo de texto dentro deste diretorio de extensão .txt e ao executar o programa, informe seu nome corretamente (junto com a extensão ex: "arquivo_teste.txt"). 

Depois de compactar, é possível descompactar o arquivo compactado para mostrar como o algoritmo consegue ler um arquivo compactado por ele e descompactar, mas nessa implementação, tal ação só possivel na mesma execução que compactou o arquivo. 

## Estruturas de Dados usadas
Para resolver este problema eu criei uma estrutura avore-fila, a qual uma hora é uma fila de prioridade que armazena os caracteres do texto e junto com a frequencia de cada, ordenando de forma crescente com base na frequencia. Depois essa mesma estrutura é manipulada para se tornar uma arvore binaria de huffman. Foi criada uma tabela para ler e armazenar a frequencia de cada caracter e é usada na construção da arvore-fila. Foi implementando também uma matriz dinamica onde é armazenada a tabela-dicionario(onde associa a cada caracter presente no texto, uma string de 0 e 1 que compreende sua nova representação binária). 

## Compilação:
Para compilar o programa digite na linha do terminal:
> gcc main.c huffman.c tabela_dicionario.c arvore-fila.c tabela_frequencia.c -o huffman.exe

E execute o arquivo huffman.exe, conforme seu sistema operacional. 
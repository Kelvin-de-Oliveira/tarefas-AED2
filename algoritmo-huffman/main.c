#include <stdio.h>
#include <stdlib.h>
//#include<windows.h> /*meu sistema operacional é o windows e preciso incluir essa bilbioteca para mudar o padroa de saida do console e nao ter problemas com caracteres especiais e acentuaçao*/
#include<string.h>
#include "tabela_frequencia.h"
#include "arvore-fila.h"
#include "tabela_dicionario.h"
#include "huffman.h"

#define TAB 256

/*Implementado por Kelvin de Oliveira, usando como referencia os videos sobre estrturas de dados do canal do youtube
Programação descomplicada, disponivel em: https://www.youtube.com/@progdescomplicada e a implementação do algoritmo por 
Fabrício Soares, disponivel em: https://gist.github.com/soaresfabricio/721a19d1c2d390c6e147.*/


int main (){

    FILE* file;
    unsigned int tab[TAB];
    Fila* fila_arvore;
    NO* arvore_huffman;
    char** tabela_dicionario;
    char *codificado, nome_arquivo[100];
    char opcao;
    int colunas;

    //SetConsoleOutputCP(65001);// funcao para para mudar o output do meu console para o padrao utf8
    
    printf("O algortimo huffman implementado nesta aplicacao, serve apenas para arquivos de texto com extensao .txt");
    printf("\nDigite o nome do arquivo .txt a ser compactado (inclua a extensao .txt e certifique-se que ele se encontra no mesmo diretorio que esta aplicacao): ");
    scanf("%s", nome_arquivo);
    fflush(stdin); 
    file = fopen (nome_arquivo, "r");

    if(file == NULL){
        printf("Arquivo nao foi encontrado");
        return 0;
    }
    inicializar_tabela_zerada(tab); // inicia tabela de frequencia
    preencher_tabela(file, tab); // prenche a tabela com a frequencia de cada tabela
    fila_arvore = inicializar_fila(); // aloca estrutura da fila
    preencher_fila(fila_arvore, tab); // preeche a fila ordenada de forma crescente pela frequencia
    arvore_huffman = construir_arvore_huffman(fila_arvore); // constroi a arvore binaria de huffman
    colunas = retorna_altura_arvore(arvore_huffman); // calcula o numero de colunas necessarias para tabela_dicionario
    tabela_dicionario = alocar_tabela(colunas); // aloca espaço para a tabela que servirá de dicionario
    preencher_dicionario(tabela_dicionario, arvore_huffman,"", colunas); // preenche o dicionario
    codificado = codificar(tabela_dicionario, file); // retorna o texto codificado 
    compactar(codificado); // compacta o arquivo tornando o texto codificado de caracteres 1 e 0 em bytes 
    fclose(file);

    printf("\nArquivo compactado com sucesso, disponivel nesse mesmo diretorio com o nome 'compactado.dat'"); 
    
    printf("\nDeseja descompactar o arquivo para verificar como o algoritmo funciona?:(S/N)");
    scanf("%c", &opcao);
    fflush(stdin); 
    if(opcao == 'S'){
        descompactar(arvore_huffman);
        printf("\nArquivo descompactado com sucesso, disponivel nesse mesmo diretorio com o nome 'descompactado.txt'");
    }

    printf("\nObrigado por usar meu algoritmo!");

    free(codificado);
    liberar_arvore(arvore_huffman);
    liberar_tabela_dicionario(tabela_dicionario);




    return 0;
}
    
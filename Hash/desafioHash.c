#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Implementado por Kelvin de Oliveria, como atividade da disciplina Algoritmos e Estruturas de Dados, ofertado pelo
INF - Instituto de Informática da Universidade Federal de Goiás (UFG), e ministrada pelo professor Ronaldo Martins Costa*/

#define TAB_TAM 2000

typedef struct No{
    unsigned int chave;
    struct No* proximo;
}No;

No* tabelaHash[TAB_TAM];

// função hash por multiplicação
unsigned int funcao_hash(unsigned int chave) {
    double A = 0.6180339887; 
    double parte_frac = (chave * A) - (unsigned int)(chave * A);
    return (unsigned int)(TAB_TAM * parte_frac);
}

// cria novos no para o encadeamento 
No* criar_no(unsigned int chave) {
    No* no_novo = (No*) malloc(sizeof(No));
    if(no_novo == NULL){
      printf("Erro ao criar novo no, para encadeamento");
      return NULL;
    }
    no_novo->chave = chave;
      no_novo->proximo = NULL;
    return no_novo;
}

// insere na tabela uma nova chave 
void inserir_tabela(unsigned int chave) {
    unsigned int indice = funcao_hash(chave);
    No* no_novo = criar_no(chave);
    if (tabelaHash[indice] == NULL) {
          tabelaHash[indice] = no_novo;
    }else {
        No* atual = tabelaHash[indice];
        while(atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = no_novo;
    }
}

// busca a chave na tabela e retorna 1 se encontrar a chave e 0 se não encontrar
int buscar_tabela(unsigned int chave, int* passos, int* colisoes) {
    unsigned int indice = funcao_hash(chave);
    No* atual = tabelaHash[indice];
    *passos = 0;
    *colisoes = 0;
    while (atual != NULL) {
        (*passos)++;
        if (atual->chave == chave) {
            return 1; 
        }
        (*colisoes)++;
        atual = atual->proximo;
    }
    return 0;
}

// carrega os arquivos de preenchimento e checagem 
unsigned int* ler_arquivo(char* arquivo_entrada, int* qtde) {
    FILE* fp = fopen(arquivo_entrada, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s\n", arquivo_entrada);
        return NULL;
    }

    unsigned int* numeros = malloc(3000 * sizeof(unsigned int));
    if(numeros == NULL){
        printf("Erro ao alocar memoria para os numeros do arquivo");
        return NULL;
    }
    *qtde = 0;
    while(fscanf(fp, "%u", &numeros[*qtde]) != EOF) {
        (*qtde)++;
    }

    fclose(fp);
    return numeros;
}


// registra o resultado da busca em um arquivo txt 
void registrar_resultado(char* arquivo_saida, int* checkin, int qtde_checkin) {
    FILE* fp = fopen(arquivo_saida, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para registrar o resultado\n");
        return;
    }

    for (int i = 0; i < qtde_checkin; i++) {
        int passos, colisoes;
        clock_t inicio = clock();
        int encontrado = buscar_tabela(checkin[i], &passos, &colisoes);
        clock_t fim = clock();
        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(fp, "Chave: %u, Encontrado: %d, Passos: %d, Colisões: %d, Tempo: %f(s)\n",
                checkin[i], encontrado, passos, colisoes, tempo);
    }

    fclose(fp);
}

int main() {
  
    for(int i = 0; i < TAB_TAM; i++) {
        tabelaHash[i] = NULL;
    }

    int qtde_numeros;
    unsigned int* numeros_aleatorios = ler_arquivo("numeros_aleatorios.txt", &qtde_numeros);
    if(numeros_aleatorios == NULL){
      return 0;
    }
    
    for (int i = 0; i < qtde_numeros; i++) {
        inserir_tabela(numeros_aleatorios[i]);
    }
  
    int qtde_checkin;
    unsigned int* checkin = ler_arquivo("checkin.txt", &qtde_checkin);
    if(checkin == NULL){
        return 0;
    }

    registrar_resultado("resultado_busca.txt", checkin, qtde_checkin);

    // para impressao do resultados das buscas 
    for (int i = 0; i < qtde_checkin; i++) {
        int passos, colisoes;
        clock_t inicio = clock();
        int encontrado = buscar_tabela(checkin[i], &passos, &colisoes);
        clock_t fim = clock();
        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("Chave: %u, Encontrado: %d, Passos: %d, Colisões: %d, Tempo: %f(s)\n", checkin[i], encontrado, passos, colisoes, tempo);
    }

    free(numeros_aleatorios);
    free(checkin);
    for (int i = 0; i < TAB_TAM; i++) {
        No* atual = tabelaHash[i];
        while(atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
  
    return 0;
}
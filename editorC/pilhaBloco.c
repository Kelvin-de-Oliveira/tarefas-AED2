#include "pilhaBloco.h"
#include <stdio.h>
#include <stdlib.h>

PilhaBlocos *criarPilha(int capacidade) {
  PilhaBlocos *pilha = (PilhaBlocos *)malloc(sizeof(PilhaBlocos));
  pilha->itens = (char *)malloc(capacidade * sizeof(char));
  pilha->topo = -1;
  pilha->capacidade = capacidade;
  return pilha;
}

void liberarPilha(PilhaBlocos *pilha) {
  free(pilha->itens);
  free(pilha);
}

void empilhar(PilhaBlocos *pilha, char item) {
  pilha->topo++;
  pilha->itens[pilha->topo] = item;
}

char desempilhar(PilhaBlocos *pilha) {
  if (pilhaVazia(pilha)) {
    return '\0';
  }
  char item = pilha->itens[pilha->topo];
  pilha->topo--;
  return item;
}

char topo(PilhaBlocos *pilha) {
  if (pilhaVazia(pilha)) {
    return '\0';
  }
  return pilha->itens[pilha->topo];
}

int pilhaVazia(PilhaBlocos *pilha) { 
  return (pilha->topo == -1); 
}

int verificarBlocosDelimitadores(const char *codigo) {
  if (codigo == NULL) {
    printf("Erro ao ler o arquivo na verificação de blocos\n");
    return 0;
  }

  PilhaBlocos *pilha = criarPilha(CAPACIDADE_INICIAL);
  int posicaoAtual = 0;
  int linhaAtual = 1;
  int linhaErro = -1;
  int dentroAspasDuplas = 0;
  int dentroAspasSimples = 0;

  while (codigo[posicaoAtual] != '\0') {
    char caractere = codigo[posicaoAtual];

    if (caractere == '"') {
      dentroAspasDuplas = !dentroAspasDuplas;
    } else if (caractere == '\'') {
      dentroAspasSimples = !dentroAspasSimples;
    } else if (!dentroAspasDuplas && !dentroAspasSimples) {
      switch (caractere) {
      case '{':
      case '[':
      case '(':
        empilhar(pilha, caractere);
        break;
      case '}':
        if (topo(pilha) == '{') {
          desempilhar(pilha);
        } else {
          linhaErro = linhaAtual;
          printf("Erro no fechamento de blocos na linha %d\n", linhaErro);
          liberarPilha(pilha);
          return 0;
        }
        break;
      case ']':
        if (topo(pilha) == '[') {
          desempilhar(pilha);
        } else {
          linhaErro = linhaAtual;
          printf("Erro no fechamento de blocos na linha %d\n", linhaErro);
          liberarPilha(pilha);
          return 0;
        }
        break;
      case ')':
        if (topo(pilha) == '(') {
          desempilhar(pilha);
        } else {
          linhaErro = linhaAtual;
          printf("Erro no fechamento de blocos na linha %d\n", linhaErro);
          liberarPilha(pilha);
          return 0;
        }
        break;
      default:
        break;
      }
    }

    if (caractere == '\n') {
      linhaAtual++;
    }
    posicaoAtual++;
  }

  if (!pilhaVazia(pilha)) {
    printf("Erro: caracteres de abertura sem fechamento nenhuma arvore "
           "sintatica sera construida\n");
    return 0;
  } else if (dentroAspasDuplas) {
    printf("Erro: aspas duplas não foram fechadas corretamente nenhuma arvore "
           "sintatica sera construida\n");
    return 0;
  } else if (dentroAspasSimples) {
    printf("Erro: aspas simples não foram fechadas corretamente nenhuma arvore "
           "sintatica sera construida\n");
    return 0;
  } else {
    printf("Verificação de blocos e delimitadores concluída sem erros.\n");
    return 1;
  }

  liberarPilha(pilha);
}
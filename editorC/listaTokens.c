#include "listaTokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAX_LINHA 1024

void inicializarListaTokens(ListaTokens *lista) {
  lista->tokens = NULL;
  lista->tamanho = 0;
  lista->capacidade = 0;
}

void adicionarToken(ListaTokens *lista, TipoToken tipo, const char *valor, int linha, int coluna) {
  if(lista->tamanho == lista->capacidade) {
    lista->capacidade = (lista->capacidade == 0) ? 1 : lista->capacidade * 2;
    lista->tokens =
        (Token *)realloc(lista->tokens, lista->capacidade * sizeof(Token));
  }
  lista->tokens[lista->tamanho].tipo = tipo;
  lista->tokens[lista->tamanho].valor = strdup(valor);
  lista->tokens[lista->tamanho].linha = linha;
  lista->tokens[lista->tamanho].coluna = coluna;
  lista->tamanho++;
}

void liberarListaTokens(ListaTokens *lista) {
  if (lista->tokens != NULL) {
    for (int i = 0; i < lista->tamanho; i++) {
      free(lista->tokens[i].valor);
    }
    free(lista->tokens);
    lista->tokens = NULL;
    lista->tamanho = 0;
    lista->capacidade = 0;
  }
}

int ehDelimitador(char c) {
  return (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' ||
          c == ']' || c == ',' || c == ';' || c == '#');
}

int ehOperador(char c, const char *codigo, int i) {
  if ((c == '=' && codigo[i + 1] == '=') ||
      (c == '&' && codigo[i + 1] == '&') ||
      (c == '|' && codigo[i + 1] == '|')) {
    return 1;
  }
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '<' ||
          c == '>' || c == '=' ||  c == '|' || c == '!' || c == '%');
}

int ehCaractereIdentificador(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
          (c >= '0' && c <= '9') || c == '_');
}

ListaTokens tokenizarCodigo(const char *codigo) {
  ListaTokens tokens;
  inicializarListaTokens(&tokens);

  int tamanho = strlen(codigo);
  int i = 0;
  int linha = 1;
  int coluna = 1;

  while (i < tamanho) {
    if (codigo[i] == ' ' || codigo[i] == '\t') {
      i++;
      coluna++;
      continue;
    }

    if (codigo[i] == '\n') {
      linha++;
      coluna = 1;
      i++;
      continue;
    }

    if (ehDelimitador(codigo[i])) {
      char delimitador[2] = {codigo[i], '\0'};
      adicionarToken(&tokens, DELIMITADOR, delimitador, linha, coluna);
      i++;
      coluna++;
    } else if (ehOperador(codigo[i], codigo, i)) {
      char operador[3] = {codigo[i], '\0'};
      if ((codigo[i] == '=' && codigo[i + 1] == '=') ||
          (codigo[i] == '&' && codigo[i + 1] == '&') ||
          (codigo[i] == '|' && codigo[i + 1] == '|')) {
        operador[1] = codigo[i + 1];
        operador[2] = '\0';
        i++;
        coluna++;
      }
      adicionarToken(&tokens, OPERADOR, operador, linha, coluna);
      i++;
      coluna++;
    } else if (codigo[i] == '"' || codigo[i] == '\'') {
      char literal[TAMANHO_MAX_LINHA];
      int j = 0;
      char delimitador = codigo[i];
      literal[j++] = codigo[i++];
      coluna++;
      if (delimitador == '\'') {
        if (i < tamanho && codigo[i] != '\'' && codigo[i] != '\n') {
          literal[j++] = codigo[i++];
          coluna++;
        }
        if (i < tamanho && codigo[i] == '\'') {
          literal[j++] = codigo[i++];
          coluna++;
          if (j == 3) { 
            literal[j] = '\0';
            adicionarToken(&tokens, LITERAL, literal, linha, coluna);
          } else {
            literal[j] = '\0';
            adicionarToken(&tokens, ERRO, literal, linha, coluna);
          }
        } else {
          literal[j] = '\0';
          adicionarToken(&tokens, ERRO, literal, linha, coluna);
        }
      } else {
        while (i < tamanho && codigo[i] != delimitador && codigo[i] != '\n') {
          literal[j++] = codigo[i++];
          coluna++;
        }
        if (i < tamanho && codigo[i] == delimitador) {
          literal[j++] = codigo[i++];
          coluna++;
        }
        literal[j] = '\0';
        adicionarToken(&tokens, LITERAL, literal, linha, coluna);
      }
    } else if (ehCaractereIdentificador(codigo[i])) {
      char identificador[TAMANHO_MAX_LINHA];
      int j = 0;
      while (i < tamanho && ehCaractereIdentificador(codigo[i])) {
        identificador[j++] = codigo[i++];
        coluna++;
      }
      identificador[j] = '\0';
      TipoToken tipo = IDENTIFICADOR;
      if (strcmp(identificador, "include") == 0 ||
          strcmp(identificador, "main") == 0 ||
          strcmp(identificador, "printf") == 0 ||
          strcmp(identificador, "scanf") == 0 ||
          strcmp(identificador, "if") == 0 ||
          strcmp(identificador, "else") == 0 ||
          strcmp(identificador, "for") == 0 ||
          strcmp(identificador, "while") == 0 ||
          strcmp(identificador, "switch") == 0 ||
          strcmp(identificador, "case") == 0 ||
          strcmp(identificador, "break") == 0 ||
          strcmp(identificador, "default") == 0 ||
          strcmp(identificador, "continue") == 0 ||
          strcmp(identificador, "do") == 0 ||
          strcmp(identificador, "return") == 0) {
        tipo = PALAVRA_CHAVE;
      }
      adicionarToken(&tokens, tipo, identificador, linha, coluna);
    } else {
      i++;
      coluna++;
    }
  }

  return tokens;
}


void imprimirTokens(ListaTokens tokens) {
  for (int i = 0; i < tokens.tamanho; i++) {
    printf("Tipo: %d, Valor: %s - Linha: %d\n",
           tokens.tokens[i].tipo, tokens.tokens[i].valor,
           tokens.tokens[i].linha);
  }
}
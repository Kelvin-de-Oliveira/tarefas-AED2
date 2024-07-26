#include "listaTokens.h"
#include "pilhaBloco.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *lerArquivoParaString(const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo");
    return NULL;
  }

  fseek(arquivo, 0, SEEK_END);
  long tamanhoArquivo = ftell(arquivo);
  fseek(arquivo, 0, SEEK_SET);

  char *conteudo = (char *)malloc(tamanhoArquivo + 1);
  if (conteudo == NULL) {
    printf("Falha ao alocar memória");
    fclose(arquivo);
    return NULL;
  }

  size_t bytesLidos = fread(conteudo, 1, tamanhoArquivo, arquivo);
  if (bytesLidos != tamanhoArquivo) {
    printf("Falha ao ler o arquivo");
    free(conteudo);
    fclose(arquivo);
    return NULL;
  }

  conteudo[tamanhoArquivo] = '\0';

  fclose(arquivo);
  return conteudo;
}

/*  Analise sintatica da diretiva #include */

typedef struct NoInclude {
  TipoToken tipo;
  char *valor;
  struct NoInclude *filhos[5];
} NoInclude;

NoInclude *criarNoInclude(TipoToken tipo, char *valor) {
  NoInclude *novo = (NoInclude *)malloc(sizeof(NoInclude));
  if (novo != NULL) {
    novo->tipo = tipo;
    novo->valor = strdup(valor);
    if (novo->valor != NULL) {
      for (int i = 0; i < 5; i++) {
        novo->filhos[i] = NULL;
      }
    } else {
      printf("Erro ao alocar memória para campo valor do no da arvore include");
      free(novo);
      return NULL;
    }
  } else {
    (printf("Erro ao alocar memoria para o no da arvore include"));
    return NULL;
  }

  return novo;
}

void liberarArvoreInclude(NoInclude *raiz) {
  if (raiz != NULL) {
    for (int i = 0; i < 5; i++) {
      if (raiz->filhos[i] != NULL) {
        liberarArvoreInclude(raiz->filhos[i]);
      }
    }
    free(raiz->valor);
    free(raiz);
  }
}

NoInclude *construirArvoreInclude(Token *tokens, int tamanho, int index) {
  if (tamanho - (index - 1) < 3)
    return NULL;

  if (tokens[index - 1].tipo != DELIMITADOR || strcmp(tokens[index - 1].valor, "#") != 0)
    return NULL;
  if (tokens[index].tipo != PALAVRA_CHAVE || strcmp(tokens[index].valor, "include") != 0)
    return NULL;
  if (tokens[index + 1].tipo == OPERADOR || strcmp(tokens[index + 1].valor, "<") == 0) {
    if (tokens[index + 2].tipo != IDENTIFICADOR)
      return NULL;
    if (tokens[index + 3].tipo != IDENTIFICADOR)
      return NULL;
    if (tokens[index + 4].tipo != OPERADOR || strcmp(tokens[index + 4].valor, ">") != 0)
      return NULL;
    NoInclude *raiz = criarNoInclude(tokens[index].tipo, tokens[index].valor);
    raiz->filhos[0] = criarNoInclude(tokens[index - 1].tipo, tokens[index - 1].valor);
    raiz->filhos[1] = criarNoInclude(tokens[index + 1].tipo, tokens[index + 1].valor);
    raiz->filhos[2] = criarNoInclude(tokens[index + 2].tipo, tokens[index + 2].valor);
    raiz->filhos[3] = criarNoInclude(tokens[index + 3].tipo, tokens[index + 3].valor);
    raiz->filhos[4] = criarNoInclude(tokens[index + 4].tipo, tokens[index + 4].valor);
    return raiz;
  } else if (tokens[index + 1].tipo == LITERAL) {
    NoInclude *raiz = criarNoInclude(tokens[index].tipo, tokens[index].valor);
    raiz->filhos[0] = criarNoInclude(tokens[index - 1].tipo, tokens[index - 1].valor);
    raiz->filhos[1] = criarNoInclude(tokens[index + 1].tipo, tokens[index + 1].valor);
    return raiz;
  }
  return NULL;
}

int verificarArvoreInclude(NoInclude *raiz) {
  if (raiz == NULL)
    return 0;

  if (raiz->tipo != PALAVRA_CHAVE || strcmp(raiz->valor, "include") != 0)
    return 0;
  if (raiz->filhos[0]->tipo != DELIMITADOR || strcmp(raiz->filhos[0]->valor, "#") != 0)
    return 0;

  if (raiz->filhos[1]->tipo == OPERADOR && strcmp(raiz->filhos[1]->valor, "<") == 0) {
    if (raiz->filhos[2]->tipo != IDENTIFICADOR)
      return 0;
    if (raiz->filhos[3]->tipo != IDENTIFICADOR)
      return 0;
    if (raiz->filhos[4]->tipo != OPERADOR || strcmp(raiz->filhos[4]->valor, ">") != 0)
      return 0;
  } else if ((raiz->filhos[1]->tipo != LITERAL))
    return 0;

  return 1;
}

void verificarIncludes(ListaTokens *tokens) {
  for (int i = 0; i < tokens->tamanho; i++) {
    if (tokens->tokens[i].tipo == PALAVRA_CHAVE && strcmp(tokens->tokens[i].valor, "include") == 0) {
      if (i > 0 && tokens->tokens[i - 1].tipo == DELIMITADOR && strcmp(tokens->tokens[i - 1].valor, "#") == 0) {
        NoInclude *raiz = construirArvoreInclude(tokens->tokens, tokens->tamanho, i);
        if (verificarArvoreInclude(raiz)) {
          printf("Analise sintatica comando #include: OK!\n");
        } else {
          printf("Erro de sintaxe para #include na linha: %d\n",
                 tokens->tokens[i].linha);
        }
        liberarArvoreInclude(raiz);
      } else
        (printf("Erro de sintaxe para #include na linha: %d\n",
                tokens->tokens[i].linha));
    }
  }
}

/*  Analise sintatica da função main */

typedef struct NoMain {
  TipoToken tipo;
  char *valor;
  struct NoMain *filhos[12];
} NoMain;

NoMain *criarNoMain(TipoToken tipo, char *valor) {
  NoMain *novo = (NoMain *)malloc(sizeof(NoMain));
  if (novo != NULL) {
    novo->tipo = tipo;
    novo->valor = strdup(valor);
    if (novo->valor != NULL) {
      for (int i = 0; i < 12; i++) {
        novo->filhos[i] = NULL;
      }
    } else {
      printf("Erro ao alocar memória para campo valor do no da arvore main");
      free(novo);
      return NULL;
    }
  } else {
    (printf("Erro ao alocar memoria para o no da arvore main"));
    return NULL;
  }
  return novo;
}

void liberarArvoreMain(NoMain *raiz) {
  if (raiz != NULL) {
    for (int i = 0; i < 12; i++) {
      if (raiz->filhos[i] != NULL) {
        liberarArvoreMain(raiz->filhos[i]);
      }
    }
    free(raiz->valor);
    free(raiz);
  }
}

NoMain *construirArvoreMain(Token *tokens, int tamanho, int index) {
  if (tamanho - (index - 1) < 5)
    return NULL;

  if (tokens[index - 1].tipo != IDENTIFICADOR || strcmp(tokens[index - 1].valor, "int") != 0)
    return NULL;
  if (tokens[index].tipo != PALAVRA_CHAVE || strcmp(tokens[index].valor, "main") != 0)
    return NULL;
  if (tokens[index + 1].tipo != DELIMITADOR || strcmp(tokens[index + 1].valor, "(") != 0)
    return NULL;
  if (tokens[index + 2].tipo == DELIMITADOR && strcmp(tokens[index + 2].valor, ")") == 0) {
    if (index + 3 >= tamanho || tokens[index + 3].tipo != DELIMITADOR || strcmp(tokens[index + 3].valor, "{") != 0)
      return NULL;
    NoMain *raiz = criarNoMain(tokens[index].tipo, tokens[index].valor); // main
    raiz->filhos[0] = criarNoMain(tokens[index - 1].tipo, tokens[index - 1].valor); // int
    raiz->filhos[1] = criarNoMain(tokens[index + 1].tipo, tokens[index + 1].valor); // (
    raiz->filhos[2] = criarNoMain(tokens[index + 2].tipo, tokens[index + 2].valor); //)
    raiz->filhos[3] = criarNoMain(tokens[index + 3].tipo, tokens[index + 3].valor); //{
    return raiz;
  } else if (tokens[index + 2].tipo == IDENTIFICADOR && strcmp(tokens[index + 2].valor, "int") == 0 &&
             tokens[index + 3].tipo == IDENTIFICADOR && strcmp(tokens[index + 3].valor, "argc") == 0 &&
             tokens[index + 4].tipo == DELIMITADOR && strcmp(tokens[index + 4].valor, ",") == 0 &&
             tokens[index + 5].tipo == IDENTIFICADOR && strcmp(tokens[index + 5].valor, "char") == 0 &&
             tokens[index + 6].tipo == OPERADOR && strcmp(tokens[index + 6].valor, "*") == 0 &&
             tokens[index + 7].tipo == IDENTIFICADOR && strcmp(tokens[index + 7].valor, "argv") == 0 &&
             tokens[index + 8].tipo == DELIMITADOR && strcmp(tokens[index + 8].valor, "[") == 0 &&
             tokens[index + 9].tipo == DELIMITADOR && strcmp(tokens[index + 9].valor, "]") == 0 &&
             tokens[index + 10].tipo == DELIMITADOR && strcmp(tokens[index + 10].valor, ")") == 0 &&
             tokens[index + 11].tipo == DELIMITADOR && strcmp(tokens[index + 11].valor, "{") == 0) {
    NoMain *raiz = criarNoMain(tokens[index].tipo, tokens[index].valor); // main
    raiz->filhos[0] = criarNoMain(tokens[index - 1].tipo, tokens[index - 1].valor); // int
    raiz->filhos[1] = criarNoMain(tokens[index + 1].tipo, tokens[index + 1].valor); // (
    raiz->filhos[2] = criarNoMain(tokens[index + 2].tipo, tokens[index + 2].valor); // int
    raiz->filhos[3] = criarNoMain(tokens[index + 3].tipo, tokens[index + 3].valor); // argc
    raiz->filhos[4] = criarNoMain(tokens[index + 4].tipo, tokens[index + 4].valor); // ,
    raiz->filhos[5] = criarNoMain(tokens[index + 5].tipo, tokens[index + 5].valor); // char
    raiz->filhos[6] = criarNoMain(tokens[index + 6].tipo, tokens[index + 6].valor); // *
    raiz->filhos[7] = criarNoMain(tokens[index + 7].tipo, tokens[index + 7].valor); // argv
    raiz->filhos[8] = criarNoMain(tokens[index + 8].tipo, tokens[index + 8].valor); // [
    raiz->filhos[9] = criarNoMain(tokens[index + 9].tipo, tokens[index + 9].valor); // ]
    raiz->filhos[10] = criarNoMain(tokens[index + 10].tipo, tokens[index + 10].valor); //)
    raiz->filhos[11] = criarNoMain(tokens[index + 11].tipo, tokens[index + 11].valor); // {
    return raiz;
  }
  return NULL;
}

int verificarArvoreMain(NoMain *raiz) {
  if (raiz == NULL)
    return 0;

  if (raiz->tipo != PALAVRA_CHAVE || strcmp(raiz->valor, "main") != 0)
    return 0;
  if (raiz->filhos[0]->tipo != IDENTIFICADOR || strcmp(raiz->filhos[0]->valor, "int") != 0)
    return 0;
  if (raiz->filhos[1]->tipo != DELIMITADOR || strcmp(raiz->filhos[1]->valor, "(") != 0)
    return 0;

  if (raiz->filhos[2]->tipo == DELIMITADOR && strcmp(raiz->filhos[2]->valor, ")") == 0) {
    if (raiz->filhos[3]->tipo != DELIMITADOR || strcmp(raiz->filhos[3]->valor, "{") != 0)
      return 0;

  } else if (raiz->filhos[2]->tipo != IDENTIFICADOR || strcmp(raiz->filhos[2]->valor, "int") != 0 ||
             raiz->filhos[3]->tipo != IDENTIFICADOR || strcmp(raiz->filhos[3]->valor, "argc") != 0 ||
             raiz->filhos[4]->tipo != DELIMITADOR || strcmp(raiz->filhos[4]->valor, ",") != 0 ||
             raiz->filhos[5]->tipo != IDENTIFICADOR || strcmp(raiz->filhos[5]->valor, "char") != 0 ||
             raiz->filhos[6]->tipo != OPERADOR || strcmp(raiz->filhos[6]->valor, "*") != 0 ||
             raiz->filhos[7]->tipo != IDENTIFICADOR ||strcmp(raiz->filhos[7]->valor, "argv") != 0 ||
             raiz->filhos[8]->tipo != DELIMITADOR || strcmp(raiz->filhos[8]->valor, "[") != 0 ||
             raiz->filhos[9]->tipo != DELIMITADOR || strcmp(raiz->filhos[9]->valor, "]") != 0 ||
             raiz->filhos[10]->tipo != DELIMITADOR || strcmp(raiz->filhos[10]->valor, ")") != 0 ||
             raiz->filhos[11]->tipo != DELIMITADOR || strcmp(raiz->filhos[11]->valor, "{") != 0) {
    return 0;
  }
  return 1;
}

void verificarMain(ListaTokens *tokens) {
  for (int i = 0; i < tokens->tamanho; i++) {
    if (tokens->tokens[i].tipo == PALAVRA_CHAVE && strcmp(tokens->tokens[i].valor, "main") == 0) {
      if (i > 0 && tokens->tokens[i - 1].tipo == IDENTIFICADOR && strcmp(tokens->tokens[i - 1].valor, "int") == 0) {
        NoMain *raiz = construirArvoreMain(tokens->tokens, tokens->tamanho, i);
        if (verificarArvoreMain(raiz)) {
          printf("Analise sintatica da função main: OK!\n");
        } else {
          printf("Erro de sintaxe na função main na linha: %d\n",
                 tokens->tokens[i].linha);
        }
        liberarArvoreMain(raiz);
      } else
        (printf("Erro de sintaxe para funçao main na linha: %d\n",
                tokens->tokens[i].linha));
    }
  }
}

/*  Analise sintatica da função printf */

typedef struct NoPrintf {
  TipoToken tipo;
  char *valor;
  struct NoPrintf **filhos;
  int numFilhos;
} NoPrintf;

NoPrintf *criarNoPrintf(TipoToken tipo, char *valor, int numFilhos) {
  int controle = 0;
  NoPrintf *novo = (NoPrintf *)malloc(sizeof(NoPrintf));
  if (novo != NULL) {
    novo->tipo = tipo;
    novo->valor = strdup(valor);
    if (novo->valor != NULL) {
      controle = (numFilhos * 2) + 4;
      novo->numFilhos = controle;
      novo->filhos = (NoPrintf **)malloc(controle * sizeof(NoPrintf *));
      if (novo->filhos != NULL) {
        for (int i = 0; i < controle; i++) {
          novo->filhos[i] = NULL;
        }
      } else {
        printf("Erro ao alocar memória para os filhos da arvore printf");
        free(novo->valor);
        free(novo);
        return NULL;
      }
    } else {
      printf("Erro ao alocar memória para campo valor do no da arvore printf");
      free(novo);
      return NULL;
    }
  } else {
    (printf("Erro ao alocar memoria para o no da arvore printf"));
    return NULL;
  }

  return novo;
}

void liberarArvorePrintf(NoPrintf *raiz) {
  if (raiz == NULL)
    return;
  for (int i = 0; i < raiz->numFilhos; i++) {
    if (raiz->filhos[i] != NULL) {
      liberarArvorePrintf(raiz->filhos[i]);
    }
  }
  free(raiz->filhos);
  free(raiz->valor);
  free(raiz);
}

int verificarEspecificadores(char *literal) {
  int cont = 0;
  int tamanho = strlen(literal);

  for (int i = 0; i < tamanho; i++) {
    if (literal[i] == '%' && i + 1 < tamanho) {
      int j = i + 1;
      if (literal[j] == '.') {
        j++;
        while (isdigit(literal[j])) {
          j++;
        }
      }
      switch (literal[j]) {
      case 'd':
      case 'i':
      case 'f':
      case 'c':
      case 's':
        cont++;
        i = j;
        break;
      default:
        break;
      }
    }
  }

  return cont;
}

NoPrintf *construirArvorePrintf(Token *tokens, int tamanho, int index) {
  if (tamanho - index < 4) return NULL;
  
  int qtde_arg = 0;

  if (tokens[index].tipo != PALAVRA_CHAVE || strcmp(tokens[index].valor, "printf") != 0) 
    return NULL;
  if (tokens[index + 1].tipo != DELIMITADOR ||strcmp(tokens[index + 1].valor, "(") != 0)
    return NULL;
  
  if (tokens[index + 2].tipo == LITERAL) {
    int qtde_arg = verificarEspecificadores(tokens[index + 2].valor);
    NoPrintf *raiz = criarNoPrintf(tokens[index].tipo, tokens[index].valor, qtde_arg);
    if(tamanho - (index  + 1) < raiz->numFilhos) return NULL;
    for (int i = 0; i < raiz->numFilhos; i++) {
      raiz->filhos[i] = criarNoPrintf(tokens[index + i + 1].tipo,
                                      tokens[index + i + 1].valor, qtde_arg);
    }
    return raiz;
  } else return NULL;
}

int verificarArvorePrintf(NoPrintf *raiz) {
  if (raiz == NULL)
    return 0;

  if (raiz->tipo != PALAVRA_CHAVE || strcmp(raiz->valor, "printf") != 0)
    return 0;
  if (raiz->filhos[0]->tipo != DELIMITADOR || strcmp(raiz->filhos[0]->valor,"(") != 0) 
    return 0;
  
  if (raiz->filhos[1]->tipo == LITERAL && raiz->numFilhos > 4){
    int aux = 0;
    for (int i = 0; i < (raiz->numFilhos - 4) / 2; i++){
      if(raiz->filhos[2 + (i *2)]->tipo != DELIMITADOR || strcmp(raiz->filhos[2 + (i *2)]->valor, ",") != 0)
        return 0;
      if(raiz->filhos[3 + (i *2)]->tipo != IDENTIFICADOR ||raiz->filhos[3 + (i *2)] == NULL)
        return 0;
      aux = 3 + (i *2);
    }
    if(raiz->filhos[aux + 1]->tipo != DELIMITADOR || strcmp(raiz->filhos[aux + 1]->valor,")") != 0)
      return 0;
    if(raiz->filhos[aux + 2]->tipo != DELIMITADOR || strcmp(raiz->filhos[aux + 2]->valor,";") != 0)
      return 0;
  } else if (raiz->filhos[1]->tipo == LITERAL && raiz->numFilhos == 4){
    if(raiz->filhos[2]->tipo != DELIMITADOR || strcmp(raiz->filhos[2]->valor,")") != 0)
      return 0;
    if(raiz->filhos[3]->tipo != DELIMITADOR || strcmp(raiz->filhos[3]->valor,";") != 0)
      return 0;
    } 
  return 1;
}

void verificarPrintf(ListaTokens *tokens) {
  for (int i = 0; i < tokens->tamanho; i++) {
    if (tokens->tokens[i].tipo == PALAVRA_CHAVE && strcmp(tokens->tokens[i].valor, "printf") == 0){
      NoPrintf *raiz = construirArvorePrintf(tokens->tokens, tokens->tamanho, i);
      if(verificarArvorePrintf(raiz)) { 
        printf("Analise sintatica da função printf:OK!\n"); 
      } else { printf("Erro de sintaxe na função printf na linha: %d\n",
               tokens->tokens[i].linha);
      }
      liberarArvorePrintf(raiz);
    }
  }
}

/*  Analise sintatica da função scanf */

typedef struct NoScanf {
  TipoToken tipo;
  char *valor;
  struct NoScanf **filhos;
  int numFilhos;
} NoScanf;

NoScanf *criarNoScanf(TipoToken tipo, char *valor, int numFilhos) {
  int controle = 0;
  NoScanf *novo = (NoScanf *)malloc(sizeof(NoScanf));
  if (novo != NULL) {
    novo->tipo = tipo;
    novo->valor = strdup(valor);
    if (novo->valor != NULL) {
      controle = (numFilhos * 2) + 4;
      novo->numFilhos = controle;
      novo->filhos = (NoScanf **)malloc(controle * sizeof(NoScanf *));
      if (novo->filhos != NULL) {
        for (int i = 0; i < controle; i++) {
          novo->filhos[i] = NULL;
        }
      } else {
        printf("Erro ao alocar memória para os filhos da arvore scanf");
        free(novo->valor);
        free(novo);
        return NULL;
      }
    } else {
      printf("Erro ao alocar memória para campo valor do no da arvore scanf");
      free(novo);
      return NULL;
    }
  } else {
    (printf("Erro ao alocar memoria para o no da arvore scanf"));
    return NULL;
  }

  return novo;
}

void liberarArvoreScanf(NoScanf *raiz) {
  if (raiz == NULL)
    return;
  for (int i = 0; i < raiz->numFilhos; i++) {
    if (raiz->filhos[i] != NULL) {
      liberarArvoreScanf(raiz->filhos[i]);
    }
  }
  free(raiz->filhos);
  free(raiz->valor);
  free(raiz);
}

int verificarEspecificadoresScanf(char *literal) {
    int cont = 0;
    int tamanho = strlen(literal);

    for (int i = 0; i < tamanho; i++) {
        if (literal[i] == '%' && i + 1 < tamanho) {
            switch (literal[i + 1]) {
            case 'd':
            case 'i':
            case 'f':
            case 'c':
            case 's':
                cont++;
                i++; 
                break;
            default:
                break;
            }
        }
    }

    return cont;
}

NoScanf *construirArvoreScanf(Token *tokens, int tamanho, int index) {
  if (tamanho - index < 4) 
    return NULL;

  int qtde_arg = 0;

  if (tokens[index].tipo != PALAVRA_CHAVE || strcmp(tokens[index].valor, "scanf") != 0) 
    return NULL;
  if (tokens[index + 1].tipo != DELIMITADOR ||strcmp(tokens[index + 1].valor, "(") != 0)
    return NULL;

  if (tokens[index + 2].tipo == LITERAL) {
    int qtde_arg = verificarEspecificadores(tokens[index + 2].valor);
    NoScanf *raiz = criarNoScanf(tokens[index].tipo, tokens[index].valor, qtde_arg);
    if(tamanho - (index  + 1) < raiz->numFilhos) return NULL; // nao adiantou de nada
    for (int i = 0; i < raiz->numFilhos; i++) {
      raiz->filhos[i] = criarNoScanf(tokens[index + i + 1].tipo,
                                      tokens[index + i + 1].valor, qtde_arg);
    }
    return raiz;
  } else return NULL;
}

int verificarArvoreScanf(NoScanf *raiz) {
  if (raiz == NULL)
    return 0;

  if (raiz->tipo != PALAVRA_CHAVE || strcmp(raiz->valor, "scanf") != 0)
    return 0;
  if (raiz->filhos[0]->tipo != DELIMITADOR || strcmp(raiz->filhos[0]->valor,"(") != 0) 
    return 0;

  if (raiz->filhos[1]->tipo == LITERAL && raiz->numFilhos > 4){
    int aux = 0;
    for (int i = 0; i < (raiz->numFilhos - 4) / 2; i++){
      if(raiz->filhos[2 + (i *2)]->tipo != DELIMITADOR || strcmp(raiz->filhos[2 + (i *2)]->valor, ",") != 0)
        return 0;
      if(raiz->filhos[3 + (i *2)]->tipo != IDENTIFICADOR ||raiz->filhos[3 + (i *2)] == NULL)
        return 0;
      aux = 3 + (i *2);
    }
    if(raiz->filhos[aux + 1]->tipo != DELIMITADOR || strcmp(raiz->filhos[aux + 1]->valor,")") != 0)
      return 0;
    if(raiz->filhos[aux + 2]->tipo != DELIMITADOR || strcmp(raiz->filhos[aux + 2]->valor,";") != 0)
      return 0;
  } else if (raiz->filhos[1]->tipo == LITERAL && raiz->numFilhos == 4)
      return 0;

  return 1;
}

void verificarScanf(ListaTokens *tokens) {
  for (int i = 0; i < tokens->tamanho; i++) {
    if (tokens->tokens[i].tipo == PALAVRA_CHAVE && strcmp(tokens->tokens[i].valor, "scanf") == 0){
      NoScanf *raiz = construirArvoreScanf(tokens->tokens, tokens->tamanho, i);
      if(verificarArvoreScanf(raiz)) { 
        printf("Analise sintatica da função scanf:OK!\n"); 
      } else { printf("Erro de sintaxe na função scanf na linha: %d\n",
               tokens->tokens[i].linha);
      }
      liberarArvoreScanf(raiz);
    }
  }
}


int main() {
  const char *nomeArquivo = "codigo.txt";
  char *codigo = lerArquivoParaString(nomeArquivo);
  ListaTokens tokens = tokenizarCodigo(codigo);
   
  if(verificarBlocosDelimitadores(codigo)){
    verificarIncludes(&tokens);
    verificarMain(&tokens);
    verificarScanf(&tokens);
    verificarPrintf(&tokens);

  }else return 0;
  
  free(codigo);
  liberarListaTokens(&tokens);

  return 0;
}
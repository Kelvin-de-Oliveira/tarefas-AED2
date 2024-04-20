#include "listaCadastro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TURMA_MAX 50

typedef struct turma Turma;

struct turma
{
  Aluno alunos[TURMA_MAX];
  int qtdAlunos;
};

Turma*  inicializar_turma(){
  Turma* turma = (Turma*)malloc(sizeof(Turma));
  if(turma == NULL){
    printf("\nErro ao alocar espao para a turma");
  }
  turma->qtdAlunos = 0;
  return turma;

}

int tamanho_turma(Turma *turma){
  return  turma->qtdAlunos;
}

int busca_binaria(Turma *turma, int matricula){
  int inicio = 0;
  int fim = turma->qtdAlunos - 1;

  while (inicio <= fim){
    int meio = (inicio + fim) / 2;
    if (turma->alunos[meio].matricula == matricula){
      return meio; // Aluno encontrado
    }
    else if (turma->alunos[meio].matricula < matricula){
      inicio = meio + 1;
    }
    else{
      fim = meio - 1;
    }
  }
  return inicio; // Aluno não encontrado, retorna a posição onde deve ser inserido
}

int existe_matricula(Turma *turma, int matricula){
  int posicao = busca_binaria(turma, matricula);

  if (turma->alunos[posicao].matricula == matricula){
    return 1;
  }
  else
    return 0;
}

void inserir_aluno(Turma *turma, Aluno aluno){
  int i, posicao;
  

   if( turma->qtdAlunos >= TURMA_MAX){
    printf("\n Turma está cheia! é necessário excluir alguem para incluir novo aluno!");
    return;
  }

  posicao = busca_binaria(turma, aluno.matricula);
  for (i = turma->qtdAlunos; i > posicao; i--){
    turma->alunos[i] = turma->alunos[i - 1];
  }
  turma->alunos[posicao] = aluno;
  turma->qtdAlunos++;
}

void imprimir_aluno(Turma *turma, int matricula){
  int posicao = busca_binaria(turma, matricula);

  printf("\n");
  printf("\nMatricula: %d", turma->alunos[posicao].matricula);
  printf("\nNome: %s", turma->alunos[posicao].nome);
  printf("\nCurso: %s", turma->alunos[posicao].curso);
  printf("\nMedia: %.2f", (turma->alunos[posicao].nota1 + turma->alunos[posicao].nota2) / 2);
  printf("\n------------------------------------\n");
}

void imprimir_turma(Turma *turma){
  int i;

  for (i = 0; i < turma->qtdAlunos; i++)
  {
    imprimir_aluno(turma, turma->alunos[i].matricula);
  }
}

void imprimir_aluno_nome_matricula(Turma* turma){
   int i;

  for (i = 0; i < turma->qtdAlunos; i++)
  {
    printf("\nNome: %s", turma->alunos[i].nome);
    printf("\nMatricula: %d", turma->alunos[i].matricula);
    printf("\n------------------------------------\n");
  }
}

void atualizar_nome_aluno(Turma *turma, char novo_nome[51], int matricula){
  int i;
  int posicao = busca_binaria(turma, matricula);

  strcpy(turma->alunos[posicao].nome, novo_nome);
}

void atualizar_curso_aluno(Turma *turma, char novo_curso[51], int matricula){
  int i;
  int posicao = busca_binaria(turma, matricula);

  strcpy(turma->alunos[posicao].curso, novo_curso);
}

void atualizar_notas_aluno(Turma *turma, float nova_nota1, float nova_nota2, int matricula){
  int i;
  int posicao = busca_binaria(turma, matricula);

  turma->alunos[posicao].nota1 = nova_nota1;
  turma->alunos[posicao].nota2 = nova_nota2;
}

void atualizar_matricula_aluno(Turma* turma, int matricula, int nova_matricula){
  int i;
  int posicao = busca_binaria(turma, matricula);
  Aluno backup;
  
  strcpy(backup.nome, turma->alunos[posicao].nome);
  strcpy(backup.curso, turma->alunos[posicao].curso);
  backup.matricula = nova_matricula;
  backup.nota1 = turma->alunos[posicao].nota1;
  backup.nota2 = turma->alunos[posicao].nota2;

  deletar_aluno(turma,turma->alunos[posicao].matricula);
  inserir_aluno(turma, backup);

}

void deletar_aluno(Turma* turma, int matricula){
  int i;
  int posicao = busca_binaria(turma, matricula);

  for (int i = posicao; i < turma->qtdAlunos - 1; i++) {
        turma->alunos[i] = turma->alunos[i + 1];
    }

  turma->qtdAlunos--;
  printf("Aluno excluido com sucesso.\n");

}
typedef struct aluno{
  int matricula;
  char nome[51];
  char curso[51];
  float nota1;
  float nota2;
} Aluno;

typedef struct turma Turma;

#define TURMA_MAX 50

Turma*  inicializar_turma();

int existe_matricula(Turma *turma, int matricula);

int tamanho_turma(Turma *turma);

void inserir_aluno(Turma *turma, Aluno aluno);

void imprimir_turma(Turma *turma);

void imprimir_aluno(Turma *turma, int matricula);

void imprimir_aluno_nome_matricula(Turma* turma);

void atualizar_nome_aluno(Turma *turma, char novo_nome[51], int matricula);

void atualizar_curso_aluno(Turma *turma, char novo_curso[51], int matricula);

void atualizar_matricula_aluno(Turma* turma, int matricula, int nova_matricula);

void atualizar_notas_aluno(Turma *turma, float nova_nota1, float nova_nota2, int matricula);

void deletar_aluno(Turma* turma, int matricula);
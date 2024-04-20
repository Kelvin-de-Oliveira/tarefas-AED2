#include"appCadastro.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void limpar_buffer(){
  int c;

  while ((c = getchar()) != '\n');
}

int validar_matricula(Turma *turma, int matricula){
  if (matricula < 0){
    printf("\n Matricula invalida! A matricula deve ser um numero positivo.\n");
    return 0; 
  }
  else if (existe_matricula(turma, matricula) == 1){
    printf("\n Já existe um aluno com essa matricula cadastrado!\n");
    return 0; 
  }else{
      return 1; 
    }
}

int validar_nome(char *nome){
  int i;
  if (strlen(nome) == 0){
    printf("\n Nome do aluno nao pode estar vazio!\n");
    return 0;
  }
  for (i = 0; nome[i] != '\0'; i++){
    if (!isalpha(nome[i]) && nome[i] != ' '){
      printf("\n Nome do aluno invalido! Deve conter apenas letras e espacos.\n");
      return 0;
    }
  }
  return 1;
}

int validar_curso(char *curso){
  if (strlen(curso) == 0){
    printf("\n Curso do aluno nao pode estar vazio!\n");
    return 0;
  }
  return 1;
}

int validar_nota(float nota1, float nota2){
  if (nota1 < 0 || nota1 > 10){
    printf("\n Nota %f eh invalida! A nota deve estar entre 0 e 10.\n", nota1);
    return 0;
  }
  if(nota2 < 0 || nota2 > 10){
    printf("\n Nota %f eh invalida! A nota deve estar entre 0 e 10.\n", nota2);
    return 0;
  }
  return 1;
}

void cadastrar_aluno(Turma *turma){
  Aluno novo_aluno;

  printf("\n Digite 0 a qualquer momento para sair.\n");
  do{
    printf("\n Digite a matricula do aluno: ");
    scanf("%d", &novo_aluno.matricula);
    limpar_buffer();
    if (novo_aluno.matricula == 0)
      return;
  }while(!validar_matricula(turma, novo_aluno.matricula));

  do{
    printf("\n Digite o nome do aluno: ");
    scanf("%50[^\n]s", novo_aluno.nome);
    limpar_buffer();
    if (strcmp(novo_aluno.nome, "0") == 0)
      return;
  }while (!validar_nome(novo_aluno.nome));
  
  do{
    printf("\n Dgite o curso do aluno: ");
    scanf("%50[^\n]s", novo_aluno.curso);
    limpar_buffer();
    if (strcmp(novo_aluno.curso, "0") == 0)
      return;
  }while (!validar_curso(novo_aluno.curso));
  
  do{
    printf("\n Digite a nota 1 do aluno: ");
    scanf("%f", &novo_aluno.nota1);
    limpar_buffer();
    if (novo_aluno.nota1 == 0)
      return;
    printf("\n Digite a nota 2 do aluno: ");
    scanf("%f", &novo_aluno.nota2);
    limpar_buffer();
    if (novo_aluno.nota2 == 0)
      return;
  }while (!validar_nota(novo_aluno.nota1, novo_aluno.nota2));
  

  inserir_aluno(turma, novo_aluno);
  printf("Aluno cadastrado com sucesso!\n");
}

void listar_aluno_ou_turma(Turma *turma){
  char opcao;
  int matricula = 0;
  int tam = tamanho_turma(turma);

  if( tam > 0){
    printf("\nDeseja imprimir apenas um aluno ou a turma inteira? (T/A)");
    scanf("%c", &opcao);
    limpar_buffer();

    while (opcao != 'T' && opcao != 't' && opcao != 'A' && opcao != 'a'){
      printf("\nOpcao invalida! Digite A para imprimir apenas um aluno ou T para imprimir a turma inteira.");
      scanf("%c", &opcao);
      limpar_buffer();
    }
    if (opcao == 'T' || opcao == 't')
      imprimir_turma(turma);
    else{
      imprimir_aluno_nome_matricula(turma);
      printf("\nInforme a matricula do aluno: ");
      scanf("%d", &matricula);
      limpar_buffer();
      imprimir_aluno(turma, matricula);
    }
  } else printf("\n A turma esta vazia");
}

void atualizar_aluno(Turma *turma){
  int matricula;
  int tam = tamanho_turma(turma);

  if(tam > 0){

    imprimir_aluno_nome_matricula(turma);

    printf("\n Informe a matricula do aluno que deseja atualizar: ");
    scanf("%d", &matricula);
    limpar_buffer();

    if (existe_matricula(turma, matricula) != 1){
      printf("\n Aluno nao encontrado com a matricula informada");
      return;
    }
    else menu_atualizar(turma, matricula);
  }else printf("\n A turma esta vazia!");
}

void menu_atualizar(Turma* turma, int matricula){
  int opcao;
  char novo_nome[51];
  char novo_curso[51];
  int nova_matricula;
  float nota1, nota2;

  printf("\n Qual informacao deseja atualizar?");
  printf("\n 1 - Nome");
  printf("\n 2 - Curso");
  printf("\n 3 - Notas");
  printf("\n 4 - matricula");
  printf("\n 0 - encerrar");
  printf("\nOpcao: ");
  scanf("%d", &opcao);
  limpar_buffer();

  switch(opcao){
		case 1:
		  printf("\n Digite o nome atualizado do aluno: \n");
      scanf("%50[^\n]s", novo_nome);
      limpar_buffer();
      if(validar_nome(novo_nome) == 1){
        atualizar_nome_aluno(turma, novo_nome, matricula);
        printf("\n Nome do aluno %d atualizado com sucesso!", matricula);
        imprimir_aluno(turma, matricula);
      }
      else menu_atualizar(turma, matricula);
			break;

		case 2:
			printf("\n Digite o curso atualizado do aluno: \n");
      //limpar_buffer();
      scanf("%50[^\n]s", novo_curso);
      limpar_buffer();
      if(validar_curso(novo_curso) == 1 ){
        atualizar_curso_aluno(turma, novo_curso, matricula);
        printf("\n Curso do aluno %d atualizado com sucesso!", matricula);
        imprimir_aluno(turma, matricula);
      }
      else menu_atualizar(turma, matricula);
			break;

		case 3:
		  printf("\n Digite qual o novo valor da nota 1: \n");
      scanf("%f", &nota1);
      limpar_buffer();
      printf("\n Digite qual o novo valor da nota 2: \n");
      scanf("%f", &nota2);
      limpar_buffer();
      if(validar_nota(nota1, nota2) == 1 ){
        atualizar_notas_aluno(turma, nota1, nota2, matricula);
        printf("\n Curso do aluno %d atualizado com sucesso!", matricula);
        imprimir_aluno(turma, matricula);
      }
      else menu_atualizar(turma, matricula);
			break;

    case 4:
      printf("\n Digite a matricula atualizada do aluno: \n");
      scanf("%d", &nova_matricula);
      limpar_buffer();
      if (nova_matricula < 0){
        printf("\n Matricula invalida! A matricula deve ser um numero positivo.\n");
        menu_atualizar(turma, matricula); 
      }else if (existe_matricula(turma, nova_matricula) == 1){
        printf("\n Essa matricula ja esta cadastrada\n");
        menu_atualizar(turma, matricula); 
      }
      else{ atualizar_matricula_aluno(turma, matricula, nova_matricula);
      printf("\n Matricula do aluno %d atualizado com sucesso!", nova_matricula);
      imprimir_aluno(turma, nova_matricula);
      }
      break;
      case 0:
      return;
    default:
			printf("Opcao invalida\n\n");
			menu_atualizar(turma, matricula);
			break;
	}
}

void excluir_aluno(Turma* turma){
  int matricula;
  char opcao;
  int tam = tamanho_turma(turma); 

  if(tam > 0){
  
    imprimir_aluno_nome_matricula(turma);

    printf("\n Informe a matricula do aluno que deseja excluir: ");
    scanf("%d", &matricula);
    limpar_buffer();

    if (existe_matricula(turma, matricula) != 1){
      printf("\n Aluno não encontrado com a matricula informada");
      return;
    }
    else{
      printf("\n Certeza que deseja excluir o aluno %d?(S/N) ", matricula);
      scanf("%c", &opcao);
      limpar_buffer();
        if(opcao == 's' || opcao == 'S')
          deletar_aluno(turma, matricula);
        else{
          printf("\n Operacao cancelada!");
          return;
        }
    }
  } else printf("\n A turma esta vazia!");
}


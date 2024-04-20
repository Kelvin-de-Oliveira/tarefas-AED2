#include "appCadastro.h"
#include <stdio.h>


void menu_crud(Turma* turma){
  int opcao;

  printf("\n");
  printf("\n Qual das operacoes voce deseja realizar?");
  printf("\n 1 - Create (criar novo registro)");
  printf("\n 2 - Read (imprimir registros)");
  printf("\n 3 - Update (atualizar registro)");
  printf("\n 4 - Delete (excluir registro)");
  printf("\n 0 - Para encerrar");
  printf("\nOpcao: ");
  scanf("%d", &opcao);
  limpar_buffer();
  switch(opcao){
		case 1:
      cadastrar_aluno(turma);
      menu_crud(turma);
			break;
		case 2:
      listar_aluno_ou_turma(turma);
      menu_crud(turma);
			break;
		case 3:
      atualizar_aluno(turma);
      menu_crud(turma);
			break;
    case 4:
      excluir_aluno(turma);
      menu_crud(turma);
			break;
    case 0: 
      return;
			break;
    default:
			break;
	}

}


int main(void) {
  Turma* turma;
  turma = inicializar_turma();
  menu_crud(turma);

  return 0;

}
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 50

int cont = 1, resp;
typedef struct aluno {
  char mat[25], nome[25];
  float mF, nF[6];
  int ativo;
} Aluno;

FILE *arq;

Aluno alunos[MAX_ALUNOS];

void ListarAlunos(), ListarAlunosNota(), AlterarNotasAlunos(), menu(), LerArq(),
    GravarArq();

int main(void) {

  LerArq();

  menu();

  GravarArq();

  return 0;
}

void CadastrarAluno() {
  char mat[25], nome[25];
  float soma = 0, nF[6];
  int op;

  do {

    system("clear");
    printf("Informe sua matricula: ");
    scanf("%s", mat);
    printf("Informe seu nome: ");
    scanf("%s", nome);
    for (int i = 0; i < 6; i++) {
      printf("Informe sua nota na disciplina %d: ", i + 1);
      scanf("%f", &nF[i]);
      soma += nF[i];
    }

    for (int q = 0; q < MAX_ALUNOS; q++) {
      if (alunos[q].ativo == 0) {
        strcpy(alunos[q].mat, mat);
        strcpy(alunos[q].nome, nome);
        alunos[q].mF = soma / 6;
        for (int i = 0; i < 6; i++) {
          alunos[q].nF[i] = nF[i];
        }
        alunos[q].ativo = 1;
        break;
      }
    }
    printf("Deseja continuar cadastrando alunos? (1 - sim / 0 - não): ");
    scanf("%d", &op);
  } while (op != 0);

  system("clear");
}

void ListarAlunos() {
  system("clear");
  printf("-------Lista de Alunos-------");
  for (int c = 0; c < MAX_ALUNOS; c++) {
    if (alunos[c].ativo == 1) {
      printf("\n------Aluno %d------\nMatricula: %s\nNome: %s\nMédia: %.2f",
             c + 1, alunos[c].mat, alunos[c].nome, alunos[c].mF);
      for (int j = 0; j < 6; j++) {
        printf("\nDisciplina %d: %.2f", j + 1, alunos[c].nF[j]);
      }
      printf("\n------------------\n");
    }
  }
  int op;
  do {
    printf("Deseja sair? (digite 0)");
    scanf("%d", &op);
  } while (op != 0);
  system("clear");
}

void ListarAlunosNota() {
  float med;
  system("clear");
  printf("Digite a média da nota para a busca: ");
  scanf("%f", &med);
  for (int c = 0; c < MAX_ALUNOS; c++) {
    if (alunos[c].ativo == 1 && alunos[c].mF >= med) {
      printf("\n------Aluno %d------\nMatricula: %s\nNome: %s\nMédia: %.2f",
             c + 1, alunos[c].mat, alunos[c].nome, alunos[c].mF);
      for (int j = 0; j < 6; j++) {
        printf("\nDisciplina %d: %.2f", j + 1, alunos[c].nF[j]);
      }
      printf("\n------------------\n");
    }
  }
  int op;
  do {
    printf("Deseja sair? (digite 0)");
    scanf("%d", &op);
  } while (op != 0);
  system("clear");
}

void AlterarNotasAlunos() {
  system("clear");
  int op;
  do {
    char matTemp[25];
    int soma = 0;
    printf("\nInforme a matricula do aluno que terá as notas alteradas: ");
    scanf("%s", matTemp);
    for (int c = 0; c < MAX_ALUNOS; c++) {
      if (alunos[c].ativo == 1 && strcmp(matTemp, alunos[c].mat) == 0) {
        for (int i = 0; i < 6; i++) {
          printf("Informe sua nota na disciplina %d: ", i + 1);
          scanf("%f", &alunos[c].nF[i]);
          soma += alunos[c].nF[i];
        }
        alunos[c].mF = soma / 6;
      }
    }
    printf("Deseja continuar? (1-sim/0-não): ");
    scanf("%d", &op);
  } while (op != 0);
  system("clear");
}

void LerArq() {
  char linha[MAX_ALUNOS][255];
  int c = 0, q = 0;

  arq = fopen("gravação.txt", "r");

  while (fgets(linha[c], 55, arq) != NULL) {
    q++;
    c++;
  }

  for (c = 0; c < q; c++) {
    char parcelas[10][25];
    char *parcela = strtok(linha[c], ",");
    int i = 0;
    while (parcela) {
      strcpy(parcelas[i], parcela);
      parcela = strtok(NULL, ",");
      i++;
    }

    int j = 0;

    for (int i = 0; i < 10; i++) {
      switch (i) {
      case 0:
        strcpy(alunos[c].mat, parcelas[i]);
        break;
      case 1:
        strcpy(alunos[c].nome, parcelas[i]);
        break;
      case 2:
        alunos[c].mF = atof(parcelas[i]);
        break;
      case 3 ... 8:
        alunos[c].nF[j] = atof(parcelas[i]);
        j++;
        break;
      case 9:
        alunos[c].ativo = atoi(parcelas[i]);
        break;
      }
    }
  }

  fclose(arq);
}

void GravarArq() {
  arq = fopen("gravação.txt", "w");
  for (int c = 0; c < MAX_ALUNOS; c++) {
    if (alunos[c].ativo == 1) {
      fprintf(arq, "%s,%s,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%d\n",
              alunos[c].mat, alunos[c].nome, alunos[c].mF, alunos[c].nF[0],
              alunos[c].nF[1], alunos[c].nF[2], alunos[c].nF[3],
              alunos[c].nF[4], alunos[c].nF[5], alunos[c].ativo);
    }
  }
  fclose(arq);
}

void menu() {
  system("clear");
  int resp;
  do {
    printf("\n-------Ações-------\n1-cadastro de aluno\n2-listagem de "
           "alunos\n3-listagem por "
           "nota\n4-alteração de notas\n\n0-encerrar\n-------------------\n");
    printf("Informe qual ação ira ser executada: ");
    scanf("%d", &resp);

    switch (resp) {
    case 1:
      CadastrarAluno();
      break;
    case 2:
      ListarAlunos();
      break;
    case 3:
      ListarAlunosNota();
      break;
    case 4:
      AlterarNotasAlunos();
      break;
    case 0:
      break;
    default:

      system("clear");
      printf("Operação Invalida!! tente novamente.");
      break;
    }

  } while (resp != 0);
}

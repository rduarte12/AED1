#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes globais
#define TAM_NOME 41 //inclui o '\0'
#define MAX_ALUNOS 50
#define NUM_NOTAS 3

typedef struct {
  char nome[TAM_NOME];
	float notas[NUM_NOTAS];
  float media;
} Aluno;

void limparBuffer() {
  /* Função para limpar o buffer de caracteres após chamadas do scanf
  */
  char c;
  while (((c = getchar()) != '\n') && (c != EOF));
} 

void addAluno(Aluno alunos[], int *num_alunos) {
  // verificar se já não está no máximo
  if (*num_alunos == MAX_ALUNOS) {
    printf("Número máximo já foi atingido\n");
    return;
  }
  // declaro uma nova instância da struct
  Aluno novo;
  // ler o nome do aluno com fgets
  // fgets tem 3 params:
  // 1) onde vai salvar a leitura
  // 2) tamanho da string a ser leita
  // 3) de onde vai ler a entrada (teclado = stdin)
  printf("Digite o nome: ");
  fgets(novo.nome, TAM_NOME, stdin);
  
  // ler as notas
  for (int i = 0; i < NUM_NOTAS; i++) {
    printf("Digite a nota %d: ", i+1);
    scanf("%f", &novo.notas[i]);
  }

  // calcular media
  float media = 0;
  for (int i = 0; i < NUM_NOTAS; i++) {
    media = media + novo.notas[i];
  }
  media = media / NUM_NOTAS;
  novo.media = media;

  // adicionar novo aluno no vetor (array)
  alunos[*num_alunos] = novo;
  *num_alunos += 1;
}

void listarAlunos(const Aluno alunos[], int num_alunos) {
  if (num_alunos == 0) {
    printf("Não há alunos para listar\n");
    return;
  }
  for (int i = 0; i < num_alunos; i++) {
    printf("Nome do aluno %s", alunos[i].nome);
    printf("Média = %.2f", alunos[i].media);
  }
}

void alunoMaiorMedia(const Aluno alunos[], int num_alunos) {
   if (num_alunos == 0) {
    printf("Não há alunos\n");
    return;
  }
  // encontro o índice do aluno de maior média
  int indice_maior = 0;
  for (int i = 0; i < num_alunos; i++) {
    if (alunos[indice_maior].media < alunos[i].media) {
      indice_maior = i;
    }
  }
  // imprimir aluno com maior média
  printf("Aluno com maior média:\n");
  printf("Nome: %s", alunos[indice_maior].nome);
  printf("Média: %.2f", alunos[indice_maior].media);
}


void main() {
  // array de alunos com contagem de tamanho
	Aluno alunos[MAX_ALUNOS];
  Aluno *alunos = (Aluno *) malloc(sizeof(Aluno) * MAX_ALUNOS);
  int num_alunos = 0; // começamos com 0 alunos
  
  int opcao;
  do {
    printf("1. Add aluno\n");
    printf("2. Listar alunos\n");
    printf("3. Mostrar aluno com a maior média\n");
    printf("0. Sair\n");
    printf("Escolha opção: ");
    scanf("%d", &opcao);
    limparBuffer();
    // menu
    switch (opcao) {
      case 1:
        // adicionar aluno
        addAluno(alunos, &num_alunos);
        break;
      case 2:
        listarAlunos(alunos, num_alunos);
        // listar alunos
        break;
      case 3:
        alunoMaiorMedia(alunos, num_alunos);
        // mostrar o aluno com a maior nota
        break;
      case 0:
        printf("Terminando execução\n");
        break;
      default:
        printf("Entrada inválida\n");
        break;
    }
  } while (opcao != 0);

  free(alunos);
  alunos = NULL;
  
  return 0;
}

/* Universidade Federal de Sao Carlos - UFSCar, Sorocaba

  Disciplina: Estruturas de Dados 1
  Prof. Tiago A. Almeida

  Exercício 1 - Ponteiros e Alocacao Dinamica

  Instrucoes
  ----------

  Este arquivo contem o codigo que auxiliara no desenvolvimento do
  exercicio. Voce precisara completar as funcoes requisitadas.

  Voce nao podera criar nenhuma outra funcao. Complete apenas as rotinas
  fornecidas. 														*/


#include <stdio.h>

/************************************************/

// Implemente aqui as suas estruturas de dados
#include <stdlib.h>
#define FIM -1 //para finalizar inscriçoes

typedef struct unidade{
	int cod;
	int alunos_total;
	int alunos_presentes;
	int *alunos;
	int blocos;
	float taxa;
	struct unidade *prox_unidade;
}Unidade;


/************************************************/

// Implemente aqui as suas funcoes e procedimentos
Unidade *cadastra_unidades(int N);
void cadastra_alunos(Unidade *unidades, int M);
void imprime_relatorio(Unidade *units);
void libera(Unidade *unids);

//apoios

//void imprime(Unidade *oi);
/************************************************/

int main()
{
  // Implemente aqui o seu programa principal

	Unidade *unidades = NULL; //inicio para lista de unidades
	int qt_uni, tam_blocos; //quantidade de unidades total

	scanf("%d", &qt_uni); //le quantidade de unidades
	unidades = cadastra_unidades(qt_uni); //funçao para cadastrar unidades

	scanf("%d", &tam_blocos);
	cadastra_alunos(unidades, tam_blocos);

	imprime_relatorio(unidades);
 
  return (0);
}


//--------EXECUÇAO DAS FUNÇOES---------
Unidade *cadastra_unidades(int N){ //funçao para registrar unidades
	Unidade *primeira, *aux, *aux2;
	int i;

	aux = (Unidade *) malloc (sizeof(Unidade));

	for(i = 0; i < N; i++){
		if(i == 0){ //para a primeira unidade
			scanf("%d %d", &aux->cod, &aux->alunos_total);
			aux->alunos_presentes = 0;
			aux->alunos = NULL;
			aux->prox_unidade = NULL;
			aux->taxa = 0;
			primeira = aux;
		}else{ //para proximas unidades
			aux2 = (Unidade *) malloc (sizeof(Unidade));
			scanf("%d %d", &aux2->cod, &aux2->alunos_total);
			aux->alunos_presentes = 0;
			aux2->prox_unidade = NULL;
			aux2->alunos = NULL;
			aux->taxa = 0;
			aux->prox_unidade = aux2;
			aux = aux2;
			aux2 = NULL;
		}
	}

	return(primeira);
}

void cadastra_alunos(Unidade *unidades, int M){ //funçao para registrar alunos
	Unidade *aux = unidades;
	int cod, flag = 0;

	//loop para inserçao de alunos
	do{ 
		scanf("%d", &cod);
		if(cod != FIM){ //se nao for caso de saida
			while(aux != NULL){
				flag = 0; //flag para busca
				if(aux->cod == cod){
					if(aux->alunos == NULL){ //caso primeiro aluno
						aux->alunos = (int *) malloc (M * sizeof(int));
						scanf("%d", &aux->alunos[0]);
						aux->alunos_presentes = aux->alunos_presentes + 1;
						aux->blocos = 1;
					}else{ //se n~ao for o primeio aluno
						if(aux->alunos_presentes == M * aux->blocos){
							aux->blocos = aux->blocos + 1;
							aux->alunos = (int *) realloc (aux->alunos, aux->blocos * M * sizeof(int));
						}
						scanf("%d", &aux->alunos[aux->alunos_presentes]);
						aux->alunos_presentes = aux->alunos_presentes + 1;
					}
					flag = 1;
				}
				aux = aux->prox_unidade;			
			}
			aux = unidades;
		}
	}while(cod != FIM);

	//arrumando taxa de presença
	aux = unidades;
	while(aux != NULL){
		aux-> taxa = ((float)aux->alunos_presentes / (float)aux->alunos_total) * 100;
		aux = aux->prox_unidade;
	}
}

void imprime_relatorio(Unidade *units){ //impress~ao da unidade que vai ser punida
	Unidade *aux = units;
	int cod, flag, menor_taxa = 101, i;

	while(aux != NULL){ //busca unidade
		if(aux->taxa < menor_taxa){
			menor_taxa = aux->taxa;
			cod = aux->cod;
		}
		aux = aux->prox_unidade;
	}

	aux = units;

	while(aux != NULL){ //faz a impressao da unidade e aluno
		if(aux->cod == cod){
			printf("%d\n", cod);
			for(i = 0; i < aux->alunos_presentes; i++){
				printf("%d\n", aux->alunos[i]);
			}
		}
		aux = aux->prox_unidade;
	}
}

void libera(Unidade *unids){ //libera memoria
	Unidade *aux = unids, *aux2;
	int i;

	while(aux != NULL){
		aux2 = aux;
		free(aux);
		aux = aux2;
	}
}

//funçoes de apoio
/*
void imprime(Unidade *oi){ //imprime pra teste
	Unidade *aux = oi;

	printf("UNIDADES----\n");
	while(aux != NULL){
		printf("%d %d %d %f\n", aux->cod, aux->alunos_total, aux->alunos_presentes, aux->taxa);
		aux = aux->prox_unidade;
	}
	printf("----\n");
}*/


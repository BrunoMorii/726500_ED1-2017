/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 15 - Hierarquia de Guildas

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as funcoes requisitadas.

	Voce nao podera criar nenhuma outra funcao. Complete apenas as
	rotinas	fornecidas.
 * ==================================================================
    Dados do aluno:

   RA: 726500
   Nome: Bruno Morii Borges

* ================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Frases e constantes pre-definidas
#define MSG_ERRO_ALOC 	"Erro de alocacao!\n"
#define MSG_JA_EXISTE	"Membro ja registrado na guilda!\n"
#define MSG_NAO_EXISTE	"Membro nao registado na guilda!\n"
#define MSG_JA_TUTORA	"O tutor ja e responsavel por um membro desta funcao!\n"
#define MSG_EXP_LIDER	"Nao se pode expulsar o lider da guilda!\n"
#define MSG_EXB_MEMBRO	"Alcunha: %s\nFuncao: %s\nPoder: %d\nTutor: %s\n\n"
#define MSG_EXB_CAPITAO	"Alcunha: %s\nFuncao: %s\nPoder: %d\nCapitao do esquadrao\n\n"
#define MSG_EMPATE 		"Empate\nPoderio: %d\n"
#define MSG_GANHADOR	"Vencedor: %s\nPoderio: %d\n"
#define MSG_CPT_COMUM	"Capitao comum: %s\n"
#define MSG_OPCAO_INV 	"Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI OS TAD's >>>





/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>
typedef struct item{
	char alcunha[21];
	char funcao[17];
	int poder;
	char tutorDireto[21];
}TItem;

typedef struct no *Arvore;

typedef struct no{
	TItem item;
	Arvore esq, dir;
}No;


Arvore criarNo(char alcunha[], char funcao[],int poder);
Arvore buscaMembro(Arvore no, char alcunha[]);
Arvore buscaPai(Arvore no, char alcunha[]);
int calculaPoder(Arvore no, int *poder);
Arvore buscarCapitao(Arvore no, Arvore aux, Arvore aux2);
void exibeEsquadrao(Arvore no, Arvore raiz, char capitao[]);
void imprime(Arvore no, Arvore raiz, char capitao[]);
void libera(Arvore no);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>
	int opc, poder, poder1, poder2;
	char alcunha[21], funcao[17], tutor[21], alcunha2[21];
	Arvore lider, aux, aux2;

	lider = (Arvore) malloc (sizeof(No));
	if(lider == NULL){
		printf(MSG_ERRO_ALOC);
		exit(1);
	}

	scanf("%[^\n]", alcunha); getchar();
	scanf("%d", &poder); getchar();

	lider = criarNo(alcunha, "Lider da guilda", poder);

	do{

		scanf("%d", &opc); getchar();

		switch(opc){
			//inserir
			case 1:
				//recebe os parametros independntemente se esta correto
				scanf("%[^\n]", alcunha); getchar();
				scanf("%[^\n]", funcao); getchar();
				scanf("%d", &poder); getchar();
				scanf("%[^\n]", tutor); getchar();

				//busca
				aux = buscaMembro(lider, alcunha);

				//inserir ou nao inserir, eis a questao
				if(aux == NULL){
					//busca tutor analisa se existe
					aux2 = buscaMembro(lider, tutor);
					if(aux2 == NULL){
						printf(MSG_NAO_EXISTE);
					}else{
						//achou tutor, analisa se esta disponivel
						if(strcmp("Suporte", funcao) == 0 && aux2->esq == NULL){
							aux2->esq = criarNo(alcunha, funcao, poder);
						}else if(strcmp("Combatente", funcao) == 0 && aux2->dir == NULL){
							aux2->dir = criarNo(alcunha, funcao, poder);
						}else{
							printf(MSG_JA_TUTORA);
						}
					}
				}else{
					printf(MSG_JA_EXISTE);
				}
				break;

			//remover
			case 2:
				scanf("%[^\n]", alcunha); getchar();

				//verifica se querem remover lider, se nao continua
				if(strcmp(lider->item.alcunha, alcunha) == 0){
					printf(MSG_EXP_LIDER);
				}else{
					//busca o membro
					aux = buscaMembro(lider, alcunha);
					//se nao achar sai, se nao remove
					if(aux == NULL){
						printf(MSG_NAO_EXISTE);
					}else{
						//busca o pai do que sera removido e deixa o campo de remocao NULL
						aux2 = buscaPai(lider, alcunha);
						//se suporte deixa esquerdo nulo, se nao deixa o direito
						if(strcmp("Suporte", aux->item.funcao) == 0){
							libera(aux);
							aux2->esq = NULL;
						}else{
							libera(aux);
							aux2->dir = NULL;
						}
					}
				}
				break;

			//exibir
			case 3:
				//recebe a alcunha
				scanf("%[^\n]", alcunha); getchar();

				//busca
				aux = buscaMembro(lider, alcunha);

				//se nao achar evita, se achar
				if(aux == NULL){
					printf(MSG_NAO_EXISTE);
				}else{
					exibeEsquadrao(aux, lider, alcunha);
				}
				break;

			//simular batalha
			case 4:
				//recebe as alcunhas
				scanf("%[^\n]", alcunha); getchar();
				scanf("%[^\n]", alcunha2); getchar();

				//busca e verifica existencia
				aux = buscaMembro(lider, alcunha);
				aux2 = buscaMembro(lider, alcunha2);
				if(aux == NULL || aux2 == NULL){
					//se nao existe membro
					printf(MSG_NAO_EXISTE);
				}else{
					//inicializa os poderes e calcula
					poder1 = 0;
					poder2 = 0;
					calculaPoder(aux, &poder1);
					calculaPoder(aux2, &poder2);
					//verifica se empatou ou houve vencedor
					if(poder1 == poder2){
						printf(MSG_EMPATE, poder1);
					}else{
						if(poder1 > poder2){
							printf(MSG_GANHADOR, aux->item.alcunha, poder1);
						}else{
							printf(MSG_GANHADOR, aux2->item.alcunha, poder2);
						}
					}
				}
				break;

			//Determinar o capitao
			case 5:
				//recebe as alcunhas
				scanf("%[^\n]", alcunha); getchar();
				scanf("%[^\n]", alcunha2); getchar();

				//busca e verifica existencia
				aux = buscaMembro(lider, alcunha);
				aux2 = buscaMembro(lider, alcunha2);
				if(aux == NULL || aux2 == NULL){
					//se nao existe membro
					printf(MSG_NAO_EXISTE);
				}else{
					//achar capitao em comum
					printf(MSG_CPT_COMUM, buscarCapitao(lider, aux, aux2)->item.alcunha);	
				}
				break;

			//sair
			case 6:
				libera(lider);
				break;

			//opcao invalida
			default:
				printf(MSG_OPCAO_INV);
		}
	}while(opc != 6);


	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

// <<< IMPLEMENTE AQUI AS FUNCOES >>>

Arvore criarNo(char alcunha[], char funcao[],int poder){
	Arvore no;

	no = (Arvore) malloc (sizeof(No));
	strcpy(no->item.alcunha, alcunha);
	strcpy(no->item.funcao, funcao);
	no->item.poder = poder;
	no->esq = NULL;
	no->dir = NULL;

	return(no);
}

Arvore buscaMembro(Arvore no, char alcunha[]){
	Arvore p;

	if(no != NULL){
		//se encontrou retorna o no
		if(strcmp(no->item.alcunha, alcunha) == 0){
			return(no);
		}

		//se n~ao continua buscando
		p = buscaMembro(no->esq, alcunha);
		if(p != NULL)
			return(p);

		p = buscaMembro(no->dir, alcunha);
		if(p != NULL)
			return(p);
	}

	return(NULL);
}

void libera(Arvore no){
	if(no != NULL){
		libera(no->esq);
		libera(no->dir);
		free(no);
	}
}

Arvore buscaPai(Arvore no, char alcunha[]){
	Arvore p;

	if(no != NULL){
		//busca se o pai tem filhos e se e o filho desjado
		if(no->esq != NULL && strcmp(no->esq->item.alcunha, alcunha) == 0){
			return(no);
		}

		if(no->dir != NULL && strcmp(no->dir->item.alcunha, alcunha) == 0){
			return(no);
		}

		//continua buscando
		p = buscaPai(no->esq, alcunha);
		if(p != NULL)
			return(p);

		p = buscaPai(no->dir, alcunha);
		if(p != NULL)
			return(p);
	}

	return(NULL);
}

void exibeEsquadrao(Arvore no, Arvore raiz, char capitao[]){
	while(no != NULL){
		imprime(no, raiz, capitao);
		exibeEsquadrao(no->esq, raiz, capitao);
		no = no->dir;
	}
}

void imprime(Arvore no, Arvore raiz, char capitao[]){
	if(strcmp(no->item.alcunha, capitao) == 0){
		printf(MSG_EXB_CAPITAO, no->item.alcunha, no->item.funcao, no->item.poder);
	}else{
		Arvore pai;
		pai = buscaPai(raiz, no->item.alcunha);
		printf(MSG_EXB_MEMBRO, no->item.alcunha, no->item.funcao, no->item.poder, pai->item.alcunha);
	}
}

int calculaPoder(Arvore no, int *poder){
	while(no != NULL){
		*poder += no->item.poder;
		calculaPoder(no->esq, poder);
		no = no->dir;
	}
}

Arvore buscarCapitao(Arvore no, Arvore aux, Arvore aux2){
	Arvore p, q;

	if(no != NULL){
		if(no == aux || no == aux2){
			return(no);
		}

		p = buscarCapitao(no->esq,  aux,  aux2);
		q = buscarCapitao(no->dir,  aux,  aux2);

		if(p != NULL && q != NULL){
			return(no);
		}else if(p == NULL && q != NULL){
			return(q);
		}else if(p != NULL && q == NULL){
			return(p);
		}		
	}

	return(NULL);
}
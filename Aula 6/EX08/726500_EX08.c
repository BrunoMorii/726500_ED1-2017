/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 08 - Listas Telefônicas

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

// Frases pre-definidas
#define MSG_ERRO_ALOC 		"Erro de alocacao!\n"
#define MSG_JA_EXISTE_LST	"O título de lista informado já está cadastrado!\n"
#define MSG_JA_EXISTE_REG	"O registro informado já está cadastrado na lista!\n"
#define MSG_NAO_EXISTE_LST	"A lista telefônica requisitada não está cadastrada!\n"
#define MSG_NAO_EXISTE_REG	"O registro buscado não está presente na lista!\n"
#define MSG_IMPRIME_REG 	"Nome: %s\nTel.: %s\n"
#define MSG_LISTA_VAZIA		"Lista vazia!\n"
#define MSG_OPCAO_INV 		"Opcao invalida!\n"

// Constantes
#define NOME_FINAL         	"END"



// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI OS TAD's >>>

typedef struct _R{
	char nome[200];
	char telefone[15];
	struct _R *ant;
	struct _R *prox;
}Registro;

typedef struct _LLT{
	char titulo[200];
	Registro *ultimo;
	struct _LLT *prox;
}ListaTelefonica;

typedef struct _L{
	ListaTelefonica *topo;
}Listas;


/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>

ListaTelefonica *criaLista(char titulo[]);
ListaTelefonica *buscaListas(Listas *listas, char titulo[]);
void insereRegistro(ListaTelefonica *lista, char nome[], char telefone[]);
Registro *buscaRegistro(ListaTelefonica *lista, char nome[], char telefone[], int modo, int deslocamento);
int listaVazia(ListaTelefonica *lista);
void imprimeLista(ListaTelefonica *lista, char opc);
void liberalista(Listas *listas);


/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>

	Listas *listas;
	ListaTelefonica *aux;
	Registro *aux2;
	char titulo[200], nome[200], telefone[15];
	int deslocamento, opc;

	listas = (Listas *) malloc (sizeof(Listas));
	listas->topo = NULL;

	if(listas == NULL){
		printf(MSG_ERRO_ALOC);
		exit(1);
	}

	do{

		scanf("%d", &opc); getchar();

		switch(opc){
			//insere uma lista
			case 1:
				scanf("%[^\n]s", titulo); getchar();

				if(buscaListas(listas, titulo) == NULL){
					aux = criaLista(titulo);
					if(listas->topo == NULL){
						listas->topo = aux;
					}else{
						aux->prox = listas->topo;
						listas->topo = aux;
					}
				}else{
					printf(MSG_JA_EXISTE_LST);
				}

				break;

			//insere um registro em uma lista
			case 2:
				scanf("%[^\n]s", titulo); getchar();
				aux = buscaListas(listas, titulo);

				if(aux == NULL){
					printf(MSG_NAO_EXISTE_LST);
				}else{
					scanf("%[^\n]s", nome); getchar();
					scanf("%[^\n]s", telefone); getchar();
					insereRegistro(aux, nome, telefone);
				}
				break;

			//busca com ou sem deslocamento
			case 3:
				scanf("%[^\n]s", titulo); getchar();
				aux = buscaListas(listas, titulo);

				if(aux == NULL){
					printf(MSG_NAO_EXISTE_LST);
				}else{
					scanf("%[^\n]s", nome); getchar();
					scanf("%d", &deslocamento); getchar();

					aux2 = buscaRegistro(aux, nome, nome, 3, deslocamento);
					if(aux2 == NULL){
						printf(MSG_NAO_EXISTE_REG);
					}else{
						printf(MSG_IMPRIME_REG, aux2->nome, aux2->telefone);
					}
				}
				break;

			//imprime uma lista
			case 4:
				scanf("%[^\n]s", titulo); getchar();
				aux = buscaListas(listas, titulo);
				if(aux == NULL){
					printf(MSG_NAO_EXISTE_LST);
				}else{
					if(listaVazia(aux)){
						printf(MSG_LISTA_VAZIA);
					}else{
						imprimeLista(aux, 'N');
					}
				}

				break;

			//imprime uma lista inversamente
			case 5:
				scanf("%[^\n]s", titulo); getchar();
				aux = buscaListas(listas, titulo);

				if(aux == NULL){
					printf(MSG_NAO_EXISTE_LST);
				}else{
					if(listaVazia(aux)){
						printf(MSG_LISTA_VAZIA);
					}else{
						imprimeLista(aux, 'I');
					}
				}
				break;

			case 6:
				liberalista(listas);
				free(listas);
				break;

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

ListaTelefonica *criaLista(char titulo[]){
	ListaTelefonica *aux = (ListaTelefonica *) malloc (sizeof(ListaTelefonica));
	Registro *cabeca = (Registro *) malloc (sizeof(Registro));
	char nome[200], telefone[15];

	if(aux == NULL){
		printf(MSG_ERRO_ALOC);
		exit(1);
	}

	//inicializa a Lista
	strcpy(cabeca->nome, "CABEÇA");
	strcpy(cabeca->telefone, "XXXXXX");
	cabeca->ant = cabeca;
	cabeca->prox = cabeca;

	strcpy(aux->titulo, titulo);
	aux->ultimo = cabeca;
	aux->prox = NULL;

	//rotina de inserçao de registros
	scanf("%[^\n]s", nome); getchar();

	while(strcmp(nome, NOME_FINAL) != 0){
		scanf("%[^\n]s", telefone); getchar();

		insereRegistro(aux, nome, telefone);

		scanf("%[^\n]s", nome); getchar();
	}


	return(aux);
}

void insereRegistro(ListaTelefonica *lista, char nome[], char telefone[]){
	Registro *aux = (Registro *) malloc (sizeof(Registro)), *aux2;

	if(listaVazia(lista)){
		strcpy(aux->nome, nome);
		strcpy(aux->telefone, telefone);
		aux->ant = lista->ultimo;
		aux->prox = lista->ultimo;
		lista->ultimo->prox = aux;
		lista->ultimo->ant = aux;
		lista->ultimo = aux;
	}else{
		if(buscaRegistro(lista, nome, telefone, 1, 0) != NULL){
			printf(MSG_JA_EXISTE_REG);
		}else{
			aux2 = buscaRegistro(lista, nome, telefone, 2, 0);
			strcpy(aux->nome, nome);
			strcpy(aux->telefone, telefone);
			if(aux2 != NULL){
				aux->prox = aux2;
				aux->ant = aux2->ant;
				aux2->ant->prox = aux;
				aux2->ant = aux;
			}else{
				aux->prox = lista->ultimo->prox;
				aux->ant = lista->ultimo;
				lista->ultimo->prox->ant = aux;
				lista->ultimo->prox = aux;
				lista->ultimo = aux;
			}
		}
	}
}

//modo define: 1 -> apenas busca para existencia, 2-> busca para inserçao, 3->busca para impressao
Registro *buscaRegistro(ListaTelefonica *lista, char nome[], char telefone[], int modo, int deslocamento){
	Registro *aux;
	int i = 0;

	if(modo == 1){
		aux = lista->ultimo->prox->prox;
		while(aux != lista->ultimo->prox){
			if(strcmp(aux->nome, nome) == 0 && strcmp(aux->telefone, telefone) == 0){
				return(aux);
			}
			aux = aux->prox;
		}

		return(NULL);
	}
	//modo para inserçao
	else if(modo == 2){
		aux = lista->ultimo->prox->prox;
		while(aux != lista->ultimo->prox){
			if(strcmp(aux->nome, nome) > 0){
				return(aux);
			}else if(strcmp(aux->nome, nome) == 0 && strcmp(aux->telefone, telefone) > 0){
					return(aux);
			}
			aux = aux->prox;
		}

		return(NULL);
	}
	//modo para impressao
	else{
		aux = lista->ultimo->prox->prox;
		while(aux != lista->ultimo->prox){
			if(strcmp(aux->nome, nome) == 0 || strcmp(aux->telefone, telefone) == 0){
				break;
			}
			aux = aux->prox;
		}

		if(aux != lista->ultimo->prox){
			if(deslocamento < 0){
				for(i = 0; i < (deslocamento * -1); i++){
					aux = aux->ant;
					if(aux == lista->ultimo->prox){
						return(NULL);
					}
				}
			}else{
				for(i = 0; i < deslocamento; i++){
					aux = aux->prox;
					if(aux == lista->ultimo->prox){
						return(NULL);
					}
				}
			}
			return(aux);
		}

		return(NULL);
	}
}

int listaVazia(ListaTelefonica *lista){
	if(lista->ultimo->prox == lista->ultimo){
		return(1);
	}
	return(0);
}

ListaTelefonica *buscaListas(Listas *listas, char titulo[]){
	ListaTelefonica *aux;

	aux = listas->topo;
	//rotina de busca
	while(aux != NULL){
		//caso encontre
		if(strcmp(aux->titulo, titulo) == 0){
			return(aux);
		}
		aux = aux->prox;
	}

	return(NULL); //caso nada seja encontrado
}

//opc define: N -> impress~ao normal; I->impressao inversa
void imprimeLista(ListaTelefonica *lista, char opc){
	Registro *aux;

	//imprime normalmente
	if(opc == 'N'){
		aux = lista->ultimo->prox->prox;

		while(aux != lista->ultimo->prox){
			printf(MSG_IMPRIME_REG, aux->nome, aux->telefone);
			aux = aux->prox;
		}
	}
	//imprime inversamente
	else{
		aux = lista->ultimo;

		while(aux != lista->ultimo->prox){
			printf(MSG_IMPRIME_REG, aux->nome, aux->telefone);
			aux = aux->ant;
		}
	}
}

void liberalista(Listas *listas){
	ListaTelefonica *aux;
	Registro *aux2, *aux3;

	while(listas->topo != NULL){
		aux2 = listas->topo->ultimo->prox;
		while(aux2 != listas->topo->ultimo){
			aux3 = aux2;
			aux2 = aux2->prox;
			free(aux3);
		}
		free(aux2);
		aux = listas->topo;
		listas->topo = listas->topo->prox;
		free(aux);
	}
}
/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 9 - Editor de texto

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as funcoes requisitadas.

	Voce nao podera criar nenhuma outra funcao. Complete apenas as
	rotinas	fornecidas.
 * ================================================================== */

#include <stdio.h>
#include <stdlib.h>

#define FALSE	0
#define TRUE	1

// Operacoes que podem ser realizadas.
#define INSERIR			'I'
#define MOVER_POSICAO	'M'
#define BACKSPACE		'B'
#define DELETE			'D'
#define IMPRIMIR		'P'
#define FIM				'F'

// Frase exibida quando houver erro nas operacoes
#define FRASE_ERROALOCACAO	"Erro de alocacao!\n"

// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI OS TAD's >>>

typedef struct _C{
	int tamanho;
	int cursor;
	char c;
	struct _C *ant;
	struct _C *prox;
}Caracter;

typedef struct _cab{
	Caracter *cabeca;
}Texto;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>

Texto *inicializaTexto();
void inserirChar(Texto *texto,char c);
void imprimirTexto(Texto *texto);
void moveCursor(Texto *texto, int mov);
void apagaChar(Texto *texto);
void deletaChar(Texto *texto);
void apagaTexto(Texto *texto);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main() {


	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>	
	Texto *texto;
	char c, opc;
	int mov;

	texto = inicializaTexto();
	if(texto == NULL){
		printf(FRASE_ERROALOCACAO);
		exit(1);
	}

	do{
		scanf("%c", &opc); getchar(); //le a opçao e depois o espaço

		switch(opc){

			//inserçao normal
			case INSERIR:
				scanf("%c", &c); getchar();
				inserirChar(texto, c);
				break;

			//move o cursor
			case MOVER_POSICAO:
				scanf("%d", &mov); getchar();
				moveCursor(texto, mov);
				break;

			//apaga um anterior ao cursor
			case BACKSPACE:
				apagaChar(texto);
				break;

			//apaga um depois do cursor
			case DELETE:
				deletaChar(texto);
				break;

			//imprime texto
			case IMPRIMIR:
				imprimirTexto(texto);
				if(texto->cabeca->tamanho != 0){
					printf("\n");
				}
				break;

			//imprime e finaliza o programa
			case FIM:
				imprimirTexto(texto);
				if(texto->cabeca->tamanho != 0){
					printf("\n");
				}
				apagaTexto(texto);
				free(texto);
				break;

		}

	}while(opc != FIM);
	
	return (0);
}

/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */


// <<< IMPLEMENTE AQUI AS FUNCOES >>>

Texto *inicializaTexto(){
	Texto *aux;
	Caracter *cabeca;


	cabeca = (Caracter *) malloc (sizeof(Caracter));

	cabeca->ant = NULL;
	cabeca->prox = NULL;
	cabeca->tamanho = 0;
	cabeca->cursor = 0;

	aux = (Texto *) malloc (sizeof(Texto));

	aux->cabeca = cabeca;

	return(aux);
}

void inserirChar(Texto *texto, char c){
	Caracter *aux, *novo = (Caracter *) malloc (sizeof(Caracter));
	int i, cursor;

	//inicializando para inserir novo
	novo->c = c;

	cursor = texto->cabeca->cursor;

	//apontador para andar
	aux = texto->cabeca;

	for(i = 0; i < cursor; i++){
		aux = aux->prox;
	}

	novo->ant = aux;
	novo->prox = aux->prox;
	aux->prox = novo;

	texto->cabeca->tamanho++;
	texto->cabeca->cursor++;	
}

void moveCursor(Texto *texto, int mov){

	if(texto->cabeca->cursor + mov > texto->cabeca->tamanho){
		texto->cabeca->cursor = texto->cabeca->tamanho; 
	}else if(texto->cabeca->cursor + mov < 0){
		texto->cabeca->cursor = 0;
	}else{
		texto->cabeca->cursor += mov;
	}
}

void apagaChar(Texto *texto){
	Caracter *aux = texto->cabeca, *libera;
	int i;

	if(texto->cabeca->cursor != 0){
		for(i = 0; i < texto->cabeca->cursor; i++){
			aux = aux->prox;
		}

		libera = aux;
		libera->ant->prox = libera->prox;
		if(libera->prox != NULL){
			libera->prox->ant = libera->ant;
		}
		free(libera);
		texto->cabeca->cursor--;
		texto->cabeca->tamanho--;
	}
}

void deletaChar(Texto *texto){
	Caracter *aux = texto->cabeca, *libera;
	int i;

	for(i = 0; i < texto->cabeca->cursor; i++){
			aux = aux->prox;
	}
	
	if(aux->prox != NULL){
		libera = aux->prox;
		if(libera->prox != NULL){
			aux->prox = libera->prox;
			libera->prox->ant = aux;
		}else{
			aux->prox = NULL;
		}
		free(libera);
		texto->cabeca->tamanho--;
	}
}



void imprimirTexto(Texto *texto){
	Caracter *aux;

	aux = texto->cabeca->prox;

	while(aux != NULL){
		printf("%c", aux->c);
		aux = aux->prox;
	}
}

void apagaTexto(Texto *texto){
	Caracter *aux = texto->cabeca, *libera;

	while(aux != NULL){
		libera = aux;
		aux = aux->prox;
		free(libera);
	}
}
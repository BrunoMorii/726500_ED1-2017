/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 04 - Ultima Carta

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

// Frase exibida quando houver erro nas operacoes
#define FRASE_ERRO_ALOC "Erro de alocacao!\n"


// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI O TAD >>>

typedef struct _carta{
	int valor;
	struct _carta *prox;
}Carta;

typedef struct _fila{
	Carta *inicio;
	Carta *fim;
}Fila;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>

int enfileira(Fila *cartas, int valor);

int desenfileira(Fila *cartas);

Fila *inicializa();

void imprime(Fila *cartas);

void libera(Fila *cartas);

void recebe_cartas(Fila *cartas);

int descobre_carta(Fila *cartas);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>
	Fila *conjunto_cartas;

	conjunto_cartas = inicializa();
	if(conjunto_cartas == NULL){
		printf(FRASE_ERRO_ALOC);
		exit(1);
	}

	recebe_cartas(conjunto_cartas); //rotina para enfileirar as cartas

	//imprime retorno da funcao que descobre a ultima carta
	printf("%d\n", descobre_carta(conjunto_cartas));

	free(conjunto_cartas);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

// <<< IMPLEMENTE AQUI AS FUNCOES >>>

Fila *inicializa(){
	Fila *aux;

	aux = (Fila *) malloc (sizeof(Fila));

	//inicializa os ponteiro de inicio e fim de fila
	aux->inicio = NULL;
	aux->fim = NULL;

	return(aux);
}

int enfileira(Fila *cartas, int valor){
	Carta *aux;

	aux = (Carta *) malloc (sizeof(Carta));

	if(aux == NULL){ //verifica de alocou corretamente
		return(0);
	}

	//da valor a carta
	aux->valor = valor;
	aux->prox = NULL;

	if(cartas->inicio == NULL){ //se fila esta vazia
		cartas->inicio = aux;
		cartas->fim = aux;
	}else{ //se nao esta vazia
		cartas->fim->prox = aux;
		cartas->fim = aux;
	}

	return(1);
}

int desenfileira(Fila *cartas){
	Carta *aux;
	int valor_recuperado;

	if(cartas->inicio == NULL){ //verifica se fila esta vaiza
		return(0);
	}

	aux = (Carta *) malloc (sizeof(Carta));
	//move o inicio da fila
	aux = cartas->inicio;
	cartas->inicio = cartas->inicio->prox;
	//recupera valor da carta
	valor_recuperado = aux->valor;

	free(aux); //libera memmoria

	return(valor_recuperado);
}

void recebe_cartas(Fila *cartas){
	int n;

	do{
		scanf("%d", &n);

		if(n != 0){
			enfileira(cartas, n);
		}
	}while(n != 0);
}

int descobre_carta(Fila *cartas){
	Fila *descarte;

	//cria pilha de descarte
	descarte = inicializa();
	if(descarte == NULL){
		printf(FRASE_ERRO_ALOC);
		exit(1);
	}

	//realiza operaçoes de descarte e mover
	while(cartas->inicio->prox != NULL){
		enfileira(descarte, desenfileira(cartas));
		enfileira(cartas, desenfileira(cartas));
	}

	imprime(descarte);

	return(cartas->inicio->valor);
}

void imprime(Fila *cartas){
	Carta *aux = cartas->inicio;

	while(aux != NULL){
		printf("%d ", aux->valor);
		aux = aux->prox;
	}

	printf("\n");
}

void libera(Fila *cartas){
	Carta *aux = cartas->inicio, *aux2;

	while(aux != NULL){
		aux2 = aux;
		aux = aux->prox;
		free(aux2);
	}
}
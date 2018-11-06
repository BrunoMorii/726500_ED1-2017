/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 05 - Dobraduras Inteligentes

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
#include <math.h>

// Frases exibidas quando houver erro nas operacoes
#define MSG_ERRO_ALOC 	"Erro de alocacao!\n"
#define MSG_VAZIO 		"Não há nenhum quebra-cabeça para ser resolvido!\n"
#define MSG_OPCAO_INV 	"Opcao invalida!\n"


// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI O TAD E REGISTROS >>>

typedef struct _puzzle{
	char tipo;
	int qtdElem;
	int *mat;
	char *bio;
}Puzzle;

typedef struct _result{
	char tipo;
	int pares;
	struct _result *prox;
}Resultado;

typedef struct _fila{
	Resultado *inicio;
	Resultado *fim;
}Fila;

typedef struct _pi{
	int n;
	char c;
	struct _pi *prox;
}NumChar;

typedef struct _pil{
	NumChar *topo;
}Pilha;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>
Fila *inicializa_puzzle();

void enfileira_puzzle(Fila *filaPuzzles, Resultado *quebraCabeca);

Resultado *desenfileira_puzzle(Fila *filaPuzzles);

int verifica_vazio(Fila *filaPuzzles);

void libera_puzzles(Fila *filaPuzzles);

Resultado *criaPuzzle(char tipo, int qtd);

int resolve_puzzle(Puzzle *puzzle);

void empilha(Pilha *pilha, int tipo, char c, int n);

void desempilha(Pilha *pilha);

void libera_pilha(Pilha *pilha);

int verifica_primo(int x);


/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>
	Fila *fila_Puzzles;
	Resultado *aux;
	char tipo;
	int opc, n;

	fila_Puzzles = inicializa_puzzle(); //incializa o fila de puzzles
	if(fila_Puzzles == NULL){
		printf(MSG_ERRO_ALOC);
		exit(1);
	}

	do{	
		scanf("%d", &opc); //leitura da opçao

		switch(opc){

			//insere puzzle
			case 1:
				scanf("\n%c %d", &tipo, &n);
				aux = criaPuzzle(tipo, n);
				enfileira_puzzle(fila_Puzzles, aux);
				break;

			//adia puzzle
			case 2:
				if(verifica_vazio(fila_Puzzles)){
					printf(MSG_VAZIO);
				}else{
					enfileira_puzzle(fila_Puzzles, desenfileira_puzzle(fila_Puzzles));
				}
				break;

			//resolve puzzle
			case 3:
				if(verifica_vazio(fila_Puzzles)){
					printf(MSG_VAZIO);
				}else{
					printf("%d (%c)\n", fila_Puzzles->inicio->pares, fila_Puzzles->inicio->tipo);
					desenfileira_puzzle(fila_Puzzles);
				}
				break;

			//sai do programa
			case 4:
				libera_puzzles(fila_Puzzles);
				break;

			default:
				printf(MSG_OPCAO_INV);
		}
	}while(opc != 4);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

// <<< IMPLEMENTE AQUI AS FUNCOES >>>

Fila *inicializa_puzzle(){
	Fila *aux;

	aux = (Fila *) malloc (sizeof(Fila));

	aux->inicio = NULL;
	aux->fim = NULL;

	return(aux);
}

void enfileira_puzzle(Fila *filaPuzzles, Resultado *quebraCabeca){

	if(verifica_vazio(filaPuzzles)){ //se a fila estiver vazia
		filaPuzzles->inicio = quebraCabeca;
		filaPuzzles->fim = quebraCabeca;
	}else{
		filaPuzzles->fim->prox = quebraCabeca;
		filaPuzzles->fim = quebraCabeca;
	}
}

Resultado *desenfileira_puzzle(Fila *filaPuzzles){
	Resultado *aux;

	aux = filaPuzzles->inicio;
	filaPuzzles->inicio = filaPuzzles->inicio->prox;
	aux->prox = NULL;

	return(aux);
}

int verifica_vazio(Fila *filaPuzzles){

	if(filaPuzzles->inicio == NULL){ //se vazio, retorna 1
		return(1);
	}

	return(0); //se nao vazio, retorna 0
}

Resultado *criaPuzzle(char tipo, int qtd){
	Puzzle *aux;
	Resultado *aux2;
	int i;
	char c;

	aux = (Puzzle *) malloc (sizeof(Puzzle));

	aux->tipo = tipo;
	aux->qtdElem = qtd;

	if(tipo == 'M'){ //para matematica
		aux->mat = (int *) malloc (qtd * sizeof(int));

		for(i = 0; i < qtd; i++){
			scanf("%d", &aux->mat[i]);
		}

	}else{ //para biologia
		aux->bio = (char *) malloc ((qtd + 1)* sizeof(char));
		i = 0;

		scanf("\n");
		while(i < qtd){
			scanf("%c", &c);

			if(c != '\n'){
				aux->bio[i] = c;
			}

			i++;
		}

		aux->bio[i] = '\0';

	}

	aux2 = (Resultado *) malloc (sizeof(Resultado));

	aux2->tipo = tipo;
	aux2->pares = resolve_puzzle(aux);
	aux2->prox = NULL;

	free(aux);
	if(tipo == 'M'){
		free(aux->mat);
	}else{
		free(aux->bio);
	}

	return(aux2);
}

int resolve_puzzle(Puzzle *puzzle){
	int i, pares = 0;
	Pilha *pilha;

	pilha = (Pilha *) malloc (sizeof(Pilha));
	pilha->topo = NULL;

	if(puzzle->tipo == 'M'){ //para matematica
		for(i = 0; i < puzzle->qtdElem; i++){
			if(pilha->topo == NULL){
				empilha(pilha, puzzle->tipo, 'c', puzzle->mat[i]);
			}else if(verifica_primo(puzzle->mat[i]) && verifica_primo(pilha->topo->n)){
				desempilha(pilha);
				pares++;
			}else{
				empilha(pilha, puzzle->tipo, 'c', puzzle->mat[i]);
			}
		}		
	}else{ //para biologia
		for(i = 0; i < puzzle->qtdElem; i++){
			if(pilha->topo == NULL){
				empilha(pilha, puzzle->tipo, puzzle->bio[i], 0);
			}else if(puzzle->bio[i] == '\0'){
				i++;
			}else if((puzzle->bio[i] == 'A' && pilha->topo->c == 'T') ||
					 (puzzle->bio[i] == 'T' && pilha->topo->c == 'A') ||
					 (puzzle->bio[i] == 'C' && pilha->topo->c == 'G') ||
					 (puzzle->bio[i] == 'G' && pilha->topo->c == 'C')){

				desempilha(pilha);
				pares++;

			}else{
				empilha(pilha, puzzle->tipo, puzzle->bio[i], 0);
			}
		}
	}

	libera_pilha(pilha);

	return(pares);
}

void empilha(Pilha *pilha, int tipo, char c, int n){
	NumChar *aux;

	aux = (NumChar *) malloc (sizeof(NumChar));

	if(tipo == 'M'){
		aux->n = n;
	}else{
		aux->c = c;
	}

	if(pilha->topo == NULL){
		aux->prox = NULL;
		pilha->topo = aux;
	}else{
		aux->prox = pilha->topo;
		pilha->topo = aux;
	}
}

void desempilha(Pilha *pilha){
	NumChar *aux;

	aux = pilha->topo;
	pilha->topo = pilha->topo->prox;
	free(aux);
}

void libera_pilha(Pilha *pilha){
	NumChar *aux;

	while(pilha->topo != NULL){
		aux = pilha->topo;
		pilha->topo = pilha->topo->prox;
		free(aux);
	}
}

int verifica_primo(int x){
	int i;

	if(x == 1){
		return(0);
	}

	for(i = 2; i <= sqrt(x); i++){
		if(x % i == 0){
			return(0);
		}
	}

	return(1);
}

void libera_puzzles(Fila *filaPuzzles){
	Resultado *aux = filaPuzzles->inicio, *aux2;

	while(aux != NULL){
		aux2 = aux;
		aux = aux->prox;
		free(aux2);
	}
}
/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 13 - Cavalos Rebeldes

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
#define MSG_JA_EXISTE		"Já existe um tabuleiro com este título cadastrado!\n"
#define MSG_NAO_EXISTE		"Não existe nenhum tabuleiro com este título!\n"
#define MSG_OPCAO_INV 		"Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI OS TAD's >>>
typedef struct _pos{
	int x,y;
}Posicao;

typedef struct _tab{
	char titulo[50];
	int n, m;
	int **A;
	struct _tab *anterior;
}Tabuleiro;

typedef struct _pil{
	Tabuleiro *topo;
}Pilha;

typedef struct _cel{
	Posicao pos;
	struct _cel *prox;
}Item;

typedef struct _f{
	Item *inicio;
	Item *fim;
}Fila;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>

void empilhaTab(Pilha *pilha, Tabuleiro *item);
void desempilhaTab(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
Tabuleiro *buscaTab(Pilha *pilha, char titulo[]);
Tabuleiro *criaTab(char titulo[]);
void imprime(Tabuleiro *tabuleiro);
int resolveTab(Tabuleiro *tab);
void enfileira(Fila *fila, Posicao p);
int filaVazia(Fila *fila);
void desenfileira(Fila *fila, Posicao *q);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>
	Pilha *tabuleiros;
	Tabuleiro *novo;
	char titulo[50];
	int opc, i, j;

	tabuleiros = (Pilha *) malloc (sizeof(Pilha));
	if(tabuleiros == NULL){
		printf(MSG_ERRO_ALOC);
		exit(0);
	}
	tabuleiros->topo = NULL;

	do{
		scanf("%d", &opc); getchar();

		switch(opc){
			//insere tabuleiro
			case 1:
				scanf("%[^\n]", titulo); getchar();
				novo = buscaTab(tabuleiros, titulo);
				if(novo != NULL){
					printf(MSG_JA_EXISTE);
				}else{
					novo = criaTab(titulo);
					empilhaTab(tabuleiros, novo);
				}
				break;

			//resolve algum tabuleiro
			case 2:
				scanf("%[^\n]", titulo); getchar();
				novo = buscaTab(tabuleiros, titulo);
				if(novo == NULL){
					printf(MSG_NAO_EXISTE);
				}else{
					printf("%d\n", resolveTab(novo));
					for(i = 0; i <= novo->n; i++){
						for(j = 0; j <= novo->m; j++){
							if(novo->A[i][j] != -2)
								novo->A[i][j] = -1;
						}
					}
				}
				break;

			//libera memoria e encerra programa
			case 3:
				while(tabuleiros->topo != NULL){
					desempilhaTab(tabuleiros);
				}
				free(tabuleiros);
				break;

			//opcao invalida
			default:
				printf(MSG_OPCAO_INV);
		}

	}while(opc != 3);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

// <<< IMPLEMENTE AQUI AS FUNCOES >>>

void empilhaTab(Pilha *pilha, Tabuleiro *item){
	item->anterior = pilha->topo;

	pilha->topo = item;
}

void desempilhaTab(Pilha *pilha){
	Tabuleiro *remove;

	remove = pilha->topo;
	pilha->topo = pilha->topo->anterior;

	free(remove);
}

int pilhaVazia(Pilha *pilha){
	return(pilha->topo == NULL);
}

//busca pelo tabuleiro
Tabuleiro *buscaTab(Pilha *pilha, char titulo[]){
	Tabuleiro *aux;

	if(pilhaVazia(pilha))
		return (NULL);

	aux = pilha->topo;
	while(aux != NULL){
		if(strcmp(aux->titulo, titulo) == 0){
			return(aux);
		}
		aux = aux->anterior;
	}

	return (NULL);
}

//cria tabuleiro e retorna
Tabuleiro *criaTab(char titulo[]){
	Tabuleiro *novo;
	int i, j;
	char p;

	//cria tabuleiro
	novo = (Tabuleiro *) malloc (sizeof(Tabuleiro));
	if(novo == NULL){
		printf(MSG_ERRO_ALOC);
		exit(0);
	}

	//da nome e inicializa campos
	strcpy(novo->titulo, titulo);

	//recebe a ordem da matriz
	scanf("%d %d", &novo->n, &novo->m); getchar();

	//alocando matrize
	novo->A = (int **) malloc (sizeof(int *) * novo->n + 1);
	for(i = 0; i <= novo->n; i++){
		novo->A[i] = (int *) malloc (sizeof(int) * novo->m + 1);
	}

	//arruma ordem
	novo->n--;
	novo->m--;

	//recebe matriz e apenas guarda posicoes encantadas
	for(i = 0; i <= novo->n; i++){
		for(j = 0; j <= novo->m; j++){
			scanf("%c", &p);
			if(p == '#'){
				novo->A[i][j] = -2;
			}else{
				novo->A[i][j] = -1;
			}
		}
		getchar();
	}	

	return(novo);
}

//funcao que resolve o tabuleiro
int resolveTab(Tabuleiro *tab){
	Posicao origem, destino, q, aux;
	Fila fila;

	//recebe origem e destino
	scanf("%d %d", &origem.x, &origem.y); getchar();
	scanf("%d %d", &destino.x, &destino.y); getchar();

	//trata origem e destino, matriz comeca em 0,0
	origem.x--;
	origem.y--;
	destino.x--;
	destino.y--;

	//se destino ou origem encatados
	if(tab->A[origem.x][origem.y] == -2 || tab->A[destino.x][destino.y] == -2)
		return(-1);

	//se origem igual destino
	if(origem.x == destino.x && origem.y == destino.y){
		return(0);
	}

	fila.inicio = NULL;
	fila.fim = NULL;

	tab->A[origem.x][origem.y] = 0;
	enfileira(&fila, origem);

	while(!filaVazia(&fila) && tab->A[destino.x][destino.y] == -1){
		desenfileira(&fila, &q);

		//verificacoes
		if((q.x + 2 <= tab->n) && (q.y + 1 <= tab->m) && (tab->A[q.x + 2][q.y + 1] == -1)){
			tab->A[q.x + 2][q.y + 1] = tab->A[q.x][q.y] + 1;
			aux.x = q.x + 2;
			aux.y = q.y + 1;
			enfileira(&fila, aux);
		}
		
		if((q.x + 2 <= tab->n) && (q.y - 1 >= 0) && (tab->A[q.x + 2][q.y - 1] == -1)){
			tab->A[q.x + 2][q.y - 1] = tab->A[q.x][q.y] + 1;
			aux.x = q.x + 2;
			aux.y = q.y - 1;
			enfileira(&fila, aux);
		}
		
		if((q.x - 2 >= 0) && (q.y + 1 <= tab->m) && (tab->A[q.x - 2][q.y + 1] == -1)){
			tab->A[q.x - 2][q.y + 1] = tab->A[q.x][q.y] + 1;
			aux.x = q.x - 2;
			aux.y = q.y + 1;
			enfileira(&fila, aux);
		}
		
		if((q.x - 2 >= 0) && (q.y - 1 >= 0) && (tab->A[q.x - 2][q.y - 1] == -1)){
			tab->A[q.x - 2][q.y - 1] = tab->A[q.x][q.y] + 1;
			aux.x = q.x - 2;
			aux.y = q.y - 1;
			enfileira(&fila, aux);
		}
		
		if((q.x + 1 <= tab->n) && (q.y + 2 <= tab->m) && (tab->A[q.x + 1][q.y + 2] == -1)){
			tab->A[q.x + 1][q.y + 2] = tab->A[q.x][q.y] + 1;
			aux.x = q.x + 1;
			aux.y = q.y + 2;
			enfileira(&fila, aux);
		}
		
		if((q.x + 1 <= tab->n) && (q.y - 2 >= 0) && (tab->A[q.x + 1][q.y - 2] == -1)){
			tab->A[q.x + 1][q.y - 2] = tab->A[q.x][q.y] + 1;
			aux.x = q.x + 1;
			aux.y = q.y - 2;
			enfileira(&fila, aux);
		}
		
		if((q.x - 1 >= 0) && (q.y + 2 <= tab->m) && (tab->A[q.x - 1][q.y + 2] == -1)){
			tab->A[q.x - 1][q.y + 2] = tab->A[q.x][q.y] + 1;
			aux.x = q.x - 1;
			aux.y = q.y + 2;
			enfileira(&fila, aux);
		}
		
		if((q.x - 1 >= 0) && (q.y - 2 >= 0) && (tab->A[q.x - 1][q.y - 2] == -1)){
			tab->A[q.x - 1][q.y - 2] = tab->A[q.x][q.y] + 1;
			aux.x = q.x - 1;
			aux.y = q.y - 2;
			enfileira(&fila, aux);
		}
	}

	return(tab->A[destino.x][destino.y]);
}

void enfileira(Fila *fila, Posicao p){
	Item *novo;

	if(filaVazia(fila)){
		novo = (Item *) malloc (sizeof(Item));
		novo->pos = p;
		novo->prox = NULL;
		fila->inicio = novo;
		fila->fim = novo;
	}else{
		novo = (Item *) malloc (sizeof(Item));
		novo->pos = p;
		novo->prox = NULL;
		fila->fim->prox = novo;
		fila->fim = novo;
	}
}

int filaVazia(Fila *fila){
	return(fila->inicio == NULL);
}

void desenfileira(Fila *fila, Posicao *q){
	Item *aux;

	if(filaVazia(fila))
		return;

	aux = fila->inicio;
	fila->inicio = aux->prox;

	*q = aux->pos;

	free(aux);
}
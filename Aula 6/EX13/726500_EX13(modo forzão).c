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
	int num_encantados;
	Posicao *encantados;
	struct _tab *anterior;
}Tabuleiro;

typedef struct _pil{
	Tabuleiro *topo;
}Pilha;

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

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>
	Pilha *tabuleiros;
	Tabuleiro *novo;
	char titulo[50];
	int opc;

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
	novo->num_encantados = 0;
	novo->encantados = (Posicao *) malloc (sizeof(Posicao));

	//recebe a ordem da matriz
	scanf("%d %d", &novo->n, &novo->m); getchar();
	novo->n--;
	novo->m--;

	//recebe matriz e apenas guarda posicoes encantadas
	for(i = 0; i <= novo->n; i++){
		for(j = 0; j <= novo->m; j++){
			scanf("%c", &p);
			if(p == '#'){
				novo->encantados = (Posicao *) realloc (novo->encantados, sizeof(Posicao) * (novo->num_encantados + 1));
				novo->encantados[novo->num_encantados].x = i;
				novo->encantados[novo->num_encantados].y = j;
				novo->num_encantados++;
			}
		}
		getchar();
	}

	return(novo);
}

//funcao que resolve o tabuleiro
int resolveTab(Tabuleiro *tab){
	int i, j, k, passos = 1;
	int matriz[100][100];
	Posicao origem, destino;

	//recebe origem e destino
	scanf("%d %d", &origem.x, &origem.y); getchar();
	scanf("%d %d", &destino.x, &destino.y); getchar();

	//trata origem e destino, matriz comeca em 0,0
	origem.x--;
	origem.y--;
	destino.x--;
	destino.y--;

	//verifica se origem ou destino sao encantados
	for(k = 0; k < tab->num_encantados; k++){
		if(origem.x == tab->encantados[k].x && origem.y == tab->encantados[k].y ||
		   destino.x == tab->encantados[k].x && destino.y == tab->encantados[k].y ){
			return(-1);
		}
	}

	//se origem igual destino
	if(origem.x == destino.x && origem.y == destino.y){
		return(0);
	}

	//preenche matriz, -1 se livre, -2 se encantado;
	for(i = 0; i <= tab->n; i++){
		for(j = 0; j <= tab->m; j++){
			matriz[i][j] = -1;
		}
	}

	for(k = 0; k < tab->num_encantados; k++){
		matriz[tab->encantados[k].x][tab->encantados[k].y] = -2;
	}

	matriz[origem.x][origem.y] = 0;

	//tentativas com passos
	for(passos = 0; passos <= 2000 && matriz[destino.x][destino.y] == -1; passos++){
		for(i = 0; i <= tab->n; i++){
			for(j = 0; j <= tab->m; j++){
				if(matriz[i][j] == passos){
					//verificacoes
					if((i + 2 <= tab->n) && (j + 1 <= tab->m) && (matriz[i + 2][j + 1] == -1)){
						matriz[i + 2][j + 1] = passos + 1;
					}
					
					if((i + 2 <= tab->n) && (j - 1 >= 0) && (matriz[i + 2][j - 1] == -1)){
						matriz[i + 2][j - 1] = passos + 1;
					}
					
					if((i - 2 >= 0) && (j + 1 <= tab->m) && (matriz[i - 2][j + 1] == -1)){
						matriz[i - 2][j + 1] = passos + 1;
					}
					
					if((i - 2 >= 0) && (j - 1 >= 0) && (matriz[i - 2][j - 1] == -1)){
						matriz[i - 2][j - 1] = passos + 1;
					}
					
					if((i + 1 <= tab->n) && (j + 2 <= tab->m) && (matriz[i + 1][j + 2] == -1)){
						matriz[i + 1][j + 2] = passos + 1;
					}
					
					if((i + 1 <= tab->n) && (j - 2 >= 0) && (matriz[i + 1][j - 2] == -1)){
						matriz[i + 1][j - 2] = passos + 1;
					}
					
					if((i - 1 >= 0) && (j + 2 <= tab->m) && (matriz[i - 1][j + 2] == -1)){
						matriz[i - 1][j + 2] = passos + 1;
					}
					
					if((i - 1 >= 0) && (j - 2 >= 0) && (matriz[i - 1][j - 2] == -1)){
						matriz[i - 1][j - 2] = passos + 1;
					}
				}
			}
		}
	}

	return(matriz[destino.x][destino.y]);
}
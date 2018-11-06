/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 06 - Batata Quente

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


// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI O TAD >>>

typedef struct _p{
	char *nome;
	struct _p *prox;
}Pessoas;

typedef struct _f{
	Pessoas *inicio, *fim;
	int tamanho;
}Fila;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>

Pessoas *criaPessoa();
void enfileira(Fila *fila, Pessoas *aux);
void batataQuente(Fila *pessoas, int K);
void retiraComeco(Fila *pessoas);
void retira(Fila *pessoas, Pessoas *aux);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>

	int N, K, i;
	char *nome;
	Fila *pessoas;
	Pessoas *aux;

	pessoas = (Fila *) malloc (sizeof(Fila));
	pessoas->inicio = NULL;
	pessoas->fim = NULL;

	scanf("%d %d\n", &N, &K);

	pessoas->tamanho = N;

	for(i = 0; i < N; i++){
		aux = criaPessoa();
		enfileira(pessoas, aux);
	}

	batataQuente(pessoas, K);

	printf("%s\n", pessoas->inicio->nome);

	free(pessoas->inicio->nome);
	free(pessoas->inicio);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

// <<< IMPLEMENTE AQUI AS FUNCOES >>>

Pessoas *criaPessoa(){
	Pessoas *aux;
	char *nome, c;
	int i = 0;
	//rotina para ter o nome
	while((scanf("%c", &c)) && c != '\n'){
		if(c != ' '){
			if(i == 0){
				nome = (char *) malloc (1 * sizeof(char));
				nome[i] = c;
				i++;
			}else{
				nome = (char *) realloc (nome, (i + 1) * sizeof(char));
				nome[i] = c;
				i++;
			}
		}
	}

	nome[i] = '\0';
	//rotina para definir o registro
	aux = (Pessoas *) malloc (sizeof(Pessoas));

	aux->nome = (char *) malloc (i * sizeof(char));
	aux->nome = nome;
	aux->prox = NULL;

	return(aux);
}

void enfileira(Fila *fila, Pessoas *aux){
	if(fila->inicio == NULL){
		fila->inicio = aux;
		fila->fim = fila->inicio;
	}else{
		fila->fim->prox = aux;
		fila->fim = aux;
	}
}

void batataQuente(Fila *pessoas, int K){
	int i = 1; //para contar a primeira pessoa, começa em 1
	Pessoas *aux = (Pessoas *) malloc (sizeof(Pessoas));

	aux = pessoas->inicio;
	//rotina de repetiç~ao at´e sobrar 1 individuo
	while(pessoas->inicio != pessoas->fim){
		for(; i < K; i++){ //busca qual retirar
			if(aux->prox == NULL){
				aux = pessoas->inicio;
			}else{
				aux = aux->prox;
			}
		}

		if(aux->prox == NULL){ //se fim de lista, retira do começo
			retiraComeco(pessoas);
		}else{ //senao, retira normalmente
			retira(pessoas, aux);
		}

		i = 0;
	}
}

void retiraComeco(Fila *pessoas){
	Pessoas *aux;

	aux = pessoas->inicio;
	pessoas->inicio = pessoas->inicio->prox;

	printf("%s\n", aux->nome);

	free(aux->nome);
	free(aux);
}

void retira(Fila *pessoas, Pessoas *aux){
	Pessoas *aux2;

	aux2 = pessoas->inicio;

	while(aux2 != aux){
		aux2 = aux2->prox;
	}

	aux2 = aux2->prox;
	aux->prox = aux2->prox;

	if(aux->prox == NULL){ //define novo fim da fila se retirado o fim antigo
		pessoas->fim = aux;
	}

	printf("%s\n", aux2->nome);

	free(aux2->nome);
	free(aux2);
}
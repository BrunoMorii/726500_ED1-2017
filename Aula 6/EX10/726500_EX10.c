/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 10 - Polinomios

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as funcoes requisitadas.

	Voce nao podera criar nenhuma outra funcao. Complete apenas as
	rotinas	fornecidas.
 * ================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

// Operacoes que podem ser realizadas.
#define LER_POLINOMIO		1
#define APAGAR_POLINOMIO	2
#define REMOVER_TERMO		3
#define RESOLVER_POLINOMIO	4
#define IMPRIMIR_POLINOMIOS	5
#define SOMAR_POLINOMIOS	6
#define SUB_POLINOMIOS		7
#define MULT_POLINOM_CONST	8
#define SAIR				9

// Frase exibida quando houver erro nas operacoes
#define FRASE_ERROALOCACAO	"Erro de alocacao!\n"
#define FRASE_OP_INVALIDA 	"Operacao invalida!\n"
#define FRASE_EXP_INVALIDO 	"Expoente invalido!\n"
#define FRASE_P_VAZIO		" Polinomio vazio!"
#define FRASE_T_N_ENCONTRADO "Termo nao encontrado!\n"

// Definicao do elemento da lista
typedef struct {
	float coef;
	int expo;
} Termo;

// Definicao do nó
typedef struct no	{
	Termo t;
	struct no *prox;
} Node;

// Definicao do Polinomio
typedef Node *Polinomio;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

/* Insere termo a termo na lista encadeada, formando um novo polinomio.
 * Caso o polinomio já exista, o mesmo é mantido e os termos são anexados. */
/* NÃO ALTERAR!!! */
int lerPolinomio(Polinomio p);

/* Imprime o termo apontado por p. */
/* NÃO ALTERAR!!! */
void imprimirTermo(Polinomio p);

/* Inicializa o polinomio. Cria o nó cabeca com expoente igual a -1.
 * Retorna (1) em caso de sucesso e (0) em caso de erro de alocação. */
int inicPolinomio(Polinomio *p);

/* Retorna (1) caso o polinomio esteja vazio (só existe o nó cabeça) e
 * (0) caso contrário. */
int polinomioVazio(Polinomio p);

/* Exibe o polinomio. Os termos sao impressos em ordem DECRESCENTE dos
 * expoentes. Retorna (1) em caso de sucesso e (0) caso o polinomio
 * esteja vazio. */
int imprimirPolinomio(Polinomio p);

/* Insere um novo termo no polinômio. Os termos são inseridos em ordem
 * CRESCENTE dos expoentes. Caso o polinômio já tenha um termo com o
 * mesmo expoente, os coeficientes devem ser somados. Retorna (1) em
 * caso de sucesso e (0) em caso de erro de alocação */
int inserirTermo(Polinomio p, Termo t);

/* Libera a memória alocada em todo o polinômio, inclusive no nó cabeça. */
void apagarPolinomio(Polinomio *p);

/* Remove do polinômio o termo enviado como argumento. Deve-se liberar a
 * memória alocada do termo removido. Retorna (1) caso o elemento seja
 * encontrado e (0) caso contrário. */
int removerTermo(Polinomio p, Termo t);

/* Dado o valor de x, retorna a solução do polinomio. Retorna (0) caso o
 * polinômio esteja vazio. */
float resolverPolinomio(Polinomio p, float x);

/* Retorna em C o resultado de A + B. */
void somarPolinomios(Polinomio a, Polinomio b, Polinomio c);

/* Retorna em C o resultado de A - B. */
void subPolinomios(Polinomio a, Polinomio b, Polinomio c);

/* Multiplica o polinômio pela constante enviada como argumento. */
void multPolinomioConst(Polinomio p, int constante);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main() {
	int Opcao; 	    // operacao escolhida pelo usuario
	Polinomio A,B,C;
	char labelPolinom; // rotulo do polinomio empregado nas operacoes
	Termo t;
	int constante;
	float x;
	
	// polinomio A
	if (!inicPolinomio(&A)){
		printf(FRASE_ERROALOCACAO);
		exit(1);
	}
	
	// polinomio B
	if (!inicPolinomio(&B)){
		printf(FRASE_ERROALOCACAO);
		exit(1);
	}

	// polinomio C que armazenara as operacoes de soma e subtracao
	if (!inicPolinomio(&C)){
		printf(FRASE_ERROALOCACAO);
		exit(1);
	}
	
	//Enquanto Opcao for diferente de SAIR.
	do {

		//Pergunta a Opcao que o usuario deseja realizar.
		scanf("%d", &Opcao);

		//Verifica qual Opcao foi escolhida.
		switch (Opcao) {
			
			// Opcao 1
			case LER_POLINOMIO:
				scanf("\n%c", &labelPolinom);
				if (labelPolinom == 'A') {
					if (!lerPolinomio(A)) {
						printf(FRASE_ERROALOCACAO);
						exit(1);
					}
					printf("A =");
					if (!imprimirPolinomio(A))
						printf(FRASE_P_VAZIO);
					printf("\n");
					
				} else if (labelPolinom == 'B') {
					if (!lerPolinomio(B)) {
						printf(FRASE_ERROALOCACAO);
						exit(1);
					}
					printf("B =");
					if (!imprimirPolinomio(B))
						printf(FRASE_P_VAZIO);
					printf("\n");
					
				} else
					printf(FRASE_OP_INVALIDA);
					
				break;			

			// Opcao 2
			case APAGAR_POLINOMIO:
				scanf("\n%c", &labelPolinom);
				if (labelPolinom == 'A') {
					apagarPolinomio(&A);
					if (!inicPolinomio(&A)){
						printf(FRASE_ERROALOCACAO);
						exit(1);
					}
					
				} else if (labelPolinom == 'B') {
					apagarPolinomio(&B);
					if (!inicPolinomio(&B)){
						printf(FRASE_ERROALOCACAO);
						exit(1);
					}
					
				} else
					printf(FRASE_OP_INVALIDA);
			
				break;

			// Opcao 3
			case REMOVER_TERMO:
				scanf("\n%c %d %f", &labelPolinom, &t.expo, &t.coef);
				if (labelPolinom == 'A') {
					if (t.coef < 0)
						printf(FRASE_EXP_INVALIDO);
					else
						if (!removerTermo(A, t))
							printf(FRASE_T_N_ENCONTRADO);
						else {
							printf("A =");
							if (!imprimirPolinomio(A))
								printf(FRASE_P_VAZIO);
							printf("\n");
						}
					
				} else if (labelPolinom == 'B') {
					if (t.coef < 0)
						printf(FRASE_EXP_INVALIDO);
					else
						if (!removerTermo(B, t))
							printf(FRASE_T_N_ENCONTRADO);		
						else {
							printf("B =");
							if (!imprimirPolinomio(B))
								printf(FRASE_P_VAZIO);
							printf("\n");
						}			
					
				} else
					printf(FRASE_OP_INVALIDA);
					
				break;
				
			// Opcao 4
			case RESOLVER_POLINOMIO:
				scanf("\n%c %f", &labelPolinom, &x);
				if (labelPolinom == 'A') {
					printf("A =");
					if (!imprimirPolinomio(A))
						printf(FRASE_P_VAZIO);
					printf(" = %.1f\n", resolverPolinomio(A, x));
					
				} else if (labelPolinom == 'B') {
					printf("B =");
					if (!imprimirPolinomio(B))
						printf(FRASE_P_VAZIO);
					printf(" = %.1f\n", resolverPolinomio(B, x));
					
				} else
					printf(FRASE_OP_INVALIDA);

				break;
				
			// Opcao 5
			case IMPRIMIR_POLINOMIOS:
				printf("A =");
				if (!imprimirPolinomio(A))
					printf(FRASE_P_VAZIO);
				printf("\n");
					
				printf("B =");
				if (!imprimirPolinomio(B))
					printf(FRASE_P_VAZIO);
				printf("\n");
				
				break;

			// Opcao 6
			case SOMAR_POLINOMIOS:
				// limpando polinomio C, que armazenara o resultado
				apagarPolinomio(&C);
				if (!inicPolinomio(&C)) {
					printf(FRASE_ERROALOCACAO);
					exit(1);
				}
				
				somarPolinomios(A, B, C);
				printf("A + B =");
				if (!imprimirPolinomio(C))
					printf(FRASE_P_VAZIO);
				printf("\n");
				
				break;

			// Opcao 7
			case SUB_POLINOMIOS:
				// limpando polinomio C, que armazenara o resultado
				apagarPolinomio(&C);
				if (!inicPolinomio(&C)) {
					printf(FRASE_ERROALOCACAO);
					exit(1);
				}
				
				subPolinomios(A, B, C);
				printf("A - B =");
				if (!imprimirPolinomio(C))
					printf(FRASE_P_VAZIO);
				printf("\n");
				
				break;
			
			// Opcao 8
			case MULT_POLINOM_CONST:
				scanf("\n%c %d", &labelPolinom, &constante);
				if (labelPolinom == 'A') {
					multPolinomioConst(A, constante);
					printf("A =");
					if (!imprimirPolinomio(A))
						printf(FRASE_P_VAZIO);
					printf("\n");
					
				} else if (labelPolinom == 'B') {
					multPolinomioConst(B, constante);
					printf("B =");
					if (!imprimirPolinomio(B))
						printf(FRASE_P_VAZIO);
					printf("\n");
					
				} else
					printf(FRASE_OP_INVALIDA);
			
				break;

			// Opcao 9
			case SAIR:
				apagarPolinomio(&A);
				apagarPolinomio(&B);
				apagarPolinomio(&C);
				break;
		}

	} while (Opcao != SAIR);
	
	return 0;
}

/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

/* Insere termo a termo na lista encadeada, formando um novo polinomio.
 * Caso o polinomio já exista, o mesmo é mantido e os termos são anexados. */
/* NÃO ALTERAR!!! */
int lerPolinomio(Polinomio p) {
	Termo t;

	scanf("%d", &t.expo);
	while (t.expo >= 0) {
		scanf("%f", &t.coef);
		if (!inserirTermo(p, t))
			return FALSE;
		scanf("%d", &t.expo);
	}

	return TRUE;
}

/* Imprime o termo apontado por p. */
/* NÃO ALTERAR!!! */
void imprimirTermo(Polinomio p) {
	if ((p->prox->t.expo != -1) && (p->t.coef > 0))
		printf(" +");
	else
		printf(" ");
		
	if (p->t.expo == 1) {
		printf("%.1fx", p->t.coef);	
	} else if (p->t.expo == 0) {
		printf("%.1f", p->t.coef);
	} else {
		printf("%.1fx^%d", p->t.coef, p->t.expo);	
	}
}

/* Inicializa o polinomio. Cria o nó cabeca com expoente igual a -1.
 * Retorna (1) em caso de sucesso e (0) em caso de erro de alocação. */
int inicPolinomio(Polinomio *p) {
	/* <<< COMPLETAR AQUI >>> */
	*p = (Node *) malloc (sizeof(Node));

	if(p == NULL){ //verificando se alocou
		return(0);
	}

	//cabeca
	(*p)->t.expo = -1;
	(*p)->prox = *p;

	return(1);
}

/* Retorna (1) caso o polinomio esteja vazio (só existe o nó cabeça) e
 * (0) caso contrário. */
int polinomioVazio(Polinomio p) {
	/* <<< COMPLETAR AQUI >>> */

	if(p->prox == p){
		return(1);
	}

	return(0);
}

/* Exibe o polinômio. Os termos sao impressos em ordem DECRESCENTE dos
 * expoentes. Retorna (1) em caso de sucesso e (0) caso o polinomio
 * esteja vazio. */
int imprimirPolinomio(Polinomio p) {
	/* <<< COMPLETAR AQUI >>> */
	//se estiver vazio
	if(polinomioVazio(p)){
		return (0);
	}

	if(p->prox->t.expo < 0){
		imprimirTermo(p);
		return(1);
	}else{
		imprimirPolinomio(p->prox);
		if(p->t.expo != -1)
			imprimirTermo(p);
	}

	return (1);
}

/* Insere um novo termo no polinômio. Os termos são inseridos em ordem
 * CRESCENTE dos expoentes. Caso o polinômio já tenha um termo com o
 * mesmo expoente, os coeficientes devem ser somados. Retorna (1) em
 * caso de sucesso e (0) em caso de erro de alocação */
int inserirTermo(Polinomio p, Termo t) {
	/* <<< COMPLETAR AQUI >>> */
	Node *aux, *novo;

	if(p->prox == p){
		novo = (Node *) malloc (sizeof(Node));
		if(novo == NULL){
			return(0);
		}

		novo->t = t;
		novo->prox = p;
		p->prox = novo;
	}else{
		aux = p;
		while(aux->prox != p){
			if(aux->t.expo == t.expo){
				aux->t.coef += t.coef;
				break;
			}else if((aux->t.expo < t.expo) && ((aux->prox->t.expo > t.expo) || (aux->prox == p))){
				novo = (Node *) malloc (sizeof(Node));
				if(novo == NULL){
					return(0);
				}

				novo->t = t;
				novo->prox = aux->prox;
				aux->prox = novo;
				break;
			}
			aux = aux->prox;
		}
		if(aux->prox == p){
			if(aux->t.expo == t.expo){
				aux->t.coef += t.coef;
			}else{
				novo = (Node *) malloc (sizeof(Node));
				if(novo == NULL){
					return(0);
				}

				novo->t = t;
				novo->prox = aux->prox;
				aux->prox = novo;
			}
		}
	}

	return(1);
}

/* Apaga toda a lista encadeada, inclusive o nó cabeça. */
void apagarPolinomio(Polinomio *p) {
	/* <<< COMPLETAR AQUI >>> */
	Node *aux, *remove;

	aux = (*p)->prox;
	while(aux != *p){
		remove = aux;
		free(remove);
		aux = aux->prox;
	}

	free(aux);
}

/* Remove do polinômio o termo enviado como argumento. Deve-se liberar a
 * memória alocada do termo removido. Retorna (1) caso o elemento seja
 * encontrado e (0) caso contrário. */
int removerTermo(Polinomio p, Termo t) {
	/* <<< COMPLETAR AQUI >>> */

	Node *aux, *anterior;

	aux = p->prox;
	while(aux != p){
		if(aux->t.expo == t.expo && aux->t.coef == t.coef){
			anterior = p;
			while(anterior->prox != aux){
				anterior = anterior->prox;
			}
			anterior->prox = aux->prox;
			free(aux);
			return(1);
		}
		aux = aux->prox;
	}

	return(0);
}

/* Dado o valor de x, retorna a solução do polinomio. Retorna (0) caso o
 * polinômio esteja vazio. */
float resolverPolinomio(Polinomio p, float x) {
	/* <<< COMPLETAR AQUI >>> */
	Node *aux;
	float solucao = 0;

	if(polinomioVazio(p)){
		return(0);
	}

	aux = p->prox;
	while(aux != p){
		solucao += aux->t.coef * pow(x, aux->t.expo);
		aux = aux->prox;
	}

	return(solucao);
}

/* Retorna em C o resultado de A + B. */
void somarPolinomios(Polinomio a, Polinomio b, Polinomio c) {
	/* <<< COMPLETAR AQUI >>> */
	Node *aux;

	aux = a->prox;

	while(aux != a){
		inserirTermo(c, aux->t);
		aux = aux->prox;
	}

	aux = b->prox;

	while(aux != b){
		inserirTermo(c, aux->t);
		aux = aux->prox;
	}
}

/* Retorna em C o resultado de A - B. */
void subPolinomios(Polinomio a, Polinomio b, Polinomio c) {
	/* <<< COMPLETAR AQUI >>> */
	Node *aux;
	Termo t;

	aux = a->prox;

	while(aux != a){
		inserirTermo(c, aux->t);
		aux = aux->prox;
	}

	aux = b->prox;

	while(aux != b){
		t.coef = -1 * aux->t.coef;
		t.expo = aux->t.expo;
		inserirTermo(c, t);
		aux = aux->prox;
	}
}

/* Multiplica o polinomio pela constante enviada como argumento. */
void multPolinomioConst(Polinomio p, int constante) {
	/* <<< COMPLETAR AQUI >>> */
	Node *aux;

	aux = p->prox;

	while(aux != p){
		aux->t.coef *= constante;
		aux = aux->prox;
	}
}

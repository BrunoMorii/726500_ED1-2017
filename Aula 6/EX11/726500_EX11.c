/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 11 - Calculadora de Polinomios com Conversor de Expressões

	Instrucoes
	----------

	Este arquivo contem o codigo que auxiliara no desenvolvimento do
	exercicio. Voce precisara completar as funcoes requisitadas.

	Voce nao podera criar nenhuma outra funcao. Complete apenas as
	rotinas	fornecidas.
 * ================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_POL 10	// tamanho máximo de polinômios que a calculadora suporta
#define TAM_EXPR 50	// tamanho máximo de uma expressão, em caracteres

#define VERDADEIRO 1
#define FALSO 0

// Operacoes que podem ser realizadas.
#define LER_POLINOMIO		1
#define APAGAR_POLINOMIO	2
#define IMPRIMIR_POLINOMIOS	3
#define LER_EXPRESSAO		4
#define RESOLVER_EXPRESSAO	5
#define SAIR				6

// Frase exibida quando houver erro nas operacoes
#define FRASE_ERROALOCACAO	"Erro de alocacao!\n"
#define FRASE_CALC_CHEIA 	"Calculadora cheia!\n"
#define FRASE_MEM_CHEIA 	"Memoria da calculadora cheia!\n"
#define FRASE_POL_INVALIDO 	"Polinomio invalido!\n"
#define FRASE_POL_VAZIO		" Polinomio vazio!"
#define FRASE_EXPR_N_INFORM	"Expressao nao informada!\n"

/* ================================================================== */
/* ========================= TAD POLINOMIO ========================== */
/* ================================================================== */
// Definicao do elemento da lista (termos do polinômio)
typedef struct {
	float coef;
	int expo;
} Termo;

// Definicao do nó
typedef struct no	{
	Termo t;
	struct no *prox;
} Node;

// Definicao do Polinômio
typedef Node *Polinomio;

/* ================================================================== */
/* ======================== TAD CALCULADORA ========================= */
/* ================================================================== */
// Definicao da Calculadora (pilha ESTÁTICA de polinômios)
typedef struct {
	Polinomio itens[TAM_POL];
	int topo;
} PilhaPolinomios;

/* ================================================================== */
/* =================== TAD CONVERSOR DE EXPRESSOES ================== */
/* ================================================================== */
// Conversor de expressões (pilha DINÂMICA de análise)
typedef struct noPilha {
	char item;
	struct noPilha *anterior;
} noPilha;

typedef struct {
	int contador;
	noPilha *topo;
} PilhaExpressoes;

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

/* Função auxiliar que retorna a precedência dos operadores. */
/* NÃO ALTERAR!!! */
int precedencia(char operador);

/* Inicializa o polinomio. Cria o nó cabeca com expoente igual a -1.
 * Retorna VERDADEIRO em caso de sucesso e FALSO em caso de erro de alocação. */
int inicPolinomio(Polinomio *p);

/* Retorna VERDADEIRO caso o polinomio esteja vazio (só existe o nó cabeça) e
 * FALSO caso contrário. */
int polinomioVazio(Polinomio p);

/* Exibe o polinomio. Os termos sao impressos em ordem DECRESCENTE dos
 * expoentes. Retorna VERDADEIRO em caso de sucesso e FALSO caso o polinomio
 * esteja vazio. */
int imprimirPolinomio(Polinomio p);

/* Insere um novo termo no polinômio. Os termos são inseridos em ordem
 * CRESCENTE dos expoentes. Caso o polinômio já tenha um termo com o
 * mesmo expoente, os coeficientes devem ser somados. Retorna VERDADEIRO em
 * caso de sucesso e FALSO em caso de erro de alocação */
int inserirTermo(Polinomio p, Termo t);

/* Libera a memória alocada em todo o polinômio, inclusive do nó cabeça. */
void apagarPolinomio(Polinomio *p);

/* Retorna em C o resultado de A + B. */
void somarPolinomios(Polinomio a, Polinomio b, Polinomio c);

/* Retorna em C o resultado de A - B. */
void subPolinomios(Polinomio a, Polinomio b, Polinomio c);

/* Retorna em C o resultado de A * B. */
void multPolinomios(Polinomio a, Polinomio b, Polinomio c);

/* Converte uma expressão da forma infixa para a forma posfixa. */
void infixa_para_posfixa(char *infix_expr, char *posfix_expr);

/* Converte uma expressão da forma infixa para a forma prefixa. */
void infixa_para_prefixa(char *infix_expr, char *posfix_expr);

/* OPERAÇÕES DA PILHA DE EXPRESSÕES (PILHA DINÃMICA) */
void criarPilhaExpr(PilhaExpressoes *pilha);
int pilhaExprVazia(PilhaExpressoes *pilha);
void liberarPilhaExpr(PilhaExpressoes *pilha);
int topoExpr(PilhaExpressoes *pilha, char *item);
int empilharExpr(PilhaExpressoes *pilha, char *item);
int desempilharExpr(PilhaExpressoes *pilha, char *item);

/* OPERAÇÕES DA PILHA DE POLINÔMIOS (PILHA ESTÁTICA) */
void criarPilhaPol(PilhaPolinomios *pilha);
int pilhaPolVazia(PilhaPolinomios *pilha);
int pilhaPolCheia(PilhaPolinomios *pilha);
int topoPol(PilhaPolinomios *pilha, Polinomio *item);
int empilharPolinomio(PilhaPolinomios *pilha, Polinomio *item);
int desempilharPolinomio(PilhaPolinomios *pilha, Polinomio *item);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main() {
	int Opcao;
	Polinomio entCalc[TAM_POL], memCalc[TAM_POL];
	Polinomio operPol1, operPol2, resultPol; // auxiliares da calculadora
	PilhaPolinomios pilhaPol;
	char expr[TAM_EXPR], expr2[TAM_EXPR];
	char labelPolinom;
	int i, nPolinomios = 0, memoria;
	expr2[0] = '\0';
	
	// Inicializa a calculadora
	for (i = 0; i < TAM_POL; i++) {
		if (!inicPolinomio(&entCalc[i]) || !inicPolinomio(&memCalc[i])) {
			printf(FRASE_ERROALOCACAO);
			exit(0);
		}
	}
	criarPilhaPol(&pilhaPol);
	
	//Enquanto Opcao for diferente de SAIR.
	do {

		//Pergunta a Opcao que o usuario deseja realizar.
		scanf("%d", &Opcao);

		//Verifica qual Opcao foi escolhida.
		switch (Opcao) {
			
			// OPCAO 1
			case LER_POLINOMIO:
			
			if (nPolinomios >= TAM_POL) {
				printf(FRASE_CALC_CHEIA);
			} else {

				if (!lerPolinomio(entCalc[nPolinomios])) {
					printf(FRASE_ERROALOCACAO);
					exit(0);
				}
				printf("%c =", 'A'+nPolinomios);
				if (!imprimirPolinomio(entCalc[nPolinomios]))
					printf(FRASE_POL_VAZIO);
				printf("\n");
				nPolinomios++;
			}
			break;			
	
			
			// OPCAO 2
			case APAGAR_POLINOMIO:
			
			scanf("\n%c", &labelPolinom);

			if (labelPolinom >= 'A' && labelPolinom < 'A' + TAM_POL) {
				apagarPolinomio(&entCalc[labelPolinom - 'A']);
				if (!inicPolinomio(&entCalc[labelPolinom - 'A'])){
					printf(FRASE_ERROALOCACAO);
					exit(0);
				}

			} else
				printf(FRASE_POL_INVALIDO);
		
			break;


			// OPCAO 3
			case IMPRIMIR_POLINOMIOS:
			for (i = 0; i < TAM_POL; i++) {

				printf("%c =", 'A'+i);
				if (!imprimirPolinomio(entCalc[i]))
					printf(FRASE_POL_VAZIO);
				printf("\n");
			}
			
			break;

			
			// OPCAO 4
			case LER_EXPRESSAO:
			scanf("\n%[^\n]", expr);

			printf("Notação infixa: %s\n", expr);
			expr2[0] = '\0';
			infixa_para_prefixa(expr, expr2);
			printf("Notação prefixa: %s\n", expr2);
			expr2[0] = '\0';
			infixa_para_posfixa(expr, expr2);
			printf("Notação posfixa: %s\n", expr2);
			
			break;
			
			
			// OPCAO 5
			case RESOLVER_EXPRESSAO:
			if (strlen(expr2) == 0) {
				printf(FRASE_EXPR_N_INFORM);
			} else {
				
				// Limpa a memória da calculadora
				memoria = 0;
				for (i = 0; i < TAM_POL; i++) {
					apagarPolinomio(&memCalc[i]);
					if (!inicPolinomio(&memCalc[i])) {
						printf(FRASE_ERROALOCACAO);
						exit(0);
					}				
				}				
				
				// Percorre a expressão
				for (i = 0; expr2[i]; i++) {

					// O caractere é operando
					if (expr2[i] >= 'A' && expr2[i] < 'A' + TAM_POL) {
						empilharPolinomio(&pilhaPol, &entCalc[expr2[i]-'A']);
					
					// O caractere é operador
					} else {
						// Reserva mais uma memória da calculadora
						if (memoria == TAM_POL) {
							printf(FRASE_MEM_CHEIA);
							exit(0);
						}
						resultPol = memCalc[memoria++];
						
						// Aplica as operações
						if (expr2[i] == '+') {
							desempilharPolinomio(&pilhaPol, &operPol2);
							desempilharPolinomio(&pilhaPol, &operPol1);
							somarPolinomios(operPol1, operPol2, resultPol);
							empilharPolinomio(&pilhaPol, &resultPol);
						}  else if (expr2[i] == '-') {
							desempilharPolinomio(&pilhaPol, &operPol2);
							desempilharPolinomio(&pilhaPol, &operPol1);
							subPolinomios(operPol1, operPol2, resultPol);
							empilharPolinomio(&pilhaPol, &resultPol);
						} else if (expr2[i] == '*') {
							desempilharPolinomio(&pilhaPol, &operPol2);
							desempilharPolinomio(&pilhaPol, &operPol1);
							multPolinomios(operPol1, operPol2, resultPol);
							empilharPolinomio(&pilhaPol, &resultPol);
						}
					}
				}
				// Desempilha o polinômio resultante
				desempilharPolinomio(&pilhaPol, &resultPol);
				printf("%s =", expr2);				
				if (!imprimirPolinomio(resultPol))
					printf(FRASE_POL_VAZIO);
				printf("\n");
			}
			break;
			
			
			// Opcao 6
			case SAIR:
			for (i = 0; i < TAM_POL; i++) {
				apagarPolinomio(&entCalc[i]);
				apagarPolinomio(&memCalc[i]);
			}
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
			return FALSO;
		scanf("%d", &t.expo);
	}

	return VERDADEIRO;
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

/* Função auxiliar que retorna a precedência dos operadores. */
/* NÃO ALTERAR!!! */
int precedencia(char operador) {
	switch (operador) {
		case '(':
		case ')': return 1;
		case '-':
		case '+': return 2;
		//case '/':	// divisão não é suportada
		case '*': return 3;
		default:
			printf("Operador nao suportado <%c>!\n", operador);
			return -1;
	}
}

/* Inicializa o polinomio. Cria o nó cabeca com expoente igual a -1.
 * Retorna VERDADEIRO em caso de sucesso e FALSO em caso de erro de alocação. */
int inicPolinomio(Polinomio *p) {
	/* COMPLETAR AQUI */
	*p = (Node *) malloc (sizeof(Node));

	if(p == NULL){ //verificando se alocou
		return(0);
	}

	//cabeca
	(*p)->t.expo = -1;
	(*p)->prox = *p;

	return(1);
}

/* Retorna VERDADEIRO caso o polinomio esteja vazio (só existe o nó cabeça) e
 * FALSO caso contrário. */
int polinomioVazio(Polinomio p) {
	/* COMPLETAR AQUI */

	if(p->prox == p){
		return(1);
	}

	return(0);
}

/* Exibe o polinômio. Os termos sao impressos em ordem DECRESCENTE dos
 * expoentes. Retorna VERDADEIRO em caso de sucesso e FALSO caso o polinomio
 * esteja vazio. */
int imprimirPolinomio(Polinomio p) {
	/* COMPLETAR AQUI */

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
 * mesmo expoente, os coeficientes devem ser somados. Retorna VERDADEIRO em
 * caso de sucesso e FALSO em caso de erro de alocação */
int inserirTermo(Polinomio p, Termo t) {
	/* COMPLETAR AQUI */

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

/* Libera a memória alocada em todo o polinômio, inclusive do nó cabeça. */
void apagarPolinomio(Polinomio *p) {
	/* COMPLETAR AQUI */

	Node *aux, *remove;

	aux = (*p)->prox;
	while(aux != *p){
		remove = aux;
		free(remove);
		aux = aux->prox;
	}

	free(aux);
}

/* Retorna em C o resultado de A + B. */
void somarPolinomios(Polinomio a, Polinomio b, Polinomio c) {
	/* COMPLETAR AQUI */
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
	/* COMPLETAR AQUI */
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

/* Retorna em C o resultado de A * B. */
void multPolinomios(Polinomio a, Polinomio b, Polinomio c) {
	/* COMPLETAR AQUI */
	Node *aux, *aux2;
	Termo t;

	aux = a->prox;

	while(aux != a){
		aux2 = b->prox;
		while(aux2 != b){
			t.expo = aux->t.expo + aux2->t.expo;
			t.coef = aux->t.coef * aux2->t.coef;
			inserirTermo(c, t);
			aux2 = aux2->prox;
		}
		aux = aux->prox;
	}
}

/* Converte uma expressão da forma infixa para a forma posfixa. */
void infixa_para_posfixa(char *infix_expr, char *posfix_expr) {
	/* COMPLETAR AQUI */
	PilhaExpressoes *pilha;
	int i = 0, j = 0;
	char c;

	pilha = (PilhaExpressoes *) malloc (sizeof(PilhaExpressoes));
	pilha->topo = NULL;

	while(infix_expr[i] != '\0'){
		if(infix_expr[i] == '('){ //se e abre parenteses so empilha
			empilharExpr(pilha, &infix_expr[i]);
		}
		//se fecha parenteses, desempilha ate (
		else if(infix_expr[i] == ')'){
			//desempilhando ate (
			while(pilha->topo->item != '('){
				desempilharExpr(pilha, &c);
				posfix_expr[j] = c;
				j++;
			}
			//desempilha o (
			desempilharExpr(pilha, &c);
		}
		//se for operando, apenas insere
		else if(infix_expr[i] >= 'A' && infix_expr[i] <= 'J'){
			posfix_expr[j] = infix_expr[i];
			j++;
		}
		//se nao analisa as precedencias
		else{
			if(pilha->topo == NULL){
				empilharExpr(pilha, &infix_expr[i]);
			}
			//checa as precedencias
			else if(precedencia(infix_expr[i]) <= precedencia(pilha->topo->item)){
				while(pilha->topo != NULL && precedencia(infix_expr[i]) <= precedencia(pilha->topo->item)){
					desempilharExpr(pilha, &c);
					posfix_expr[j] = c;
					j++;
				}
				empilharExpr(pilha, &infix_expr[i]);
			}
			//caso contrario so insere na pilha
			else{
				empilharExpr(pilha, &infix_expr[i]);
			}
			
		}
		i++;
	}

	/*
	//rotina para ver pilha
	aux = pilha->topo;
	while(aux != NULL){
		printf("%c\n", aux->item);
		aux = aux->anterior;
	}*/

	//esvazir pilha
	while(pilha->topo != NULL){
		desempilharExpr(pilha, &c);
		posfix_expr[j] = c;
		j++;
	}
	posfix_expr[j] = '\0';

}

/* Converte uma expressão da forma infixa para a forma prefixa. */
void infixa_para_prefixa(char *infix_expr, char *prefix_expr) {
	/* COMPLETAR AQUI */
	char expr[TAM_EXPR], expr2[TAM_EXPR];
	int i, j;
	PilhaExpressoes *pilha;
	char c;

	pilha = (PilhaExpressoes *) malloc (sizeof(PilhaExpressoes));
	pilha->topo = NULL;

	//inverte a string infixa, trata abertura e fechamento de parenteses
	for(i = strlen(infix_expr) - 1, j = 0; j < strlen(infix_expr);i--, j++){
		if(infix_expr[i] == '('){
			expr[j] = ')';
		}else if(infix_expr[i] == ')'){
			expr[j] = '(';
		}else{
			expr[j] = infix_expr[i];
		}
	}
	expr[j] = '\0';
	
	//passa o invertido para posfixa
	i = 0;
	j = 0;

	while(expr[i] != '\0'){
		if(expr[i] == '('){ //se e abre parenteses so empilha
			empilharExpr(pilha, &expr[i]);
		}
		//se fecha parenteses, desempilha ate (
		else if(expr[i] == ')'){
			//desempilhando ate (
			while(pilha->topo->item != '('){
				desempilharExpr(pilha, &c);
				expr2[j] = c;
				j++;
			}
			//desempilha o (
			desempilharExpr(pilha, &c);
		}
		//se for operando, apenas insere
		else if(expr[i] >= 'A' && expr[i] <= 'J'){
			expr2[j] = expr[i];
			j++;
		}
		//se nao analisa as precedencias
		else{
			if(pilha->topo == NULL){
				empilharExpr(pilha, &expr[i]);
			}
			//checa as precedencias
			else if(precedencia(expr[i]) < precedencia(pilha->topo->item)){
				while(pilha->topo != NULL && precedencia(expr[i]) < precedencia(pilha->topo->item)){
					desempilharExpr(pilha, &c);
					expr2[j] = c;
					j++;
				}
				empilharExpr(pilha, &expr[i]);
			}
			//caso contrario so insere na pilha
			else{
				empilharExpr(pilha, &expr[i]);
			}
			
		}
		i++;
	}

	/*
	//rotina para ver pilha
	aux = pilha->topo;
	while(aux != NULL){
		printf("%c\n", aux->item);
		aux = aux->anterior;
	}*/

	//esvazir pilha
	while(pilha->topo != NULL){
		desempilharExpr(pilha, &c);
		expr2[j] = c;
		j++;
	}
	expr2[j] = '\0';

	//inverte a posfixa e coloca no destino (prefixa)
	for(i = strlen(expr2) - 1, j = 0; j < strlen(expr2);i--, j++){
		prefix_expr[j] = expr2[i]; 
	}
	prefix_expr[j] = '\0';

	//strcpy(prefix_expr, expr);
}


/* ================================================================== */
/* ======== OPERAÇÕES DA PILHA DE EXPRESSÕES (PILHA DINÃMICA) ======= */
/* ================================================================== */
/* Inicializa a pilha de expressões (dinâmica). */
void criarPilhaExpr(PilhaExpressoes *pilha) {
	/* COMPLETAR AQUI */
}

/* Retorna VERDADEIRO caso a pilha esteja vazia e FALSO caso contrário. */
int pilhaExprVazia(PilhaExpressoes *pilha) {
	/* COMPLETAR AQUI */
	return(pilha->topo == NULL);
}

/* Libera todos os nós da pilha de expressões (dinâmica). */
void liberarPilhaExpr(PilhaExpressoes *pilha) {
	/* COMPLETAR AQUI */
	noPilha *aux, *remove;

	aux = pilha->topo;

	while(aux != NULL){
		remove = aux;
		aux = aux->anterior;
		free(remove);
	}
}

/* Retorna em item o elemento do topo da pilha, sem removê-lo! Retorna FALSO
 * caso a pilha esteja vazia e VERDADEIRO caso contrário. */
int topoExpr(PilhaExpressoes *pilha, char *item) {
	/* COMPLETAR AQUI */
	if(pilhaExprVazia)
		return (FALSO);

	*item = pilha->topo->item;

	return (VERDADEIRO);
}

/* Empilha uma expressão na pilha de expressões. Em caso de sucesso, 
 * apenas retorna VERDADEIRO. Em caso de erro de alocação, deve imprimir
 * FRASE_ERROALOCACAO e encerrar o programa exit(0). */
int empilharExpr(PilhaExpressoes *pilha, char *item) {
	/* COMPLETAR AQUI */

	noPilha *novo = (noPilha *) malloc (sizeof(noPilha));
	if(novo == NULL){
		printf(FRASE_ERROALOCACAO);
		exit(0);
	}

	novo->item = *item;
	novo->anterior = pilha->topo;

	pilha->topo = novo;
	pilha->contador++;

	return(VERDADEIRO);
}

/* Desempilha uma expressão da pilha de expressões. Retorna VERDADEIRO em caso
 * de sucesso e FALSO caso a pilha esteja vazia. */
int desempilharExpr(PilhaExpressoes *pilha, char *item) {
	/* COMPLETAR AQUI */
	noPilha *aux = pilha->topo;

	if(pilhaExprVazia(pilha))
		return(FALSO);

	*item = aux->item;

	pilha->topo = pilha->topo->anterior;

	free(aux);
	pilha->contador--;

	return(VERDADEIRO);
}


/* ================================================================== */
/* ======== OPERAÇÕES DA PILHA DE POLINÔMIOS (PILHA ESTÁTICA) ======= */
/* ================================================================== */
/* Inicializa a pilha de polinômios (estática). */
void criarPilhaPol(PilhaPolinomios *pilha) {
	/* COMPLETAR AQUI */

	pilha->topo = -1;
}

/* Retorna VERDADEIRO caso a pilha esteja vazia e FALSO caso contrário. */
int pilhaPolVazia(PilhaPolinomios *pilha) {
	/* COMPLETAR AQUI */
	return(pilha->topo == -1);
}

/* Retorna VERDADEIRO caso a pilha esteja cheia e FALSO caso contrário. */
int pilhaPolCheia(PilhaPolinomios *pilha) {
	/* COMPLETAR AQUI */
	return(pilha->topo == 9);
}

/* Retorna em item o elemento do topo da pilha, sem removê-lo! Retorna FALSO
 * caso a pilha esteja vazia e VERDADEIRO caso contrário. */
int topoPol(PilhaPolinomios *pilha, Polinomio *item) {
	/* COMPLETAR AQUI */
	if(pilhaPolVazia(pilha))
		return (FALSO);

	*item = pilha->itens[pilha->topo];

	return(VERDADEIRO);
}

/* Empilha um polinômio na pilha de polinômios. Retorna VERDADEIRO em caso
 * de sucesso e FALSO caso a pilha esteja cheia. */
int empilharPolinomio(PilhaPolinomios *pilha, Polinomio *item) {
	/* COMPLETAR AQUI */
	if(pilhaPolCheia(pilha))
		return(FALSO);

	pilha->topo++;
	pilha->itens[pilha->topo] = *item;

	return(VERDADEIRO);
}

/* Desempilha um polinômio da pilha de polinômios. Retorna VERDADEIRO em caso
 * de sucesso e FALSO caso a pilha esteja vazia. */
int desempilharPolinomio(PilhaPolinomios *pilha, Polinomio *item) {
	/* COMPLETAR AQUI */

	if(pilhaPolVazia(pilha))
		return(FALSO);

	*item = pilha->itens[pilha->topo];
	pilha->topo--;

	return(VERDADEIRO);
}

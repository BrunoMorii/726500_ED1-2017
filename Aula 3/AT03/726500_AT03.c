/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Estruturas de dados 1
    Prof. Tiago A. Almeida

    Exercício: StackCrypt

    Instrucoes
    ----------

    Este arquivo contem o codigo que auxiliara no desenvolvimento do
    exercicio. Voce precisara completar as partes requisitadas.
* ================================================================== */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTO_MAX 1000 // tamanho maximo do texto


// --- DEFINICAO DO TAD ---
typedef char TItem;

typedef struct SCelula *TApontador;

typedef struct SCelula {
  TItem Item;
  TApontador Prox;
} TCelula;

typedef struct {
  TApontador Topo;
  int Tamanho;
} TPilha;



// --- PROTOTIPO DAS FUNCOES
int Ler_texto(char Texto[], int max_size);
void TPilha_Inicia(TPilha *pPilha);
int TPilha_EhVazia(TPilha *pPilha);
int TPilha_Tamanho(TPilha *pPilha);
void TPilha_Imprime(TPilha *pPilha);
int TPilha_Empilha(TPilha *pPilha, TItem x);
int TPilha_Desempilha(TPilha *pPilha, TItem *pX);
char *Criptografa(char *Texto, int nPilhas);
char *Descriptografa(char *Texto, int nPilhas);




// --- FUNCAO PRINCIPAL -- NAO ALTERAR ---
int main()
{
  char Texto[TEXTO_MAX];
  size_t nPilhas;

  Ler_texto(Texto, TEXTO_MAX);
  scanf("%zu", &nPilhas);

  printf("%s\n", Criptografa(Texto, nPilhas));

  return 0;
}



/* -------------------------
   IMPLEMENTACAO DAS FUNCOES
   -------------------------*/

/* Le um texto do teclado e retorna o seu tamanho */
int Ler_texto(char Texto[], int max_size)
{
	int ch, i = 0;
	                 
	while ((ch = getchar()) != '\n'){
	 if (i < max_size) {
	    Texto[i] = ch;
	    i++;
	 }
	}

	Texto[i] = '\0';
	
	return i;
}


/* Inicia as variaveis da pilha */
void TPilha_Inicia(TPilha *pPilha)
{
  pPilha->Topo = NULL;
  pPilha->Tamanho = 0;
}


/* Retorna se a pilha esta vazia */
int TPilha_EhVazia(TPilha *pPilha)
{
  return (pPilha->Topo == NULL);
}


/* Retorna o tamanho da pilha */
int TPilha_Tamanho(TPilha *pPilha)
{
  return (pPilha->Tamanho);
}


/* Imprime os elementos da pilha */
void TPilha_Imprime(TPilha *pPilha)
{
  TApontador p;

  p = pPilha->Topo;
  while (p != NULL) {
    printf("%c\n", p->Item);
    p = p->Prox;
  }
}


// <<< IMPLEMENTE AQUI AS DEMAIS FUNCOES >>>

int TPilha_Empilha(TPilha *pPilha, TItem x){
	TCelula *aux;

	aux = (TCelula *) malloc (sizeof(TCelula));
	aux->Item = x;
	aux->Prox = pPilha->Topo;
	pPilha->Topo = aux;
	pPilha->Tamanho++;

	return(0);
}

int TPilha_Desempilha(TPilha *pPilha, TItem *pX){
	TCelula *aux;

	*pX = pPilha->Topo->Item;
	aux = pPilha->Topo;
	pPilha->Topo = pPilha->Topo->Prox;

	free(aux);

	return(0);
}

char *Criptografa(char *Texto, int nPilhas){
	int i;
	char *textoFinal;
	TPilha *pilhas;

	textoFinal = (char *) malloc (strlen(Texto) * sizeof(char));

	pilhas = (TPilha *) malloc (nPilhas * sizeof(TPilha));

	for(i = 0; i < nPilhas; i++){
		TPilha_Inicia(&pilhas[i]);
	}

	for(i = 0; Texto[i] != '\0'; i++){
		TPilha_Empilha(&pilhas[i % nPilhas], Texto[i]);
	}

	for(i = 0; i < strlen(Texto); i++){
		TPilha_Desempilha(&pilhas[i % nPilhas], &textoFinal[i]);
	}

	return(textoFinal);
}

char *Descriptografa(char *Texto, int nPilhas){

}
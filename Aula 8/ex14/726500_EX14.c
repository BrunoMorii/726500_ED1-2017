/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 14 - Recuperacao da Arvore Binaria

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


// <<< IMPLEMENTE AQUI O SEU CODIGO >>>
#include <stdio.h>
#include <stdlib.h>

typedef struct no *AB;

typedef struct no{
	int num;
	AB esq, dir;
}No;

AB inicializa();
AB criaNo(int n, AB esq, AB dir);
AB constroi(int *preOrdem, int *emOrdem, int tam);
int Pesquisa(int *preOrdem, int esq, int dir, int num);
AB constroiRecursivamente(int *preOrdem, int *pNo, int *emOrdem, int esq, int dir);
void imprime_pos(AB no);
void libera(AB no);


int main(){
	int i, tamanho, *preOrdem, *emOrdem;
	AB raiz;

	//recebe tamanho da sequencia
	scanf("%d", &tamanho);

	//inicializa e recebe as sequencias

	//pre-ordem
	preOrdem = (int *) malloc (sizeof(int) * tamanho);
	if(preOrdem == NULL){
		printf("ERRO DE ALOCACAO\n");
		exit(1);
	}

	for(i = 0; i < tamanho; i++){
		scanf("%d", &preOrdem[i]);
	}

	//em-ordem
	emOrdem = (int *) malloc (sizeof(int) * tamanho);
	if(emOrdem == NULL){
		printf("ERRO DE ALOCACAO\n");
		exit(1);
	}

	for(i = 0; i < tamanho; i++){
		scanf("%d", &emOrdem[i]);
	}

	raiz = constroi(preOrdem, emOrdem, tamanho);

	imprime_pos(raiz);

	libera(raiz);

	return (0);
}

AB inicializa(){
	return NULL;
}

AB criaNo(int n, AB esq, AB dir){
	AB no;

	no = (AB) malloc (sizeof(No));
	no->num = n;
	no->esq = esq;
	no->dir = dir;
	return(no);
}

void libera(AB no){
	if(no != NULL){
		libera(no->esq);
		libera(no->dir);
		free(no);
	}
}

AB constroi(int *preOrdem, int *emOrdem, int tam){
	int no;
	no = 0;
	
	return constroiRecursivamente(preOrdem, &no, emOrdem, 0, tam - 1);
}

int Pesquisa(int *preOrdem, int esq, int dir, int num){
	int raiz;

	for(raiz = esq; raiz <= dir; raiz++){
		if(preOrdem[raiz] == num)
			return (raiz);
	}

	return (0);
}

AB constroiRecursivamente(int *preOrdem, int *pNo, int *emOrdem, int esq, int dir){
	AB pEsq, pDir;
	int num, raiz;

	if(esq <= dir){
		num = preOrdem[(*pNo)++];
		raiz = Pesquisa(emOrdem, esq, dir, num);
		pEsq = constroiRecursivamente(preOrdem, pNo, emOrdem, esq, raiz - 1);
		pDir = constroiRecursivamente(preOrdem, pNo, emOrdem, raiz + 1, dir);
		return criaNo(num, pEsq, pDir);
	}

	return inicializa();
}

void imprime_pos(AB no){
	if(no != NULL){
		imprime_pos(no->esq);
		imprime_pos(no->dir);
		printf("%d\n", no->num);
	}
}
/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 19 - Batalha de referências

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
#include <ctype.h>

// Frases pre-definidas
#define MSG_ERRO_ALOC 	  "Erro de alocacao!\n"
#define MSG_NAO_EXT  	  "Palavra inexistente na tabela!\n"
#define MSG_TAB_VAZIA	  "Tabela vazia!\n"
#define MSG_EMPATE	  	  "Empate!\n"
#define MSG_OPCAO_INV 	  "Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI OS TAD's >>>
typedef struct p{
	char palavra[11];
	int pontos;
}Palavra;

typedef struct no{
	Palavra p;
	int fb;
	struct no *esq, *dir;
}No;

typedef No *Arvore;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>

void iniciaArvore(Arvore *raiz);
int insereAVL(Arvore *no, Palavra p);
void passarMaiusculas(char palavra[11]);
void LL(Arvore *no);
void RR(Arvore *no);
void LR(Arvore *no);
void RL(Arvore *no);
int balanceamentoE(Arvore *no);
int balanceamentoD(Arvore *no);
Arvore buscaAVL(Arvore no, char palavra[11]);
int removeAVL(Arvore *no, Palavra p);
int sucessor(Arvore *p, Arvore *r);
void R_LL(Arvore *no);
void R_RR(Arvore *no);
void R_LR(Arvore *no);
void R_RL(Arvore *no);
int R_balanceamentoE(Arvore *no);
int R_balanceamentoD(Arvore *no);
int combate(Arvore raiz, long long int *maiorPontuacao);
void imprimeTabela(Arvore no);
void liberaTabela(Arvore *no);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>
	Arvore raiz, no;
	char heroi1[21], heroi2[21];
	Palavra p;
	long long int pontos;
	int i, n, opc, ganhador;

	iniciaArvore(&raiz);

	do{
		scanf("%d", &opc); getchar();
		switch(opc){

			//insere n palavras
			case 1:
				scanf("%d", &n); getchar();//numero de palavras
				//insere as n palavras
				for(i = 0; i < n; i++){
					//leitura dos dados
					scanf("%[^' '] %d", p.palavra, &p.pontos); getchar();
					passarMaiusculas(p.palavra);
					//tenta inserir, se ja existir, atualiza o valor
					if(!insereAVL(&raiz, p)){
						no = buscaAVL(raiz, p.palavra);
						no->p.pontos = p.pontos;
					}
				}
				break;

			//remove uma palavra
			case 2:
				scanf("%[^\n]", p.palavra);
				passarMaiusculas(p.palavra);
				if(buscaAVL(raiz, p.palavra) != NULL){
					removeAVL(&raiz, p);
				}else{
					printf(MSG_NAO_EXT);
				}
				break;

			//faz a batalha
			case 3:
				//le o nome dos dois herois
				pontos = 0;
				scanf("%[^\n]", heroi1); getchar();
				scanf("%[^\n]", heroi2); getchar();
				ganhador = combate(raiz, &pontos);
				if(ganhador == 1){
					printf("%s\n%lld\n", heroi1, pontos);
				}else if(ganhador == 2){
					printf("%s\n%lld\n", heroi2, pontos);
				}else{
					printf(MSG_EMPATE);
					printf("%lld\n", pontos);
				}

				break;

			//imprime a tabela
			case 4:
				if(raiz == NULL){
					printf(MSG_TAB_VAZIA);
				}else{
					imprimeTabela(raiz);
				}
				break;

			//finaliza o programa
			case 5:
				liberaTabela(&raiz);
				break;

			default:
				printf(MSG_OPCAO_INV);
		}

	}while(opc != 5);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

// <<< IMPLEMENTE AQUI AS FUNCOES >>>


void iniciaArvore(Arvore *raiz){
	*raiz = NULL;
}

int insereAVL(Arvore *no, Palavra p){

	if(*no == NULL){
		//cria novo no e insere com os dados
		(*no) = (Arvore) malloc(sizeof(No));
		(*no)->p = p;
		(*no)->fb = 0;
		(*no)->esq = NULL;
		(*no)->dir = NULL;
		return 1;
	}else if(strcmp((*no)->p.palavra, p.palavra) > 0){
		if(insereAVL(&(*no)->esq, p)){
			switch((*no)->fb){
				case -1:
					(*no)->fb = 0;
					return 0;

				case 0:
					(*no)->fb = 1;
					return 1;

				case 1:
					return !balanceamentoE(no);

			}
		}
		return 0;
	}else if(strcmp((*no)->p.palavra, p.palavra) < 0){
		if(insereAVL(&(*no)->dir, p)){
			switch((*no)->fb){
				case 1:
					(*no)->fb = 0;
					return 0;

				case 0:
					(*no)->fb = -1;
					return 1;

				case -1:
					return !balanceamentoD(no);

			}
		}
		return 0;
	}

	return 0;
}

void LL(Arvore *no){
	Arvore pB;

	pB = (*no)->esq;
	(*no)->esq = pB->dir;
	pB->dir = (*no);
	(*no)->fb = 0;
	pB->fb = 0;
	*no = pB;
}

void RR(Arvore *no){
	Arvore pB;

	pB = (*no)->dir;
	(*no)->dir = pB->esq;
	pB->esq = (*no);
	(*no)->fb = 0;
	pB->fb = 0;
	*no = pB;
}

void LR(Arvore *no){
	Arvore pB, pC;

	pB = (*no)->esq;
	pC = pB->dir;
	pB->dir = pC->esq;
	pC->esq = pB;
	(*no)->esq = pC->dir;
	pC->dir = (*no);
	if(pC->fb == 1){
		(*no)->fb = -1;
	}else{
		(*no)->fb = 0;
	}
	if(pC->fb == -1){
		pB->fb = 1;
	}else{
		pB->fb = 0;
	}
	pC->fb = 0;
	*no = pC;
}

void RL(Arvore *no){
	Arvore pB, pC;

	pB = (*no)->dir;
	pC = pB->esq;
	pB->esq = pC->dir;
	pC->dir = pB;
	(*no)->dir = pC->esq;
	pC->esq = (*no);
	if(pC->fb == -1){
		(*no)->fb = 1;
	}else{
		(*no)->fb = 0;
	}
	if(pC->fb == 1){
		pB->fb = -1;
	}else{
		pB->fb = 0;
	}
	pC->fb = 0;
	*no = pC;
}

int balanceamentoE(Arvore *no){
	short int bal;

	if((*no)->esq == NULL){
		bal = 0;
	}else{
		bal = (*no)->esq->fb;
	}

	if(bal > 0){
		LL(no);
		return 1;
	}else if(bal < 0){
		LR(no);
		return 1;
	}

	return 0;
}

int balanceamentoD(Arvore *no){
	short int bal;
	if((*no)->dir == NULL){
		bal = 0;
	}else{
		bal = (*no)->dir->fb;
	}

	if(bal < 0){
		RR(no);
		return 1;
	}else if(bal > 0){
		RL(no);
		return 1;
	}

	return 0;
}

void passarMaiusculas(char palavra[11]){
	int i = 0;

	while(palavra[i] != '\0'){
		palavra[i] = toupper(palavra[i]);
		i++;
	}
}

int removeAVL(Arvore *no, Palavra p){
	Arvore aux;
	int ret;

	if(*no == NULL){
		return 0;
	}else if(strcmp((*no)->p.palavra, p.palavra) > 0){
		if(removeAVL(&(*no)->esq, p)){
			switch((*no)->fb){
				case 1:
					(*no)->fb = 0;
					return 1;
				case 0:
					(*no)->fb = -1;
					return 0;
				case -1:
					return R_balanceamentoD(no);
			}
		}
		return 0;
	}else if(strcmp((*no)->p.palavra, p.palavra) < 0){
		if(removeAVL(&(*no)->dir, p)){
			switch((*no)->fb){
				case -1:
					(*no)->fb = 0;
					return 1;
				case 0:
					(*no)->fb = 1;
					return 0;
				case 1:
					return R_balanceamentoE(no);
			}
		}
		return 0;
	}else{
		aux = *no;
		if(aux->esq == NULL){
			*no = aux->dir;
			ret = 1;
		}else if(aux->dir == NULL){
			*no = aux->esq;
			ret = 1;
		}else{
			if(sucessor(&aux, &aux->dir)){
				switch((*no)->fb){
					case -1:
						(*no)->fb = 0;
						ret = 1;
						break;
					case 0:
						(*no)->fb = 1;
						ret = 0;
						break;
					case 1:
						ret = R_balanceamentoE(no);
				}
			}else{
				ret = 0;
			}
		}
		free(aux);
		return ret;
	}
}

int sucessor(Arvore *q, Arvore *r){
	if((*r)->esq != NULL){
		if(sucessor(q, &(*r)->esq)){
			switch((*r)->fb){
				case 1:
					(*r)->fb = 0;
					return 1;
				case 0:
					(*r)->fb = -1;
					return 0;
				case -1:
					return R_balanceamentoD(r);
			}
		}
		return 0;
	}else{
		(*q)->p = (*r)->p;
		*q = *r;
		*r = (*r)->dir;
		return 1;
	}
}

void R_LL(Arvore *no){
	Arvore pB;

	pB = (*no)->esq;
	(*no)->esq = pB->dir;
	pB->dir = (*no);
	if(pB->fb == 0){
		(*no)->fb = 1;
		pB->fb = -1;
	}else{
		(*no)->fb = 0;
		pB->fb = 0;
	}
	*no = pB;
}

void R_RR(Arvore *no){
	Arvore pB;

	pB = (*no)->dir;
	(*no)->dir = pB->esq;
	pB->esq = (*no);
	if(pB->fb == 0){
		(*no)->fb = -1;
		pB->fb = 1;
	}else{
		(*no)->fb = 0;
		pB->fb = 0;
	}
	*no = pB;
}

int R_balanceamentoE(Arvore *no){
	short int bal;
	if((*no)->esq == NULL){
		bal = 0;
	}else{
		bal = (*no)->esq->fb;
	}

	if(bal > 0){
		R_LL(no);
		return 1;
	}else if(bal < 0){
		LR(no);
		return 1;
	}else{
		R_LL(no);
		return 0;
	}
}

int R_balanceamentoD(Arvore *no){
	short int bal;
	if((*no)->dir == NULL){
		bal = 0;
	}else{
		bal = (*no)->dir->fb;
	}

	if(bal < 0){
		R_RR(no);
		return 1;
	}else if(bal > 0){
		RL(no);
		return 1;
	}else{
		R_RR(no);
		return 0;
	}

	return 0;
}


Arvore buscaAVL(Arvore no, char palavra[11]){
	if(no != NULL){
		if(strcmp(no->p.palavra, palavra) == 0){
			return no;
		}else if(strcmp(no->p.palavra, palavra) > 0){
			return buscaAVL(no->esq, palavra);
		}else if(strcmp(no->p.palavra, palavra) < 0){
			return buscaAVL(no->dir, palavra);
		}
	}

	return NULL;
}

int combate(Arvore raiz, long long int *maiorPontuacao){
	int i = -1, j = 0, k = 0, combo = 1;
	long long int pontos[2] = {0};
	char c, palavra[1001], frase[1001];
	Arvore no;

	do{
		//i e iterador que indica o heroi, se impar e 1, se par e 2
		i++;
		combo = 1;
		//inicializa k = 0, iterador da frase
		k = 0;
		//recebe a frase
		scanf("%[^\n]", frase); getchar();
		passarMaiusculas(frase);
		//se nao for ponto executa a leitura
		if(strcmp(frase, ".") != 0){
			do{
				//j e iterador da palavra, le uma palavra por vez
				j = 0;
				while(frase[k] != ' ' && frase[k] != '\0'){
					palavra[j++] = (frase[k++]);
				}
				palavra[j] = '\0';
				//finaliza a palavra com o \0
				//colcoa em c o espaço ou \0 depois da palavra e ja passa para a pr´oxima iteraçao
				c = frase[k++];

				no = buscaAVL(raiz, palavra);

				if(no != NULL){
					pontos[i % 2] += combo * no->p.pontos;
					if(combo < 1024){
						combo *= 2;
					}
				}else{
					combo = 1;
				}
			}while(c != '\0');
		}
	}while(strcmp(frase, ".") != 0);

	if(pontos[0] > pontos[1]){
		*maiorPontuacao = pontos[0];
		return 1;
	}else if(pontos[0] < pontos[1]){
		*maiorPontuacao = pontos[1];
		return 2;
	}else{
		*maiorPontuacao = pontos[0];
		return 0;
	}
}

void imprimeTabela(Arvore no){
	if(no != NULL){
		printf("%s %d\n", no->p.palavra, no->p.pontos);
		imprimeTabela(no->esq);
		imprimeTabela(no->dir);
	}
}

void liberaTabela(Arvore *no){
	if(*no != NULL){
		liberaTabela(&(*no)->esq);
		liberaTabela(&(*no)->dir);
		free(*no);
	}
}
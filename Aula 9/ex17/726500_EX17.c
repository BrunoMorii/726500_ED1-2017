/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 17 - Treinador de corvos

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

// Frases e constantes pre-definidas
#define MSG_ERRO_ALOC 	  "Erro de alocacao!\n"
#define MSG_JA_EXT_CASA	  "Casa ja memorizada!\n"
#define MSG_JA_EXT_TRT	  "Territorio ja memorizado!\n"
#define MSG_NAO_EXT_CASA  "A casa referenciada nao esta memorizada!\n"
#define MSG_NAO_EXT_TRT   "O territorio referenciado nao esta memorizado!\n"
#define MSG_CASA_REMOVIDA "A casa referenciada foi removida pois se tornou nao unica!\n"
#define MSG_POS_OCUPADA   "A posicao referenciada ja esta ocupada!\n"
#define MSG_NAO_RMV_UNICO "Nao e possivel remover todos os territorios de uma casa!\n"
#define MSG_ARV_VAZIA	  "Arvore de Casas vazia!\n"
#define MSG_OPCAO_INV 	  "Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI OS TAD's >>>
typedef struct nt{
	int valor;
	struct nt *esq, *dir;
}NoTerritorio;

typedef NoTerritorio *Territorio;

typedef struct ac{
	char nome[21];
	int importancia;
	Territorio raiz;
	struct ac *esq, *dir;
}NoCasa;

typedef NoCasa *Casa;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>

void casaInicia(Casa *raiz);
int ACVazia(Casa raiz);
void inserirCasa(Casa *raiz, char nome[], int importancia);
void inserirCasaNaArvore(Casa *raiz, Casa novo);
void inserirTerritorio(Territorio raiz, char lado, int importancia);
Casa buscaCasa(Casa raiz, int importancia);
Territorio buscaTerritorio(Territorio raiz, int importancia);
void exibirTerritorios(Territorio raiz);
int verificaABBT(Territorio raiz);
int verificaABBTE(Territorio raiz, Territorio no);
int verificaABBTD(Territorio raiz, Territorio no);
int verificaABBC(Casa raiz);
int verificaABBCE(Casa raiz, Casa no);
int verificaABBCD(Casa raiz, Casa no);
int verificaMenorABBT(Territorio no, int valor);
int verificaMaiorABBT(Territorio no, int valor);
int verificaMenorABBC(Casa no, int valor);
int verificaMaiorABBC(Casa no, int valor);
Casa removeCasa(Casa *no, int importancia);
int removeTerritorio(Territorio *no, int importancia);
void TerritorioSucessor(Territorio *q, Territorio *r);
void CasaSucessor(Casa *q, Casa *r);
void exibirCasas(Casa raiz);
void liberaCasas(Casa raiz);
void liberaCasa(Casa casa);
void liberaTerritorios(Territorio raiz);
//novos
Casa buscaCasaG(Casa *raiz, int importancia);

/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){
	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>
	char nome[21], lado;
	int opc, importancia, impP;
	Casa raiz, novo, rem;
	Territorio pai, ter;

	raiz = (Casa) malloc (sizeof(NoCasa));
	if(raiz == NULL){
		printf(MSG_ERRO_ALOC);
		exit(1);
	}
	casaInicia(&raiz);

	do{
		scanf("%d", &opc); getchar();
		switch(opc){
			//memorizar nova casa
			case 1:
				//le dados da nova casa
				scanf("%[^' '] %d", nome, &importancia); getchar();
				inserirCasa(&raiz, nome, importancia);
				break;

			//memorizar novo territorio
			case 2:
				scanf("%d", &importancia); getchar();
				novo = buscaCasa(raiz, importancia);
				scanf("%d %c %d", &impP, &lado, &importancia); getchar();

				if(novo == NULL){
					printf(MSG_NAO_EXT_CASA);
				}else{
					pai = buscaTerritorio(novo->raiz, impP);
					if(pai != NULL){
						if((lado == 'E' && pai->esq != NULL) || (lado == 'D' && pai->dir != NULL)){
							printf(MSG_POS_OCUPADA);
						}else{
							ter = buscaTerritorio(novo->raiz, importancia);
							if(ter != NULL){
								printf(MSG_JA_EXT_TRT);
							}else{
								inserirTerritorio(pai, lado, importancia);
								
								rem = removeCasa(&raiz, novo->importancia);

								if(verificaABBT(rem->raiz) == 0 && rem->importancia > 0){
									rem->importancia *= -1;
								}else if(verificaABBT(rem->raiz) == 1 && rem->importancia < 0){
									rem->importancia *= -1;
								}

								if(rem->importancia < 0){
									rem->importancia -= importancia;
								}else{
									rem->importancia += importancia;
								}

								novo = buscaCasa(raiz, rem->importancia);
								if(novo == NULL){
									inserirCasaNaArvore(&raiz, rem);
								}else{
									printf(MSG_CASA_REMOVIDA);
								}
							}
						}
					}else{
						printf(MSG_NAO_EXT_TRT);
					}
				}
				break;

			//esquecer casa
			case 3:
				scanf("%d", &importancia); getchar();

				novo = removeCasa(&raiz, importancia);

				if(novo == NULL)
					printf(MSG_NAO_EXT_CASA);
				break;

			//esquecer territorio
			case 4:
				scanf("%d %d", &impP, &importancia);
				novo = buscaCasa(raiz, impP);
				if(novo == NULL){
					printf(MSG_NAO_EXT_CASA);
				}else if(novo->raiz->esq == NULL && novo->raiz->dir == NULL){
					printf(MSG_NAO_RMV_UNICO);
				}else{
					if(removeTerritorio(&(novo->raiz), importancia)){
						rem = removeCasa(&raiz, novo->importancia);

						if(verificaABBT(rem->raiz) == 0 && rem->importancia > 0){
							rem->importancia *= -1;
						}else if(verificaABBT(rem->raiz) == 1 && rem->importancia < 0){
							rem->importancia *= -1;
						}

						if(rem->importancia < 0){
							rem->importancia += importancia;
						}else{
							rem->importancia -= importancia;
						}

						novo = buscaCasa(raiz, rem->importancia);
						if(novo == NULL){
							inserirCasaNaArvore(&raiz, rem);
						}else{
							printf(MSG_CASA_REMOVIDA);
						}
					}else{
						printf(MSG_NAO_EXT_TRT);
					}
				}
				break;

			//exibir arvore de casas
			case 5:
				if(ACVazia(raiz)){
					printf(MSG_ARV_VAZIA);
				}else{
					exibirCasas(raiz);
				}
				break;

			//exibir territorios
			case 6:
				scanf("%d", &importancia); getchar();
				novo = buscaCasa(raiz, importancia);
				if(novo == NULL){
					printf(MSG_NAO_EXT_CASA);
				}else{
					exibirTerritorios(novo->raiz);
				}
				break;

			//libera memoria
			case 7:
				liberaCasas(raiz);
				break;

			//opc invalida
			default:
				printf(MSG_OPCAO_INV);
			
		}
	}while(opc != 7);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

// <<< IMPLEMENTE AQUI AS FUNCOES >>>

void casaInicia(Casa *raiz){
	*raiz = NULL;
}

int ACVazia(Casa raiz){
	return(raiz == NULL);
}

//tenta inserir a nova Casa
void inserirCasa(Casa *raiz, char nome[], int importancia){
	Casa novo = (Casa) malloc (sizeof(NoCasa)), casa;
	Territorio novoT = (Territorio) malloc (sizeof(NoTerritorio)), busca, ter;
	char lado;
	int pai, imp;

	if(novo == NULL){
		printf(MSG_ERRO_ALOC);
		exit(1);
	}

	if(novoT == NULL){
		printf(MSG_ERRO_ALOC);
		exit(1);
	}

	//cria casa
	strcpy(novo->nome, nome);
	novo->importancia = importancia;
	novo->esq = NULL;
	novo->dir = NULL;

	//insere o primeiro terriotorio
	novoT->valor = importancia;
	novoT->esq = NULL;
	novoT->dir = NULL;

	//aponta para a raiz
	novo->raiz = novoT;

	do{
		//le a importancia do pai
		scanf("%d", &pai); getchar();

		//se nao for condiçao de saida
		if(pai != -1){
			scanf("%c %d", &lado, &imp); getchar();

			//busca o pai referenciado
			busca = buscaTerritorio(novo->raiz, pai);
			if(busca != NULL){
				//verifica se ja esta ocupado
				if((lado == 'E' && busca->esq != NULL) || (lado == 'D' && busca->dir != NULL)){
					printf(MSG_POS_OCUPADA);
				}else{
					//verifica se ja existe e insere
					ter = buscaTerritorio(novo->raiz, imp);
					if(ter != NULL){
						printf(MSG_JA_EXT_TRT);
					}else{
						inserirTerritorio(busca, lado, imp);
						novo->importancia += imp;
					}
				}
			}else{
				printf(MSG_NAO_EXT_TRT); 
			}
		}
	}while(pai != -1);

	//verifica se e abb caso nao, multiplica por -1

	if(verificaABBT(novo->raiz) == 0){
		novo->importancia *= -1;
	}

	casa = buscaCasa(*raiz, importancia);
	if(casa != NULL){
		printf(MSG_JA_EXT_CASA);
		liberaCasa(novo);
	}else{
		inserirCasaNaArvore(raiz, novo);
	}
}

void inserirCasaNaArvore(Casa *raiz, Casa novo){
	Casa *aux = raiz;

	if((*raiz) == NULL){
		*raiz = novo;
	}else{
		while((*aux) != NULL){
			if((*aux)->importancia > novo->importancia){
				if((*aux)->esq == NULL){
					(*aux)->esq = novo;
					return;
				}else{
					aux = &(*aux)->esq;
				}
			}else{
				if((*aux)->dir == NULL){
					(*aux)->dir = novo;
					return;
				}else{
					aux = &(*aux)->dir;
				}
			}
		}
	}
}

//retorna 1 se inseriu, 0 do contrario
void inserirTerritorio(Territorio raiz, char lado, int importancia){
	Territorio novo = (Territorio) malloc (sizeof(NoTerritorio));

	if(novo == NULL){
		printf(MSG_ERRO_ALOC);
		exit(1);
	}

	novo->valor = importancia;
	novo->esq = NULL;
	novo->dir = NULL;

	if(lado == 'E'){
		raiz->esq = novo;
	}else{
		raiz->dir = novo;
	}
}

//retorna 1 se encontrar a Casa, senao 0
Casa buscaCasa(Casa raiz, int importancia){
	if(raiz != NULL){
		if(raiz->importancia == importancia){
			return raiz;
		}

		if(raiz->importancia > importancia){
			return buscaCasa(raiz->esq, importancia);
		}else{
			return buscaCasa(raiz->dir, importancia);
		}	
	}

	return NULL;
}

Territorio buscaTerritorio(Territorio raiz, int importancia){
	Territorio t;

	if(raiz != NULL){
		if(raiz->valor == importancia){
			return raiz;
		}
		
		t = buscaTerritorio(raiz->esq, importancia);
		if(t != NULL){
			return t;
		}

		t = buscaTerritorio(raiz->dir, importancia);
		if(t != NULL){
			return t;
		}
	}

	return NULL;
}

void exibirCasas(Casa raiz){
	if(raiz != NULL){
		exibirCasas(raiz->esq);
		printf("%d\n", raiz->importancia);
		exibirCasas(raiz->dir);
	}
}
void exibirTerritorios(Territorio raiz){
	if(raiz != NULL){
		exibirTerritorios(raiz->esq);
		printf("%d\n", raiz->valor);
		exibirTerritorios(raiz->dir);
	}
}

int verificaABBT(Territorio raiz){
	return(verificaABBTE(raiz, raiz->esq) && verificaABBTD(raiz, raiz->dir));
}

int verificaABBTE(Territorio raiz, Territorio no){
	int t;

	if(no != NULL){
		if(!verificaMenorABBT(no, raiz->valor)){
			return 0;
		}

		t = verificaABBTE(no, no->esq);
		if(t == 0){
			return t;
		}
		
		t = verificaABBTD(no, no->dir);
			return t;
	}

	return 1;
}

int verificaABBTD(Territorio raiz, Territorio no){
	int t;

	if(no != NULL){
		if(!verificaMaiorABBT(no, raiz->valor)){
			return 0;
		}

		t = verificaABBTE(no, no->esq);
		if(t == 0)
			return t;

		t = verificaABBTD(no, no->dir);
			return t;
	}

	return 1;
}

int verificaMenorABBT(Territorio no, int valor){
	int t;

	if(no != NULL){
		if(no->valor > valor){
			return 0;
		}

		t = verificaMenorABBT(no->esq, valor);
		if(t == 0)
			return t;

		t = verificaMenorABBT(no->dir, valor);
			return t;
	}

	return 1;
}

int verificaMaiorABBT(Territorio no, int valor){
	int t;

	if(no != NULL){
		if(no->valor < valor){
			return 0;
		}

		t = verificaMaiorABBT(no->esq, valor);
		if(t == 0)
			return t;

		t = verificaMaiorABBT(no->dir, valor);
			return t;
	}

	return 1;
}


int verificaABBC(Casa raiz){
	return(verificaABBCE(raiz, raiz->esq) && verificaABBCD(raiz, raiz->dir));
}

int verificaABBCE(Casa raiz, Casa no){
	int t;

	if(no != NULL){
		if(!verificaMenorABBC(no, raiz->importancia)){
			return 0;
		}

		t = verificaABBCE(no, no->esq);
		if(t == 0){
			return t;
		}
		
		t = verificaABBCE(no, no->dir);
			return t;
	}

	return 1;
}

int verificaABBCD(Casa raiz, Casa no){
	int t;

	if(no != NULL){
		if(!verificaMaiorABBC(no, raiz->importancia)){
			return 0;
		}

		t = verificaABBCD(no, no->esq);
		if(t == 0)
			return t;

		t = verificaABBCD(no, no->dir);
			return t;
	}

	return 1;
}

int verificaMenorABBC(Casa no, int valor){
	int t;

	if(no != NULL){
		if(no->importancia > valor){
			return 0;
		}

		t = verificaMenorABBC(no->esq, valor);
		if(t == 0){
			return t;
		}

		t = verificaMenorABBC(no->dir, valor);
			return t;
	}

	return 1;
}

int verificaMaiorABBC(Casa no, int valor){
	int t;

	if(no != NULL){
		if(no->importancia > valor){
			return 0;
		}

		t = verificaMaiorABBC(no->esq, valor);
		if(t == 0){
			return t;
		}

		t = verificaMaiorABBC(no->dir, valor);
			return t;
	}

	return 1;
}

Casa removeCasa(Casa *no, int importancia){
	Casa q, ret;

	if(*no == NULL){
		return NULL;
	}else if((*no)->importancia > importancia){
		return removeCasa(&(*no)->esq, importancia);
	}else if((*no)->importancia < importancia){
		return removeCasa(&(*no)->dir, importancia);
	}else{
		ret = (Casa) malloc (sizeof(NoCasa));
		if(ret == NULL){
			printf(MSG_ERRO_ALOC);
			exit(1);
		}
		strcpy(ret->nome, (*no)->nome);
		ret->importancia = (*no)->importancia;
		ret->raiz = (*no)->raiz;
		ret->esq = NULL;
		ret->dir = NULL;
		q = *no;
		if(q->esq == NULL){
			*no = q->dir;
		}else if(q->dir == NULL){
			*no = q->esq;
		}else{
			CasaSucessor(&q, &q->dir);
		}
		free(q);
		return(ret);
	}
}

int removeTerritorio(Territorio *no, int importancia){
	Territorio q;
	int t;

	if(*no != NULL){
		if((*no)->valor == importancia){
			q = *no;
			if(q->esq == NULL){
				*no = q->dir;
			}else if(q->dir == NULL){
				*no = q->esq;
			}else{
				TerritorioSucessor(&q, &q->dir);
			}
			free(q);
			return 1;
		}
		
		t = removeTerritorio(&(*no)->esq, importancia);
		if(t != 0){
			return t;
		}

		t = removeTerritorio(&(*no)->dir, importancia);
			return t;
	}

	return 0;
}

void CasaSucessor(Casa *q, Casa *r){
	if((*r)->esq != NULL){
		CasaSucessor(q, &(*r)->esq);
	}else{
		(*q)->raiz = (*r)->raiz;
		(*q)->importancia = (*r)->importancia;
		strcpy((*q)->nome, (*r)->nome);
		*q = *r;
		*r = (*r)->dir;
	}
}

void TerritorioSucessor(Territorio *q, Territorio *r){
	if((*r)->esq != NULL){
		TerritorioSucessor(q, &(*r)->esq);
	}else{
		(*q)->valor = (*r)->valor;
		*q = *r;
		*r = (*r)->dir;
	}
}

void liberaCasas(Casa raiz){
	if(raiz != NULL){
		liberaCasas(raiz->esq);
		liberaCasas(raiz->dir);
		liberaCasa(raiz);
	}
}

void liberaCasa(Casa casa){
	liberaTerritorios(casa->raiz);
	free(casa);
}

void liberaTerritorios(Territorio raiz){
	if(raiz != NULL){
		liberaTerritorios(raiz->esq);
		liberaTerritorios(raiz->dir);
		free(raiz);
	}
}


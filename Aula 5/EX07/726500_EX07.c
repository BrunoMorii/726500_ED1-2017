/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 07 - Gestão de Estacionamentos

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
#define MSG_JA_EXISTE		"O título de relatório informado já está cadastrado!\n"
#define MSG_NAO_EXISTE_REL	"O relatório requisitado não está cadastrado!\n"
#define MSG_NAO_EXISTE_PLC	"A placa informada não está presente no relatório!\n"
#define MSG_OPCAO_INV 		"Opcao invalida!\n"
#define MSG_EXIBE_HORARIO	"E: %02dh%02d | S: %02dh%02d\n"


// === TAD E DEMAIS REGISTROS ===

// <<< DEFINA AQUI OS TAD's >>>

typedef struct _C{
	char placa[9];
	int in_h, in_m;
	int out_h, out_m;
	struct _C *prox;
}Carro;

/*typedef struct _FC{
	Carro *inicio;
	Carro *fim;
	int nCarros;
}FilaCarros;*/

typedef struct _R{
	char nome[200];
	int capacidade;
	Carro *topo;
	int validade;
	struct _R *prox;
}Relatorio;

typedef struct _FR{
	Relatorio *inicio;
	Relatorio *fim;
	int nRelatorios;
}FilaRelatorios;

/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>

Relatorio *criaRelatorio(char nome[], int capacidade);

void enfileiraRelatorios(FilaRelatorios *fila, Relatorio *relatorio);

Relatorio *buscaRelatorio(FilaRelatorios *fila, Relatorio *relatorio, char nome[]);

int buscaCarro(Relatorio *relatorio, char placa[]);

int verificaValidade(Relatorio *pilha, Carro *atual, int capacidade, int *nAtual);

void empilha(Relatorio *pilha, Carro *atual);

void desempilha(Relatorio *pilha);

void liberaRelatorios(FilaRelatorios *relatorios);

void liberaCarros(Carro *topo);


/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>
	int opc, capacidade;
	FilaRelatorios *relatorios;
	Relatorio *aux;
	char nome[200], placa_teste[9];

	//aloca, verifica e inicializa relatorios
	relatorios = (FilaRelatorios *) malloc (sizeof(FilaRelatorios));
	if(relatorios == NULL){
		printf(MSG_ERRO_ALOC);
		exit(1);
	}

	relatorios->inicio = NULL;
	relatorios->fim = NULL;

	// rotina de excuçao com menu de opçoes
	do{
		scanf("%d", &opc);

		switch(opc){
			//inserir
			case 1:
				scanf("\n%[^\n]s", nome);
				scanf("%d", &capacidade); getchar();
				if(buscaRelatorio(relatorios, aux, nome)){
					printf(MSG_JA_EXISTE);
				}else{
					aux = criaRelatorio(nome, capacidade);
					enfileiraRelatorios(relatorios, aux);
				}
				break;

			//verificar
			case 2:
				scanf("\n%[^\n]s", nome);
				aux = buscaRelatorio(relatorios, aux, nome);
				if(aux != NULL){
					//printf("Validade : %d\n", aux->validade);
					if(aux->validade == 1){
						printf("Válido\n");
					}else{
						printf("Inválido\n");
					}
				}else{
					printf(MSG_NAO_EXISTE_REL);
				}
				break;

			//busca
			case 3:
				scanf("\n%[^\n]s", nome);
				aux = buscaRelatorio(relatorios, aux, nome);
				scanf("\n%[^\n]s", placa_teste);
				if(aux != NULL){
					if(buscaCarro(aux, placa_teste) == 0){
						printf(MSG_NAO_EXISTE_PLC);
					}
				}else{
					printf(MSG_NAO_EXISTE_REL);
				}
				break;

			//saida
			case 4:
				liberaRelatorios(relatorios);
				break;

			//opçao invalida
			default:
				printf(MSG_OPCAO_INV);
		}
	}while(opc != 4);

	/*
	//rotina de impressao para testes
	aux = relatorios->inicio;
	printf("---------------------------\n");
	while(aux != NULL){
		printf("%s - %d\n", aux->nome, aux->capacidade);
		aux2 = aux->topo;
		while(aux2 != NULL){
			printf("%s - %02dh%02d %02dh%02d\n", aux2-> placa, aux2->in_h, aux2->in_m, aux2->out_h, aux2->out_m);
			aux2 = aux2->prox;
		}
		aux = aux->prox;
		printf("---------------------------\n");
	}*/

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

// <<< IMPLEMENTE AQUI AS FUNCOES >>>

Relatorio *criaRelatorio(char nome[], int capacidade){
	Relatorio *aux = (Relatorio *) malloc (sizeof(Relatorio)), *pilha = (Relatorio *) malloc (sizeof(Relatorio));
	Carro *aux2;
	int i = 0, nAtual = 0;
	char placa[9], end[9];

	//inicia relatorio
	strcpy(aux->nome, nome);
	aux->prox = NULL;
	aux->topo = NULL;
	aux->validade = 1;

	aux->capacidade = capacidade;

	pilha->topo = NULL;

	//rotina para inserir carros
	for(i = 0; i <8; i++){
		scanf("%c", &placa[i]);

	}
	placa[8] = '\0';
	getchar();

	strcpy(end, "END-0000");

	while(strcmp(placa, end) != 0){
		//rotina para inserir carros
		aux2 = (Carro *) malloc (sizeof(Carro));
		strcpy(aux2->placa, placa);
		scanf("%dh%d %dh%d", &aux2->in_h, &aux2->in_m, &aux2->out_h, &aux2->out_m);
		getchar();

		if(aux->topo == NULL){
			aux2->prox = NULL;
			aux->topo = aux2;
		}else{
			aux2->prox = aux->topo;
			aux->topo = aux2;
		}

		//verifica validade
		if((aux->validade == 1) && (!verificaValidade(pilha, aux2, aux->capacidade, &nAtual))){
			aux->validade = 0;
			
			liberaCarros(pilha->topo);
		}

		//nova leitura de placa
		for(i = 0; i <8; i++){
			scanf("%c", &placa[i]);
		}
		placa[8] = '\0'; getchar();
	}

	free(pilha);

	return(aux);
}

int verificaValidade(Relatorio *pilha, Carro *atual, int capacidade, int *nAtual){
	Carro *aux;

	//verifica se esta no horario de funcionamento
	if( ((atual->in_h * 60 + atual->in_m) < 6 * 60) || ((atual->out_h * 60 + atual->out_m) > 22 * 60) ){
		return(0);
	}
	//verifica se hora de entrada maior ou igual que a de saida
	else if((atual->in_h * 60 + atual->in_m) >= (atual->out_h * 60 + atual->out_m)){
		return(0);
	}
	//verifica com os anteriores
	aux = pilha->topo;
	while(aux != NULL){
		//verifica se ´e o mesmo tempo de entrada e/ou saida
		if(((aux->in_h * 60 + aux->in_m) == (atual->out_h * 60 + atual->out_m)) ||
		   ((aux->in_h * 60 + aux->in_m) == (atual->in_h * 60 + atual->in_m)) ||
		   ((aux->out_h * 60 + aux->out_m) == (atual->out_h * 60 + atual->out_m)) ||
		   ((aux->out_h * 60 + aux->out_m) == (atual->in_h * 60 + atual->in_m))){
			return(0);
		}
		aux = aux->prox;
	}

	if((*nAtual) == 0){
		empilha(pilha, atual);
		(*nAtual)++;
		if(*nAtual > capacidade){ //condiçao para verificar capacidade
				return(0);
		}

		return(1);
	}else{
		//verifica se carros anteriores sairam antes de o atual entrar
		if((pilha->topo->out_h * 60 + pilha->topo->out_m) < (atual->in_h * 60 + atual->in_m)){
			while(pilha->topo != NULL && (pilha->topo->out_h * 60 + pilha->topo->out_m) < (atual->in_h * 60 + atual->in_m)){
				desempilha(pilha);
				(*nAtual)--;
			}

			if( pilha->topo != NULL && (
				(pilha->topo->in_h * 60 + pilha->topo->in_m) > (atual->in_h * 60 + atual->in_m) ||
				(pilha->topo->out_h * 60 + pilha->topo->out_m) < (atual->out_h * 60 + atual->out_m))){
				return(0);
			}

			empilha(pilha, atual);
			(*nAtual)++;

			if(*nAtual > capacidade){ //condiçao para verificar capacidade
				return(0);
			}

			return(1);
		}
		//se nenhuma das anteriores, apenas empilha
		else{

			if( pilha->topo != NULL && (
				(pilha->topo->in_h * 60 + pilha->topo->in_m) > (atual->in_h * 60 + atual->in_m) ||
				(pilha->topo->out_h * 60 + pilha->topo->out_m) < (atual->out_h * 60 + atual->out_m))){
				return(0);
			}

			empilha(pilha, atual);
			(*nAtual)++;

			if(*nAtual > capacidade){ //condiçao para verificar capacidade
				return(0);
			}

			return(1);
		}
	}
}

void empilha(Relatorio *pilha, Carro *atual){
	Carro *aux = (Carro *) malloc (sizeof(Carro));

	*aux = *atual;

	if(pilha->topo == NULL){
		aux->prox = NULL;
		pilha->topo = aux;
	}else{
		aux->prox = pilha->topo;
		pilha->topo = aux;
	}
}

void desempilha(Relatorio *pilha){
	Carro *aux;

	aux = pilha->topo;
	pilha->topo = pilha->topo->prox;
	free(aux);
}

void enfileiraRelatorios(FilaRelatorios *fila, Relatorio *relatorio){
	if(fila->inicio == NULL){
		fila->inicio = relatorio;
		fila->fim = fila->inicio;
	}else{
		fila->fim->prox = relatorio;
		fila->fim = relatorio;
	}
}

//verifica a existencia de um relatorio. Serve para busca e para inserçao
Relatorio *buscaRelatorio(FilaRelatorios *fila, Relatorio *relatorio, char nome[]){
	Relatorio *aux = fila->inicio;

	while(aux != NULL){
		if(strcmp(aux->nome, nome) == 0){
			relatorio = aux;
			return(aux);
		}
		aux = aux->prox;
	}

	return(aux);
}

int buscaCarro(Relatorio *relatorio, char placa[]){
	Carro *carro = relatorio->topo;

	while(carro != NULL){
		if(strcmp(carro->placa, placa) == 0){
			printf(MSG_EXIBE_HORARIO, carro->in_h, carro->in_m, carro->out_h, carro->out_m);
			return(1);
		}
		carro = carro->prox;
	}

	return(0);
}

void liberaRelatorios(FilaRelatorios *relatorios){
	Relatorio *aux;

	while(relatorios->inicio != NULL){
		liberaCarros(relatorios->inicio->topo);
		aux = relatorios->inicio;
		relatorios->inicio = relatorios->inicio->prox;
		free(aux);
	}
}

void liberaCarros(Carro *topo){
	Carro *aux;

	while(topo != NULL){
		aux = topo;
		topo = topo->prox;
		free(aux);
	}
}
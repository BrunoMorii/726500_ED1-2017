/* Universidade Federal de Sao Carlos - UFSCar, Sorocaba

  Disciplina: Estruturas de Dados 1
  Prof. Tiago A. Almeida

  Exercício 3 - (TAD Pilha) Calculadora Pós-Fixada

  Instrucoes
  ----------

  Este arquivo contem o codigo que auxiliara no desenvolvimento do
  exercicio. Voce precisara completar as funcoes requisitadas.

  Voce nao podera criar nenhuma outra funcao. Complete apenas as rotinas
  fornecidas.                             */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************/

// Implemente aqui as suas estruturas de dados
#define OPERADOR 1
#define OPERANDO 2

typedef struct eq{
	int tipo;
	char operando_operador;
	float valorOperando;
	struct eq *prox;
}Equacao;

typedef struct in{
	Equacao *topo;
	int tamanho;
}inicioPilha;

typedef struct val{
	float valor;
	struct val *prox;
}Valor;

typedef struct val_{
	Valor *topo;
}inicioValor;


/************************************************/

// Implemente aqui as suas funcoes e procedimentos

void empilhaPrincipal(inicioPilha *Pilha, char c);

void empilhaValores(inicioValor *Valores, inicioPilha *Pilha);

void atribuiValores(inicioValor *Valores, inicioPilha *Pilha);

float desempilhaValores(inicioValor *Valores);

float calcular(inicioPilha *Pilha);

void invertePilha(inicioPilha *Pilha);

float desempilhaPilha(inicioPilha *Pilha);

void liberaPilha(inicioPilha * Pilha);

/*void printa(inicioPilha *Pilha){
	Equacao *aux = Pilha->topo;

	while(aux != NULL){
		printf("%.f ", aux->valorOperando);
		aux = aux->prox;
	}
	printf("fim pilha---------\n");
}*/

/************************************************/

int main(){
	// Implemente aqui o seu programa principal

	inicioPilha *pilha_principal;
	inicioValor *pilha_valores;
	//Equacao *aux;
	char c;

	//Rotina para inicializar pilhas
	pilha_principal = (inicioPilha *) malloc (sizeof(inicioPilha));
	pilha_principal->topo = NULL;
	pilha_principal->tamanho = 0;
	pilha_valores = (inicioValor *) malloc (sizeof(inicioValor));
	pilha_valores->topo = NULL;

	//Rotina para receber a equaçao
	scanf("%c", &c);

	while(c != '\n'){
		empilhaPrincipal(pilha_principal, c);
		scanf("%c", &c);
	}

	empilhaValores(pilha_valores, pilha_principal);

	atribuiValores(pilha_valores, pilha_principal);

	//libera apontador de pilha de valores que ja ta fazia
	free(pilha_valores);

	invertePilha(pilha_principal);
	/*
	//rotina auxiliar para testes
	aux = pilha_principal->topo;
	while(aux != NULL){
		printf("%d %c ", aux->tipo, aux->operando_operador);
		if(aux->tipo == 2){
			printf("%f\n", aux->valorOperando);
		}else{
			printf("\n");
		}
		aux = aux->prox;
	}
	printf("%d\n", pilha_principal->tamanho);*/

	printf("%f\n", calcular(pilha_principal));

	liberaPilha(pilha_principal);
 
	return (0);
}

//ROTINA DE FUNÇOES 

void empilhaPrincipal(inicioPilha *Pilha, char c){
	Equacao *aux = (Equacao *) malloc (sizeof(Equacao));

	aux->operando_operador = c;
	if( c == '*' || c == '-' || c == '/' || c == '+'){
		aux->tipo = OPERADOR;
	}else{
		aux->tipo = OPERANDO;
	}

	if(Pilha == NULL){
		aux->prox = NULL;
		Pilha->topo = aux;
	}else{
		aux->prox = Pilha->topo;
		Pilha->topo = aux;
	}

	Pilha->tamanho++;
}

void empilhaValores(inicioValor *Valores, inicioPilha *Pilha){
	Equacao *aux = Pilha->topo;
	Valor *aux2;

	while(aux != NULL){
		while((aux->tipo == 1) && (aux != NULL)){
			aux = aux->prox;
		}
		
		if(aux != NULL){
			if(Valores->topo == NULL){
				aux2 = (Valor *) malloc (sizeof(Valor));
				scanf("%f", &aux2->valor);
				aux2->prox = NULL;
				Valores->topo = aux2;
			}else{
				aux2 = (Valor *) malloc (sizeof(Valor));
				scanf("%f", &aux2->valor);
				aux2->prox = Valores->topo;
				Valores->topo = aux2;
			}
			aux = aux->prox;
		}
	}
}

void atribuiValores(inicioValor *Valores, inicioPilha *Pilha){
	Equacao *aux = (Equacao *) malloc (sizeof(Equacao));

	aux = Pilha->topo;

	while(aux != NULL){
		while((aux->tipo == 1) && (aux != NULL)){
			aux = aux->prox;
		}
		
		if(aux != NULL){
			aux->valorOperando = desempilhaValores(Valores);
			aux = aux->prox;
		}
	}
}

float desempilhaValores(inicioValor *Valores){
	float valor;
	Valor *aux;

	valor = Valores->topo->valor;
	aux = Valores->topo;
	Valores->topo = Valores->topo->prox;
	free(aux);

	return(valor);
}

void invertePilha(inicioPilha *Pilha){
	Equacao *aux;
	inicioPilha *ap = (inicioPilha *) malloc (sizeof(inicioPilha));

	ap->topo = NULL;

	while(Pilha->topo != NULL){
		if(ap->topo == NULL){
			aux = Pilha->topo;
			Pilha->topo = Pilha->topo->prox;
			aux->prox = NULL;
			ap->topo = aux;
		}else{
			aux = Pilha->topo;
			Pilha->topo = Pilha->topo->prox;
			aux->prox = ap->topo;
			ap->topo = aux;
		}
	}

	Pilha->topo = ap->topo;
}

float calcular(inicioPilha *Pilha){
	Equacao *aux2;
	inicioPilha *operandos = (inicioPilha *) malloc (sizeof(inicioPilha));
	float resultado = 0, a, b;
	int i;

	operandos->topo = NULL;

	for(i = 0; i < Pilha->tamanho; i++){
		if(Pilha->topo->tipo == OPERANDO){
			if(operandos->topo == NULL){
				aux2 = (Equacao *) malloc (sizeof(Equacao));
				aux2->valorOperando = desempilhaPilha(Pilha);
				aux2->prox = NULL;
				operandos->topo = aux2;
			}else{
				aux2 = (Equacao *) malloc (sizeof(Equacao));
				aux2->valorOperando = desempilhaPilha(Pilha);
				aux2->prox = operandos->topo;
				operandos->topo = aux2;
			}
		}else{
			a = desempilhaPilha(operandos); 
			b = desempilhaPilha(operandos);
		
			if(Pilha->topo->operando_operador == '*'){
				resultado = a * b;
			}else if(Pilha->topo->operando_operador == '+'){
				resultado = a + b;
			}else if(Pilha->topo->operando_operador == '-'){
				resultado = b - a;
			}else{
				resultado = b / a;
			}
			desempilhaPilha(Pilha);

			aux2 = (Equacao *) malloc (sizeof(Equacao));
			aux2->valorOperando = resultado;
			aux2->prox = operandos->topo;
			operandos->topo = aux2;
		}
		
	}

	return(resultado);
}

float desempilhaPilha(inicioPilha *Pilha){
	float valor;
	Equacao *aux = Pilha->topo;

	valor = Pilha->topo->valorOperando;
	aux = Pilha->topo;
	Pilha->topo = Pilha->topo->prox;
	free(aux);

	return(valor);
}

void liberaPilha(inicioPilha * Pilha){
	Equacao *aux = Pilha->topo, *aux2;

	while(aux != NULL){
		aux2 = aux;
		free(aux2);
		aux = aux->prox;
	}
}
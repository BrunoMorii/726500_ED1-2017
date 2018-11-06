/* ================================================================== *
    Universidade Federal de Sao Carlos - UFSCar, Sorocaba

    Disciplina: Estruturas de dados 1
    Prof. Tiago A. Almeida

    Exercício: K-Nearest Neighboors

    Instrucoes
    ----------

    Este arquivo contem o codigo que auxiliara no desenvolvimento do
    exercicio. Voce precisara completar as partes requisitadas.
* ================================================================== */

#include <stdio.h>
#include <math.h>		// funcao de equacao de distancia euclidiana

#define MAX_PONTOS	100000	// numero maximo de pontos


// --- DEFINICAO DO TAD ---
// <<< DEFINA AQUI O TAD PONTO >>>
typedef struct ponto
{
	int x;
	int y;
}Ponto;

void receberPontos(Ponto *pontos, int N);
int acharProximo(Ponto *pontos, Ponto Pr, int N);
void imprimir(Ponto *pontos, Ponto Pr, int indice);

// --- PROTOTIPO DAS FUNCOES
float calcularDistancia(Ponto p1, Ponto p2);
// <<< DEFINA AQUI AS DEMAIS FUNCOES >>>

// --- FUNCAO PRINCIPAL
int main(){

	// <<< IMPLEMENTE O CODIGO AQUI >>>
	Ponto vetPontos[100000], Pr;
	unsigned int numPontos;

	scanf("%u", &numPontos);

	receberPontos(vetPontos, numPontos);
	
	scanf("%d %d", &Pr.x, &Pr.y);

	imprimir(vetPontos, Pr, acharProximo(vetPontos, Pr, numPontos));

	return (0);
}




/* -------------------------
   IMPLEMENTACAO DAS FUNCOES
   -------------------------*/


float calcularDistancia(Ponto p1, Ponto p2){
	float dist;

	dist = sqrt(pow(p1.x - p2.x, 2.0) + pow(p1.y - p2.y, 2.0));

	return(dist);
}

// <<< IMPLEMENTE AQUI AS DEMAIS FUNCOES >>>

void receberPontos(Ponto *pontos, int N){ //funç~ao para receber pontos
	int i;

	for(i = 0; i < N; i++){
		scanf("%d %d", &pontos[i].x, &pontos[i].y);
	}
}

int acharProximo(Ponto *pontos, Ponto Pr, int N){
	int ponto_proximo, i;
	float menor_dist;

	menor_dist = calcularDistancia(Pr, pontos[0]);

	for(i = 1; i < N; i++){
		if(calcularDistancia(Pr, pontos[i]) < menor_dist){
			menor_dist = calcularDistancia(Pr, pontos[i]);
			ponto_proximo = i;
		}
	}

	return(ponto_proximo);
}

void imprimir(Ponto *pontos, Ponto Pr, int indice){

	printf("%.d %.d\n%.2f\n", pontos[indice].x, pontos[indice].y, calcularDistancia(Pr, pontos[indice]));

}
/* ================================================================== *
	Universidade Federal de Sao Carlos - UFSCar, Sorocaba

	Disciplina: Estruturas de Dados 1
	Prof. Tiago A. Almeida

	Exercício 12 - Gerenciador Estratégico

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

// Frases pre-definidas
#define MSG_ERRO_ALOC 		"Erro de alocacao!\n"
#define MSG_NAO_EXISTE_POS	"Posição inexistente!\n"
#define MSG_NAO_EXISTE_LC 	"Linha/coluna inexistente!\n"
#define MSG_NAO_EXISTE_MT	"Matriz inexistente!\n"
#define MSG_INCOMPATIVEL	"Dimensões incompatíveis!\n"
#define MSG_OPCAO_INV 		"Opcao invalida!\n"



// === TAD E DEMAIS REGISTROS ===
// <<< NAO ALTERAR >>>

typedef float TItem;

typedef struct SCelula *TApontador;

typedef struct SCelula
{
	int Linha, Coluna;
	TItem Item;
	TApontador Abaixo, Direita;
}
TCelula;

typedef struct
{
	TApontador Cabeca;
	int NLinhas, NColunas;
}
TMatriz;



/* ================================================================== */
/* ===================== PREAMBULO DAS FUNCOES ====================== */
/* ================================================================== */

// <<< COLOQUE O PREAMBULO DAS FUNCOES >>>

TCelula *fazMatriz(int n, int m);
void liberaMatriz(TMatriz *matriz);


/* ================================================================== */
/* ======================== ROTINA PRINCIPAL ======================== */
/* ================================================================== */

int main(){

	// <<< IMPLEMENTE AQUI A ROTINA PRINCIPAL>>>
	TMatriz matrizes[5];
	TCelula *matriz;
	int i, opc, n, m;

	for(i = 1; i < 5; i++){
		matrizes[i].Cabeca = NULL;
	}

	do{
		scanf("%d", &opc);

		switch(opc){
			//inserir matriz
			case 1:
				scanf("%d %d %d", &i, &n, &m);
				matriz = fazMatriz(n, m);
				if(matriz[i].Cabeca == NULL){
					matriz[i].Cabeca = matriz;
				}else{
					liberaMatriz(matrizes[i].Cabeca);
					matriz[i].Cabeca = matriz;
				}
				break;

			//alterar posicao
			case 2:

				break;

			//soma de linha
			case 3:

				break;

			//soma de colunas
			case 4:

				break;

			//busca por maximo
			case 5:

				break;

			//busca por minimo
			case 6:

				break;

			//soma de matriz
			case 7:

				break;

			//transposiçao
			case 8:

				break;

			//exibicao de posicao
			case 9:

				break;

			//exibicao de linha/coluna
			case 10:

				break;

			//sair
			case 11:

				break;

			default:
				printf("MSG_OPCAO_INV");

		}
	}while(opc != 11);

	return (0);
}



/* ================================================================== */
/* ========== FUNCOES QUE DETERMINAM AS OPERACOES POSSIVEIS ========= */
/* ================================================================== */

// <<< IMPLEMENTE AQUI AS FUNCOES >>>
TCelula *fazMatriz(int n, int m){
	TApontador cabeca, aux, aux2;
	int i;

	cabeca->Linha = -1;
	cabeca->Coluna = -1;
	aux2 = cabeca;

	for(i = 1; i < n; i++){
		aux = (TCelula *) malloc (sizeof(TCelula));
		aux->Linha = -1;
		aux->Coluna = i;
		aux2->Direita = aux;
		aux2 = aux;
	}
}

void liberaMatriz(TMatriz *matriz){

}
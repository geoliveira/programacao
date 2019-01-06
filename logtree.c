#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logtree.h"

//Inicializa o registrador l.
void log_inicializar(Log **l) {
	*l = NULL;
}

void log_registrar(Log **l, int conta, int classe, int timer, int caixa) {
	Log *no = (Log*) malloc(sizeof(Log));
	(*no).conta = conta;
	(*no).classe = classe;
	(*no).timer = timer;
	(*no).caixa = caixa;
	(*no).esq = NULL;
	(*no).dir = NULL;
	(*no).pai = NULL;
	
	if (*l == NULL)	{
		*l = no;
	} else {
		Log *aux = *l, *aux2 = NULL;

		// Percorremos a arvore até chegar em um nó folha
		while (aux != NULL) {
			aux2 =  aux; // Guarda o valor do nó

			if (conta < (*aux).conta) 
				aux = (*aux).esq;
			else
				aux = (*aux).dir;
		}
		//aux2 é o nó pai do inserido
		if (conta > (*aux2).conta)
			(*aux2).dir = no;
		else 
			(*aux2).esq = no;

		(*no).pai = aux2;
	}
}

//Percorremos toda a arvore salvando os valores dos nós cujos têm valores dos clientes da classe desejada
float log_media_por_classe(Log **l, int classe) {
	if (*l == NULL) return 0;
	
	Log *aux = minimo(*l); // Começamos pelo minímo até chegar ao máximo, e assim percorrendo toda a árvore
	double s = 0,n = 0; //O tipo double garante o dado

	while (aux != NULL) {
		if ((*aux).classe == classe) {
			n++;
			s += (*aux).timer;
		}

		aux = sucessor(*l, (*aux).conta); // Função sucessor() é necessária para percorrer todo os nós da árvore
	}

	return (s/n);
}

// Segue a lógica da função float log_media_por_classe(Log **l, int classe)
int log_obter_soma_por_classe(Log **l, int classe) {
	if (*l == NULL) return 0;
	
	Log *aux = minimo(*l);// Começamos pelo minímo até chegar ao máximo, e assim percorrendo toda a árvore
	int s = 0;

	while (aux != NULL) {
		if ((*aux).classe == classe) s += (*aux).timer;

		aux = sucessor(*l, (*aux).conta);// Função sucessor() é necessária para percorrer todo os nós da árvore
	}

	return s;
}

// Segue a lógica da função
int log_obter_contagem_por_classe(Log **l, int classe) {
	if (*l == NULL) return 0;
	
	Log *aux = minimo(*l);// Começamos pelo minímo até chegar ao máximo, e assim percorrendo toda a árvore
	int n = 0;

	while (aux != NULL) {
		if ((*aux).classe == classe)
			n++;

		aux = sucessor(*l, (*aux).conta);// Função sucessor() é necessária para percorrer todo os nós da árvore
	}

	return n;
}

// #################################################### FUNÇÕES ADD ####################################################
//Funções adicionais usadas para percorremos a arvore

Log *minimo(Log *no) {
	if (no == NULL) return 0;
	
	Log *aux = no;

	while ((*aux).esq != NULL)
		aux = (*aux).esq;
	
	return aux;
}

Log *sucessor(Log *no, int conta) {
	Log *aux2, *aux = buscar(no, conta);

	if ((*aux).dir != NULL || (*aux).pai == NULL) {
		return minimo((*aux).dir);
	}
	else {
		if ((*aux).pai->esq == aux){
			return (*aux).pai;
		}
		else {
			Log *aux2 = (*aux).pai;
			
			while ((*aux2).pai != NULL && (*aux2).pai->dir == aux2)
				aux2 = (*aux2).pai;

			return (*aux2).pai;
		}
	}
}

//Função é usada na função Log *sucessor(Log *no, int conta)
Log *buscar(Log *raiz, int conta) {
	Log *aux = raiz;

	while (aux != NULL && (*aux).conta != conta)
		if (conta > (*aux).conta)
			aux = (*aux).dir;
		else
			aux = (*aux).esq;
		
	return aux;
}
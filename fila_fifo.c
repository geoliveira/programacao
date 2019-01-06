#include <stdio.h>
#include <stdlib.h>
#include "fila_fifo.h"

//Inicializa o ponteiro para o nó cabeça 
void f_inicializar (Fila_FIFO **f) {
	*f = NULL;
}

//Inseri na lista caso não tenha chave duplicada e não falte memória
int f_inserir (Fila_FIFO **f, int chave, int valor) {
	Fila_FIFO *novo = (Fila_FIFO*) malloc(sizeof(Fila_FIFO));
	
	if (novo == NULL) return 0; // Falha, pois não há mais memória

	(*novo).chave = chave;
	(*novo).valor = valor;

	if (*f == NULL) {
		(*novo).prox = NULL;
		*f = novo;

		return 1;
	}
	
	Fila_FIFO *aux, *aux2 = *f;

	//Percorre a lista até o último elemento
	while (aux2 != NULL) {
		aux = aux2; //Guarda elemento e passa para o próximo próximo da lista

		if ((*aux2).chave == chave) return 0; // Retorna 0 pois não é permitido nó com mesmo valor de chave

		aux2 = (*aux2).prox;
	}
	//aux é o último elemento da lista
	(*aux).prox = novo;

	return 1;
}

int f_obter_proxima_chave (Fila_FIFO **f) { 
	if (*f == NULL) return -1;

	Fila_FIFO *aux = *f;

	int x = (*aux).chave;

	*f = (*aux).prox;
	
	free(aux); // Libera espaço do nó cabeça
	
	return x;
}

int f_consultar_proxima_chave (Fila_FIFO **f) {
	if (*f == NULL) return -1;	
	
	Fila_FIFO *aux = *f;
	
	return (*aux).chave;
}

int f_consultar_proximo_valor (Fila_FIFO **f) {
	if (*f == NULL) return -1;

	Fila_FIFO *aux = *f;
	
	return (*aux).valor;
}

int f_num_elementos (Fila_FIFO **f) {
	Fila_FIFO *aux = *f;
	int i = 0;

	//Percorre a lista até o final
	while (aux != NULL) {
		i++;
		aux = (*aux).prox;
	}

	return i;
}

int f_consultar_chave_por_posicao (Fila_FIFO **f, int posicao) {
	if (*f == NULL) return -1;

	Fila_FIFO *aux = *f;
	int i = 1;

	// Percorre a lista até i = posição dentro dos limites da lista
	for (i=1; i < posicao && aux != NULL; i++) aux = (*aux).prox;

	// Não percorremos toda a lista e tivermos encontrado a chave na posição desejada
	if (aux != NULL && i == posicao) return (*aux).chave;

	return -1;
}

int f_consultar_valor_por_posicao (Fila_FIFO **f, int posicao) {
	if (*f == NULL) return -1;

	Fila_FIFO *aux = *f;
	int i = 1;

	// Percorre a lista até i = posição dentro dos limites da lista
	for (i=1; i < posicao && aux != NULL; i++) aux = (*aux).prox;

	// Não percorremos toda a lista e tivermos encontrado o valor na posição desejada
	if (aux != NULL && i == posicao) return (*aux).valor;

	return -1;
}
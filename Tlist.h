#include <stdlib.h>
#include <stdio.h>

typedef struct nodo
{
	int info;
	struct nodo *sig;
} tnodo;

typedef struct list
{
	tnodo *head;
	tnodo *tail;
	tnodo *curr;
	int largo;
	int pos;
} Tlist;

Tlist *crear_lista(){
	Tlist *A;
	 A = (Tlist *)malloc(sizeof(Tlist));
	return A;
}

void printlista(Tlist *L)
{
	if (L->largo == 0)
	{
		printf("#\t\t\tLista vacia\t\t\t#\n");
		return;
	}
	tnodo *aux = L->head;
	printf(">> [ ");
	for (int i = 0; i < L->largo; i++)
	{
		printf("%d ",aux->sig->info);
		aux = aux->sig;
	}
	printf("]\n");
	printf(">>> Largo lista: %d\n",L->largo);
	printf(">>> Memoria utilizada: %ld bytes\n",sizeof(tnodo)*(L->largo+1));
	return;
}

void eliminar_lista(Tlist *L)
{
	if (L->largo == 0) return;
	tnodo *aux;
	if (L->curr == L->tail)
	{
		free((void *)L->tail);
		L->tail = L->curr;
		L->largo--;
		return;
	}
	aux = L->curr->sig->sig;
	free((void *)L->curr->sig);
	L->curr->sig = aux;
	L->largo--;
	return;
}

int getval(Tlist *L)
{
	if (L->curr == L->tail)
	{
		return L->curr->info;
	}
	return L->curr->sig->info;
}

void next(Tlist *L)
{
	if (L->curr == L->tail){
		return;
	}
	L->curr = L->curr->sig;
	L->pos++;
	return;
}

void prev(Tlist *L)
{
	if (L->curr == L->head) return;
	L->curr = L->head;
	int i;
	for (i = 0; i < L->pos-1; i++)	L->curr = L->curr->sig;
	L->pos = L->pos-1;
}

int buscar(int item, Tlist *L)
{
	if (L->largo == 0) return 0;
	tnodo *aux = L->head;
	int i;
	for (i = 0; i < L->largo; i++)
	{
		aux = aux->sig;
		if (aux->info == item) return 1;
	}
	return 0;
}

void toHome(Tlist *L)
{
	L->curr = L->head;
	return;
}

int getlarge(Tlist *L)
{
	return L->largo;
}


void insertar(int item, Tlist* L)
{
	tnodo *aux;
	if (L->head == NULL)
	{
		L->head = (tnodo *)calloc(1,sizeof(tnodo));
		L->curr = L->head;
		L->tail = L->head;
	}
	if (L->largo == 0)
	{
		L->curr->sig = (tnodo *)calloc(1,sizeof(tnodo));
		L->curr->sig->info = item;
		L->tail = L->curr->sig;
		L->largo++;
		return;
	}
	aux = (tnodo *)calloc(1,sizeof(tnodo));
	aux->info = item;
	aux->sig = L->curr->sig;
	L->curr->sig = aux;
	if (L->curr == L->tail)
	{
		L->tail = L->curr->sig;
	}
	L->largo++;
}

void erase_lista(Tlist *L){
	if (L->largo == 0)
	{
		free((void *)L->head);
		return;
	}
	int i;
	while(L->largo > 0)
	{
		tnodo *aux = L->head;
		for (i = 0; i < L->largo; i++)
		{
			aux = aux->sig;
		}
		free((void *)aux);
		L->largo--;
	}
	free((void *)L->head);
	return;
}

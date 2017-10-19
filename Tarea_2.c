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

typedef struct dispersa
{
	int n_elem;
	int n_filas;
	int n_col;
	Tlist *Filas;
	Tlist *Columnas;
	Tlist *Valores;
}Matriz;

Matriz *crear_matriz(){
	Matriz *A;
	A = (Matriz *)malloc(sizeof(Matriz));
	A->Valores = crear_lista();
	A->Filas = crear_lista();
	A->Columnas = crear_lista();
	A->n_elem = 0;
	A->n_filas = 0;
	A->n_col = 0;
	return A;
}

void print_info(Matriz *A){
	printf("Numero de elementos: %d\n",A->n_elem);
	printf("Numero de filas: %d\n",A->n_filas);
	printf("Numero de columnas: %d\n",A->n_col);
}

Matriz *swap_m_n(Matriz *A){
	Matriz *B;
	int i;
	B = crear_matriz();
	B->n_elem = A->n_elem;
	B->n_filas = A->n_col;
	B->n_col = A->n_filas;
	toHome(A->Valores);
	toHome(A->Filas);
	toHome(A->Columnas);
	for (i = 0; i < A->n_elem; i++)
	{
		insertar(getval(A->Valores),B->Valores);
		insertar(getval(A->Filas),B->Columnas);
		insertar(getval(A->Columnas),B->Filas);
		next(A->Valores);
		next(A->Filas);
		next(A->Columnas);
	}
	return B;
}

int input_val(int i, int j, int val, int sum, Matriz *A){
	if (i > A->n_filas) return 0;
	if (j > A->n_col) return 0;
	if (sum == 1)
	{
		toHome(A->Filas);
		toHome(A->Columnas);
		toHome(A->Valores);
		int a;
		for (a = 0; a < A->n_elem; a++)
		{
			if (getval(A->Filas) == i && j == getval(A->Columnas)){
				A->Valores->curr->sig->info = A->Valores->curr->sig->info + val;
				return 1;
			}
		next(A->Filas);
		next(A->Columnas);
		next(A->Valores);
		}
	}
	if (sum == 0)
	{
		toHome(A->Filas);
		toHome(A->Columnas);
		toHome(A->Valores);
		int a;
		for (a = 0; a < A->n_elem; a++)
		{
			if (getval(A->Filas) == i && j == getval(A->Columnas))
			{
				A->Valores->curr->sig->info = val;
				return 1;
			}
		next(A->Filas);
		next(A->Columnas);
		next(A->Valores);
		}
	}
	insertar(val,A->Valores);
	insertar(i,A->Filas);
	insertar(j,A->Columnas);
	A->n_elem = A->n_elem + 1;
	return 1;
}

void set_limit(int fil, int col, Matriz *A){
	A->n_filas = fil;
	A->n_col = col;
}

Matriz *diag(Matriz *A){
	int i,a;
	Matriz *B;
	B = crear_matriz();
	set_limit(A->n_filas,A->n_col,B);
	toHome(A->Filas);
	toHome(A->Columnas);
	toHome(A->Valores);
	a = A->n_elem;
	for (i = 0; i < A->n_elem; i++)
	{
		if(getval(A->Filas)!=getval(A->Columnas)){
			a--;
		}
		else{
			input_val(getval(A->Filas),getval(A->Columnas),getval(A->Valores),0,B);
		}
		next(A->Filas);
		next(A->Columnas);
		next(A->Valores);
	}
	B->n_elem=a;
	return B;
}

void print_dispersa(Matriz *A){
	int i;
	int val,fila,col;
	printf("---------------------\n");
	printf("Matriz Dispersa\n");
	printf("---------------------\n");
	printf("Numero de elementos: %d\n",A->n_elem);
	printf("Numero de filas: %d\n",A->n_filas);
	printf("Numero de columnas: %d\n",A->n_col);
	toHome(A->Valores);
	toHome(A->Filas);
	toHome(A->Columnas);
	for (i = 0; i < A->n_elem; i++)
	{
		val = getval(A->Valores);
		fila = getval(A->Filas);
		col = getval(A->Columnas);
		printf("(%d,%d) = %d\n",fila,col,val);
		next(A->Valores);
		next(A->Filas);
		next(A->Columnas);
	}
	printf("---------------------\n");
}

void* alloc_dispersa(int m, int n){
	Matriz *A;
	A = crear_matriz();
	set_limit(m,n,A);
	return (void *)A;
}

void free_dispersa(void* A){
	erase_lista(((Matriz *)A)->Valores);
	erase_lista(((Matriz *)A)->Filas);
	erase_lista(((Matriz *)A)->Columnas);
	free((void*)A);
	return;
}

int ingresar_valor(void* A, int i, int j, int valor){
	return input_val(i,j,valor,0,(Matriz *)A);
}

void imprimir_matriz(void* A);

void* suma(void* A, void* B);

void* multiplicacion(void* A, void* B);

void binaria(void* (*fun)(void*,void*), void* A, void* B);

void* Trasponer(void* A);

void* diagonal(void* A){
	
}

void unaria(void* (*fun)(void*), void* A);

void element_wise_op(int (*fun)(int), void* A);

int main(int argc, char const *argv[])
{
	Matriz *B;
	B = (Matriz *)alloc_dispersa(3,3);
	set_limit(3,3,B);
	ingresar_valor((void *)B,3,3,14);
	ingresar_valor((void *)B,1,2,21);
	ingresar_valor((void *)B,3,2,11);
	ingresar_valor((void *)B,2,2,-4);
	print_dispersa(B);
	free_dispersa(B);
	return 0;
}

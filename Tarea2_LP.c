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
	Tlist *Aux = ((Matriz *)A)->Valores;
	free((void*)Aux);
	Aux = ((Matriz *)A)->Columnas;
	free((void*)Aux);
	Aux = ((Matriz *)A)->Filas;
	free((void*)Aux);
	free((void*)A);
	return;
}

int ingresar_valor(void* A, int i, int j, int valor){
	return input_val(i,j,valor,0,(Matriz *)A);
}

void imprimir_matriz(void* A){
	print_dispersa((Matriz *)A);
	return;
}

void* suma(void* A, void* B){
	Matriz *D;
	D = (Matriz*)alloc_dispersa(((Matriz *)A)->n_filas,((Matriz *)A)->n_col);
	int i;
	int elem_A = ((Matriz *)A)->n_elem;
	int elem_B = ((Matriz *)B)->n_elem;
	toHome(((Matriz *)A)->Valores);
	toHome(((Matriz *)A)->Filas);
	toHome(((Matriz *)A)->Columnas);
	for (i = 0; i < elem_A; i++)
	{
		input_val(getval(((Matriz *)A)->Filas),getval(((Matriz *)A)->Columnas),getval(((Matriz *)A)->Valores),0,D);
		next(((Matriz *)A)->Valores);
		next(((Matriz *)A)->Filas);
		next(((Matriz *)A)->Columnas);
	}
	toHome(((Matriz *)B)->Valores);
	toHome(((Matriz *)B)->Filas);
	toHome(((Matriz *)B)->Columnas);
	for (i = 0; i < elem_B; i++)
	{
		input_val(getval(((Matriz *)B)->Filas),getval(((Matriz *)B)->Columnas),getval(((Matriz *)B)->Valores),1,D);
		next(((Matriz *)B)->Valores);
		next(((Matriz *)B)->Filas);
		next(((Matriz *)B)->Columnas);
	}
	return (void *)D;
}

void* multiplicacion(void* A, void* B){
	Matriz *C;
	C = (Matriz *)alloc_dispersa(((Matriz *)A)->n_filas,((Matriz *)B)->n_col);
	int i,valor,fila,j;
	toHome(((Matriz *)A)->Valores);
	toHome(((Matriz *)A)->Filas);
	toHome(((Matriz *)A)->Columnas);
	toHome(((Matriz *)B)->Valores);
	toHome(((Matriz *)B)->Filas);
	toHome(((Matriz *)B)->Columnas);
	for (i = 0; i < ((Matriz *)A)->n_elem; i++)
	{
		for (j = 0; j < ((Matriz *)B)->n_elem; j++)
		{
			if (getval(((Matriz *)A)->Columnas)==getval(((Matriz *)B)->Filas))
			{
				input_val(getval(((Matriz *)A)->Filas),getval(((Matriz *)B)->Columnas),getval(((Matriz *)A)->Valores)*getval(((Matriz *)B)->Valores),1,C);
			}
			next(((Matriz *)B)->Valores);
			next(((Matriz *)B)->Filas);
			next(((Matriz *)B)->Columnas);
		}
		toHome(((Matriz *)B)->Valores);
		toHome(((Matriz *)B)->Filas);
		toHome(((Matriz *)B)->Columnas);
		next(((Matriz *)A)->Valores);
		next(((Matriz *)A)->Filas);
		next(((Matriz *)A)->Columnas);
	}
	return C;
}

void binaria(void* (*fun)(void*,void*), void* A, void* B);

void* Trasponer(void* A);

void* diagonal(void* A){
	Matriz *B;
	B = diag((Matriz *)A);
	return B;
}

void unaria(void* (*fun)(void*), void* A);

void element_wise_op(int (*fun)(int), void* A);

int main(int argc, char const *argv[])
{
	Matriz *A;
	Matriz *B;
	Matriz *C;
	A = (Matriz *)alloc_dispersa(3,3);
	B = (Matriz *)alloc_dispersa(3,3);
	ingresar_valor((void *)A,1,1,2);
	ingresar_valor((void *)A,1,3,2);
	ingresar_valor((void *)A,2,1,1);
	ingresar_valor((void *)A,2,2,1);
	ingresar_valor((void *)A,2,3,1);
	ingresar_valor((void *)A,3,1,2);
	ingresar_valor((void *)A,3,3,1);
	ingresar_valor((void *)B,1,1,1);
	ingresar_valor((void *)B,1,2,1);
	ingresar_valor((void *)B,1,3,1);
	ingresar_valor((void *)B,2,2,1);
	ingresar_valor((void *)B,2,3,2);
	ingresar_valor((void *)B,3,1,1);
	imprimir_matriz((void *)A);
	imprimir_matriz((void *)B);
	C = (Matriz *)multiplicacion((void *)A,(void *)B);
	imprimir_matriz(C);
	free_dispersa(B);
	free_dispersa(A);
	free_dispersa(C);
	return 0;
}

#include <stdlib.h>
#include <stdio.h>

/******** Struct: tnodo ********************
Descripcion: Nodo base de una lista
Composicion:
	info: Entero con el valor del nodo
	sig: Puntero hacia el siguiente nodo de la lista
************************************************/

typedef struct nodo
{
	int info;
	struct nodo *sig;
} tnodo;

/******** Struct: Tlist ********************
Descripcion: Estuctura la cual representa una lista
Composicion:
	head: Puntero que contiene la direccion de memoria del primer elemento de la lista
	curr: Puntero que contiene la direccion de memoria del elemento actual de la lista
	curr: puntero que contiene la direccion de memoria del elemento final de la lista
	largo: Entero que contiene el largo de la lista
	pos: Entero que contiene la posicion actual del curr dentro de la lista
************************************************/

typedef struct list
{
	tnodo *head;
	tnodo *tail;
	tnodo *curr;
	int largo;
	int pos;
} Tlist;

/******** Funcion: crear_lista ********************
Descripcion: Crea una estructura del tipo lista en memoria dinamica
Parametros: Ninguno
Retorno: Un puntero del tipo lista
************************************************/

Tlist *crear_lista(){
	Tlist *A;
	 A = (Tlist *)calloc(1,sizeof(Tlist));
	return A;
}

/******** Funcion: printlista ********************
Descripcion: Imprime los valores de una lista ademas de su tamaño y el espacio que ocupa en el heap
Parametros:
	L: Puntero hacia la lista a imprimir
Retorno: Ninguno
************************************************/

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

/******** Funcion: eliminar_lista ********************
Descripcion: borra el nodo en el cual se situa el curr dentro de la lista
Parametros:
	L: Puntero hacia la lista
Retorno: Ninguno
************************************************/

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

/******** Funcion: getval ********************
Descripcion: Retorna el valor del nodo donde se encuentra curr
Parametros:
	L: Puntero hacia la lista
Retorno: Valor de la lista en la poscion actual
************************************************/

int getval(Tlist *L)
{
	if (L->curr == L->tail)
	{
		return L->curr->info;
	}
	return L->curr->sig->info;
}

/******** Funcion: next  ********************
Descripcion: Mueve el puntero de curr al siguiente nodo en caso de no haber terminado la lista
Parametros:
	L: Puntero hacia la lista
Retorno: Ninguno
************************************************/

void next(Tlist *L)
{
	if (L->curr == L->tail){
		return;
	}
	L->curr = L->curr->sig;
	L->pos++;
	return;
}

/******** Funcion: prev  ********************
Descripcion: Mueve el puntero de curr al nodo anterior en caso de no estar en el principio de la lista
Parametros:
	L: Puntero hacia la lista
Retorno: Ninguno
************************************************/

void prev(Tlist *L)
{
	if (L->curr == L->head) return;
	L->curr = L->head;
	int i;
	for (i = 0; i < L->pos-1; i++)	L->curr = L->curr->sig;
	L->pos = L->pos-1;
}

/******** Funcion: buscar  ********************
Descripcion: Busca un entero en particular dentro de la lista
Parametros:
	item: entero a buscar dentro de la lista
	L: Puntero hacia la lista
Retorno: Un 1 en caso de estar el elemento o un 0 en caso contrario
************************************************/

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

/******** Funcion: toHome  ********************
Descripcion: Mueve el puntero de curr al nodo en el cual comienza la lista
Parametros:
	L: Puntero hacia la lista
Retorno: Ninguno
************************************************/

void toHome(Tlist *L)
{
	L->curr = L->head;
	return;
}

/******** Funcion: getlarge  ********************
Descripcion: Obtiene el valor correspondiente al largo de la lista
Parametros:
	L: Puntero hacia la lista
Retorno: Entero el cual representa el largo de nodos de la lista
************************************************/

int getlarge(Tlist *L)
{
	return L->largo;
}

/******** Funcion: insertar  ********************
Descripcion: Inserta un elemento en la posicion actual del curr
Parametros:
	item: entero a insertar dentro de la lista
	L: Puntero hacia la lista
Retorno: Ninguno
************************************************/

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

/******** Funcion: erase_lista  ********************
Descripcion: Elimina la lista completa de la memoria
Parametros:
	L: Puntero hacia la lista
Retorno: Ninguno
************************************************/

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

/******** Struct: Matriz ********************
Descripcion: Estuctura la cual representa una matriz
Composicion:
	n_elem: Entero el cual representa la cantidad de elementos de la matriz
	n_filas: Entero el cual representa la cantidad de filas de la matriz
	n_col: Entero el cual representa la cantidad de colas de la matriz
	Valores: Puntero a una lista el cual contiene los valores de la matriz
	Filas: Puntero a una lista el cual contiene las filas de los valores
	Columnas: Puntero a una lista el cual contiene las columnas de los valores
************************************************/

typedef struct dispersa
{
	int n_elem;
	int n_filas;
	int n_col;
	Tlist *Filas;
	Tlist *Columnas;
	Tlist *Valores;
}Matriz;

/******** Funcion: crear_matriz ********************
Descripcion: Crea una estructura del tipo matriz en memoria dinamica
Parametros: Ninguno
Retorno: Un puntero del tipo matriz
************************************************/

Matriz *crear_matriz(){
	Matriz *A;
	A = (Matriz *)calloc(1,sizeof(Matriz));
	A->Valores = crear_lista();
	A->Filas = crear_lista();
	A->Columnas = crear_lista();
	A->n_elem = 0;
	A->n_filas = 0;
	A->n_col = 0;
	return A;
}

/******** Funcion: print info ********************
Descripcion: Imprime en pantalla la informacion acerca de la matriz
Parametros:
	A: Puntero a la matriz
Retorno: Ninguno
************************************************/

void print_info(Matriz *A){
	printf("Numero de elementos: %d\n",A->n_elem);
	printf("Numero de filas: %d\n",A->n_filas);
	printf("Numero de columnas: %d\n",A->n_col);
}

/******** Funcion: swap_m_n ********************
Descripcion: Cambia las filas de la matriz por sus columnas y viceversa
Parametros:
	A: Puntero a la matriz
Retorno: Puntero a la matriz con las filas y columnas permutadas
************************************************/

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

/******** Funcion: input_val ********************
Descripcion: Inserta un valor en la matriz
Parametros:
	i: Entero con la posicion de la fila a insertar el valor
	j: Entero con la posicion de la columna a insertar el valor
	val: Entero con el valor a insertar en la matriz
	sum: Entero el cual indica si el valor se sobrescribe o suma (en caso de que haya un valor en la misma posicion)
	A: Puntero a la matriz
Retorno: Retorna un 1 indicando que la operacion fue exitosa o 0 en caso contrario
************************************************/

int input_val(int i, int j, int val, int sum, Matriz *A){
	if (i > A->n_filas){
		printf("Fuera de la dimension de la matriz\n");
		return 0;
	}
	if (j > A->n_col){
		printf("Fuera de la dimension de la matriz\n");
		return 0;
	}
	if (val == 0 && sum == 0){
		toHome(A->Filas);
		toHome(A->Columnas);
		toHome(A->Valores);
		int a;
		for (a = 0; a < A->n_elem; a++)
		{
			if (getval(A->Filas) == i && j == getval(A->Columnas)){
				eliminar_lista(A->Valores);
				eliminar_lista(A->Filas);
				eliminar_lista(A->Columnas);
				A->n_elem--;
				toHome(A->Filas);
				toHome(A->Columnas);
				toHome(A->Valores);
				return 1;
			}
			next(A->Filas);
			next(A->Columnas);
			next(A->Valores);
		}
	} 
	if (sum == 1)
	{
		toHome(A->Filas);
		toHome(A->Columnas);
		toHome(A->Valores);
		int a;
		for (a = 0; a < A->n_elem; a++)
		{
			if (getval(A->Filas) == i && j == getval(A->Columnas)){
				if (A->Valores->curr->sig->info + val == 0)
				{
					eliminar_lista(A->Valores);
					eliminar_lista(A->Filas);
					eliminar_lista(A->Columnas);
					A->n_elem--;
					return 1;
				}
				else{
					A->Valores->curr->sig->info = A->Valores->curr->sig->info + val;
					return 1;
				}
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

/******** Funcion: set_limit ********************
Descripcion: Fija la dimensionalidad de la matriz
Parametros:
	fil: Entero el cual representa la cantidad de filas
	col: Entero el cual representa la cantidad de columnas
	A: Puntero a la matriz
Retorno: Ninguno
************************************************/

void set_limit(int fil, int col, Matriz *A){
	A->n_filas = fil;
	A->n_col = col;
}

/******** Funcion: diag ********************
Descripcion: Retorna una nueva matriz con solo los elementos en la diagonal de la matriz dada
Parametros:
	A: Puntero a la matriz
Retorno: Matriz con solo elementos en su diagonal
************************************************/

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

/******** Funcion: alloc_dispersa ********************
Descripcion: Crea una matriz de m filas por n columnas en memoria dinamica
Parametros:
	m: Entero que representa la camtidad de filas
	n: Entero que representa la camtidad de columnas
Retorno: Puntero a void
************************************************/

void* alloc_dispersa(int m, int n){
	Matriz *A;
	A = crear_matriz();
	set_limit(m,n,A);
	return (void *)A;
}

/******** Funcion: free_dispersa ********************
Descripcion: Borra una matriz de la memoria dinamica
Parametros:
	A: Puntero a void
Retorno: Ninguno
************************************************/

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

/******** Funcion: input_val ********************
Descripcion: Inserta un valor en la matriz
Parametros:
	A: Puntero a void
	i: Entero con la posicion de la fila a insertar el valor
	j: Entero con la posicion de la columna a insertar el valor
	valor: Entero con el valor a insertar en la matriz
Retorno: Retorna un 1 indicando que la operacion fue exitosa o 0 en caso contrario
************************************************/

int ingresar_valor(void* A, int i, int j, int valor){
	return input_val(i,j,valor,0,(Matriz *)A);
}

/******** Funcion: imprimir_matriz ********************
Descripcion: Imprime en pantalla la informacion de la matriz y sus elementos
Parametros:
	A: Puntero a void
Retorno: Ninguno
************************************************/

void imprimir_matriz(void* A){
	int i;
	int val,fila,col;
	toHome(((Matriz *)A)->Valores);
	toHome(((Matriz *)A)->Filas);
	toHome(((Matriz *)A)->Columnas);
	for (i = 0; i < ((Matriz *)A)->n_elem; i++)
	{
		val = getval(((Matriz *)A)->Valores);
		fila = getval(((Matriz *)A)->Filas);
		col = getval(((Matriz *)A)->Columnas);
		printf("(%d,%d) = %d\n",fila,col,val);
		next(((Matriz *)A)->Valores);
		next(((Matriz *)A)->Filas);
		next(((Matriz *)A)->Columnas);
	}
	return;
}

/******** Funcion: imprimir_matriz ********************
Descripcion: Suma dos matrices validas en dimensionalidad
Parametros:
	A: Puntero a void
	B: Puntero a void
Retorno: Puntero a void
************************************************/

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
	return ((void *)D);
}

/******** Funcion: multiplicacion ********************
Descripcion: Multiplica dos matrices validas en dimensionalidad
Parametros:
	A: Puntero a void
	B: Puntero a void
Retorno: Puntero a void
************************************************/

void* multiplicacion(void* A, void* B){
	Matriz *C;
	if (((Matriz *)A)->n_col!=((Matriz *)B)->n_filas)
	{
		printf("Error de dimensiones al multiplicar\n");
		exit(0);
	}
	C = (Matriz *)alloc_dispersa(((Matriz *)A)->n_filas,((Matriz *)B)->n_col);
	int i,j;
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

/******** Funcion: trasponer ********************
Descripcion: Permuta las filas con las columnas de una matriz
Parametros:
	A: Puntero a void
Retorno: Puntero a void
************************************************/

void* trasponer(void* A){
	Matriz *B;
	int i;
	B = (Matriz *)alloc_dispersa(((Matriz *)A)->n_col,((Matriz *)A)->n_filas);
	toHome(((Matriz *)A)->Valores);
	toHome(((Matriz *)A)->Filas);
	toHome(((Matriz *)A)->Columnas);
	for (i = 0; i < ((Matriz *)A)->n_elem; i++)
	{
		if(input_val(getval(((Matriz *)A)->Columnas),getval(((Matriz *)A)->Filas),getval(((Matriz *)A)->Valores),0,B)==0){
			printf("Error al insertar valores\n");
			exit(1);
		}
		next(((Matriz *)A)->Valores);
		next(((Matriz *)A)->Filas);
		next(((Matriz *)A)->Columnas);
	}
	return ((void *)B);
}

/******** Funcion: diagonal ********************
Descripcion: Obtiene la matriz con los valores diagonales de la matriz ingresada
Parametros:
	A: Puntero a void
Retorno: Puntero a void
************************************************/

void* diagonal(void* A){
	Matriz *B;
	B = diag((Matriz *)A);
	return ((void *)B);
}

/******** Funcion: element_wise_op ********************
Descripcion: Obtiene la matriz con los valores modificados por una funcion
Parametros:
	fun: Puntero a una funcion con un elemento entero con retorno entero
	A: Puntero a void
Retorno: Puntero a void
************************************************/

void *element_wise_op(int (*fun)(int), void* A){
	int i;
	Matriz *Aux;
	Aux = crear_matriz();
	set_limit(((Matriz *)A)->n_filas,((Matriz *)A)->n_col,Aux);
	toHome(((Matriz *)A)->Valores);
	toHome(((Matriz *)A)->Filas);
	toHome(((Matriz *)A)->Columnas);
	for (i = 0; i < ((Matriz *)A)->n_elem; i++){
		if (fun(getval(((Matriz *)A)->Valores)) != 0)
		{
			input_val(getval(((Matriz *)A)->Filas),getval(((Matriz *)A)->Columnas),fun(getval(((Matriz *)A)->Valores)),0,Aux);
			next(((Matriz *)A)->Valores);
			next(((Matriz *)A)->Filas);	
			next(((Matriz *)A)->Columnas);
		}
		else{
			next(((Matriz *)A)->Valores);
			next(((Matriz *)A)->Filas);	
			next(((Matriz *)A)->Columnas);
		}
	}
	toHome(((Matriz *)A)->Valores);
	toHome(((Matriz *)A)->Filas);
	toHome(((Matriz *)A)->Columnas);
	free_dispersa(A);
	A = (void *)Aux;
	return A;
}

/******** Funcion: unaria ********************
Descripcion: Aplica una funcion a la matriz imprimiendo el resultado
Parametros:
	fun: Puntero a una funcion con un elemento de puntero a void con retorno a un puntero void
	A: Puntero a void
Retorno: Ninguno
************************************************/

void unaria(void* (*fun)(void*), void* A){
	void *Z = fun(A);
	imprimir_matriz(Z);
	free_dispersa(Z);
	return;
}

/******** Funcion: binaria ********************
Descripcion: Aplica una funcion a dos matrices e imprime el resultado
Parametros:
	fun: puntero a una funcion con dos elementos de puntero a void con retorno a un puntero void
	A: Puntero a void
	B: Puntero a void
Retorno: Ninguno
************************************************/

void binaria(void* (*fun)(void*,void*), void* A, void* B){
	void *Z;
	Z = fun(A,B);
	imprimir_matriz(Z);
	free_dispersa(Z);
	return;
}

/******** Funcion: doblar ********************
Descripcion: Dobla el entero ingresado
Parametros:
	a: Entero
Retorno: El doble de a
************************************************/

int doblar(int a){
	return 2*a;
}

int main(int argc, char const *argv[])
{
	void *A;
	void *B;
	void *C;
	void *D;
	void *(*foo)(void *);
	void *(*fuu)(void *,void *);
	void *(*fee)(void *,void *);
	int (*fun)(int);
	foo = &trasponer;
	fuu = &multiplicacion;
	fee = &suma;
	fun = &doblar;
	A = alloc_dispersa(3,3);
	ingresar_valor(A,1,1,1);
	ingresar_valor(A,1,2,2);
	ingresar_valor(A,1,3,3);
	ingresar_valor(A,2,1,4);
	printf("--------------------------------\n");
	printf("------------- Matriz A ---------\n");
	printf("--------------------------------\n");
	imprimir_matriz(A);
	printf("--------------------------------\n");
	B = alloc_dispersa(3,3);
	ingresar_valor(B,1,1,-1);
	ingresar_valor(B,1,2,2);
	ingresar_valor(B,2,1,4);
	printf("------------- Matriz B ---------\n");
	printf("--------------------------------\n");
	imprimir_matriz(B);
	printf("--------------------------------\n");
	C = alloc_dispersa(4,4);
	ingresar_valor(C,3,2,5);
	ingresar_valor(C,1,4,2);
	ingresar_valor(C,4,2,3);
	ingresar_valor(C,2,1,7);
	ingresar_valor(C,1,2,1);
	printf("------------- Matriz C ---------\n");
	printf("--------------------------------\n");
	imprimir_matriz(C);
	printf("--------------------------------\n");
	D = alloc_dispersa(4,4);
	ingresar_valor(D,2,1,1);
	ingresar_valor(D,1,3,1);
	ingresar_valor(D,2,2,5);
	ingresar_valor(D,2,4,2);
	ingresar_valor(D,1,2,9);
	printf("------------- Matriz D ---------\n");
	printf("--------------------------------\n");
	imprimir_matriz(D);
	printf("--------------------------------\n");
	printf("-------- Traspuesta de A -------\n");
	printf("--------------------------------\n");
	unaria(foo,A);
	printf("--------------------------------\n");
	printf("------------ A + B -------------\n");
	printf("--------------------------------\n");
	binaria(fee,A,B);
	printf("--------------------------------\n");
	printf("------------ C x D -------------\n");
	printf("--------------------------------\n");
	binaria(fuu,C,D);
	printf("--------------------------------\n");
	printf("-------- Traspuesta de D -------\n");
	printf("--------------------------------\n");
	unaria(foo,D);
	printf("--------------------------------\n");
	printf("------------- 2 x [A] ----------\n");
	printf("--------------------------------\n");
	A = element_wise_op(fun,A);
	imprimir_matriz(A);
	printf("--------------------------------\n");
	free_dispersa(A);
	free_dispersa(B);
	free_dispersa(C);
	free_dispersa(D);
	return 0;
}

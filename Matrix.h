#include <stdlib.h>
#include <stdio.h>

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

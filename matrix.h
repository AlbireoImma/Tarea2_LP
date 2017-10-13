#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Matrix
{
public:
	Matrix();
	void Matrix_Size(int a);
	int getValue(int a,int b);	// Obtener valor
	void SetVal(int a, int b);	// Escribir valor
	// void clearMatrix(); 		// Limpiar la matriz
	void printMatrix();			// Imprimir la matrix
	int *Comparar_filas(int a, int b);
	int *Revisar_estaticos(int a, int* Arreglo);
	~Matrix(); 					// Destructor
private:
	int *Array;
	int m;
	int n;
};


Matrix::Matrix(){
	m =0;
	n =0;
	Array = NULL;
}

void Matrix::Matrix_Size(int a)
{
	n = a;
	m = a;
	printf("%ld\n",a*a);
	int c = n*n;
	Array = (int *)calloc(c,sizeof(int));
	if (Array!=NULL) printf("Memoria Inicializada\n");
	if (Array == NULL) printf("Memoria no Inicializada\n");
}

Matrix::~Matrix()
{
	free((void *)Array);
}

void Matrix::SetVal(int a, int b)
{
	int i;
	i = a*(n)+b;
	Array[i]=1;
}

int Matrix::getValue(int a, int b)
{
	return Array[a*n+b];
}

void Matrix::printMatrix()
{
	int j=0;
	int a = 0;
	for (int i = 0; i < m; i++)
	{
		printf("[ ");
		while(j%n!=0 || j==0)
		{
			printf("%li ", Array[a]);
			j++;
			a++;
		}
		printf("]\n");
		j=0;
	}
}

int *Matrix::Comparar_filas(int a, int b)
{
	int *sol;
	//int *sol_new;
	int cant=0;
	sol = (int *)calloc(n+1,sizeof(int));
	sol[0] = 0;
	for (int i = 0; i < n; i++)
	{
		if (Array[a*n+i]==1 && Array[b*n+i]==1)
		{
			cant++;
			sol[cant]=i;
		}
	}
	sol[0] = cant;
	//sol_new = (int *)realloc(sol,sizeof(int)*(cant+1));
	return sol;
}

int *Matrix::Revisar_estaticos(int a, int* Arreglo)
{
	int *aux2;
	aux2 = (int *)calloc(Arreglo[0],sizeof(int));
	int cant = 0;
	for (int i = 0; i < Arreglo[0]; i++)
	{
		if (Array[a*n+Arreglo[i+1]]==1)
		{
			cant++;
			aux2[cant]=Arreglo[i+1];
		}
	}
	aux2[0]=cant;
	free((void *)Arreglo);
	Arreglo = aux2;
	return Arreglo;
}
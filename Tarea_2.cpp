#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

typedef struct nodo
{
	int info;
	struct nodo *sig;
} tnodo;

class Lista{
public:
	Lista();
	void insertar(int item);
	void eliminar();
	void printlista();
	int getval();
	int buscar(int item);
	void next();
	void prev();
	void toHome();
	int getlarge();
	void erase();
	~Lista();
	tnodo *head;
	tnodo *tail;
	tnodo *curr;
	int largo;
	int pos;
};

Lista::Lista(){
	head = new tnodo;
	curr = head;
	tail = head;
	pos = 0;
	largo = 0;
}


Lista::~Lista(){
	if (largo == 0)
	{
		delete head;
		return;
	}
	while(largo > 0)
	{
		tnodo *aux = head;
		for (int i = 0; i < largo; i++)
		{
			aux = aux->sig;
		}
		delete aux;
		largo--;
	}
	delete head;
}

void Lista::insertar(int item){
	tnodo *aux;
	if (head == NULL)
	{
		head = new tnodo;
		curr = head;
		tail = head;
	}
	if (largo == 0)
	{
		curr->sig = new tnodo;
		curr->sig->info = item;
		tail = curr->sig;
		largo++;
		return;
	}
	aux = new tnodo;
	aux->info = item;
	aux->sig = curr->sig;
	curr->sig = aux;
	if (curr == tail)
	{
		tail = curr->sig;
	}
	largo++;
}

void Lista::eliminar(){
	if (largo == 0)
	{
		return;
	}
	tnodo *aux;
	aux = curr->sig->sig;
	if (curr->sig == tail)
	{
		tail = curr;
	}
	free((void *)curr->sig);
	curr->sig = aux;
	largo--;
}

int Lista::getval(){
	return curr->sig->info;
}

void Lista::printlista(){
	if (largo == 0)
	{
		printf("Lista vacia\n");
		return;
	}
	tnodo *aux = head;
	printf("[ ");
	for (int i = 0; i < largo; i++)
	{
		printf("%d ",aux->sig->info);
		aux = aux->sig;
	}
	printf("]\n");
	printf(">> Largo lista: %d\n",largo);
	printf(">> Memoria utilizada: %ld bytes\n",sizeof(tnodo)*(largo+1));
}

void Lista::next(){
	if (curr == tail) return;
	curr = curr->sig;
	pos++;
}

void Lista::prev(){
	if (curr == head) return;
	curr = head;
	for (int i = 0; i < pos-1; i++)	curr = curr->sig;
	pos = pos-1;
}

int Lista::buscar(int item){
	if (largo == 0) return 0;
	tnodo *aux = head;
	int i;
	for (i = 0; i < largo; i++)
	{
		aux = aux->sig;
		if (aux->info == item) return 1;
	}
	return 0;
}

void Lista::toHome(){
	curr = head;
}

int Lista::getlarge(){
	return largo;
}

void Lista::erase(){
	if (largo == 0)
	{
		delete head;
		return;
	}
	while(largo > 0)
	{
		tnodo *aux = head;
		for (int i = 0; i < largo; i++)
		{
			aux = aux->sig;
		}
		delete aux;
		largo--;
	}
	delete head;
}

class Dispersa
{
public:
	int n_col;
	int n_fil;
	int n_elem;
	Lista Valores;
	Lista Filas;
	Lista Columnas;
	Dispersa();
	void set_limit(int col,int fil);
	int input_val(int i,int j, int val,bool sum);
	void print_dispersa();
	void print_info();
	void swap_m_n();
	void diag();
	~Dispersa();
	
};

Dispersa::Dispersa(){
	n_col=0;
	n_fil=0;
	n_elem=0;
	Lista Valores;
	Lista Filas;
	Lista Columnas;
}

Dispersa::~Dispersa(){
	return ;
}

void Dispersa::print_info(){
	cout << "numero de filas: "<<n_fil<<endl;
	cout << "numero de columnas: "<<n_col<<endl;
	cout << "numero de elementos: "<<n_elem<<endl;
}

void Dispersa::swap_m_n(){
	static Lista Aux;
	Aux = Filas;
	Filas = Columnas;
	Columnas = Aux;
	return;
}

int Dispersa::input_val(int i,int j, int val,bool sum){
	if (i > n_fil) return 0;
	if (j > n_col) return 0;
	if (sum == true)
	{
		Filas.toHome();
		Columnas.toHome();
		Valores.toHome();
		int a;
		for (a = 0; a < n_elem; a++)
		{
			if (Filas.getval() == i and j == Columnas.getval())
			{
				Valores.curr->sig->info = Valores.curr->sig->info + val;
				return 1;
			}
		Filas.next();
		Columnas.next();
		Valores.next();
		}
	}
	if (sum == false)
	{
		Filas.toHome();
		Columnas.toHome();
		Valores.toHome();
		int a;
		for (a = 0; a < n_elem; a++)
		{
			if (Filas.getval() == i and j == Columnas.getval())
			{
				Valores.curr->sig->info = val;
				return 1;
			}
			Filas.next();
			Columnas.next();
			Valores.next();
		}
	}
	Valores.insertar(val);
	Filas.insertar(i);
	Columnas.insertar(j);
	n_elem = n_elem + 1;
	return 1;
}

void Dispersa::set_limit(int fil, int col){
	n_fil = fil;
	n_col = col;
}

void Dispersa::print_dispersa(){
	int i;
	int val,fila,col;
	cout << "---------------------" << endl;
	cout << "Matriz Dispersa" << endl;
	cout << "---------------------" << endl;
	cout << "numero de filas: " << n_fil << endl;
	cout << "numero de columnas: " << n_col << endl;
	cout << "numero de elementos: " << n_elem << endl;
	Valores.toHome();
	Filas.toHome();
	Columnas.toHome();
	for (i = 0; i < n_elem; i++)
	{
		val = Valores.getval();
		fila = Filas.getval();
		col = Columnas.getval();
		cout << "(" << fila << "," << col << ") = " << val << endl;
		Valores.next();
		Filas.next();
		Columnas.next();
	}
	cout << "---------------------" << endl;
}

void Dispersa::diag(){
	int i,a;
	Filas.toHome();
	Valores.toHome();
	Columnas.toHome();
	a = n_elem;
	for (i = 0; i < n_elem; i++)
	{
		if(Filas.getval()!=Columnas.getval()){
			Filas.eliminar();
			Columnas.eliminar();
			Valores.eliminar();
			a--;
		}
		else{
			Filas.next();
			Columnas.next();
			Valores.next();
		}
	}
	n_elem=a;
	return;
}


void* alloc_dispersa(int m, int n){
	Dispersa *A = new Dispersa;
	A->set_limit(m,n);
	return (void *)A;
}

void free_dispersa(void* A){
	delete (Dispersa*)A;
	return;
}

int ingresar_valor(void* A, int i, int j, int valor){
	int a = ((Dispersa *)A)->input_val(i,j,valor,false);
	return a;
}

void imprimir_matriz(void* A){
	((Dispersa *)A)->print_dispersa();
	return;
}

void* suma(void* A,void* B){
	Dispersa *D;
	D = (Dispersa*)alloc_dispersa(((Dispersa *)A)->n_fil,((Dispersa *)A)->n_col);
	int i;
	int elem_A = ((Dispersa *)A)->n_elem;
	int elem_B = ((Dispersa *)B)->n_elem;
	((Dispersa *)A)->Valores.toHome();
	((Dispersa *)A)->Filas.toHome();
	((Dispersa *)A)->Columnas.toHome();
	for (i = 0; i < elem_A; i++)
	{
		D->input_val(((Dispersa *)A)->Filas.getval(),((Dispersa *)A)->Columnas.getval(),((Dispersa *)A)->Valores.getval(),false);
		((Dispersa *)A)->Valores.next();
		((Dispersa *)A)->Filas.next();
		((Dispersa *)A)->Columnas.next();
	}
	((Dispersa *)B)->Valores.toHome();
	((Dispersa *)B)->Filas.toHome();
	((Dispersa *)B)->Columnas.toHome();
	for (i = 0; i < elem_B; i++)
	{
		D->input_val(((Dispersa *)B)->Filas.getval(),((Dispersa *)B)->Columnas.getval(),((Dispersa *)B)->Valores.getval(),true);
		((Dispersa *)B)->Valores.next();
		((Dispersa *)B)->Filas.next();
		((Dispersa *)B)->Columnas.next();
	}
	return (void *)D;
}

void* multiplicacion(void* A, void* B){}

void binaria(void* (*fun)(void*,void*), void* A,void* B){}

void* transponer(void* A){
	((Dispersa *)A)->swap_m_n();
	return (void *)A;
}

void* diagonal(void* A){
	((Dispersa *)A)->diag();
	return (void *)A;
}

void unaria(void* (*fun)(void*), void* A){}

void* element_wise_op(int (*fun)(int), void* A){}

int main(int argc, char const *argv[])
{
	cout << "---------------------" << endl;
	cout << "|\t\tMain\t\t|" << endl;
	Dispersa *A;
	Dispersa *B;
	Dispersa *C;
	//Dispersa *B;
	A = (Dispersa*)alloc_dispersa(3,3);
	B = (Dispersa*)alloc_dispersa(3,3);
	ingresar_valor((void *)A,1,1,1);
	ingresar_valor((void *)A,1,3,2);
	ingresar_valor((void *)A,2,1,3);
	ingresar_valor((void *)A,3,1,4);
	ingresar_valor((void *)A,3,3,5);
	imprimir_matriz((void *)A);
	ingresar_valor((void *)B,1,1,1);
	ingresar_valor((void *)B,1,3,2);
	ingresar_valor((void *)B,2,1,3);
	ingresar_valor((void *)B,3,1,4);
	ingresar_valor((void *)B,3,3,5);
	imprimir_matriz((void *)B);
	C = (Dispersa *)suma((void *)A,(void *)B);
	imprimir_matriz((void *)C);
	//B = (Dispersa*)alloc_dispersa(4,4);
	//B->print_dispersa();
	free_dispersa((void *)A);
	free_dispersa((void *)B);
	return 0;
}
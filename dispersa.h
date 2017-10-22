#ifndef _DISPERSA_H_
#define _DISPERSA_H_

	void* alloc_dispersa(int m, int n);
	void free_dispersa(void* A);
	int ingresar_valor(void* A, int i, int j, int valor);
	void imprimir_matriz(void* A);
	void* suma(void*A,void*B);
	void* multiplicacion(void*A,void*B);
	void binaria(void* (*fun)(void*,void*), void* A, void* B);
	void* transponer(void* A);
	void* diagonal(void* A);
	void unaria(void* (*fun)(void*), void* A);
	void* element_wise_op(int (*fun)(int), void* A);

#endif
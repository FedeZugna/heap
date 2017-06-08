#include "heap.h"
#include "testing.h"
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LONGITUD_ARRAY_PRUEBA 25

int comp_ints(const void* a, const void* b) {
	int* a_temp = (int*)a;
	int* b_temp = (int*)b;
	return (*a_temp) - (*b_temp);
}

void imprimir_vector_pruebas(int *vector_pruebas) {
	for (size_t i=0;i<LONGITUD_ARRAY_PRUEBA;i++) {
		printf("%d\n", vector_pruebas[i] );
	}
}

void pruebas_heap_alumno(void){
	/* VARIABLES AUXILIARES */
	int t1 = 5;
	int t2 = 8;
	int t3 = 2;
	int t4 = 3;
	int t5 = 0;
	//int vector_pruebas[LONGITUD_ARRAY_PRUEBA];
	/* HEAP VACIO */
	heap_t* heap = heap_crear(comp_ints);
	print_test("El heap fue creado, y no es NULL", (heap != NULL));
	print_test("Desencolar es NULL", heap_desencolar(heap) == NULL);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("El maximo del heap es NULL", heap_ver_max(heap) == NULL);
	heap_destruir(heap, NULL);
	/* HEAP DE A UN ELEMENTO */
	heap = heap_crear(comp_ints);
	print_test("El heap fue creado, y no es NULL", (heap != NULL));
	print_test("Desencolar es NULL", heap_desencolar(heap) == NULL);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("El maximo del heap es NULL", heap_ver_max(heap) == NULL);
	print_test("Encolar 5 es true", heap_encolar(heap, &t1) == true);
	print_test("El maximo del heap es 5", heap_ver_max(heap) == &t1);
	print_test("Encolar 8 es true", heap_encolar(heap, &t2));
	print_test("El largo del heap es 2", heap_cantidad(heap) == 2);
	print_test("El maximo del heap es 8", heap_ver_max(heap) == &t2);
	print_test("Desencolar devuelve 8", heap_desencolar(heap) == &t2);
	print_test("El largo del heap es 1", heap_cantidad(heap) == 1);
	print_test("Encolar 2 es true", heap_encolar(heap, &t3));
	print_test("El largo del heap es 2", heap_cantidad(heap) == 2);
	print_test("El maximo del heap es 5", heap_ver_max(heap) == &t1);
	print_test("Desencolar devuelve 5", heap_desencolar(heap) == &t1);
	heap_destruir(heap, NULL);
	/* HEAP POCOS ELEMENTOS */
	heap = heap_crear(comp_ints);
	print_test("El heap fue creado, y no es NULL", (heap != NULL));
	print_test("Desencolar es NULL", heap_desencolar(heap) == NULL);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("El maximo del heap es NULL", heap_ver_max(heap) == NULL);
	print_test("Encolar 5 es true", heap_encolar(heap, &t1));
	print_test("Encolar 8 es true", heap_encolar(heap, &t2));
	print_test("Encolar 2 es true", heap_encolar(heap, &t3));
	print_test("Encolar 3 es true", heap_encolar(heap, &t4));
	print_test("Encolar 0 es true", heap_encolar(heap, &t5));
	print_test("El largo del heap es 5", heap_cantidad(heap) == 5);
	print_test("El maximo del heap es 8",heap_ver_max(heap) == &t2);
	print_test("desencolar devuelve 8", heap_desencolar(heap) == &t2);
	print_test("el largo del heap es 4", heap_cantidad(heap) == 4);
	print_test("el maximo del heap es 5",heap_ver_max(heap) == &t1);
	print_test("desencolar devuelve 5", heap_desencolar(heap) == &t1);
	print_test("desencolar devuelve 3", heap_desencolar(heap) == &t4);
	heap_destruir(heap, NULL);
	/*HEAP VOLUMEN*/
	heap=heap_crear(comp_ints);
	size_t largo_clave=10000;
	print_test("El heap fue creado, y no es NULL", (heap != NULL));
	print_test("Desencolar es NULL", heap_desencolar(heap) == NULL);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("El maximo del heap es NULL", heap_ver_max(heap) == NULL);
	size_t i=0;
	bool ok=true;
	for(i=0;i<largo_clave;i++){
		ok &= heap_encolar(heap,&i);
	}
	print_test("Se pudieron guardar todos los elementos",ok);
	print_test("El maximo es 9999", heap_ver_max(heap) == &i);
	heap_destruir(heap,NULL);
	/*HEAP SORT*/
	heap=heap_crear(comp_ints);
	void** vector=malloc(7 * sizeof(void*));
	int i1=9,i2=8,i3=7,i4=6,i5=5,i6=4,i7=3;
	vector[0]=&i1;
	vector[1]=&i2;
	vector[2]=&i3;
	vector[3]=&i4;
	vector[4]=&i5;
	vector[5]=&i6;
	vector[6]=&i7;
	for(size_t k=0;k<7;k++){
		printf("%d ",*(int*)vector[k]);
	}
	heap_sort(vector,7,comp_ints);
	printf("\nDe menor a mayor: \n");
	for(size_t k=0;k<7;k++){
		printf("%d ",*(int*)vector[k]);
	}
	printf("\n");
	free(vector);
	heap_destruir(heap, NULL);
}


	
	
	


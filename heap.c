#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGO_INICIAL 10
#define FACTOR_CARGA 70
#define DUPLICA 2
#define FACTOR_DESCARGA 30

struct heap{
	void** vector;
	cmp_func_t cmp;
	size_t largo;
	size_t elementos;
};


void swap(void** vector,size_t primero,size_t segundo){
	void* aux=vector[primero];
	vector[primero]=vector[segundo];
	vector[segundo]=aux;
}

void downheap(void** vector,size_t elem,size_t pos,cmp_func_t cmp){
	if (pos >= elem) {
		return;
	}
	size_t pos_h_izq = pos*2 + 1;
	size_t pos_h_der = pos*2 + 2;
	size_t pos_mayor = pos;
	int comparacion;
	if(pos_h_izq < elem){
		comparacion=cmp(vector[pos],vector[pos_h_izq]);
		if(comparacion < 0)	pos_mayor=pos_h_izq;
	}
	if(pos_h_der < elem){
		comparacion=cmp(vector[pos_mayor],vector[pos_h_der]);
		if(comparacion < 0) pos_mayor=pos_h_der;
	}
	if(pos_mayor != pos){
		swap(vector,pos,pos_mayor);
		downheap(vector,elem,pos_mayor,cmp);
	}
}



void upheap(void** vector,size_t elem,size_t pos,cmp_func_t cmp){
	if(pos==0) return;
	size_t pos_padre = (pos-1)/2;
	void* dato1=vector[pos];
	void* dato2=vector[pos_padre];
	int comparacion=0;
	comparacion=cmp(dato1,dato2);
	if(comparacion > 0){
		swap(vector,pos,pos_padre);
		upheap(vector,elem,pos_padre,cmp);
	}
}

void heapify(void** vector,size_t elem,cmp_func_t cmp){
	for(size_t i=(elem/2 -1);i>0;i--){
		downheap(vector,elem,i,cmp);
	}
	downheap(vector,elem,0,cmp);
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos,cant,cmp);
	for(size_t i=cant-1;i>0;i--){
		swap(elementos,0,i);
		downheap(elementos,i,0,cmp);
	}
}

bool heap_redimensionar(heap_t *heap,size_t capacidad){
	void* aux=realloc(heap->vector,(sizeof(void*) * capacidad));
	if(capacidad > 0 && aux == NULL) return false;
	heap->vector=aux;
	heap->largo=capacidad;
	return true;
}

heap_t *heap_crear(cmp_func_t cmp){
	if(cmp==NULL) return NULL;
	heap_t* heap=malloc(sizeof(heap_t));
	if(!heap) return NULL;
	heap->vector=malloc(LARGO_INICIAL * sizeof(void*));
	if(!heap->vector){
		free(heap);
		return NULL;
	}
	heap->cmp=cmp;
	heap->largo=LARGO_INICIAL;
	heap->elementos=0;
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	if(cmp==NULL) return NULL;
	heap_t* heap=malloc(sizeof(heap_t));
	if(!heap) return NULL;
	heap->vector=malloc(n*sizeof(void*));
	if(n>0 && heap->vector==NULL){
		free(heap);
		return NULL;
	}
	heap->cmp=cmp;
	heap->elementos=0;
	heap->largo=n;
	for(size_t i=0;i<n;i++){
		heap->vector[i]=arreglo[i];
		heap->elementos++;
		upheap(heap->vector,heap->elementos,heap->elementos-1,heap->cmp);
	}
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	void* aux;
	while(!heap_esta_vacio(heap)){
		aux=heap_desencolar(heap);
		if(destruir_elemento != NULL){
			destruir_elemento(aux);
		}
	}
	if(heap->vector != NULL){
		free(heap->vector);
	}
	free(heap);
}

size_t heap_cantidad(const heap_t *heap){
	return heap->elementos;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->elementos==0;
}

bool heap_encolar(heap_t *heap, void *elem){
	if(heap_esta_vacio(heap)){
		heap->elementos++;
		heap->vector[0]=elem;
		return true;
	}else{
		heap->elementos++;
		heap->vector[heap_cantidad(heap)-1]=elem;
		if(heap_cantidad(heap) >= (heap->largo*FACTOR_CARGA/100)){
			heap_redimensionar(heap, heap->largo*DUPLICA);
		}
		upheap(heap->vector,heap->elementos,heap->elementos-1,heap->cmp);
		return true;
	}
	return false;
}

void *heap_ver_max(const heap_t *heap){
	if(heap_esta_vacio(heap)){
		return NULL;
	}
	void* elem_a_devolver=heap->vector[0];
	return elem_a_devolver;
}

void *heap_desencolar(heap_t *heap){
	if(!heap_esta_vacio(heap)){
		void* aux=heap_ver_max(heap);
		swap(heap->vector,0,heap_cantidad(heap)-1);
		heap->vector[heap_cantidad(heap)-1]=NULL;
		heap->elementos--;
		if((heap_cantidad(heap)<= (heap->largo*FACTOR_DESCARGA/100)) && (heap->largo > LARGO_INICIAL)){
			heap_redimensionar(heap,heap->largo/DUPLICA);
		}	
		downheap(heap->vector,heap->elementos,0,heap->cmp);
		return aux;
	}
	return NULL;
}

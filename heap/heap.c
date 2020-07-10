#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HEAP_TAM_INICIAL 10

struct heap{
    void **datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};


size_t calculo_pos_padre(size_t pos){
    return (pos - 1) / 2;
}

size_t calculo_pos_hijos(size_t pos, size_t *hijo_izquierdo){
    *hijo_izquierdo = 2 * pos + 1;
    return 2 * pos + 2;
}

bool padre_menor_que_hijo(const void *padre, const void* hijo, cmp_func_t cmp){
    return cmp(padre,hijo) < 0 ? true : false;
}

size_t comparar_hijos(void ** arr,size_t izq,size_t der, cmp_func_t cmp){
	return cmp(arr[izq],arr[der]) > 0 ? izq : der;
}

void swap(void **arr, size_t x, size_t y){
    void *aux = arr[x];
    arr[x] = arr[y];
    arr[y] = aux;
}

void downheap(void **arr,size_t tam,size_t padre, cmp_func_t cmp){
    if(padre >= tam/2){    
    //	printf(" Padre = %lu y tam/2 = %lu en condición de corte \n",padre,tam/2);
    	//printf("En downheap tengo que volver con padre = %lu y su valor %d\n",padre,*(int*)arr[padre]);
    	return;
    }
    size_t izquierdo = 0;
    size_t derecho = calculo_pos_hijos(padre,&izquierdo); //
    size_t hijo = izquierdo;
    if(derecho < tam) //Estos casos es cuando un padre tiene los 2 hijos, si solo tiene el izquierdo dejo el izquierdo y ya
 		hijo = comparar_hijos(arr,izquierdo,derecho,cmp); // con esto me salvo de hacer demasiados ifs, directamente me quedo con el mas grande entre el izq y el derecho
//    printf("tam = %lu, padre = %lu ,izquierdo = %lu y derecho = %lu \n",tam,padre,izquierdo,derecho);
    //printf("Con padre = %lu su valor = %d \n izquierdo = %lu su valor %d \nderecho = %lu su valor = %d\nhijo mayor = %lu su valor = %d\n\n",padre,*(int*)arr[padre],izquierdo,*(int*)arr[izquierdo],derecho,*(int*)arr[derecho],hijo,*(int*)arr[hijo]);
  //  printf("No es condición de corte \n");


    if(padre_menor_que_hijo(arr[padre],arr[hijo],cmp)){
        //printf("Entro y hago el swap, de padre = %d e hijo = %d\n",*(int*)arr[padre],*(int*)arr[hijo]);
        swap(arr,padre,hijo);
        //printf("Cambio a padre = %d e hijo = %d \n\n",*(int*)arr[padre],*(int*)arr[hijo]);
    	downheap(arr,tam,hijo,cmp);
    }
  // 	else
//    	downheap(arr,tam,padre,cmp);

}

void upheap(void **arr,size_t hijo, cmp_func_t cmp){
    if(hijo == 0)    
    	return;
    size_t padre = calculo_pos_padre(hijo);
    //printf("Padre: %zu , Hijo: %zu \n",padre,hijo);
    //if(padre_menor_que_hijo(arr[padre],arr[hijo],cmp)){
    //printf("Padre: %d ,Hijo: %d",*(int*)arr[padre],*(int*)arr[hijo]);
    if(cmp(arr[hijo],arr[padre]) > 0){
       	swap(arr,padre,hijo);
        upheap(arr,padre,cmp);
    }
}


heap_t *heap_crear(cmp_func_t cmp){
    heap_t *heap = malloc(sizeof(heap_t));
    if(!heap)   return NULL;

    heap->datos = malloc(HEAP_TAM_INICIAL*sizeof(void*));
    if(!heap->datos){
        free(heap);
        return NULL;
    }

    heap->tam = HEAP_TAM_INICIAL;
    heap->cant = 0;
    heap->cmp = cmp;

    return heap;
}

bool heap_redimensionar(heap_t *heap,size_t nuevo_tam){
    void *aux_datos = realloc(heap->datos,sizeof(void*) * nuevo_tam);
    if(nuevo_tam > 0 && !aux_datos)
        return false;

    heap->tam = nuevo_tam;
    heap->datos = aux_datos;

    return true;
}


void heapify(void *arr[],size_t n, cmp_func_t cmp){
    for(size_t i = n-1; i >= 0 && i < n; i--){
    	//printf("Entre a heapify en i = %lu \n",i);
     //   printf(" : %d \n",*(int*)arr[i]);
        downheap(arr,n,i,cmp);        
    }
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t *heap = heap_crear(cmp);
    if(!heap)   return NULL;

    if(n > heap->tam){
        if(!heap_redimensionar(heap,n))
            return NULL;
    }

    for(size_t i = 0; i < n; i++){
        heap->datos[i] = arreglo[i];
     //   printf("Funca: %d \n",*(int*)heap->datos[i]);
    }
   // printf("Entré aca \n");
    heap->cant = n;
    heapify(heap->datos,n,cmp);
    return heap;
//Heapify
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    if(destruir_elemento)
        free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
    return !heap->cant;
}

bool heap_encolar(heap_t *heap, void *elem){
    if(heap->cant == heap->tam){
        if(!heap_redimensionar(heap,heap->cant*2))
            return false;
    }
    heap->datos[heap->cant] = elem;
    //le paso como hijo, el valor de la ultima posicion de datos.
    upheap(heap->datos,heap->cant,heap->cmp);
    heap->cant++;
    return true;
}

void *heap_ver_max(const heap_t *heap){
    return heap_esta_vacio(heap) ? NULL : heap->datos[0];
}


void *heap_desencolar(heap_t *heap){
    if(heap_esta_vacio(heap))
        return NULL;

    if(heap->cant*4 == heap->tam){
        if(!heap_redimensionar(heap,heap->tam / 2))
            return NULL;
    }
    void * aux = heap->datos[0];
    //printf("voy a desencolar el %d", *(int*)aux);

    heap->datos[0] = heap->datos[heap->cant-1];
	heap->cant--;

	downheap(heap->datos,heap->cant,0,heap->cmp);

	return aux;    
}


void heap_sort_wrapper(void *arr[],size_t cant, cmp_func_t cmp){
    if(cant == 1)
        return;
    swap(arr,0,cant-1);
    cant--;
    downheap(arr,cant,0,cmp);
    heap_sort_wrapper(arr,cant,cmp);
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    if(cant < 1)
        return;
    heapify(elementos,cant,cmp);
    heap_sort_wrapper(elementos,cant,cmp);
}

void heap_imprimir(heap_t *p){
    printf("  _______\n");
    for(size_t i = 0;   i < p->cant; i++){
        printf("  |  %d  |\n  -------\n",*(int *)p->datos[i]);
    }
    printf("\n \n");
}


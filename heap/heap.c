#include "heap.h"

#define HEAP_TAM_INICIAL 10

struct heap{
    void **datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

heap_t *heap_crear(cmp_func_t cmp){
    heap_t *heap = malloc(sizeof(heap));
    if(!heap)   return NULL;

    heap->datos = malloc(sizeof(void*));
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
    for(int i = n; i >= 0; i--)
        downheap(arr,n,i,cmp);
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
//Heapify
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    //De esto no estoy seguro
    if(destruir_elemento != NULL){
        for(size_t i = 0; i < heap->cant -1; i++){
            destruir_elemento(heap->datos[i]);
    }
    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

void swap(void **arr, size_t x, size_t y){
    void *aux = arr[x];
    arr[x] = arr[y];
    arr[y] = arr[x];
}

size_t calculo_pos_padre(size_t pos){
    return (pos - 1) / 2;
}

size_t calculo_pos_hijos(size_t pos, size_t *hijo_izquierdo){
    *hijo_izquierdo = 2 * pos + 1;
    return 2 * pos + 2;
}


bool padre_menor_que_hijo(size_t padre, size_t hijo, cmp_func_t cmp){
    return cmp(padre,hijo) < 0 ? true : false;
}


void upheap(void **arr,size_t hijo, cmp_func_t cmp){
    if(hijo == 0)    
    	return;
    size_t padre = calculo_pos_padre(hijo);
    if(padre_menor_que_hijo(padre,hijo,cmp)){
        swap(arr,padre,hijo);
        upheap(arr,padre,cmp);
    }

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

size_t comparar_hijos(void ** arr,size_t izq,size_t der, cmp_func_t cmp){
	return cmp(arr[izq],arr[der]) <= 0 ? der : izq;
}

void downheap(void **arr,size_t tam,size_t padre, cmp_func_t cmp){
    if(padre >= tam)    
    	return;
    size_t izquierdo = NULL;
    size_t derecho = calculo_pos_hijos(padre,&izquierdo); // tranquilamente podemos calcularlo para hijo izquierdo y despues sumarle uno, pero por ahí queda mas lindo así, va nose, como prefieras
    size_t hijo = comparar_hijos(arr,izquierdo,derecho,cmp); // con esto me salvo de hacer demasiados ifs, directamente me quedo con el mas grande entre el izq y el derecho

    if(padre_menor_que_hijo(padre,hijo,cmp)){
        swap(arr,padre,hijo);
        downheap(arr,tam,padre,cmp);
    }

}

void *heap_desencolar(heap_t *heap){
    if(heap_esta_vacio(heap))
        return NULL;

    if(heap->cant*4 == heap->tam){
        if(!heap_redimensionar(heap,heap->cant / 2))
            return NULL;
    }
    void * aux = heap->datos[0];

    heap->datos[0] = heap->datos[heap->cant-1];
	heap->cant--;

	downheap(heap->datos,heap->cant,heap->cmp);

	return aux;    
}


void heap_sort_wrapper(void *arr[],size_t cant, cmp_func_t cmp){
    if(cant == 1)
        return;
    swap(arr,0,cant-1);
    cant--;
    downheap(arr,0,cmp,cant);
    heap_sort_wrapper(arr,cant,cmp);
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    if(cant < 1)
        return;
    heapify(elementos);
    heap_sort_wrapper(elementos,cant,cmp);
}
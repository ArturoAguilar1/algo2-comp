#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparar_enteros(const void *a,const void *b){
    if(*(int*)a > *(int*)b)
        return 1;
    else if( *(int*)a < *(int*)b)
        return -1;
    else
        return 0; 
    
}


void pruebas_heap_vacio(void){
    heap_t *heap = heap_crear(comparar_enteros);

    print_test("Prueba heap crear heap vacio",heap);
    print_test("Prueba heap la cantidad es cero",heap_cantidad(heap) == 0);
    print_test("Prueba heap desencolar de algo que esta vacio es NULL",heap_desencolar(heap) == NULL);
    print_test("Prueba heap ver max de un heap vacio no existe",heap_ver_max(heap) == NULL);
    print_test("Prueba heap esta vacio",heap_esta_vacio(heap));

    heap_destruir(heap,NULL);
    print_test("El heap fue destruido correctamente",true);
}

void pruebas_heap_encolar(void){
    heap_t *heap = heap_crear(comparar_enteros);
    int valor1 = 1; int valor2 = 2; int valor3 = 5; int valor4 = 0; int valor5 = 9;

    print_test("Prueba heap encolar el valor1 = 1",heap_encolar(heap,&valor1));
    print_test("Prueba heap encolar el valor2 = 2",heap_encolar(heap,&valor2));
    print_test("Prueba heap encolar el valor3 = 5",heap_encolar(heap,&valor3));
    print_test("Prueba heap encolar el valor4 = 0",heap_encolar(heap,&valor4));
    print_test("Prueba heap encolar el valor5 = 9",heap_encolar(heap,&valor5));
    heap_imprimir(heap);
    print_test("Prueba heap no esta vacio",!heap_esta_vacio(heap));
    print_test("Prueba heap cantidad es 5", heap_cantidad(heap) == 5);
    print_test("Prueba heap ver el maximo es el valor5 = 9", *(int*)heap_ver_max(heap) == valor5);
    print_test("Prueba heap desencolar me devuelve el valor5",*(int*)heap_desencolar(heap) == valor5);
    heap_imprimir(heap);
    print_test("Prueba heap la cantidad disminuye, la cantidad es 4", heap_cantidad(heap)==4);
    print_test("Prueba heap, ahora el maximo es el valor3 = 5",*(int*)heap_ver_max(heap) == valor3);
    print_test("Prueba heap desencolar el valor3",*(int*)heap_desencolar(heap) == valor3);
    print_test("El maximo cambia nuevamente, es el valor2 = 2",*(int*)heap_ver_max(heap) == valor2);
    print_test("Prueba heap la cantidad queda en 3", heap_cantidad(heap) == 3);
    heap_imprimir(heap);
    heap_destruir(heap,NULL);
    print_test("El heap fue destruido correctamente con NULL",true);
}

void pruebas_heap_crear_desde_arreglo(void){
    int arr[9] = {0,3,6,1,7,11,2,4,8};
    void **v = malloc(sizeof(void*) * 10);
    for(size_t i = 0; i < 10; i++){
        v[i] = &arr[i];
        printf("V: %d \t",*(int*)v[i]);
    }
    // int valor1 = 1; int valor2 = 2; int valor3 = 5; int valor4 = 0; int valor5 = 9;
    // int valor1 = 7; int valor7 = 11; int valor8 = 8; int valor9 = 3; int valor10 = 10;
    heap_t *heap = heap_crear_arr(v,(size_t)9,comparar_enteros);
    heap_imprimir(heap);

    heap_destruir(heap,free);
}


void pruebas_heap_alumno(void){
    //Llamar aca a todas:
    //pruebas_heap_vacio();
    //pruebas_heap_encolar();
    pruebas_heap_crear_desde_arreglo();
}





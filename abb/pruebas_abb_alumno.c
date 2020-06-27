#include "abb.h"

#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

void imprimir_strings(void * str){
    printf(" %s \n",(char*)str);
}

void imprimir_enteros(void *dato){
    printf(" %d \n",*(int*)dato);
}

bool visitar(const char *clave, void *dato, void *extra){
    if( !(*(int*)dato % 2 == 0)){
        *(int*)dato *= *(int*)extra;
    }
    return true;
}

int comparar_enteros(const char *a,const char *b){
    int aux_a = atoi(a);
    int aux_b = atoi(b);
    if(aux_a > aux_b)
        return 1;
    else if( aux_a < aux_b)
        return -1;
    else
        return 0; 
    
}

void pruebas_guardar(){
    abb_t* abb = abb_crear(comparar_enteros,NULL);

    char *clave1 = "10";//, *valor1 = "guau";
    char *clave2 = "7";//, *valor2 = "miau";
    char *clave3 = "15";//, *valor3 = "mu";
    int v[10] = {10,7,15,3,1,5,15,13,12,2};
    
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, &v[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2,&v[1]));
    print_test("Prueba abb inserta r clave3", abb_guardar(abb, clave3,&v[2]));
        print_test("Prueba abb insertar clave1", abb_guardar(abb, "3", &v[3]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, "1", &v[4]));
    print_test("Prueba abb inserta r clave3", abb_guardar(abb, "5",&v[5]));
        print_test("Prueba abb insertar clave1", abb_guardar(abb, "15", &v[6]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, "13",&v[7]));
    print_test("Prueba abb inserta r clave3", abb_guardar(abb, "12", &v[8]));


    printf("Cantidad: %zu \n",abb_cantidad(abb));

    imprimir_arbol(abb,imprimir_strings);

    // abb_in_order(abb,visitar,&v[9]);
    // imprimir_arbol(abb,imprimir_enteros);

    // abb_borrar(abb,"1");
    // abb_borrar(abb,"5");
     abb_borrar(abb,"10");
    //abb_borrar(abb,"7");
    printf("\n\n");
    imprimir_arbol(abb,imprimir_strings);
    printf("Cantidad: %zu \n",abb_cantidad(abb));

}












void pruebas_abb_alumno(void){
    //Aca llamar a todas las funciones de pruebas
    pruebas_guardar();
}











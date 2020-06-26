#include "abb.h"

#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

// void imprimir_strings(void * str){
//     printf(" %s \n",(char*)str);
// }

void pruebas_guardar(){
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb inserta r clave3", abb_guardar(abb, clave3, valor3));

    printf("Cantidad: %zu \n",abb_cantidad(abb));

    //imprimir_arbol(abb,imprimir_strings);

}












void pruebas_abb_alumno(void){
    //Aca llamar a todas las funciones de pruebas
    pruebas_guardar();
}











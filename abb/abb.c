#include "abb.h"

typedef struct nodo_abb{
    struct nodo_abb *izq;
    struct nodo_abb *der;
    char* clave;
    void* dato;
}nodo_abb_t;

struct abb{
    nodo_abb_t *raiz;
    size_t cantidad;
    abb_destruir_dato_t destruir;
    //Comparar define si tengo que ir a derecha o a izquierda para buscar mi dato, si da == 0 entonces es el dato
    abb_comparar_clave_t comparar;
};

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t *abb = malloc(sizeof(abb_t));
    if(!abb)    return NULL;

    return abb;
}





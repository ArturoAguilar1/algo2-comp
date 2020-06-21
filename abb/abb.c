#define  _POSIX_C_SOURCE 200809L
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

struct abb_iter{
    const abb_t *abb;
    nodo_abb_t actual; 
};

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t *abb = malloc(sizeof(abb_t));
    if(!abb)    return NULL;
    
    abb->raiz = malloc(sizeof(nodo_abb_t));
    if(!abb->raiz){
        free(abb);
        return NULL;
    }
    //Tengo que inicializar los campos de nodo raiz?

    abb->cantidad = 0;
    abb->comparar = cmp;
    abb->destruir = destruir_dato;

    return abb;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    return true;
}


void *abb_borrar(abb_t *arbol, const char *clave){
    return NULL;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
    return NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    return true;
}

size_t abb_cantidad(abb_t *arbol){
    return arbol->cantidad;
}

void abb_destruir(abb_t *arbol){
    return;
}

// Iterador Interno
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    return;
}

//Iterador Externo

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t *abb_iter = malloc(sizeof(abb_iter_t));
    if(!abb_iter)   return NULL;

    abb_iter->abb = arbol;


    return abb_iter;
}


bool abb_iter_in_avanzar(abb_iter_t *iter){
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    return NULL;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return true;
}

void abb_iter_in_destruir(abb_iter_t* iter){
    free(iter);
}
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "hash.h"

//Tiene que ser si o si numero primo el inicial
#define TAM_HASH_INICIAL 13


typedef enum{
    VACIO = 0,
    OCUPADO = 1,
    BORRADO = 2,
}estado_t;

typedef struct{
    char *clave;
    void *dato;
    estado_t estado;
}hash_campo_t;

struct hash{
    size_t cantidad;
    size_t capacidad;
    hash_campo_t *campo;
    hash_destruir_dato_t destruir_hash;
};

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t * hash = malloc(sizeof(hash_t));
    if(!hash)   return NULL;

    hash->capacidad = TAM_HASH_INICIAL;
    hash->cantidad = 0;


    return hash;
}


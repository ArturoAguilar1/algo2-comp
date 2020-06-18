#include <stdlib.h>
#include <string.h>

#include "hash.h"

typedef enum{
    VACIO = 0,
    OCUPADO = 1,
    
}estado_t;

struct hash{
    size_t cantidad;
    size_t capacidad;
};

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t * hash = malloc(sizeof(hash_t));
    if(!hash)   return NULL;



    return hash;
}


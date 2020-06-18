#include <stdlib.h>
#include <string.h>

#include "hash.h"

struct hash{
    size_t cantidad;

};

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t * hash = malloc(sizeof(hash_t));
    if(!hash)   return NULL;



    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){

	
}
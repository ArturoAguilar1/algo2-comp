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
    hash_campo_t *tabla;
    hash_destruir_dato_t destruir_hash;
};

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t * hash = malloc(sizeof(hash_t));
    if(!hash)   
    	return NULL;

    hash->capacidad = TAM_HASH_INICIAL;
    hash->cantidad = 0;

    hash -> tabla = malloc(sizeof(hash_campo_t)*hash-> capacidad);
    if(!hash -> campo){
    	free(hash);
    	return NULL;
    }

    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	hash_campo_t * campo = malloc(sizeof(hash_campo_t));
	if(!campo)
		return false;

	

	campo -> clave = clave;
	campo -> dato = dato;
	campo -> estado = OCUPADO;

	int indice = f(clave) % hash -> capacidad;
	
	hash[indice] = campo;

	return true;

}

size_t hash_cantidad(const hash_t * hash){
	return hash->cantidad;
}

bool hash_borrar (hash_t * hash,const char * clave){


}
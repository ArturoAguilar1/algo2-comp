#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string.h>
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
    hash_destruir_dato_t destruir_hash_dato;
};

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t *hash = malloc(sizeof(hash_t));
    if(!hash)   
    	return NULL;

    hash->capacidad = TAM_HASH_INICIAL;
    hash->cantidad = 0;
    hash->destruir_hash_dato = destruir_dato;
    hash->tabla = malloc(sizeof(hash_campo_t)*hash->capacidad);
    if(!hash -> campo){
    	free(hash);
    	return NULL;
    }
    for(size_t i=0;i<hash->capacidad;i++)
    	hash->tabla[i].estado = VACIO; //Deberiamos dejar esto? siempre va a quedar O(13) pero como son siempre 13 elementos al final es O(1)

    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	hash_campo_t *campo = malloc(sizeof(hash_campo_t));
	if(!campo)
		return false;

	char *copia = strdup(clave); 
	campo -> clave = copia;
	campo -> dato = dato;
	campo -> estado = OCUPADO;

	int indice = f(clave) % hash -> capacidad;
	
	if(!strcmp(hash->tabla[indice]->clave),clave) //En esta parte no se si hay que borrar algo mas, la clave asumo que se encargaría barbara de borrarla, por lo tanto a nosotros no nos debería importar borrar la clave. 
		hash->destruir_hash_dato(hash->tabla[indice].dato); 
	//Quiero guardar la misma clave, hago el caso borde.

	else if(hash->tabla[indice].estado == OCUPADO){
		while(hash->tabla[indice].estado == VACIO){
			indice++;
			if(indice == hash -> capacidad); //Esto lo saqué del hash cerrado
				indice=0;
		}
	}
	//Falta ver lo del tema de redimensionar si completamos una cierta cantidad.

	hash->tabla[indice] = campo;


	return true;

}

size_t hash_cantidad(const hash_t *hash){
	return hash->cantidad;
}

bool hash_borrar (hash_t *hash,const char *clave){

}
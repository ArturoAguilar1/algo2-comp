#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string.h>
#include "hash.h"

//Tiene que ser si o si numero primo el inicial
#define TAM_HASH_INICIAL 13


//uint32_t murmurhash(const char *key, uint32_t len, uint32_t seed);

typedef enum{
    LIBRE = 0,
    OCUPADO = 1,
    BORRADO = 2,
}estado_t;

typedef struct{

    char *clave;
    void *dato;
    estado_t estado;
}hash_campo_t;

struct hash{
    size_t cant;
    size_t tam;
    hash_campo_t *tabla;
    hash_destruir_dato_t destruir_hash_dato;
};

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t *hash = malloc(sizeof(hash_t));
    if(!hash)   
    	return NULL;
    hash->tam = TAM_HASH_INICIAL;
    hash->cant = 0;
    hash->destruir_hash_dato = destruir_dato;
    hash->tabla = malloc(sizeof(hash_campo_t)*hash->tam);
    if(!hash->tabla){
    	free(hash);
    	return NULL;
    }
    for(size_t i=0;i<hash->tam;i++)
    	hash->tabla[i].estado = LIBRE; //Deberiamos dejar esto? siempre va a quedar O(13) pero como son siempre 13 elementos al final es O(1)

    return hash;
}

// bool hash_guardar(hash_t *hash, const char *clave, void *dato){
// 	uint32_t seed = 0;
// 	hash_campo_t *campo = malloc(sizeof(hash_campo_t));
// 	if(!campo)
// 		return false;

// 	char *copia = strdup(clave); 
// 	campo->clave = copia;
// 	campo->dato = dato;
// 	campo->estado = OCUPADO;

// 	int indice = murmurhash(clave,(uint32_t)strlen(clave),seed) % hash -> tam;
	
// 	if(!strcmp(hash->tabla[indice].clave,clave)) //En esta parte no se si hay que borrar algo mas, la clave asumo que se encargaría barbara de borrarla, por lo tanto a nosotros no nos debería importar borrar la clave. 
// 		hash->destruir_hash_dato(hash->tabla[indice].dato); 
// 	//Quiero guardar la misma clave, hago el caso borde.

// 	else if(hash->tabla[indice].estado == OCUPADO){
// 		while(hash->tabla[indice].estado == LIBRE){
// 			indice++;
// 			if(indice == hash->tam) //Esto lo saqué del hash cerrado
// 				indice = 0;
// 		}
// 	}
// 	//Falta ver lo del tema de redimensionar si completamos una cierta cantidad.

// 	hash->tabla[indice] = *campo;


// 	return true;

// }

size_t hash_cantidad(const hash_t *hash){
	return hash->cant;
}

void *hash_borrar(hash_t *hash, const char *clave){
	return NULL;
}





//Funcion de hash: Murmurhash3 de:
// https://github.com/jwerle/murmurhash.c/blob/master/murmurhash.c

// uint32_t murmurhash(const char *key, uint32_t len, uint32_t seed) {
//   uint32_t c1 = 0xcc9e2d51;
//   uint32_t c2 = 0x1b873593;
//   uint32_t r1 = 15;
//   uint32_t r2 = 13;
//   uint32_t m = 5;
//   uint32_t n = 0xe6546b64;
//   uint32_t h = 0;
//   uint32_t k = 0;
//   uint8_t *d = (uint8_t *) key; // 32 bit extract from `key'
//   const uint32_t *chunks = NULL;
//   const uint8_t *tail = NULL; // tail - last 8 bytes
//   int i = 0;
//   int l = len / 4; // chunk length

//   h = seed;

//   chunks = (const uint32_t *) (d + l * 4); // body
//   tail = (const uint8_t *) (d + l * 4); // last 8 byte chunk of `key'

//   // for each 4 byte chunk of `key'
//   for (i = -l; i != 0; ++i) {
//     // next 4 byte chunk of `key'
//     k = chunks[i];

//     // encode next 4 byte chunk of `key'
//     k *= c1;
//     k = (k << r1) | (k >> (32 - r1));
//     k *= c2;

//     // append to hash
//     h ^= k;
//     h = (h << r2) | (h >> (32 - r2));
//     h = h * m + n;
//   }

//   k = 0;

//   // remainder
//   switch (len & 3) { // `len % 4'
//     case 3: k ^= (tail[2] << 16);
//     case 2: k ^= (tail[1] << 8);

//     case 1:
//       k ^= tail[0];
//       k *= c1;
//       k = (k << r1) | (k >> (32 - r1));
//       k *= c2;
//       h ^= k;
//   }

//   h ^= len;

//   h ^= (h >> 16);
//   h *= 0x85ebca6b;
//   h ^= (h >> 13);
//   h *= 0xc2b2ae35;
//   h ^= (h >> 16);

//   return h;
// }


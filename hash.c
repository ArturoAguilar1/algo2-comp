#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string.h>
#include "hash.h"

//Tiene que ser si o si numero primo el inicial
#define TAM_HASH_INICIAL 13
#define FACTOR_DE_CARGA 0.7
#define TABLA_INICIO 0

uint32_t murmurhash (const char *key, uint32_t len, uint32_t seed);
uint32_t FNV1A_Pippip(const char *str, size_t wrdlen);

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

struct hast_iter{
	hash_t* hash;
	hash_campo_t actual;
	size_t posicion;
};



hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t *hash = malloc(sizeof(hash_t));
    if(!hash)   
    	return NULL;
	hash->tabla = malloc(sizeof(hash_campo_t)*TAM_HASH_INICIAL);
    if(!hash->tabla){
    	free(hash);
    	return NULL;
    }
		
    hash->tam = TAM_HASH_INICIAL;
    hash->cant = 0;
    hash->destruir_hash_dato = destruir_dato;

    for(size_t i=0;i<hash->tam;i++)
    	hash->tabla[i].estado = LIBRE; //Deberiamos dejar esto? siempre va a quedar O(13) pero como son siempre 13 elementos al final es O(1)

    return hash;
}

hash_t * hash_redimensionar(hash_t * nuevo, const hash_t *viejo){
	hash_t *hash = malloc(sizeof(hash_campo_t));
	if(!hash)
		return NULL;
	hash->tabla = malloc()

}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	uint32_t seed = 0;

	int indice = murmurhash(clave,(uint32_t)strlen(clave),seed) % hash -> tam;
	
	if(!strcmp(hash->tabla[indice].clave,clave)) //En esta parte no se si hay que borrar algo mas, la clave asumo que se encargaría barbara de borrarla, por lo tanto a nosotros no nos debería importar borrar la clave. 
		hash->destruir_hash_dato(hash->tabla[indice].dato); 
	//Quiero guardar la misma clave, hago el caso borde.

	//else if(hash->tabla[indice].estado == OCUPADO || hash->tabla[indice].estado == BORRADO) Al pedo este if porque si encuentro uno vacio nunca va a entrar en el while (19/06)
	while(hash->tabla[indice].estado == OCUPADO || hash->tabla[indice.estado == BORRADO]){
		indice++;
		if(indice >= hash->tam) //Esto lo saqué del hash cerrado
			indice = 0;
	}
	
	//Falta ver lo del tema de redimensionar si completamos una cierta cantidad.
	if((double)(hash->cantidad / hash->capacidad) >= FACTOR_DE_CARGA){
	}
	
	hash->tabla[indice].clave = strdup(clave); // Esto es lo que me había equivocado de no hacer un malloc sino que ya lo tenemos malloqueado (19/06)
	hash->tabla[indice].dato = dato;
	hash->tabla[indice].estado = OCUPADO;
	hash->cant++;

	return true;

}

size_t hash_cantidad(const hash_t *hash){
	return hash->cant;
}

void *hash_borrar(hash_t *hash, const char *clave){
	return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave){

		int indice = murmurhash(clave,(uint32_t)strlen(clave),seed) % hash -> tam;

	while(hash->tabla[indice].estado == OCUPADO || hash->tabla[indice].estado == BORRADO){
		while(hash->tabla[indice].estado == BORRADO){
			indice++;
			if(indice >= hash->tam)
				indice = 0;
		}
		
		if(!strcmp(hash->tabla[indice].clave,clave))
			break;
			
		indice++;
	
		if(indice >= hash->tam)
			indice = 0;
			
	}
	
	if(hash->tabla[indice].estado == VACIO)
		return NULL;

	return hash->tabla[indice].dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave){

	int indice = murmurhash(clave,(uint32_t)strlen(clave),seed) % hash -> tam;

	while(hash->tabla[indice].estado == OCUPADO || hash->tabla[indice].estado == BORRADO){
		while(hash->tabla[indice].estado == BORRADO){
			indice++;
			if(indice >= hash->tam)
				indice = 0;
		}
		
		if(!strcmp(hash->tabla[indice].clave,clave))
			break;
			
		indice++;
	
		if(indice >= hash->tam)
			indice = 0;
			
	}
	

	if(hash->tabla[indice].estado == VACIO)
		return false;

	return true;
}



void hash_destruir(hash_t *hash){

	for(size_t i=0;i<hash->tam;i++){
		if(hash->tabla[indice].estado == OCUPADO){ //el .h dice que debemos eliminar cada par, el tema es que no se si la funcion destruir hash dato recibe 2 parametros o 1, por eso lo puse dos veces (19/06)
			hash->destruir_hash_dato(hash->tabla[i].dato);
			hash->destruir_hash_dato(hash->tabla[i].clave);
		}
	}
	free(hash->tabla);
	free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
	hash_iter_t *iterador = malloc(sizeof(hash_iter_t));
	if(!iterador)
		return NULL;

	iterador->hash = hash;
	iterador.actual = hash->tabla[TABLA_INICIO];
	iterador->posicion = TABLA_INICIO;

	return iterador;
}

bool hash_iter_avanzar(hash_iter_t *iter){
	if(hash_iter_al_final(iter))
		return false;
	iter->posicion++;
	iter.actual = iter->hash->tabla[posicion];
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
	const char clave = strdup(iter->actual.clave);
	return clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
	return iter->posicion < iter->hash->tam
}

void hash_iter_destruir(hash_iter_t* iter){
	free(iter);
}


//Funcion de hash: Murmurhash3 de:
// https://github.com/jwerle/murmurhash.c/blob/master/murmurhash.c

uint32_t murmurhash(const char *key, uint32_t len, uint32_t seed) {
  uint32_t c1 = 0xcc9e2d51;
  uint32_t c2 = 0x1b873593;
  uint32_t r1 = 15;
  uint32_t r2 = 13;
  uint32_t m = 5;
  uint32_t n = 0xe6546b64;
  uint32_t h = 0;
  uint32_t k = 0;
  uint8_t *d = (uint8_t *) key; // 32 bit extract from `key'
  const uint32_t *chunks = NULL;
  const uint8_t *tail = NULL; // tail - last 8 bytes
  int i = 0;
  int l = len / 4; // chunk length

  h = seed;

  chunks = (const uint32_t *) (d + l * 4); // body
  tail = (const uint8_t *) (d + l * 4); // last 8 byte chunk of `key'

  // for each 4 byte chunk of `key'
  for (i = -l; i != 0; ++i) {
    // next 4 byte chunk of `key'
    k = chunks[i];

    // encode next 4 byte chunk of `key'
    k *= c1;
    k = (k << r1) | (k >> (32 - r1));
    k *= c2;

    // append to hash
    h ^= k;
    h = (h << r2) | (h >> (32 - r2));
    h = h * m + n;
  }

  k = 0;

  // remainder
  switch (len & 3) { // `len % 4'
    case 3: k ^= (tail[2] << 16);
    case 2: k ^= (tail[1] << 8);

    case 1:
      k ^= tail[0];
      k *= c1;
      k = (k << r1) | (k >> (32 - r1));
      k *= c2;
      h ^= k;
  }

  h ^= len;

  h ^= (h >> 16);
  h *= 0x85ebca6b;
  h ^= (h >> 13);
  h *= 0xc2b2ae35;
  h ^= (h >> 16);

  return h;
}

/*La encontre en: https://www.codeproject.com/Articles/716530/Fastest-Hash-Function-for-Table-Lookups-in-C
Ahi explica que tiene muy buen rendimiento comparado a otras.
Necesita la macro de funcion _PaDr_KAZE
*/
uint32_t FNV1A_Pippip(const char *str, size_t wrdlen) {
	const uint32_t PRIME = 591798841; 
  uint32_t hash32; 
  uint64_t hash64 = 14695981039346656037U;
	size_t Cycles, NDhead;
  if (wrdlen > 8) {
	Cycles = ((wrdlen - 1)>>4) + 1; NDhead = wrdlen - (Cycles<<3);
  #pragma nounroll
        for(; Cycles--; str += 8) {
		hash64 = ( hash64 ^ (*(uint64_t *)(str)) ) * PRIME;        
		hash64 = ( hash64 ^ (*(uint64_t *)(str+NDhead)) ) * PRIME;        
	}
} else
	hash64 = ( hash64 ^ _PADr_KAZE(*(uint64_t *)(str+0), (8-wrdlen)<<3) ) * PRIME;        
  hash32 = (uint32_t)(hash64 ^ (hash64>>32)); 

return hash32 ^ (hash32 >> 16);
} 


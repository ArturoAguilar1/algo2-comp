#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

void pruebas_hash_catedra(void);
void pruebas_volumen_catedra(size_t);


uint32_t murmurhash (const char *key, uint32_t len, uint32_t seed);

int main(int argc, char *argv[])
{
    // if (argc > 1) {
    //     // Asumimos que nos están pidiendo pruebas de volumen.
    //     long largo = strtol(argv[1], NULL, 10);
    //     pruebas_volumen_catedra((size_t) largo);

    //     return failure_count() > 0;
    // }

    // printf("\n~~~ PRUEBAS CÁTEDRA ~~~\n");
    // pruebas_hash_catedra();
    printf("Prueba con funcion hash:\n");
    const char *key = "hola";
    printf("hola\n");
    uint32_t seed = 0;
    uint32_t hash = murmurhash(key,(uint32_t)strlen(key),seed);
    printf("Hasheado1: %u \n",hash);

    uint32_t hash1 = murmurhash("Hola",(uint32_t)strlen(key),seed);
    printf("Hasheado2: %u \n",hash1);

    uint32_t hash2 = murmurhash("Arturo Javier Aguilar Lopez",(uint32_t)strlen(key),seed);
    printf("Hasheado2: %u \n",hash2);


    return failure_count() > 0;
}


uint32_t murmurhash (const char *key, uint32_t len, uint32_t seed) {
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


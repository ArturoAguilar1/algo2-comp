#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "hash.h"

//Tiene que ser si o si numero primo el inicial
#define TAM_HASH_INICIAL 13
#define FACTOR_REDIMENSION 0.7

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
    size_t cantidad;
    size_t capacidad;
    size_t carga;
    hash_campo_t *tabla;
    hash_destruir_dato_t destruir_dato;
};

struct hash_iter{

};

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t * hash = malloc(sizeof(hash_t));
    if(!hash)   return NULL;

    hash->capacidad = TAM_HASH_INICIAL;
    hash->cantidad = 0;


    return hash;
}

/*
Se debe guardar una copia de la clave! -> strdup
En el cerrado se busca a partir del índice obtenido con la función de hashing una posición que esté libre (Linear Probing). Para esto es necesario tener en cuenta los estados (LIBRE, OCUPADO y BORRADO, sobre el último se va a hablar en siguientes clases). Los estados lo debería implementar usando enum.
Si se quiere guardar con una clave que ya está en el TDA, se debe reemplazar el valor guardado por el nuevo.
*/
bool hash_guardar(hash_t *hash, const char *clave, void *dato){
}


//Tanto el el abierto (buscando en listas) como en el cerrado (buscando posición a partir de índice obtenido),
//se busca de la misma forma que se inserta, hasta encontrar un elemento con la clave deseada.
void *hash_obtener(const hash_t *hash, const char *clave){

}


/*Se debe redimensionar cada vez que el factor de carga \alpha = n/m (n representa la cantidad de elementos, m representa el tamaño de la tabla) supere un valor definido (factor de redimensión).
En el caso del hash cerrado, a la hora de calcular \alpha, en n se deben contar la cantidad de elementos borrados y ocupados (que son las pociones en las cuales no se puede insertar).
En el caso del hash cerrado, \alpha es la proporción de posiciones ocupadas, por lo que toma valores entre 0 y 1, por este motivo el factor de redimensión deberá ser un número entre esos valores (como puede ser 0.7).
Al redimensionar se debe crear una tabla nueva y volver a hashear todos los elementos, ya que al cambiar el tamaño cambiaran los índices obtenidos al aplicarle h(k) % m (h(k) % m).
*/
//Hash redimensionar
//bool redimensionar_hash(hast_t* hash){}


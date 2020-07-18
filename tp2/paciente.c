#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "paciente.h"

struct paciente{
    int año_inscripcion;
    char *nombre;
};

paciente_t *paciente_crear(const char *nombre, int año){
    paciente_t *paciente = malloc(sizeof(paciente_t));
    if(!paciente)   return NULL;

    paciente->nombre = strdup(nombre);
    if(!paciente->nombre){
        free(paciente);
        return NULL;
    }

    paciente->año_inscripcion = año;

    return paciente;
}

void *paciente_parse(char** params, void *extra){
    return paciente_crear(params[0],atoi(params[1]));
}

void paciente_destruir(paciente_t *p){
    free(p->nombre);
    free(p);
}

void paciente_imprimir(paciente_t *pac){
    printf("%s : %d \n", pac->nombre,pac->año_inscripcion);
}


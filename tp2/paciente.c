#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "paciente.h"

struct paciente{
    int ano_inscripcion;
    char *nombre;
};

paciente_t *paciente_crear(const char *nombre, int ano){
    paciente_t *paciente = malloc(sizeof(paciente_t));
    if(!paciente)   return NULL;

    paciente->nombre = strdup(nombre);
    if(!paciente->nombre){
        free(paciente);
        return NULL;
    }

    paciente->ano_inscripcion = ano;

    return paciente;
}

char *paciente_nombre(paciente_t *pac){
    return pac->nombre;
}

void *paciente_parse(char** params, void *extra){
    return paciente_crear(params[0],atoi(params[1]));
}

void paciente_destruir(paciente_t *p){
    free(p->nombre);
    free(p);
}

void paciente_imprimir(paciente_t *pac){
    printf("%s : %d \n", pac->nombre,pac->ano_inscripcion);
}


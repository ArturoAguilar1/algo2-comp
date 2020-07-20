#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "doctor.h"

struct doctor{
    char * nombre;
    char * especialidad;
    size_t cant_pacientes_atendidos;
};

void doctor_atender(doctor_t *doc){
    doc->cant_pacientes_atendidos++;
}

char *doctor_especialidad(doctor_t *doc){
    return doc->especialidad;
}

size_t doctor_cantidad_pacientes_atendidos(doctor_t *doc){
    return doc->cant_pacientes_atendidos;
}

const char *doctor_nombre(doctor_t *doc){
    return doc->nombre;
}

doctor_t *doctor_crear(const char *nombre, char* esp){
    doctor_t *doctor = malloc(sizeof(doctor_t));
    if(!doctor) return NULL;

    doctor->nombre = strdup(nombre);
    if(!doctor->nombre){
        free(doctor);
        return NULL;
    }

    doctor->especialidad = strdup(esp);
    if(!doctor->especialidad){
        free(doctor);
        free(doctor->nombre);
        return NULL;
    }

    doctor->cant_pacientes_atendidos = 0;

    return doctor;
}

void *doctor_parse(char** params, void *extra){
    return doctor_crear(params[0],params[1]);
}

void doctor_destruir(doctor_t *doc){
    free(doc->especialidad);
    free(doc->nombre);
    free(doc);
}

void doctor_imprimir(doctor_t *doc){
    printf("%s : %s \n",doc->nombre,doc->especialidad);
}


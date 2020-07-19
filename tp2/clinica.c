#include <stdio.h>

#include "mensajes.h"
#include "hash.h"
#include "lista.h"
#include "abb.h"
#include "paciente.h"
#include "turnos.h"
#include "doctor.h"
#include "heap.h"
typedef enum{
    OK,
    ERROR_PACIENTE_NO_ENCONTRADO,
    ERROR_NO_EXISTE_ESP,
    ERROR_URGENCIA
}st_pedir_turno;

typedef struct clinica{
	lista_t *lista_doctores;
	lista_t *lista_pacientes;
	hash_t *hash_especialidades;
	hash_t *hash_pacientes;
	abb_t *abb_doctores;
}clinica_t;

clinica_t *clinica_crear(char *archivo_doc, char *archivo_pac){
    clinica_t *clinica = malloc(sizeof(clinica_t));
    if(!clinica)    return NULL;

    clinica->lista_doctores = csv_crear_estructura(archivo_doc,doctor_parse,NULL);
    if(!clinica->lista_doctores){
        free(clinica);
        return NULL;
    }
    clinica->lista_pacientes = csv_crear_estructura(archivo_pac,paciente_parse,NULL);
    if(!clinica->lista_pacientes){
        free(clinica);
        lista_destruir(clinica->lista_doctores,doctor_destruir);
        return NULL;
    }

    
    clinica->hash_especialidades = especialidades_a_hash(clinica->lista_doctores);
    if(!clinica->hash_especialidades){
        free(clinica);
        lista_destruir(clinica->lista_doctores,doctor_destruir);
        lista_destruir(clinica->lista_pacientes,paciente_destruir);
        return NULL;
    }

    clinica->hash_pacientes = pacientes_a_hash(clinica->lista_pacientes);
    if(!clinica->hash_pacientes){
        free(clinica);
        lista_destruir(clinica->lista_doctores,doctor_destruir);
        lista_destruir(clinica->lista_pacientes,paciente_destruir);
        hash_destruir(clinica->hash_especialidades);
        return NULL;
    }

    clinica->abb_doctores = doctores_a_abb(clinica->lista_doctores);
    if(!clinica->abb_doctores){
        free(clinica);
        lista_destruir(clinica->lista_doctores,doctor_destruir);
        lista_destruir(clinica->lista_pacientes,paciente_destruir);
        hash_destruir(clinica->hash_especialidades);
        hash_destruir(clinica->hash_pacientes);
        return NULL;
    }

    return clinica;
}

int prioridad_pacientes(const void *a,const void *b){

    return 0;
}

abb_t *doctores_a_abb(const lista_t *lista){

}

hash_t *pacientes_a_hash(const lista_t *lista){

}

hash_t *especialidades_a_hash(const lista_t *lista){
    hash_t *hash_esp = hash_crear(turnos_destruir);
    if(!hash_esp)   return NULL;
    lista_iter_t *iter = lista_iter_crear(lista);
    if(!iter){
        free(hash_esp);
        return NULL;
    }
    while(!lista_iter_al_final(iter)){
        turnos_t *turnos = turno_crear(prioridad_pacientes);
        if(!turnos) return NULL;
        doctor_t *doc = lista_iter_ver_actual(iter);
        hash_guardar(hash_esp,doctor_especialidad(doc),turnos);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);

    return hash_esp;
}

clinica_imprimir_atender(st_atender){
    //OK :  Se atiende a NOMBRE_PACIENTE
    //N paciente(s) en espera para NOMBRE_ESPECIALIDAD
    
}

void clinica_pedir_turno(clinica_t *clinica, char **params){
    st_pedir_turno st;
    size_t *cant_pacientes_encolados;
    st = pedir_turno(clinica,params,&cant_pacientes_encolados);
    switch (st){
    case OK:
        fprintf(stdout,PACIENTE_ENCOLADO,params[0]);
        fprintf(stdout,CANT_PACIENTES_ENCOLADOS,cant_pacientes_encolados,params[1]);
        break;
    case ERROR_PACIENTE_NO_ENCONTRADO:
        fprintf(stdout,ENOENT_PACIENTE,params[0]);
        break;
    case ERROR_NO_EXISTE_ESP:
        fprintf(stdout,ENOENT_ESPECIALIDAD,params[1]);
        break;
    case ERROR_URGENCIA:
        fprintf(stdout,ENOENT_URGENCIA,params[2]);
    default:
        break;
    }
}

st_pedir_turno pedir_turno(clinica_t *clinica,char**params,size_t *cant_pacientes_encolados){
    paciente_t *paciente = hash_obtener(clinica->hash_pacientes,params[0]);
    if(!paciente){
        //no pertenece
        return ERROR_PACIENTE_NO_ENCONTRADO;
    }
    turnos_t *turno = hash_obtener(clinica->hash_especialidades,params[1]);
    if(!turno){
        //no pertene la especilidad en el hash especialides
        return ERROR_NO_EXISTE_ESP;
    }
    
    if(!turno_encolar(turno,paciente,cant_pacientes_encolados,params[2])){
        return ERROR_URGENCIA;
    }
    else{
        return OK;
    }
}

// void encolar_turno(hash_t *especialidades,char *esp,size_t *cant_pacientes_encolados){
//     turnos_t *turnos = hash_obtener(especialides,esp);
//     if(!turnos){
//         hash_guardar(especialidades,turnos_crear())
//     }
//     if(!strcmp(params[2],"URGENTE")){
//         cola_encolar(turnos->cola,)
//     }
// }





#include "mensajes.h"
#include "hash.h"
#include "lista.h"
#include "abb.h"
#include "paciente.h"
#include "turnos.h"

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
        fprintf(stdout,CANT_PACIENTES_ENCOLADOS,cant_pacientes_encolados,params[1])
        break;
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



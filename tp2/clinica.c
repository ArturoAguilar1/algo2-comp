#include <stdio.h>
#include <string.h>

#include "mensajes.h"
#include "hash.h"
#include "lista.h"
#include "abb.h"
#include "paciente.h"
#include "turnos.h"
#include "doctor.h"
#include "heap.h"
#include "clinica.h"
#include "csv.h"
typedef enum{
    OK_PEDIR_TURNO,
    ERROR_PACIENTE_NO_ENCONTRADO,
    ERROR_NO_EXISTE_ESP,
    ERROR_URGENCIA
}st_pedir_turno;

typedef enum{
    OK_ATENDER_SIG,
    ERROR_NO_PACIENTES_ESPERA,
    ERROR_NOMBRE_DOCTOR
}st_atender_sig;

struct clinica{
	lista_t *lista_doctores;
	lista_t *lista_pacientes;
	hash_t *hash_especialidades;
	hash_t *hash_pacientes;
	abb_t *abb_doctores;
};

abb_t *doctores_a_abb(lista_t *lista);
hash_t *pacientes_a_hash(lista_t *lista);
hash_t *especialidades_a_hash(lista_t *lista);
st_pedir_turno pedir_turno(clinica_t *clinica,char **params,size_t *cant_pacientes_encolados);
st_atender_sig atender_siguiente(clinica_t *clinica,char *nom_doctor,size_t *cant_pac_espera,char *especialidad, char *nom_paciente);

void wrapper_destruir_doctor(void *dato){
    doctor_destruir(dato);
}

void wrapper_destruir_paciente(void *dato){
    paciente_destruir(dato);
}

void wrapper_destruir_turno(void *dato){
    turnos_destruir(dato);
}

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
        lista_destruir(clinica->lista_doctores,wrapper_destruir_doctor);
        return NULL;
    }

    
    clinica->hash_especialidades = especialidades_a_hash(clinica->lista_doctores);
    if(!clinica->hash_especialidades){
        free(clinica);
        lista_destruir(clinica->lista_doctores,wrapper_destruir_doctor);
        lista_destruir(clinica->lista_pacientes,wrapper_destruir_paciente);
        return NULL;
    }

    clinica->hash_pacientes = pacientes_a_hash(clinica->lista_pacientes);
    if(!clinica->hash_pacientes){
        free(clinica);
        lista_destruir(clinica->lista_doctores,wrapper_destruir_doctor);
        lista_destruir(clinica->lista_pacientes,wrapper_destruir_paciente);
        hash_destruir(clinica->hash_especialidades);
        return NULL;
    }

    clinica->abb_doctores = doctores_a_abb(clinica->lista_doctores);
    if(!clinica->abb_doctores){
        free(clinica);
        lista_destruir(clinica->lista_doctores,wrapper_destruir_doctor);
        lista_destruir(clinica->lista_pacientes,wrapper_destruir_paciente);
        hash_destruir(clinica->hash_especialidades);
        hash_destruir(clinica->hash_pacientes);
        return NULL;
    }

    return clinica;
}

// int prioridad_pacientes(const void *a,const void *b){

//     return 0;
// }

abb_t *doctores_a_abb( lista_t *lista){
    abb_t *abb_docs = abb_crear(strcmp,NULL);
    if(!abb_docs)   return NULL;
    lista_iter_t *iter = lista_iter_crear(lista);
    if(!iter){
        free(abb_docs);
        return NULL;
    }
    while(!lista_iter_al_final(iter)){
        doctor_t *doc = lista_iter_ver_actual(iter);
        abb_guardar(abb_docs,doctor_nombre(doc),doc);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);

    return abb_docs;
}

hash_t *pacientes_a_hash(lista_t *lista){
    hash_t *hash_pacientes = hash_crear(NULL);
    if(!hash_pacientes) return NULL;

    lista_iter_t *iter = lista_iter_crear(lista);
    if(!iter){
        free(hash_pacientes);
        return NULL;
    }
    while(!lista_iter_al_final(iter)){
        paciente_t *paciente = lista_iter_ver_actual(iter);
        hash_guardar(hash_pacientes,paciente_nombre(paciente),paciente);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);

    return hash_pacientes;
}

hash_t *especialidades_a_hash(lista_t *lista){
    hash_t *hash_esp = hash_crear(wrapper_destruir_turno);
    if(!hash_esp)   return NULL;
    lista_iter_t *iter = lista_iter_crear(lista);
    if(!iter){
        free(hash_esp);
        return NULL;
    }
    while(!lista_iter_al_final(iter)){
        turnos_t *turnos = turno_crear();
        if(!turnos) return NULL;
        doctor_t *doc = lista_iter_ver_actual(iter);
        hash_guardar(hash_esp,doctor_especialidad(doc),turnos);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);

    return hash_esp;
}
/*
clinica_imprimir_atender(st_atender){
    //OK :  Se atiende a NOMBRE_PACIENTE
    //N paciente(s) en espera para NOMBRE_ESPECIALIDAD
    
}*/

void clinica_pedir_turno(clinica_t *clinica, char **params){
    st_pedir_turno st;
    size_t cant_pacientes_encolados;
    st = pedir_turno(clinica,params,&cant_pacientes_encolados);
   // hash_imprimir(clinica->hash_especialidades);
    switch (st){
    case OK_PEDIR_TURNO:
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

st_pedir_turno pedir_turno(clinica_t *clinica,char **params,size_t *cant_pacientes_encolados){
    paciente_t *paciente = hash_obtener(clinica->hash_pacientes,params[0]);
    if(!paciente){
        //no pertenece
        return ERROR_PACIENTE_NO_ENCONTRADO;
    }
    turnos_t *turno = hash_obtener(clinica->hash_especialidades,params[1]);
    // if(!turno){
    //     //no pertene la especilidad en el hash especialides
    //     return ERROR_NO_EXISTE_ESP;
    // }
    printf("Params[0]:%s, Params[1]: %s , Params[2]: %s \n", params[0],params[1],params[2]);
    if(!turno_encolar(turno,paciente,cant_pacientes_encolados,params[2])){
        return ERROR_URGENCIA;
    }
    else{
        return OK_PEDIR_TURNO;
    }
}

// void clinica_atender_siguiente(clinica_t *clinica, char **params){
//     st_atender_sig st;
//     size_t cant_pacientes_espera;
//     char *esp;
//     char *nom_paciente;
//     //O tambien directamente, podria mandarle a atender siguiente los datos del paciente o doctor

//     st = atender_siguiente(clinica,params[0],&cant_pacientes_espera,esp,nom_paciente);
//     switch (st){
//     case OK_ATENDER_SIG:
//         fprintf(stdout,PACIENTE_ATENDIDO,nom_paciente);
//         fprintf(stdout,CANT_PACIENTES_ENCOLADOS,cant_pacientes_espera,esp);
//         break;
//     case ERROR_NO_PACIENTES_ESPERA:
//         fprintf(stdout,SIN_PACIENTES);
//         break;
//     case ERROR_NOMBRE_DOCTOR:
//         fprintf(stdout,ENOENT_DOCTOR,params[0]);
//         break;
//     default:
//         break;
//     }
// }

// st_atender_sig atender_siguiente(clinica_t *clinica,char *nom_doctor,size_t *cant_pac_espera,char *especialidad, char *nom_paciente){
//     //Busco el doctor en abb -> O(log(d))
//     doctor_t *doc = abb_obtener(clinica->abb_doctores,nom_doctor);
//     if(!doc){
//         //no existe el doctor
//         return ERROR_NOMBRE_DOCTOR;
//     }
//     //busco su especialidad en hash_esp
//     turnos_t *turno = hash_obtener(clinica->hash_especialidades,doctor_especialidad(doc));
//     if(turnos_vacios(turno)){
//         //DADA LA especialidad que me pasan, me fijo si hay pacientes que atender o no
//         return ERROR_NO_PACIENTES_ESPERA;
//     }
//     //Ya el punteor que apunta a cola_urgencia y heap_regulares dada la especialidad del doctor ingresado

//     doctor_atender(doc);
//     especialidad = doctor_especialidad(doc);
//     //que turnos, que puede acceder a la estructura de turnos, me diga cuantos pacientes hay para la especialdiad y
//     // tambien que paciende desencoló 
//     //turnos_desencolar(cant_pac_espera,nom_paciente);


//     return OK_ATENDER_SIG;
// }

// void encolar_turno(hash_t *especialidades,char *esp,size_t *cant_pacientes_encolados){
//     turnos_t *turnos = hash_obtener(especialides,esp);
//     if(!turnos){
//         hash_guardar(especialidades,turnos_crear())
//     }
//     if(!strcmp(params[2],"URGENTE")){
//         cola_encolar(turnos->cola,)
//     }
// }


void clinica_destruir(clinica_t *clinica){
    lista_destruir(clinica->lista_doctores,wrapper_destruir_doctor);
    lista_destruir(clinica->lista_pacientes,wrapper_destruir_paciente);
    hash_destruir(clinica->hash_especialidades);
    hash_destruir(clinica->hash_pacientes);
    abb_destruir(clinica->abb_doctores);
    free(clinica);
}



// bool imp_doctores(void *dato, void*extra){
// 	doctor_imprimir(dato);
// 	return true;
// }

// bool imp_pacientes(void *dato, void *extra){
// 	paciente_imprimir(dato);
// 	return true;
// }

// void wrraper_destruir_doc(void *dato){
// 	doctor_destruir(dato);
// }

// void wrraper_destruir_pac(void *dato){
// 	paciente_destruir(dato);
// }


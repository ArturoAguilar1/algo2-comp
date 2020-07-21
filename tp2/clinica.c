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
st_atender_sig atender_siguiente(clinica_t *clinica,char *nom_doctor,size_t *cant_pac_espera,char *nom_paciente,char *especialidad);

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

int prioridad_pacientes_regulares(const void *a, const void *b){
    int aux1 = paciente_ano_inscripcion((paciente_t*)a);
    int aux2 = paciente_ano_inscripcion((paciente_t*)b);
    if(aux1 > aux2)
        return -1;
    else if(aux1 < aux2)
        return 1;
    else
        return 0;
    
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
        turnos_t *turnos = turno_crear(prioridad_pacientes_regulares);
        if(!turnos) {
            free(hash_esp);
            lista_iter_destruir(iter);
            return NULL;
        }
        doctor_t *doc = lista_iter_ver_actual(iter);
        hash_guardar(hash_esp,doctor_especialidad(doc),turnos);;
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);

    return hash_esp;
}

void clinica_pedir_turno(clinica_t *clinica,char **params){
    st_pedir_turno st;
    size_t cant_pacientes_encolados;
    st = pedir_turno(clinica,params,&cant_pacientes_encolados);
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
        return ERROR_PACIENTE_NO_ENCONTRADO;
    }
    turnos_t *turno = hash_obtener(clinica->hash_especialidades,params[1]);
    if(!turno){
        return ERROR_NO_EXISTE_ESP;
    }
    if(!turno_encolar(turno,paciente,cant_pacientes_encolados,params[2])){
        return ERROR_URGENCIA;
    }
    else{
        return OK_PEDIR_TURNO;
    }
}


void clinica_atender_siguiente(clinica_t *clinica,char **params){
    size_t cant_pacientes_espera;
    doctor_t *doc = abb_obtener(clinica->abb_doctores,params[0]);
    if(!doc){
        fprintf(stdout,ENOENT_DOCTOR,params[0]);
        return;
    }
    turnos_t *turno = hash_obtener(clinica->hash_especialidades,doctor_especialidad(doc));
    if(turnos_vacios(turno)){
        fprintf(stdout,SIN_PACIENTES);
        return;
    }
    doctor_atender(doc);
    char *nom_paciente = turno_desencolar(turno,&cant_pacientes_espera);
    fprintf(stdout,PACIENTE_ATENDIDO,nom_paciente);
    fprintf(stdout,CANT_PACIENTES_ENCOLADOS,cant_pacientes_espera,doctor_especialidad(doc));

    return;

}

size_t cant_rango(abb_t *abb,char *inicio, char *fin){
    abb_iter_t *abb_iter = abb_iter_in_crear(abb,inicio,fin);
    if(!abb_iter){
        //fprintf(stdout,DOCTORES_SISTEMA,(size_t)0);
        return 0;
    }
    size_t contador = 0;
    while(!abb_iter_in_al_final(abb_iter)){
        contador++;
        if(!abb_iter_in_avanzar(abb_iter))
            break;
    }
    abb_iter_in_destruir(abb_iter);
    return contador;
}
void clinica_informe_doctores(clinica_t *clinica, char **params){
    if(abb_cantidad(clinica->abb_doctores) == 0){
        fprintf(stdout,DOCTORES_SISTEMA,abb_cantidad(clinica->abb_doctores));
        return;
    }
    size_t cantidad_rango = cant_rango(clinica->abb_doctores,params[0],params[1]);
    fprintf(stdout,DOCTORES_SISTEMA,cantidad_rango);

    if(cantidad_rango != 0){
    abb_iter_t *abb_iter = abb_iter_in_crear(clinica->abb_doctores,params[0],params[1]);
    if(!abb_iter){
        return;
    }
    size_t i = 1;
    while(!abb_iter_in_al_final(abb_iter)){
        doctor_t *doc = abb_obtener(clinica->abb_doctores,abb_iter_in_ver_actual(abb_iter));
        fprintf(stdout,INFORME_DOCTOR,i++,doctor_nombre(doc),doctor_especialidad(doc),doctor_cantidad_pacientes_atendidos(doc));
        if(!abb_iter_in_avanzar(abb_iter))
            break;
    }
    abb_iter_in_destruir(abb_iter);
    }
}
void clinica_destruir(clinica_t *clinica){
    lista_destruir(clinica->lista_doctores,wrapper_destruir_doctor);
    lista_destruir(clinica->lista_pacientes,wrapper_destruir_paciente);
    hash_destruir(clinica->hash_especialidades);
    hash_destruir(clinica->hash_pacientes);
    abb_destruir(clinica->abb_doctores);
    free(clinica);
}


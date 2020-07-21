#ifndef __CLINICA__H_
#define __CLINICA__H_

typedef struct clinica clinica_t;

// Crea un expediente de la clínica
clinica_t *clinica_crear(char *archivo_doc, char *archivo_pac);

// Pide un turno para un paciente contemplando si se trata de una urgencia o un turno regular, especificando la especialidad. Si se pasa alguna especialidad o paciente incorrecto, no se pide el turno e informa el error.
// Pre: Se creó el expediente de la clínica. Se computaron los pacientes afiliados a la clínica.
// Post: Se pidió un turno a el paciente asignado, si se dieron los parámetros correctos.
void clinica_pedir_turno(clinica_t *clinica,char **params);

// Destruye el expediente de la clínica.
// Pre: Se creó el expediente de la clínica.
// Post: Se destruyó el expediente de la clínica.
void clinica_destruir(clinica_t *clinica);

// Atiende al siguiente paciente de una especialidad asignada, priorizando a los casos urgentes. De no haberlos prioriza a los regulares con mas años de antiguedad en la clínica.
// En caso de un mal uso del mismo (Especialidad o doctores inexistentes) no hace nada e informa del error.
// Pre: Se creó el expediente de la clínica. Se computaron los doctores que trabajan para la clínica.
// Post: Se atiende al paciente designado, si se dieron los parámetros correctos.

void clinica_atender_siguiente(clinica_t *clinica, char **params);

// Informa todos los doctores presentes en la clínica (o los que se deseén saber), y su especialidad.
// Pre: Se creó el expediente de la clínica. Se computaron los doctores que trabajan para la clínica.
// Post: Devuelve una lista con todos (o los que se deseén) los doctores y su especialidad. 
void clinica_informe_doctores(clinica_t *clinica, char **params);

#endif 


#ifndef __CLINICA__H_
#define __CLINICA__H_

typedef struct clinica clinica_t;

clinica_t *clinica_crear(char *archivo_doc, char *archivo_pac);
void clinica_pedir_turno(clinica_t *clinica, char **params);
void clinica_destruir(clinica_t *clinica);

#endif 
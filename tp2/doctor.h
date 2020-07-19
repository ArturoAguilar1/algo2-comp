#ifndef DOCTOR_H
#define DOCTOR_H

typedef struct doctor doctor_t;

doctor_t *doctor_crear(const char *nombre, char* especialidad);
void doctor_destruir(doctor_t *doc);
void *doctor_parse(char** params, void *extra);
void doctor_imprimir(doctor_t *doc);
char *doctor_especialidad(doctor_t *doc);
const char *doctor_nombre(doctor_t *doc);
void doctor_atender(doctor_t *doc);

#endif


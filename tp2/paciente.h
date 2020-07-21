#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente paciente_t;

paciente_t *paciente_crear(const char *nombre, int ano);
void paciente_destruir(paciente_t *p);
void *paciente_parse(char** params, void *extra);
void paciente_imprimir(paciente_t *pac);
int paciente_ano_inscripcion(paciente_t *paciente);
char *paciente_nombre(paciente_t *pac);

#endif


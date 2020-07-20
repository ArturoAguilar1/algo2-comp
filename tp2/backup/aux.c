//Pedazos de codigo por si se necesitan despues
// void clinica_atender_siguiente(clinica_t *clinica, char **params){
//     st_atender_sig st;
//     size_t cant_pacientes_espera;
//     //doctor_t *doc = abb_obtener(clinica->abb_doctores,params[0]);
//     char *esp = malloc(sizeof(char)*15);
//     char *nom_paciente = malloc(sizeof(char)*15);
//     //O tambien directamente, podria mandarle a atender siguiente los datos del paciente o doctor

//     st = atender_siguiente(clinica,params[0],&cant_pacientes_espera,nom_paciente,esp);
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
//     free(esp);
//     free(nom_paciente);
// }

// st_atender_sig atender_siguiente(clinica_t *clinica,char *nom_doctor,size_t *cant_pac_espera,char *nom_paciente,char *especialidad){
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
//     nom_paciente = turno_desencolar(turno,cant_pac_espera);


//     return OK_ATENDER_SIG;
// }

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

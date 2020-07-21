//Pedazos de codigo por si se necesitan despues


    // lista_t *lista_informe = lista_crear();
    // if(!lista_informe){
    //     return;
    // }
    // while(!abb_iter_in_al_final(abb_iter)){
    //     doctor_t *doc = abb_obtener(clinica->abb_doctores,abb_iter_in_ver_actual(abb_iter));
    //     lista_insertar_ultimo(lista_informe,doc);
    //     contador_doc++;
    //     if(!abb_iter_in_avanzar(abb_iter))
    //         break;
    // }
    // abb_iter_in_destruir(abb_iter);
//     lista_iter_t *iter_lista = lista_iter_crear(lista_informe);
//     if(!iter_lista){
//         lista_destruir(lista_informe,NULL);
//         return;
//     }
//     fprintf(stdout,DOCTORES_SISTEMA,contador_doc);
//     size_t i = 1;
//     while(!lista_iter_al_final(iter_lista)){
//         doctor_t *doc = lista_iter_ver_actual(iter_lista);
//         fprintf(stdout,INFORME_DOCTOR,i++,doctor_nombre(doc),doctor_especialidad(doc),doctor_cantidad_pacientes_atendidos(doc));
//         lista_iter_avanzar(iter_lista);
//     }
//     lista_iter_destruir(iter_lista);
//     lista_destruir(lista_informe,NULL);
// }


    // doctor_t *doc1 = abb_obtener(clinica->abb_doctores,params[0]);
    // if(!doc1 && strcmp(params[0],"") != 0){
    //     fprintf(stdout,ENOENT_DOCTOR,params[0]);
    //     return;
    // }
    // doc1 = abb_obtener(clinica->abb_doctores,params[1]);
    // if(!doc1 && strcmp(params[1],"") != 0){
    //     fprintf(stdout,ENOENT_DOCTOR,params[1]);
    //     return;
    // }

        // if(strcmp(abb_iter_in_ver_actual(abb_iter),params[1]) > 0 && strcmp(abb_iter_in_ver_actual(abb_iter),params[0]) < 0){
    //     fprintf(stdout,DOCTORES_SISTEMA,(size_t)0);
    //     lista_destruir(lista_informe,NULL);
    //     return;
    // }
    // if(strcmp(abb_iter_in_ver_actual(abb_iter),params[1]) < 0 && strcmp(abb_iter_in_ver_actual(abb_iter),params[0]) < 0){
    //     fprintf(stdout,DOCTORES_SISTEMA,(size_t)0);
    //     lista_destruir(lista_informe,NULL);
    //     return;
    // }

void abb_in_order_rangos(nodo_abb_t* nodo, abb_comparar_clave_t cmp, char* inicio, char* fin, bool visitar(const char*, void*, void*), void* extra, bool* seguir_iterando) {
	if (!nodo) return;

	if (cmp(inicio, nodo->clave) < 0){
		abb_in_order_rangos(nodo->izq, cmp, inicio, fin, visitar, extra, seguir_iterando);
	}

	if (*seguir_iterando && cmp(inicio, nodo->clave) <= 0 && cmp(fin, nodo->clave) >= 0) {
		if (!visitar(nodo->clave, nodo->dato, extra))
			*seguir_iterando = false;
	}

	if (cmp(fin, nodo->clave) > 0){
		abb_in_order_rangos(nodo->der, cmp, inicio, fin, visitar, extra, seguir_iterando);
	}
}

void abb_iterar_rango(abb_t* arbol, char* inicio, char* fin, bool visitar(const char*, void*, void*), void* extra) {
	bool seguir_iterando = true;
	abb_in_order_rangos(arbol->raiz, arbol->comparar, inicio, fin, visitar, extra, &seguir_iterando);
}

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

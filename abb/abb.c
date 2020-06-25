#define  _POSIX_C_SOURCE 200809L
#include "abb.h"
#include "pila.h"
#define MENOR -1
#define MAYOR 1

typedef struct nodo_abb{
    struct nodo_abb *izq;
    struct nodo_abb *der;
    char* clave;
    void* dato;
}nodo_abb_t;

struct abb{
    nodo_abb_t *raiz;
    size_t cantidad;
    abb_destruir_dato_t destruir;
    //Comparar define si tengo que ir a derecha o a izquierda para buscar mi dato, si da == 0 entonces es el dato
    abb_comparar_clave_t comparar;
};

struct abb_iter{
    const abb_t *abb;
    nodo_abb_t actual; 
};

nodo_abb_t *nodo_abb_crear(const char *clave, void *dato){
	nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));
	if(!nodo)
		return false;
	
	nodo->clave = strdup(clave);
	nodo->dato = dato;

	nodo->der = NULL;
	nodo->izq = NULL;

	return nodo;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t *abb = malloc(sizeof(abb_t));
    if(!abb)    return NULL;
    
    // abb->raiz = malloc(sizeof(nodo_abb_t));
    // if(!abb->raiz){
    //     free(abb);
    //     return NULL;
    // }
    abb->raiz = NULL;

    abb->cantidad = 0;
    abb->comparar = cmp;
    abb->destruir = destruir_dato;

    return abb;
}


bool abb_guadar_wrapper(abb_t *arbol, nodo_abb_t *raiz, nodo_abb_t *nodo){
	if(!comparar(raiz->clave,nodo->clave)) // UN NODO YA EXISTENTE TIENE LA MISMA CLAVE
		return false;
	
	if(comparar(nodo->clave,raiz->clave) <= MENOR){ //El nodo está en un valor mas chico que la raiz, tengo que doblar a la izq
		if(!raiz->izq){ // EL IZQUIERDO DE LA RAIZ NO ESTÁ POR LO TANTO AHORA EL IZQUIERDO APUNTA A ESTE NODO
			raiz->izq = nodo;
			return true;
		}
		else 
			abb_guadar_wrapper(arbol,raiz->izq,nodo); // LA RAIZ IZQUIERDA EXISTE POR LO TANTO TENGO QUE SEGUIR BUSCANDO PERO PONGO COMO RAIZ A RAIZ->IZQ
	} 
	
	if(comparar(nodo->clave,raiz->clave) >= MAYOR){ // ES IGUAL QUE EN RAIZ IZQUIERDA PERO AHORA ES PARA LA DERECHA
		if(!raiz->der){
			raiz->der = nodo;
			return true;
		}
		else 
			abb_guardar_wrapper(arbol,raiz->der,nodo);
	}

}

/*Tengo la duda si la hacemos que devuelva un nodo_abb_t, o si tiene que devolver un entero o un bool.
Osea, esta la tenemos que usar en las 4 primitivas, busca y devuelve si lo encontró u no.
En guardar-> si encuentra el lugar donde meterlo devolveria ese nodo e inserto el nuevo nodo a izq o der del nodo que devuevle.
En pertence-> true o false
En obtener-> devuelve el dato que tiene ese nodo
En borrar -> devuelve la posicion en que esta para luego proceder como se deba en borrar.
*/
nodo_abb_t* buscar(nodo_abb_t *raiz,const char *clave,abb_comparar_clave_t cmp){
	if(!raiz)
		return raiz;
	if(cmp(raiz->clave,clave) == 0)
		return NULL;
	else if(cmp(raiz->clave,clave) < 0)
		return buscar(raiz->izq,clave,cmp);
	else if(cmp(raiz->clave,clave) > 0)
		return buscar(raiz->der,clave,cmp);	
}

void inorder(nodo_abb_t *raiz)
{
    if(raiz!=NULL) // checking if the raiz is not null
    {
        inorder(raiz->izq); // visiting left child
        printf(" %d ", *(int*)raiz->dato); // printing data at raiz
        inorder(raiz->der);// visiting right child
    }
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	if(!arbol)	return false;

	if()
	nodo_abb_t *nodo = nodo_abb_crear(clave,dato);

	// if(!arbol->raiz){ //El arbol no tiene hojas por lo tanto la raiz es el nodo
	// 	arbol->raiz = nodo;
	// 	return true;
	// }

	// if(!abb_guadar_wrapper(arbol,raiz,nodo)){
	// 	destruir(nodo->dato);
	// 	free(nodo->clave);
	// 	free(nodo);
	// 	return false;
	// } // HAY UN NODO YA EXISTENTE QUE YA TIENE LA MISMA CLAVE.
    
    return true;
}


void *abb_borrar(abb_t *arbol, const char *clave){
    return NULL;
}

//TENEMOS QUE ARMAR UN RECORRER PARA MODULARIZAR Y NO REPETIR CÓDIGO

// bool abb_obtener_wrapper(const abb_t *arbol,nodo_abb_t *raiz,const char *clave){
// 	if(!raiz)
// 		return NULL;


// 	if(raiz->comparar(clave,raiz->clave) <= MENOR){
// 		return abb_pertenece(arbol,raiz->izq,clave);
// 	} // me tengo que ir al izquierdo
	
// 	if(!arbol->comparar(raiz->clave,clave))
// 		return raiz->dato; //Encontré el dato

// 	if(arbol->comparar(clave,raiz->clave) >= MAYOR){
// 		return abb_pertenece(arbol,raiz->der,clave);
// 	} // me tengo que ir al derecho

//     return NULL;
// }

void *abb_obtener(const abb_t *arbol, const char *clave){
	if(!arbol)
	    return NULL;
	return abb_obtener_wrapper(arbol,arbol->raiz,clave);
}

// bool abb_pertenece_wrapper(const abb_t *arbol,nodo_abb_t *raiz,const char *clave){ //RESPETA EL RECORRIDO IN ORDER (IZQ-RAIZ-DER)
// 	if(!raiz)
// 		return false; 

// 	if(raiz->comparar(clave,raiz->clave) <= MENOR){
// 		return abb_pertenece_wrapper(arbol,raiz->izq,clave);
// 	} // me tengo que ir al izquierdo

// 	if(!arbol->comparar(raiz->clave,clave))
// 		return true; //Encontré la clave


// 	if(arbol->comparar(clave,raiz->clave) >= MAYOR){
// 		return abb_pertenece_wrapper(arbol,raiz->der,clave);
// 	} // me tengo que ir al derecho
	
//     return false;
// }
bool abb_pertenece(const abb_t *arbol, const char *clave){
	if(!arbol)
		return false;
	return abb_pertenece_wrapper(arbol,arbol->raiz,clave);
}

size_t abb_cantidad(abb_t *arbol){
    return arbol->cantidad;
}

void abb_destruir_wrapper(abb_t *arbol, nodo_abb_t * raiz){
	
	if(raiz && raiz->izq)
		abb_destruir_wrapper(arbol,raiz->izq);
	// me tengo que ir al izquierdo
	
	if(raiz && raiz->der)
		abb_destruir_wrapper(arbol,raiz->der);
	 // me tengo que ir al derecho
	
	if(raiz){ // estoy en una hoja , tengo que liberar de abajo para arriba, CREO QUE NO ES NECESARIO PREGUNTAR SI RAIZ EXISTE, PERO COMO DIJIMOS A PRINCIPIO HAGAMOSLO TODO RUSTICO
		if(arbol->destruir)
			arbol->destruir(raiz->dato);
		free(raiz->clave);
		free(raiz);
	}
	return; 
}

void abb_destruir(abb_t *arbol){
	if (!arbol)
	    return;
	abb_destruir_wrapper(arbol,arbol->raiz);
	free(arbol);
}

// Iterador Interno
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    return;
}

//Iterador Externo

// abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
//     abb_iter_t *abb_iter = malloc(sizeof(abb_iter_t));
//     if(!abb_iter)   return NULL;

// 	pila_t *pila_in = malloc(sizeof(pila_t));
// 	if(!pila_in){
// 		free(abb_iter);
// 		return NULL;
// 	}
// 	pila_apilar(arbol->raiz);


//     abb_iter->abb = arbol;
//     abb_iter->actual = arbol -> raiz;

//     return abb_iter;
// }


// bool abb_iter_in_avanzar(abb_iter_t *iter){
//     if (abb_iter_in_al_final(iter))
//     	return false;

//     	if(iter->actual->izq)
//     		iter->actual = iter->actual -> izq;
//     	else if(iter->actual->der)
// 	    	iter->actual = iter->actual -> der; // 
    	
//     	return true;
// }

// bool abb_iter_in_al_final(const abb_iter_t *iter){
// 	return (!iter->actual || (!iter->actual->izq && !iter->actual->der))
// }
// // Hay dos casos que considerar, este es el caso 1 que te lo explico por wp 

// bool abb_iter_in_al_final(const abb_iter_t *iter){
// 	return !iter->actual;
// } // caso 2

//Si la pila esta vacia, quiere decir que el iter llegó al final.
bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->abb->raiz);
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	return (char*)pila_ver_tope(iter->abb->raiz);
}


// const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
// 	return !abb_iter_in_al_final(iter) ? iter->actual->clave : NULL;
// }

// bool abb_iter_in_avanzar(abb_iter_t *iter){
//     if (abb_iter_in_al_final(iter))
//     	return false;

//     	if(iter->actual->izq)
//     		iter->actual = iter->actual -> izq;
//     	else
// 	    	iter->actual = iter->actual -> der; // 
    	
//     	return true;
// }

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->abb->raiz);
    free(iter);
}



#include "abb.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo_abb {
    struct nodo_abb* izq;
    struct nodo_abb* der;
    const char* clave;
    void* dato;
}nodo_abb_t;

nodo_abb_t* nodo_abb_crear(const char* clave, char* dato){
    nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
    if(!nodo) return NULL;
    nodo->clave = clave;
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void nodo_abb_destruir(nodo_abb_t* nodo){
    free(nodo);
}

struct abb{
    nodo_abb_t* raiz;
    size_t cant;
    abb_destruir_dato_t destruir;
    abb_comparar_clave_t cmp;
};

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb = malloc(sizeof(abb_t));
    if(!abb)return NULL;
    abb->raiz = NULL;
    abb->cant = 0;
    abb->destruir = destruir_dato;
    abb->cmp = cmp;
    return abb;
}

bool wrapper_guardar(abb_t* arbol, nodo_abb_t* actual, const char* clave, nodo_abb_t* nodo){
    if(!actual){
        actual = nodo;
        return true;
    }
    int integrer = arbol->cmp(clave, actual->clave);
    if (integrer < 0){
    //la clave es menor qe el actual, llamamos para la izq;
        wrapper_guardar(arbol, actual->izq, clave, nodo);
    }
    if (integrer > 0){
    //la clave es mayor que el actual llamamos para la der;
        wrapper_guardar(arbol, actual->der, clave, nodo);
    }
    // si llego aca es porq ya estaba el elemento
    return false;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    nodo_abb_t* nodo = nodo_abb_crear(clave, dato); // creo un nuevo nodo
    if(!nodo) return false;                         
    if(!arbol->raiz){                               //si no hay raiz
        arbol->raiz = nodo;
        arbol->cant ++;
        return true;
    }
    if(!wrapper_guardar(arbol, arbol->raiz, clave, nodo)){ //si ya estaba el elemento 
        free(nodo);
        return false;
    }
    arbol->cant ++;
    return true;
}

void buscar_elemento(abb_t* arbol, nodo_abb_t* actual , const char* clave, nodo_abb_t** padre, nodo_abb_t** elemento){
    if (!actual){
        return;
    }
    int integrer = arbol->cmp(clave, actual->clave);
    if (integrer < 0){
        // es menor llamamos para la izq;
        *padre = actual;
        buscar_elemento(arbol, actual->izq, clave, padre, elemento);
    }
    if (integrer > 0){
        // es mayor llamamos para la der;
        *padre = actual;
        buscar_elemento(arbol, actual->der, clave, padre, elemento);
    }
    // si llego aca es porq encontre el elemento
    *elemento = actual;
}

nodo_abb_t* buscar_reemplazante(nodo_abb_t* actual){
    actual = actual->der;
    while(actual->izq){
        actual = actual->izq;
    }
    return actual;
}

void* abb_borrar(abb_t* arbol, const char *clave){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* elemento = NULL;
    void* dato = elemento->dato;
    buscar_elemento(arbol, arbol->raiz, clave, &padre, &elemento);
    // si tiene un solo hijo
    if ((elemento->izq && !elemento->der) || (elemento->der && !elemento->izq)){
        int integrer = arbol->cmp(padre->clave, elemento->clave);
        if ((elemento->izq && !elemento->der)){  //el elemento solo tiene hijo izquierdo
            if (integrer < 0) padre->der = elemento->izq; // el padre es menor al hijo
            if (integrer > 0) padre->izq = elemento->izq; // el padre es mayor al hijo
        }
        if ((elemento->der && !elemento->izq)){  // el elemento solo tiene un hijo derecho
            if (integrer < 0)padre->der = elemento->der; // el padre es menor al hijo
            if (integrer > 0) padre->izq = elemento->der; //el padres es mayor al hijo
        }
    }
    // si tiene dos hijos
    if(elemento->izq && elemento->der){
        nodo_abb_t* reemplazante =  buscar_reemplazante(elemento); // busco un reemplazante
        const char* nueva_clave = reemplazante->clave;                         // me guardo la clave
        void* valor = abb_borrar(arbol, nueva_clave);                    // me guardo el valor y borro el reemplazante
        elemento->clave = nueva_clave;                                   // piso clave del elemento       
        elemento->dato = valor;                                   // piso el valor del elemento
    }
    //destryo el nodo y devuelvo el elemento (si llega aca y no pasa por los ifs  es porque no hay hijos)
    nodo_abb_destruir(elemento);
    arbol->cant -- ;
    return dato;
}

/**/
void *abb_obtener(const abb_t *arbol, const char *clave){
    return NULL;
}

/**/
bool abb_pertenece(const abb_t *arbol, const char *clave){
    return false;
}

/**/
size_t abb_cantidad(abb_t *arbol){
    return arbol->cant;
}

/**/
void abb_destruir(abb_t *arbol){
    free(arbol);
}



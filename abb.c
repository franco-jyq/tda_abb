#define _POSIX_C_SOURCE 200809L
#include "abb.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

typedef struct nodo_abb {
    struct nodo_abb* izq;
    struct nodo_abb* der;
    char* clave;
    void* dato;
}nodo_abb_t;

nodo_abb_t* nodo_abb_crear(char* clave, char* dato){
    nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
    if(!nodo) return NULL;
    nodo->clave = clave;
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void nodo_abb_destruir(nodo_abb_t* nodo){
    free(nodo->clave);
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

void buscar_elemento(const abb_t* arbol, nodo_abb_t* actual , const char* clave, nodo_abb_t** padre, nodo_abb_t** elemento){
    if (!actual){
        *elemento = NULL;
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
    if(integrer == 0){
        *elemento = actual;
    }    
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    char* copia_clave = strdup(clave);
    if (!copia_clave) return false;
    nodo_abb_t* nodo = nodo_abb_crear(copia_clave, dato);
    if(!nodo){
        free(copia_clave);
        return false;
    }                          
    if(!arbol->raiz){                               
        arbol->raiz = nodo;
        arbol->cant ++;
        return true;
    }
    nodo_abb_t* padre = NULL;
    nodo_abb_t* elemento = NULL;
    buscar_elemento(arbol, arbol->raiz, clave, &padre, &elemento);
    if(!elemento){
        int integrer = arbol->cmp(padre->clave, clave);
        if (integrer < 0) padre->der = nodo; // el padre es menor al hijo
        if (integrer > 0) padre->izq = nodo; // el padre es mayor al hijo     
    }
    else{
        elemento->dato = dato;
        nodo_abb_destruir(nodo);
    }
    arbol->cant ++;
    return true;
}


nodo_abb_t* buscar_reemplazante(nodo_abb_t* actual){
    actual = actual->der;
    while(actual->izq){
        actual = actual->izq;
    }
    return actual;
}

void* abb_borrar(abb_t* arbol, const char *clave){
    //puts(arbol->raiz->clave);
    nodo_abb_t* padre = NULL;
    nodo_abb_t* elemento = NULL;
    buscar_elemento(arbol, arbol->raiz, clave, &padre, &elemento);
    if (!elemento) return NULL; // devuelve NULL si no esta
    void* dato = elemento->dato;
    // si tiene un solo hijo
    if((elemento->izq && !elemento->der) || (elemento->der && !elemento->izq)){
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
        nodo_abb_t* reemplazante =  buscar_reemplazante(elemento);       // busco un reemplazante
        char* nueva_clave = strdup(reemplazante->clave);                         // me guardo la clave)
        void* valor = abb_borrar(arbol, nueva_clave);                    // me guardo el valor y borro el reemplazante
        free(elemento->clave);
        elemento->clave = nueva_clave;                                   // piso clave del elemento       
        elemento->dato = valor;                                          // piso el valor del elemento
        return dato;                                                     // devuelvo el dato aca porq si no resta la cantidad dos veces
    }
    else {
        if(!padre) arbol->raiz = NULL; // si no hay padre es porque es la raiz
        else{
            int integrer = arbol->cmp(padre->clave, elemento->clave);
            if (integrer < 0) padre->der = NULL; // el padre es menor al hijo
            if (integrer > 0) padre->izq = NULL; // el padre es mayor al hijo
        }
        nodo_abb_destruir(elemento); // si no va a destruir el elemento (no tiene que hacerlo aca)
    }
    //destryo el nodo y devuelvo el elemento (si llega aca y no pasa por los ifs  es porque no hay hijos)   
    arbol->cant -- ;
    return dato;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_abb_t* elemento = NULL;
    nodo_abb_t* padre = NULL;
    buscar_elemento(arbol,arbol->raiz ,clave,&padre,&elemento);
    if(elemento) return elemento->dato;
    return NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    nodo_abb_t* elemento = NULL;
    nodo_abb_t* padre = NULL;   
    buscar_elemento(arbol, arbol->raiz ,clave, &padre, &elemento);
    return elemento != NULL;
}

size_t abb_cantidad(abb_t *arbol){
    return arbol->cant;
}

void _abb_destruir(abb_t* arbol,nodo_abb_t* actual){ // wrapper
    if (!actual) return;
    _abb_destruir(arbol,actual->izq);
    _abb_destruir(arbol,actual->der);
    if (arbol->destruir) arbol->destruir(actual->dato);
    nodo_abb_destruir(actual);
}

void abb_destruir(abb_t *arbol){
    _abb_destruir(arbol,arbol->raiz);
    free(arbol);
}



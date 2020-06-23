#include<stdio.h>
#include<stdlib.h>
#include "testing.h"
#include "abb.h"
#include<string.h>

void prueba_abb_vacio(){
    abb_t* arbol = abb_crear(strcmp, NULL); 
    print_test("Se creo el abb", arbol != NULL);
    print_test("La cantidad de elementos es 0", abb_cantidad(arbol) == 0);
    print_test ("No puedo borrar elementos", abb_borrar(arbol,"a") == NULL);
    print_test ("No puedo obtener elementos", abb_obtener(arbol,"a") == NULL);
    abb_destruir(arbol);
    print_test("Se destruyo el abb vacio", true);    
}

void prueba_guardar(){
    
}


void pruebas_abb_alumno(){
    printf("INICIO PRUEBAS ALUMNOS \n");
    prueba_abb_vacio();
}
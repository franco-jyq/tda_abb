#include<stdio.h>
#include<stdlib.h>
#include "testing.h"
#include "abb.h"
#include<string.h>
const char CLAVE1[6] = "perro";
#define DATO_1 1



void prueba_abb_vacio(){
    abb_t* arbol = abb_crear(strcmp, NULL); 
    print_test("Se creo el abb", arbol != NULL);
    print_test("La cantidad de elementos es 0", abb_cantidad(arbol) == 0);
    print_test ("No puedo borrar elementos", abb_borrar(arbol, CLAVE1) == NULL);
    print_test ("No puedo obtener elementos", abb_obtener(arbol, CLAVE1) == NULL);
    abb_destruir(arbol);
    print_test("Se destruyo el abb vacio", true);    
}

void prueba_guardar_unitaria(){
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    print_test("se pudo guardar el elemento", abb_guardar(arbol, CLAVE1, &dato1) == true);
    print_test("el elemento se encuentra en la estructura", abb_pertenece(arbol, CLAVE1) == true);
    print_test("la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    abb_destruir(arbol);
}


void pruebas_abb_alumno(){
    printf("INICIO PRUEBAS ALUMNOS \n");
    prueba_abb_vacio();
    prueba_guardar_unitaria();
}
#include<stdio.h>
#include<stdlib.h>
#include "testing.h"
#include "abb.h"
#include<string.h>
const char clave1[6] = "perro";
const char clave2[5] = "gato";
const char clave3[5] = "vaca";
#define DATO_1 1



void prueba_abb_vacio(){
    printf("INICIO PRUEBA ABB VACIO \n");
    abb_t* arbol = abb_crear(strcmp, NULL); 
    print_test("Se creo el abb", arbol != NULL);
    print_test("La cantidad de elementos es 0", abb_cantidad(arbol) == 0);
    print_test ("No puedo borrar elementos", abb_borrar(arbol, clave1) == NULL);
    print_test ("No puedo obtener elementos", abb_obtener(arbol, clave1) == NULL);
    abb_destruir(arbol);
    print_test("Se destruyo el abb vacio", true);    
}

void prueba_guardar_unitaria(){
    printf("INICIO PRUEBA GUARDAR UNITARIAS \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    print_test("se pudo guardar el elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("el elemento se encuentra en la estructura", abb_pertenece(arbol, clave1) == true);
    print_test("la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    abb_destruir(arbol);
}

void prueba_guardar_algunos_elementos(){
    printf("INICIO PRUEBA GUARDAR ALGUNOS ELEMENTOS \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    print_test("se pudo guardar el elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("la cantidad es 1", abb_cantidad(arbol) == 1);
    print_test("el elemento se encuentra en la estructura", abb_pertenece(arbol, clave1));
    print_test("se pudo guardar el elemento", abb_guardar(arbol, clave2, &dato2) == true);
    print_test("la cantidad es 2", abb_cantidad(arbol) == 2);
    print_test("el elemento se encuentra en la estructura", abb_pertenece(arbol, clave2));
    print_test("se pudo guardar el elemento", abb_guardar(arbol, clave3, &dato3) == true);
    print_test("la cantidad es 3", abb_cantidad(arbol) == 3);
    print_test("el elemento se encuentra en la estructura", abb_pertenece(arbol, clave3));
    abb_destruir(arbol);
}

void pruebas_abb_alumno(){
    printf("INICIO PRUEBAS ALUMNOS \n");
    prueba_abb_vacio();
    prueba_guardar_unitaria();
    prueba_guardar_algunos_elementos();
}


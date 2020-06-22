#include<stdio.h>
#include<stdlib.h>
#include "testing.h"
#include "abb.h"
#include<string.h>

void prueba_abb_crear(){
    abb_t* arbol = abb_crear(strcmp, NULL); 
    print_test("se creo el abb", arbol != NULL);
    abb_destruir(arbol);    
}


void pruebas_abb_alumno(){
    printf("INICIO PRUEBAS ALUMNOS \n");
    prueba_abb_crear();
}
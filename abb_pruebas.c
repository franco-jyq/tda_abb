#include<stdio.h>
#include<stdlib.h>
#include "testing.h"
#include "abb.h"
#include<string.h>
const char clave1[6] = "perro";
const char clave2[5] = "gato";
const char clave3[5] = "vaca";
const char clave4[5] = "mono";
const char clave5[5] = "pato";
const char clave6[9] = "pinguino";
const char clave7[6] = "zebra";



                
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

void prueba_borrar_unitaria(){
    printf("INICIO PRUEBA BORRAR UNITARIA \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    print_test("se pudo guardar el elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("se borro el elemento", *(int*)abb_borrar(arbol, clave1) == dato1);
    print_test("el elemento no pertence a la estructura", abb_pertenece(arbol, clave1) == false);
    print_test("cantidad de elementos es  0", abb_cantidad(arbol) == 0);
    abb_destruir(arbol);
}

void prueba_borrar_escalera(){
    printf("INICIO PRUEBA BORRAR ESCALERA \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    print_test("se pudo guardar el elemento", abb_guardar(arbol, "1", &dato1) == true);
    print_test("se pudo guardar el elemento", abb_guardar(arbol, "2", &dato1) == true);
    print_test("se pudo guardar el elemento", abb_guardar(arbol, "3", &dato1) == true);
    print_test("se pudo guardar el elemento", abb_guardar(arbol, "4", &dato1) == true);
    print_test("se pudo guardar el elemento", abb_guardar(arbol, "5", &dato1) == true);
    print_test("se borro el elemento", abb_borrar(arbol, "1"));
    abb_destruir(arbol);

}

void prueba_borrar_algunos_elementos(){
    printf("INICIO PRUEBA BORRAR ALGUNOS ELEMENTOS \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    print_test("se pudo guardar el elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("se pudo guardar el elemento", abb_guardar(arbol, clave2, &dato2) == true);
    print_test("se pudo guardar el elemento", abb_guardar(arbol, clave3, &dato3) == true);
    print_test("cantidad de elementos es 3", abb_cantidad(arbol) == 3);
    /*borro el primer elemento*/
    print_test("se borro el elemento", *(int*)abb_borrar(arbol, clave1) == dato1);
    print_test("el elemento no pertence a la estructura", abb_pertenece(arbol, clave1) == false);
    print_test("cantidad de elementos es  2", abb_cantidad(arbol) == 2);
    /*borro el segundo elemento*/
    print_test("se borro el elemento", *(int*)abb_borrar(arbol, clave2) == dato2);
    print_test("el elemento no pertence a la estructura", abb_pertenece(arbol, clave2) == false);
    print_test("cantidad de elementos es  1", abb_cantidad(arbol) == 1);
    /*borro el tercer elemento*/
    print_test("se borro el elemento", *(int*)abb_borrar(arbol, clave3) == dato3);
    print_test("el elemento no pertence a la estructura", abb_pertenece(arbol, clave3) == false);
    print_test("cantidad de elementos es  0", abb_cantidad(arbol) == 0);
    /*destruyo el arbol*/
    abb_destruir(arbol);
}

/**********************************************************************************
 * 
 *                      Pruebas iterador externo
 * 
 * ********************************************************************************/

void prueba_iter_vacio(){
    printf("INICIO PRUEBAS ITERADOR EXTERNO \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(arbol);
    print_test("se creo el iterador", iter!= NULL);
    print_test("avanzar si esta vacia es false", abb_iter_in_avanzar(iter) == false);
    print_test("ver actual si esta vacia es NULL", abb_iter_in_ver_actual(iter) == NULL);
    print_test("esta al final cuando esta vacio devuelve true", abb_iter_in_al_final(iter) == true);
    abb_iter_in_destruir(iter);
    abb_destruir(arbol);
}

void prueba_iter_algunos_elementos(){
    abb_t* arbol = abb_crear(strcmp, NULL);
    /*Guardo algunos elementos*/
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    int dato4 = 4;
    int dato5 = 5;
    int dato6 = 6;
    int dato7 = 7;
    abb_guardar(arbol, clave1, &dato1);
    abb_guardar(arbol, clave2, &dato2);
    abb_guardar(arbol, clave3, &dato3);
    abb_guardar(arbol, clave4, &dato4);
    abb_guardar(arbol, clave5, &dato5);
    abb_guardar(arbol, clave6, &dato6);
    abb_guardar(arbol, clave7, &dato7);    
    abb_iter_t* iter = abb_iter_in_crear(arbol);
    print_test("iter ver actual es clave2", strcmp(abb_iter_in_ver_actual(iter), clave2) == 0);
    print_test("iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("iter avanzar es true", abb_iter_in_avanzar(iter) == true);
    /*Ahora estoy en el segundo elemento*/
    print_test("iter ver actual es clave4", strcmp(abb_iter_in_ver_actual(iter), clave4) == 0);
    print_test("iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("iter avanzar es true", abb_iter_in_avanzar(iter) == true);    
    /*Ahora estoy en el tercer elemento*/
    print_test("iter ver actual es clave5", strcmp(abb_iter_in_ver_actual(iter), clave5) == 0);
    print_test("iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("iter avanzar es true", abb_iter_in_avanzar(iter) == true);    
    /*Ahora estoy en el cuarto elemento*/
    print_test("iter ver actual es clave1", strcmp(abb_iter_in_ver_actual(iter), clave1) == 0);
    print_test("iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("iter avanzar es true", abb_iter_in_avanzar(iter) == true);    
    /*Ahora estoy en el quinto elemento*/
    print_test("iter ver actual es clave6", strcmp(abb_iter_in_ver_actual(iter), clave6) == 0);
    print_test("iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("iter avanzar es true", abb_iter_in_avanzar(iter) == true);
    /*Ahora estoy en el sexto elemento*/
    print_test("iter ver actual es clave3", strcmp(abb_iter_in_ver_actual(iter), clave3) == 0);
    print_test("iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("iter avanzar es true", abb_iter_in_avanzar(iter) == true);
    /*Ahora estoy en el septimo elemento*/
    print_test("iter ver actual es clave7", strcmp(abb_iter_in_ver_actual(iter), clave7) == 0);
    print_test("iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("iter avanzar es true", abb_iter_in_avanzar(iter) == true);
    /*Ahora estoy al final*/
    print_test("iter al final es true", abb_iter_in_al_final(iter) == true);
    /*Destruyo el iterador*/
    abb_iter_in_destruir(iter);
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

void pruebas_abb_alumno(){
    printf("INICIO PRUEBAS ALUMNOS \n");
    prueba_abb_vacio();
    prueba_guardar_unitaria();
    prueba_guardar_algunos_elementos();
    prueba_borrar_unitaria();
    prueba_borrar_escalera();
    prueba_borrar_algunos_elementos();
    /*pruebas iterador externo*/
    prueba_iter_vacio();
    prueba_iter_algunos_elementos();
}


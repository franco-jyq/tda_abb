#include<stdio.h>
#include<stdlib.h>
#include "testing.h"
#include "abb.h"
#include<string.h>
const char* clave1 = "perro";
const char* clave2 = "gato";
const char* clave3 = "vaca";
const char* clave4 = "mono";
const char* clave5 = "pato";
const char* clave6 = "pinguino";
const char* clave7 = "zebra";
const char* clave8 = "serpiente";

                
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
    print_test("Se pudo guardar el elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("El elemento se encuentra en la estructura", abb_pertenece(arbol, clave1) == true);
    print_test("La cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    abb_destruir(arbol);
}

void prueba_guardar_algunos_elementos(){
    printf("INICIO PRUEBA GUARDAR ALGUNOS ELEMENTOS \n");
    
    /*Inicializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;

    print_test("Se pudo guardar el primer elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("La cantidad es 1", abb_cantidad(arbol) == 1);
    print_test("El primer elemento se encuentra en la estructura", abb_pertenece(arbol, clave1));
    print_test("Se pudo guardar el segundo elemento", abb_guardar(arbol, clave2, &dato2) == true);
    print_test("La cantidad es 2", abb_cantidad(arbol) == 2);
    print_test("El segundo elemento se encuentra en la estructura", abb_pertenece(arbol, clave2));
    print_test("Se pudo guardar el tercer elemento", abb_guardar(arbol, clave3, &dato3) == true);
    print_test("La cantidad es 3", abb_cantidad(arbol) == 3);
    print_test("El tercer elemento se encuentra en la estructura", abb_pertenece(arbol, clave3));
    
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

void prueba_guardar_reemplazando(){
    printf("INICIO PRUEBAS GUARDAR REEMPLAZANDO \n");
    
    /*inicalizo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int valor1 = 1;
    int valor2 = 2;
    int valor3 = 3;
    int valor4 = 4;
    
    /*guardo 4 valor*/
    print_test("Se guardo la clave1", abb_guardar(arbol, clave1, &valor1));
    print_test("Se guardo la clave2", abb_guardar(arbol, clave2, &valor2));
    print_test("Se guardo la clave3", abb_guardar(arbol, clave3, &valor3));
    print_test("Se guardo la clave4", abb_guardar(arbol, clave4, &valor4));
    
    /*reemplazo valor de clave 1*/
    print_test("Obtener de clave 1 es valor1", *(int*)abb_obtener(arbol, clave1) == valor1);
    print_test("Reemplazo el valor de la clave1", abb_guardar(arbol, clave1, &valor2));
    print_test("Obtener de clave 1 ahora es valor2", *(int*)abb_obtener(arbol, clave1) == valor2);
    
    /*reemplazo el valor de clave 4*/
    print_test("Obtener de clave4 es valor4", *(int*)abb_obtener(arbol, clave4) == valor4);
    print_test("Reemplazo el valor de la clave4", abb_guardar(arbol, clave4, &valor3));
    print_test("Obtener de clave 4 ahora es valor4", *(int*)abb_obtener(arbol, clave4) == valor3);
    
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

void prueba_borrar_raiz_sin_hijos(){
    printf("INICIO PRUEBA BORRAR RAIZ SIN HIJOS \n");
    
    /*Inicializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;

    /*Pruebas*/
    print_test("Se pudo guardar el elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("Se borro el elemento", *(int*)abb_borrar(arbol, clave1) == dato1);
    print_test("El elemento no pertence a la estructura", abb_pertenece(arbol, clave1) == false);
    print_test("La cantidad de elementos es  0", abb_cantidad(arbol) == 0);
    
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

void prueba_borrar_raiz_con_dos_hijos(){
    printf("INICIO PRUEBA BORRAR RAIZ CON DOS HIJOS \n");
    
    /*Inicializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    
    /*Guardo algunos elementos*/
    print_test("Se pudo guardar el primer elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("Se pudo guardar el segundo elemento", abb_guardar(arbol, clave2, &dato1) == true);
    print_test("Se pudo guardar el tercer elemento", abb_guardar(arbol, clave3, &dato1) == true);
    
    /*Borro la raiz*/
    print_test("Se borro el valor1", abb_borrar(arbol, clave1));
    print_test("El elemento ya no pertenece a la estructura", abb_pertenece(arbol, clave1) == false);
    
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

void prueba_borrar_raiz_con_un_hijo(){
    printf("INICIO PRUEBA BORRAR  RAIZ CON UN HIJO \n");
    
    /*Inicializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    
    /*Guardo dos elementos*/
    print_test("Se pudo guardar el primer elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("Se pudo guardar el segundo elemento", abb_guardar(arbol, clave2, &dato1) == true);
    
    /*Borro la raiz*/
    print_test("Se borro el valor1", abb_borrar(arbol, clave1));
    print_test("El elemento ya no pertenece a la estructura", abb_pertenece(arbol, clave1) == false);
    
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

void prueba_borrar_sin_hijos(){
    printf("INICIO PRUEBA BORRAR SIN HIJOS \n");
    
    /*Inicializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    
    /*Guardo dos elementos*/
    print_test("Se pudo guardar el primer elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("Se pudo guardar el segundo elemento", abb_guardar(arbol, clave2, &dato1) == true);
    
    /*Borro el elemento 2*/
    print_test("Se borro el valor2", abb_borrar(arbol, clave2));
    print_test("El elemento ya no pertenece a la estructura", abb_pertenece(arbol, clave2) == false);
    
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

void prueba_borrar_con_un_hijo(){
    printf("INICIO PRUEBA BORRAR CON UN HIJO \n");
    
    /*Inicializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    
    /*Guardo tres elementos*/
    print_test("Se pudo guardar el primer elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("Se pudo guardar el segundo elemento", abb_guardar(arbol, clave2, &dato1) == true);
    print_test("Se pudo guardar el elemento", abb_guardar(arbol, clave4, &dato1) == true);
    
    /*Borro el elemento 2*/
    print_test("Se borro el valor2", abb_borrar(arbol, clave2));
    print_test("El elemento ya no pertenece a la estructura", abb_pertenece(arbol, clave2) == false);
    
    /*Destuyo el arbol*/
    abb_destruir(arbol);
}

void prueba_borrar_con_dos_hijos(){
    printf("INICIO PRUEBA BORRAR CON DOS HIJOS \n");
    
    /*Incializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    
    /*Guardo cuatro elementos*/
    print_test("Se pudo guardar el primer elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("Se pudo guardar el segundo elemento", abb_guardar(arbol, clave5, &dato1) == true);
    print_test("Se pudo guardar el tercer elemento", abb_guardar(arbol, clave3, &dato1) == true);
    print_test("Se pudo guardar el cuarto elemento", abb_guardar(arbol, clave7, &dato1) == true);
    
    /*Borro el elemento 2*/
    print_test("Se borro el valor5", abb_borrar(arbol, clave5));
    print_test("El elemento ya no pertenece a la estructura", abb_pertenece(arbol, clave2) == false);
    
    /*Destruyo el arbol*/
    abb_destruir(arbol); 
}

void prueba_borrar_algunos_elementos(){
    printf("INICIO PRUEBA BORRAR ALGUNOS ELEMENTOS \n");
    
    /*Inicializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    
    /*Guardo algunos elementos*/
    print_test("Se pudo guardar el primer elemento", abb_guardar(arbol, clave1, &dato1) == true);
    print_test("Se pudo guardar el segundo elemento", abb_guardar(arbol, clave2, &dato2) == true);
    print_test("Se pudo guardar el tercer elemento", abb_guardar(arbol, clave3, &dato3) == true);
    print_test("La cantidad de elementos es 3", abb_cantidad(arbol) == 3);
    
    /*Borro el primer elemento*/
    print_test("Se borro el elemento", *(int*)abb_borrar(arbol, clave1) == dato1);
    print_test("El elemento no pertence a la estructura", abb_pertenece(arbol, clave1) == false);
    print_test("La cantidad de elementos es 2", abb_cantidad(arbol) == 2);
    
    /*Borro el segundo elemento*/
    print_test("Se borro el elemento", *(int*)abb_borrar(arbol, clave2) == dato2);
    print_test("El elemento no pertence a la estructura", abb_pertenece(arbol, clave2) == false);
    print_test("La cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    
    /*Borro el tercer elemento*/
    print_test("Se borro el elemento", *(int*)abb_borrar(arbol, clave3) == dato3);
    print_test("El elemento no pertence a la estructura", abb_pertenece(arbol, clave3) == false);
    print_test("La cantidad de elementos es 0", abb_cantidad(arbol) == 0);
    
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

bool visitar(const char* clave, void* dato, void* extra){
    printf("clave: %s \n", clave);
    return true;
}

bool visitar_con_extra(const char* clave, void* dato, void* extra){
    (*(int*)extra) ++;
    if(*(int*)extra > 4) return false;
    printf("clave: %s \n", clave);
    return true;
}

void prueba_abb_in_order(){
    printf("INICIO PRUEBA ITERADOR INTERNO \n");

    /*Creo el arbol*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    
    /*Inicializo variables*/
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    int dato4 = 4;
    int dato5 = 5;
    int dato6 = 6;
    int dato7 = 7;
    int extra = 0;

    /*Guardo 7 elementos*/
    abb_guardar(arbol, clave1, &dato1);
    abb_guardar(arbol, clave2, &dato2);
    abb_guardar(arbol, clave3, &dato3);
    abb_guardar(arbol, clave4, &dato4);
    abb_guardar(arbol, clave5, &dato5);
    abb_guardar(arbol, clave6, &dato6);
    abb_guardar(arbol, clave7, &dato7); 
     
    /*Recorro in order*/
    abb_in_order(arbol, visitar, NULL);
    print_test("Recorrido in order: gato-mono-pato-perro-pinguino-vaca-zebra ", true);


    /*Recorro hasta el cuarto elemento*/    
    abb_in_order(arbol, visitar_con_extra, &extra);
    print_test("Se recorrieron solo 4 elementos", true);

    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

/**********************************************************************************
 * 
 *                      Pruebas iterador externo
 * 
 * ********************************************************************************/

void prueba_iter_vacio(){
    printf("INICIO PRUEBAS ITERADOR EXTERNO \n");
    
    /*Inicializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(arbol);
    
    /*Pruebas*/
    print_test("Se creo el iterador", iter!= NULL);
    print_test("Avanzar si esta vacio devuelve false", abb_iter_in_avanzar(iter) == false);
    print_test("Ver actual si esta vacio es NULL", abb_iter_in_ver_actual(iter) == NULL);
    print_test("Esta al final cuando esta vacio devuelve true", abb_iter_in_al_final(iter) == true);
    
    /*Destruyo el iterador*/
    abb_iter_in_destruir(iter);
    
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

void prueba_iter_algunos_elementos(){
    
    /*Inicializo variables*/
    abb_t* arbol = abb_crear(strcmp, NULL);
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    int dato4 = 4;
    int dato5 = 5;
    int dato6 = 6;
    int dato7 = 7;

    /*Guardo 7 elemetnos*/
    abb_guardar(arbol, clave1, &dato1);
    abb_guardar(arbol, clave2, &dato2);
    abb_guardar(arbol, clave3, &dato3);
    abb_guardar(arbol, clave4, &dato4);
    abb_guardar(arbol, clave5, &dato5);
    abb_guardar(arbol, clave6, &dato6);
    abb_guardar(arbol, clave7, &dato7);    
    
    /*Creo el iterador*/
    abb_iter_t* iter = abb_iter_in_crear(arbol);
    
    /*Estoy en el primer elemento*/
    print_test("Iter ver actual es clave2", strcmp(abb_iter_in_ver_actual(iter), clave2) == 0);
    print_test("Iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter) == true);
    
    /*Ahora estoy en el segundo elemento*/
    print_test("Iter ver actual es clave4", strcmp(abb_iter_in_ver_actual(iter), clave4) == 0);
    print_test("Iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter) == true);    
    
    /*Ahora estoy en el tercer elemento*/
    print_test("Iter ver actual es clave5", strcmp(abb_iter_in_ver_actual(iter), clave5) == 0);
    print_test("Iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter) == true);    
    
    /*Ahora estoy en el cuarto elemento*/
    print_test("Iter ver actual es clave1", strcmp(abb_iter_in_ver_actual(iter), clave1) == 0);
    print_test("Iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter) == true);    
    
    /*Ahora estoy en el quinto elemento*/
    print_test("Iter ver actual es clave6", strcmp(abb_iter_in_ver_actual(iter), clave6) == 0);
    print_test("Iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter) == true);
    
    /*Ahora estoy en el sexto elemento*/
    print_test("Iter ver actual es clave3", strcmp(abb_iter_in_ver_actual(iter), clave3) == 0);
    print_test("Iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter) == true);
    
    /*Ahora estoy en el septimo elemento*/
    print_test("Iter ver actual es clave7", strcmp(abb_iter_in_ver_actual(iter), clave7) == 0);
    print_test("Iter al final es false", abb_iter_in_al_final(iter) == false);
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter) == true);
    
    /*Ahora estoy al final*/
    print_test("Iter al final es true", abb_iter_in_al_final(iter) == true);
    
    /*Destruyo el iterador*/
    abb_iter_in_destruir(iter);
   
    /*Destruyo el arbol*/
    abb_destruir(arbol);
}

void pruebas_abb_alumno(){
    prueba_abb_vacio();
    prueba_guardar_unitaria();
    prueba_guardar_algunos_elementos();
    prueba_guardar_reemplazando();
    prueba_borrar_raiz_sin_hijos();
    prueba_borrar_raiz_con_dos_hijos();
    prueba_borrar_raiz_con_un_hijo();
    prueba_borrar_sin_hijos();
    prueba_borrar_con_un_hijo();
    prueba_borrar_con_dos_hijos();
    prueba_borrar_algunos_elementos();
    prueba_abb_in_order();
    /*pruebas iterador externo*/
    prueba_iter_vacio();
    prueba_iter_algunos_elementos();
}


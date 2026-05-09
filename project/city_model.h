#ifndef CITY_MODEL_H
#define CITY_MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_STR_LEN 100
#define MAX_CALLES 50
#define MAX_PUNTOS 200

typedef struct {
    double x;
    double y;

} Punto;

typedef struct {
    char nombre[MAX_STR_LEN];
    Punto inicio;
    Punto fin;
    char sentido; /* 'X' o 'Y' */
} Calle;

typedef struct {
    char nombre[MAX_STR_LEN];
    char nombre_calle[MAX_STR_LEN];
    double posicion; /* Distancia desde el inicio de la calle */
    Punto ubicacion; /* Coordenada calculada */
} PuntoTuristico;

typedef struct {
    Punto p;
    int id_calle_a;
    int id_calle_b;
} Interseccion;

/* Prototipos de funciones */

/*
    Buscamos usar el algoritmo de orientación 
    para determinar si dos calles se intersectan.
*/
bool se_intersectan(Calle c1, Calle c2);
int orientacion(Punto p, Punto q, Punto r);
bool on_segment(Punto p, Punto q, Punto r);



Punto calcular_interseccion(Calle c1, Calle c2);
int leer_archivo(const char *filename, Calle *calles, int *num_calles, PuntoTuristico *puntos, int *num_puntos);
double calcular_distancia(Punto p1, Punto p2);


#endif

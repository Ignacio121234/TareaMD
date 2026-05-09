#ifndef CITY_MODEL_H
#define CITY_MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_STR_LEN 100
#define MAX_CALLES 50
#define MAX_INTERSECCIONES 1300
#define MAX_PUNTOS_TURISTICOS 100

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
    char name_calle_a[MAX_STR_LEN];
    char name_calle_b[MAX_STR_LEN];
} Interseccion;

/* Prototipos de funciones */
int orientacion(Punto p, Punto q, Punto r);
bool on_segment(Punto p, Punto q, Punto r);
bool se_intersectan(Calle c1, Calle c2);
Interseccion calcular_interseccion(Calle c1, Calle c2);


#endif

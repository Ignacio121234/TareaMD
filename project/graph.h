#include <stdio.h>
#include <string.h>
#include "city_model.h"

#define MAX_STR_LEN 100
#define MAX_VECINOS 100  // COMO SON UN MAXIMO DE 50 CALLES y por 2 direcciones posibles
#define MAX_NODOS ( 2 * MAX_CALLES + MAX_INTERSECCIONES + MAX_PUNTOS_TURISTICOS )




typedef enum {
    TIPO_TURISTICO,
    TIPO_INTERSECCION
} TipoNodo;


typedef struct {
    char nombre[MAX_STR_LEN];
    int id;
    TipoNodo tipo;
    union {
        PuntoTuristico turistico;
        Interseccion interseccion;
    } info;

    int vecinos[MAX_VECINOS]; // IDs de los nodos vecinos
    int num_vecinos;
} Nodo;

typedef struct {
    Nodo nodos[MAX_NODOS];
    int num_nodos;
} Grafo;

void inicializar_grafo(Grafo *grafo);
int agregar_nodo_turistico(Grafo *grafo, PuntoTuristico pt);
int agregar_nodo_interseccion(Grafo *grafo, Interseccion inter);
void agregar_arista(Grafo *grafo, int id1, int id2);
void imprimir_grafo(Grafo *grafo);

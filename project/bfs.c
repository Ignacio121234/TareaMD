#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "city_model.h"
#include "graph.h"

// Funcion para ver por que calle vamos (compara los nodos)
void obtener_calle(Nodo n1, Nodo n2, char *calle_encontrada) {
    char calles_n1[2][100] = {"", ""};
    char calles_n2[2][100] = {"", ""};
    int total_n1 = 0, total_n2 = 0;

    if (n1.tipo == TIPO_TURISTICO) {
        strcpy(calles_n1[0], n1.info.turistico.nombre_calle);
        total_n1 = 1;
    } else {
        strcpy(calles_n1[0], n1.info.interseccion.name_calle_a);
        strcpy(calles_n1[1], n1.info.interseccion.name_calle_b);
        total_n1 = 2;
    }

    if (n2.tipo == TIPO_TURISTICO) {
        strcpy(calles_n2[0], n2.info.turistico.nombre_calle);
        total_n2 = 1;
    } else {
        strcpy(calles_n2[0], n2.info.interseccion.name_calle_a);
        strcpy(calles_n2[1], n2.info.interseccion.name_calle_b);
        total_n2 = 2;
    }

    for (int i = 0; i < total_n1; i++) {
        for (int j = 0; j < total_n2; j++) {
            if (strcmp(calles_n1[i], calles_n2[j]) == 0) {
                strcpy(calle_encontrada, calles_n1[i]);
                return;
            }
        }
    }
}


// BFS para encontrar la ruta
void hacer_ruta(Grafo *grafo, int id_inicio, int id_destino) {
    bool visitado[MAX_NODOS] = {false};
    int padre[MAX_NODOS]; 
    
    for (int i = 0; i < MAX_NODOS; i++) {
        padre[i] = -1;
    }

    int cola[MAX_NODOS];
    int inicio_cola = 0, fin_cola = 0;

    cola[fin_cola] = id_inicio;
    fin_cola++;
    visitado[id_inicio] = true;

    bool encontre_destino = false;

    // BFS
    while (inicio_cola < fin_cola) {
        int id_actual = cola[inicio_cola];
        inicio_cola++;

        if (id_actual == id_destino) {
            encontre_destino = true;
            break; 
        }

        Nodo nodo_actual = grafo->nodos[id_actual];
        
        for (int i = 0; i < nodo_actual.num_vecinos; i++) {
            int id_vecino = nodo_actual.vecinos[i];

            if (visitado[id_vecino] == false) {
                visitado[id_vecino] = true;
                padre[id_vecino] = id_actual; 
                cola[fin_cola] = id_vecino; 
                fin_cola++;
            }
        }
    }

    // Reconstruir camino e imprimir
    if (encontre_destino == true) {
        int camino_al_reves[MAX_NODOS];
        int cantidad_pasos = 0;
        
        int actual = id_destino;
        while (actual != -1) {
            camino_al_reves[cantidad_pasos] = actual;
            cantidad_pasos++;
            actual = padre[actual];
        }

        int ruta_derecha[MAX_NODOS];
        for (int i = 0; i < cantidad_pasos; i++) {
            ruta_derecha[i] = camino_al_reves[cantidad_pasos - 1 - i];
        }

        char calle_actual[100] = "";
        char calle_siguiente[100] = "";

        printf("Inicio en: %s\n", grafo->nodos[ruta_derecha[0]].info.turistico.nombre);

        for (int i = 0; i < cantidad_pasos - 1; i++) {
            Nodo nodo1 = grafo->nodos[ruta_derecha[i]];
            Nodo nodo2 = grafo->nodos[ruta_derecha[i+1]];

            obtener_calle(nodo1, nodo2, calle_siguiente);

            if (strcmp(calle_actual, calle_siguiente) != 0) {
                if (i == 0) {
                    printf("-> Camina por calle %s.\n", calle_siguiente);
                } else {
                    printf("-> Dobla en calle %s.\n", calle_siguiente);
                }
                strcpy(calle_actual, calle_siguiente); 
            }
        }
        printf("-> Llegaste a: %s\n", grafo->nodos[ruta_derecha[cantidad_pasos-1]].info.turistico.nombre);
        
    } else {
        printf("No se encontro un camino valido.\n");
    }
}

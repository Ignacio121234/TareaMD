#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city_model.h"
#include "graph.h"

void leer_archivo_ciudad(Calle calles[], int *total_calles, PuntoTuristico lugares[], int *total_lugares);
void hacer_ruta(Grafo *grafo, int id_inicio, int id_destino);

int main() {
    Calle calles[MAX_CALLES];
    PuntoTuristico lugares[MAX_PUNTOS_TURISTICOS];
    int total_calles = 0, total_lugares = 0;
    Grafo mi_grafo;

    leer_archivo_ciudad(calles, &total_calles, lugares, &total_lugares);
    inicializar_grafo(&mi_grafo);

    
    int ids_turisticos[MAX_PUNTOS_TURISTICOS];
    for (int i = 0; i < total_lugares; i++) {
        for (int j = 0; j < total_calles; j++) {
            if (strcmp(lugares[i].nombre_calle, calles[j].nombre) == 0) {
                if (calles[j].sentido == 'X') {
                    lugares[i].ubicacion.x = calles[j].inicio.x + lugares[i].posicion;
                    lugares[i].ubicacion.y = calles[j].inicio.y;
                } else {
                    lugares[i].ubicacion.x = calles[j].inicio.x;
                    lugares[i].ubicacion.y = calles[j].inicio.y + lugares[i].posicion;
                }
                break;
            }
        }
        ids_turisticos[i] = agregar_nodo_turistico(&mi_grafo, lugares[i]);
    }

    for (int i = 0; i < total_calles; i++) {
        for (int j = i + 1; j < total_calles; j++) {
            if (se_intersectan(calles[i], calles[j])) {
                Interseccion inter = calcular_interseccion(calles[i], calles[j]);
                agregar_nodo_interseccion(&mi_grafo, inter);
            }
        }
    }

    for (int i = 0; i < mi_grafo.num_nodos; i++) {
        for (int j = i + 1; j < mi_grafo.num_nodos; j++) {
            Nodo *n1 = &mi_grafo.nodos[i];
            Nodo *n2 = &mi_grafo.nodos[j];
            bool compartir_calle = false;

            // Extraemos los nombres de las calles de cada nodo para comparar
            char c1_a[100] = "", c1_b[100] = "";
            char c2_a[100] = "", c2_b[100] = "";

            if (n1->tipo == TIPO_TURISTICO) {
                strcpy(c1_a, n1->info.turistico.nombre_calle);
            } else {
                strcpy(c1_a, n1->info.interseccion.name_calle_a);
                strcpy(c1_b, n1->info.interseccion.name_calle_b);
            }

            if (n2->tipo == TIPO_TURISTICO) {
                strcpy(c2_a, n2->info.turistico.nombre_calle);
            } else {
                strcpy(c2_a, n2->info.interseccion.name_calle_a);
                strcpy(c2_b, n2->info.interseccion.name_calle_b);
            }

            if (strcmp(c1_a, c2_a) == 0 || (strlen(c1_b) > 0 && strcmp(c1_b, c2_a) == 0) ||
                (strlen(c2_b) > 0 && strcmp(c1_a, c2_b) == 0) ||
                (strlen(c1_b) > 0 && strlen(c2_b) > 0 && strcmp(c1_b, c2_b) == 0)) {
                compartir_calle = true;
            }

            if (compartir_calle) {
                agregar_arista(&mi_grafo, n1->id, n2->id);
            }
        }
    }

    printf("\n--- Ruta Turistica Generada ---\n");
    for (int i = 0; i < total_lugares - 1; i++) {
        printf("\nTramo %d: %s -> %s\n", i + 1, lugares[i].nombre, lugares[i+1].nombre);
        hacer_ruta(&mi_grafo, ids_turisticos[i], ids_turisticos[i+1]);
    }

    return 0;
}
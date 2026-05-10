#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city_model.h"
#include "graph.h"

//copiar esto para runear codigo
//gcc main.c archivotxt.c bfs.c city_model.c graph.c -o main -lm ; if ($?) { .\main }

void leer_archivo_ciudad(Calle calles[], int *total_calles, PuntoTuristico lugares[], int *total_lugares);
bool hacer_ruta(Grafo *grafo, int id_inicio, int id_destino, bool visitados_globales[]);

// Función de comparación para ordenar nodos por posición en la calle
int comparar_nodos_calle(const void *a, const void *b) {
    typedef struct { int id; double pos; } NodoEnCalle;
    NodoEnCalle *n1 = (NodoEnCalle *)a;
    NodoEnCalle *n2 = (NodoEnCalle *)b;
    if (n1->pos < n2->pos) return -1;
    if (n1->pos > n2->pos) return 1;
    return 0;
}

int main() {
    char opcion[10];
    typedef struct { int id; double pos; } NodoEnCalle;

    do {
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
                        // La posición es la coordenada X
                        double dx = calles[j].fin.x - calles[j].inicio.x;
                        lugares[i].ubicacion.x = lugares[i].posicion;
                        if (fabs(dx) > 0.000001) {
                            double t = (lugares[i].posicion - calles[j].inicio.x) / dx;
                            lugares[i].ubicacion.y = calles[j].inicio.y + t * (calles[j].fin.y - calles[j].inicio.y);
                        } else {
                            lugares[i].ubicacion.y = calles[j].inicio.y;
                        }
                    } else {
                        // La posición es la coordenada Y
                        double dy = calles[j].fin.y - calles[j].inicio.y;
                        lugares[i].ubicacion.y = lugares[i].posicion;
                        if (fabs(dy) > 0.000001) {
                            double t = (lugares[i].posicion - calles[j].inicio.y) / dy;
                            lugares[i].ubicacion.x = calles[j].inicio.x + t * (calles[j].fin.x - calles[j].inicio.x);
                        } else {
                            lugares[i].ubicacion.x = calles[j].inicio.x;
                        }
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

        // --- NUEVA LÓGICA DE CONECTIVIDAD LINEAL ---
        for (int s = 0; s < total_calles; s++) {
            NodoEnCalle nodos_en_esta_calle[MAX_NODOS];
            int cantidad_en_calle = 0;

            for (int n = 0; n < mi_grafo.num_nodos; n++) {
                Nodo *nodo_actual = &mi_grafo.nodos[n];
                bool pertenece = false;
                double posicion = 0;

                if (nodo_actual->tipo == TIPO_TURISTICO) {
                    if (strcmp(nodo_actual->info.turistico.nombre_calle, calles[s].nombre) == 0) {
                        pertenece = true;
                        posicion = nodo_actual->info.turistico.posicion;
                    }
                } else {
                    if (strcmp(nodo_actual->info.interseccion.name_calle_a, calles[s].nombre) == 0 ||
                        strcmp(nodo_actual->info.interseccion.name_calle_b, calles[s].nombre) == 0) {
                        pertenece = true;
                        posicion = calcular_distancia(calles[s].inicio, nodo_actual->info.interseccion.p);
                    }
                }

                if (pertenece) {
                    nodos_en_esta_calle[cantidad_en_calle].id = nodo_actual->id;
                    nodos_en_esta_calle[cantidad_en_calle].pos = posicion;
                    cantidad_en_calle++;
                }
            }

            // Ordenar los nodos de la calle por su posición
            qsort(nodos_en_esta_calle, cantidad_en_calle, sizeof(NodoEnCalle), comparar_nodos_calle);

            // Conectar solo nodos adyacentes en la calle
            for (int k = 0; k < cantidad_en_calle - 1; k++) {
                agregar_arista(&mi_grafo, nodos_en_esta_calle[k].id, nodos_en_esta_calle[k+1].id);
            }
        }
        // --- FIN DE NUEVA LÓGICA ---

        printf("\n--- Ruta Turistica Generada ---\n");
        bool punto_ya_visitado[MAX_PUNTOS_TURISTICOS] = {false};
        
        int actual = 0; 
        punto_ya_visitado[actual] = true;

        while (actual < total_lugares - 1) {
            int siguiente = actual + 1;
            
            while (siguiente < total_lugares && punto_ya_visitado[siguiente]) {
                siguiente++;
            }

            if (siguiente >= total_lugares) {
                break;
            }

            printf("\nTramo: %s -> %s\n", lugares[actual].nombre, lugares[siguiente].nombre);
            
            hacer_ruta(&mi_grafo, ids_turisticos[actual], ids_turisticos[siguiente], punto_ya_visitado);
            
            punto_ya_visitado[siguiente] = true;
            actual = siguiente;
        }

        // --- INICIO VALIDACIÓN ESTRICTA ---
        bool respuesta_valida = false;
        do {
            printf("\n¿Desea leer otro archivo? (si/no): ");
            if (scanf("%s", opcion) != 1) {
                printf("Error en la entrada.\n");
                continue;
            }

            if (strcmp(opcion, "si") == 0 || strcmp(opcion, "no") == 0) {
                respuesta_valida = true;
            } else {
                printf("Error: Respuesta no valida. Debe ingresar exactamente 'si' o 'no'.\n");
            }
        } while (!respuesta_valida);
        // --- FIN VALIDACIÓN ESTRICTA ---

    } while (strcmp(opcion, "si") == 0);

    printf("Gracias por usar el sistema. ¡Adios!\n");
    return 0;
}
#include "graph.h"

void inicializar_grafo(Grafo *grafo) {
    grafo->num_nodos = 0;
}

int agregar_nodo_turistico(Grafo *grafo, PuntoTuristico pt) {
    if (grafo->num_nodos >= MAX_NODOS) {
        fprintf(stderr, "Error: No se pueden agregar más nodos al grafo.\n");
        return -1;
    }
    Nodo *nodo = &grafo->nodos[grafo->num_nodos];
    nodo->id = grafo->num_nodos;
    nodo->tipo = TIPO_TURISTICO;
    nodo->info.turistico = pt;
    nodo->num_vecinos = 0;
    grafo->num_nodos++;
    return nodo->id;
}

int agregar_nodo_interseccion(Grafo *grafo, Interseccion inter) {
    if (grafo->num_nodos >= MAX_NODOS) {
        fprintf(stderr, "Error: No se pueden agregar más nodos al grafo.\n");
        return -1;
    }
    Nodo *nodo = &grafo->nodos[grafo->num_nodos];
    nodo->id = grafo->num_nodos;
    nodo->tipo = TIPO_INTERSECCION;
    nodo->info.interseccion = inter;
    nodo->num_vecinos = 0;
    grafo->num_nodos++;
    return nodo->id;
}

int ya_es_vecino(Nodo *nodo, int id_buscado) {
    for (int i = 0; i < nodo->num_vecinos; i++) {
        if (nodo->vecinos[i] == id_buscado) {
            return 1; // Verdadero: ya existe
        }
    }
    return 0; // Falso: no existe
}

void agregar_arista(Grafo *grafo, int id1, int id2) {
    if (id1 < 0 || id1 >= grafo->num_nodos || id2 < 0 || id2 >= grafo->num_nodos) {
        fprintf(stderr, "Error: IDs de nodos inválidos para agregar arista.\n");
        return;
    }
    
    // Evitar auto-bucles (un nodo no puede conectarse consigo mismo)
    if (id1 == id2) return;

    Nodo *nodo1 = &grafo->nodos[id1];
    Nodo *nodo2 = &grafo->nodos[id2];

    // Solo agregamos si no son vecinos previamente
    if (!ya_es_vecino(nodo1, id2)) {
        if (nodo1->num_vecinos < MAX_VECINOS) {
            nodo1->vecinos[nodo1->num_vecinos++] = id2;
        } else {
            fprintf(stderr, "Error: Nodo %d ha alcanzado el máximo de vecinos.\n", id1);
        }
    }

    if (!ya_es_vecino(nodo2, id1)) {
        if (nodo2->num_vecinos < MAX_VECINOS) {
            nodo2->vecinos[nodo2->num_vecinos++] = id1;
        } else {
            fprintf(stderr, "Error: Nodo %d ha alcanzado el máximo de vecinos.\n", id2);
        }
    }
}

void imprimir_grafo(Grafo *grafo) {
    for (int i = 0; i < grafo->num_nodos; i++) {
        Nodo *nodo = &grafo->nodos[i];
        
        printf("Nodo ID: %d, Tipo: %s, ", nodo->id, 
              (nodo->tipo == TIPO_TURISTICO) ? "Turístico" : "Intersección");
              
        if (nodo->tipo == TIPO_TURISTICO) {
            printf("Nombre: %s\n", nodo->info.turistico.nombre);
        } else {
            // Imprime el cruce completo para facilitar la depuración
            printf("Cruce: %s con %s\n", 
                   nodo->info.interseccion.name_calle_a, 
                   nodo->info.interseccion.name_calle_b);
        }
        
        printf("  Vecinos: ");
        for (int j = 0; j < nodo->num_vecinos; j++) {
            printf("%d ", nodo->vecinos[j]);
        }
        printf("\n");
    }
}
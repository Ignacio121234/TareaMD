#include <stdio.h>
#include <stdlib.h>
#include "city_model.h"

// --- LECTURA DEL ARCHIVO ---
void leer_archivo_ciudad(Calle calles[], int *total_calles, PuntoTuristico lugares[], int *total_lugares) {
    char nombre_archivo[100];
    FILE *archivo = NULL;

    while (archivo == NULL) {
        printf("Escribe el nombre del archivo del mapa: ");
        scanf("%s", nombre_archivo);
        
        archivo = fopen(nombre_archivo, "r");
        if (archivo == NULL) {
            printf("Error: No se encontro el archivo. Escribelo bien.\n");
        }
    }

    fscanf(archivo, "%d", total_calles);
    for (int i = 0; i < *total_calles; i++) {
        fscanf(archivo, "%s %lf %lf %lf %lf %c", 
               calles[i].nombre, 
               &calles[i].inicio.x, &calles[i].inicio.y, 
               &calles[i].fin.x, &calles[i].fin.y, 
               &calles[i].sentido);
    }

    fscanf(archivo, "%d", total_lugares);
    for (int i = 0; i < *total_lugares; i++) {
        fscanf(archivo, "%s %s %lf", 
               lugares[i].nombre, 
               lugares[i].nombre_calle, 
               &lugares[i].posicion);
    }

    fclose(archivo);
}
#include <stdio.h>
#include <stdlib.h>
#include "city_model.h"

// --- LECTURA DEL ARCHIVO ---
void leer_archivo_ciudad(Calle calles[], int *total_calles, PuntoTuristico lugares[], int *total_lugares) {
    char nombre_archivo[100];
    FILE *archivo = NULL;

    while (archivo == NULL) {
        printf("\nEscribe el nombre del archivo del mapa: ");
        if (scanf("%s", nombre_archivo) != 1) {
            printf("Error en la entrada.\n");
            continue;
        }
        
        archivo = fopen(nombre_archivo, "r");
        if (archivo == NULL) {
            printf("Error: No se encontro el archivo '%s'. Escribelo bien.\n", nombre_archivo);
        }
    }

    if (fscanf(archivo, "%d", total_calles) != 1) {
        printf("Error al leer la cantidad de calles.\n");
        fclose(archivo);
        return;
    }

    if (*total_calles > MAX_CALLES) {
        printf("Error: El archivo tiene %d calles (maximo %d).\n", *total_calles, MAX_CALLES);
        *total_calles = MAX_CALLES;
    }

    for (int i = 0; i < *total_calles; i++) {
        fscanf(archivo, "%s %lf %lf %lf %lf %c", 
               calles[i].nombre, 
               &calles[i].inicio.x, &calles[i].inicio.y, 
               &calles[i].fin.x, &calles[i].fin.y, 
               &calles[i].sentido);
        
        // Validar rango 0-2000
        if (calles[i].inicio.x < 0 || calles[i].inicio.x > 2000 ||
            calles[i].inicio.y < 0 || calles[i].inicio.y > 2000 ||
            calles[i].fin.x < 0 || calles[i].fin.x > 2000 ||
            calles[i].fin.y < 0 || calles[i].fin.y > 2000) {
            printf("Advertencia: Calle %s tiene coordenadas fuera de rango (0-2000).\n", calles[i].nombre);
        }
    }

    if (fscanf(archivo, "%d", total_lugares) != 1) {
        printf("Error al leer la cantidad de puntos turisticos.\n");
        fclose(archivo);
        return;
    }

    for (int i = 0; i < *total_lugares; i++) {
        fscanf(archivo, "%s %s %lf", 
               lugares[i].nombre, 
               lugares[i].nombre_calle, 
               &lugares[i].posicion);
    }

    fclose(archivo);
    printf("Archivo cargado exitosamente.\n");
}
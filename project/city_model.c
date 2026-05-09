#include "city_model.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


/*
 La idea es que en este archivo se logre dejar el modelo de la cuidad listo 
 para poder calcular las intersecciones entre calles, y también para calcular 
 la distancia entre puntos turísticos y las calles.
*/



// 1. Calcula la orientación de los 3 puntos
// Retorna 0 (Colineal), 1 (Horario), o 2 (Antihorario)
int orientacion(Punto p, Punto q, Punto r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0.0) return 0; // colineales
    return (val > 0.0) ? 1 : 2; // horario o antihorario
}

bool on_segment(Punto p, Punto q, Punto r) {
    return (q.x <= fmax(p.x, r.x) && q.x >= fmin(p.x, r.x) &&
            q.y <= fmax(p.y, r.y) && q.y >= fmin(p.y, r.y));
}

bool se_intersectan(Calle c1, Calle c2) {
    Punto p1 = c1.inicio, q1 = c1.fin;
    Punto p2 = c2.inicio, q2 = c2.fin;

    int o1 = orientacion(p1, q1, p2);
    int o2 = orientacion(p1, q1, q2);
    int o3 = orientacion(p2, q2, p1);
    int o4 = orientacion(p2, q2, q1);

    // Casos generales
    if (o1 != o2 && o3 != o4)
        return true;

    // Casos especiales
    if (o1 == 0 && on_segment(p1, p2, q1)) return true;
    if (o2 == 0 && on_segment(p1, q2, q1)) return true;
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;

    return false; // No se intersectan
}

void calcular_interseccion(Calle c1, Calle c2) {
    Interseccion inter;
    Punto pto;
    Punto p1 = c1.inicio, q1 = c1.fin;
    Punto p2 = c2.inicio, q2 = c2.fin;

    double d = (p1.x - q1.x) * (p2.y - q2.y) - (p1.y - q1.y) * (p2.x - q2.x);
    if (d == 0.0) {
        pto.x = p1.x; // Colineales, tomar un punto cualquiera
        pto.y = p1.y;
        return pto;
    }

    double num_x = (p1.x * q1.y - p1.y * q1.x) * (p2.x - q2.x) - (p1.x - q1.x) * (p2.x * q2.y - p2.y * q2.x);
    double num_y = (p1.x * q1.y - p1.y * q1.x) * (p2.y - q2.y) - (p1.y - q1.y) * (p2.x * q2.y - p2.y * q2.x);
    pto.x = num_x / d;
    pto.y = num_y / d;

    inter.p = pto;
    

    return inter; 
}


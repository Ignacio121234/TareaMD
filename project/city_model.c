#include "city_model.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
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

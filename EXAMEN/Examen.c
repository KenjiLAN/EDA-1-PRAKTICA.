#include <stdio.h>
#include <stdlib.h>

// función para limpiar el bUfer de entrada (LO QUE ME SIRVIO EN LA PRACTICA DE LAS PELICULAS XD)
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int n, nuevo_tamano, i;
    float *calificaciones = NULL; // apuntador guarda las calificaciones
    float suma = 0.0;              // variable para acumular calificaciones
    int adicionales;              // para los estudiantes adicionales

    // 1. solicita cuántos alumnos van a poner o registrar 
    do {
        printf("-----Cuantos estudiantes vas registrar? ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("\nError: POR FAVOR INGRESA UN NUMERO MAYOR QUE 0.\n");
            limpiarBuffer();
        } else {
            break;
        }
    } while (1);

    // 2. reserva memoria dinámica para las primeras calificaciones 
    calificaciones = (float *)malloc(n * sizeof(float));
    if (calificaciones == NULL) {
        printf("\nError: No se pudo asignar memoria.\n"); // Verifica si malloc fallo
        return 1;
    }

    // 3. se hace la captura y la operacion para sacar los promedios 
    for (i = 0; i < n; i++) {
        do {
            printf("Calificacion del estudiante %d: ", i + 1);
            if (scanf("%f", &calificaciones[i]) != 1 || calificaciones[i] < 0 || calificaciones[i] > 10) {
                printf("\nError: POR FAVOR INGRESA UNA CALIFICACION VALIDA DE ENTRE 0 y 10..!!!.\n");
                limpiarBuffer();
            } else {
                suma += calificaciones[i];
                break;
            }
        } while (1);
    }

    // 4. El primer promedio 
    printf("\nPromedio inicial: %.2f\n", suma / n);

    // 5. pregunta para agregar más estudiantes 
    do {
        printf("\n---Quieres agregar a mas estudiantes? (cantidad, 0 para no): ");
        if (scanf("%d", &adicionales) != 1 || adicionales < 0) {
            printf("\nError: POR FAVOR INGRESA UN NUMERO VALIDO!! (0 o mayor).\n");
            limpiarBuffer();
        } else {
            break;
        }
    } while (1);

    if (adicionales > 0) {
        nuevo_tamano = n + adicionales; // hace el nuevo tamaño del arreglo

        // 6. amplia el arreglo con realloc
        float *temp = (float *)realloc(calificaciones, nuevo_tamano * sizeof(float));
        if (temp == NULL) {
            printf("\nError: No se pudo ampliar la memoria.\n");// verifica si realloc fallo o no
            free(calificaciones); // libera la memoria asignada antes
            return 1;
        }
        calificaciones = temp;

        for (i = n; i < nuevo_tamano; i++) { // captura las nuevas calificaciones
            do {
                printf("Calificacion del estudiante %d: ", i + 1);
                if (scanf("%f", &calificaciones[i]) != 1 || calificaciones[i] < 0 || calificaciones[i] > 10) {
                    printf("\nError: POR FAVOR INGRESA UNA CALIFICACION VALIDA ENTRE 0 y 10.\n");
                    limpiarBuffer(); //trabajando limpio
                } else {
                    break;
                }
            } while (1);
        }

        suma = 0.0;
        for (i = 0; i < nuevo_tamano; i++) {  // recalcula la suma total
            suma += calificaciones[i];
        }

        n = nuevo_tamano;  // actualiza el valor de n para mostrar el tamaño nuevo 
    }

    // 7. muestra todas las calificaciones y el promedio final
    printf("\n=== Calificaciones registradas ===\n");
    for (i = 0; i < n; i++) {
        printf("\nEstudiante %d: %.2f\n", i + 1, calificaciones[i]);
    }
    printf("\nPromedio general: %.2f\n", suma / n);

    // 8. libera la memoria utilizada para evitar desbordamiento la liked memory
    free(calificaciones);
    printf("\n.....Memoria liberada exitosamente!!.\n");

    return 0;
}


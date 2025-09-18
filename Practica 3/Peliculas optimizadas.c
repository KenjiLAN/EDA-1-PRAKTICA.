#include <stdio.h>
#include <string.h>
#include <ctype.h>//AQUÍ SIGUE MI PEQUEÑA AYUDA PARA AHORRAR TEXTO XDXDXD
#include <stdlib.h>

#ifdef _WIN32
#define LIMPIAR system("cls")
#else
#define LIMPIAR system("clear")
#endif
#define MAX_PELIS 10
#define NUM_DIR 2

struct pelicula {
    char nombre[20];
    char genero[20];
    int  anio;
    int  numDirectores;
    char directores[NUM_DIR][20];
};

//    FUNCIONES AUXILIARES TIPO C
int esnumero(const char *cadena) {
    if (cadena[0] == '\0') return 0;             
    for (int i = 0; cadena[i]; i++) {
        if (!isdigit((unsigned char)cadena[i])) return 0;
    }
    return 1;
}

void limpiarCadena(char *cadena) {
    cadena[strcspn(cadena, "\n")] = '\0';
}

void leerCadena(const char *msg, char *dest, int size) {
    printf("%s", msg);
    fgets(dest, size, stdin);
    limpiarCadena(dest);
}

int leerNumero(const char *msg, int min, int max) {
    char buffer[64];
    int valor;

    while (1) {
        printf("%s", msg);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            clearerr(stdin);
            continue;
        }
        limpiarCadena(buffer);

        if (!esnumero(buffer)) {
            printf("Error INGRESA SOLO NUMEROS!.\n");
            continue;
        }

        valor = atoi(buffer);

        if (valor < min || valor > max) {
            printf("Valor fuera de rango (%d - %d). Intenta de nuevo.\n", min, max);
            continue;
        }

        return valor;
    }
}

void mostrarPelicula(struct pelicula p) {
    printf("\nTitulo: %s\n", p.nombre);
    printf("Genero: %s\n", p.genero);
    printf("Anio: %d\n", p.anio);
    printf("Directores (%d):\n", p.numDirectores);
    for (int j = 0; j < p.numDirectores; j++) {
        printf("  - %s\n", p.directores[j]);
    }
}

void pausar() {
    printf("\nPresiona ENTER para continuar...");
    getchar();
}

// EL FOKIN PROGRAMA
int main() {
    struct pelicula videoteca[MAX_PELIS];
    int cantidad = 0;
    int opcion;

    do {
        LIMPIAR;
        printf("\n===== MENU DE VIDEOTECA =====\n");
        printf("1. Ingresar pelicula\n");
        printf("2. Ver peliculas\n");
        printf("3. Buscar pelicula\n");
        printf("0. Salir\n");
        printf("Selecciona una opcion: ");

        opcion = leerNumero("", 0, 3);

        switch (opcion) {
            case 1:
                LIMPIAR;
                if (cantidad >= MAX_PELIS) {
                    printf("El limite de peliculas ha sido alcanzado.\n");
                    pausar();
                    break;
                }

                printf("\n--- Ingresar nueva pelicula ---\n");
                leerCadena("Nombre: ", videoteca[cantidad].nombre, 20);
                leerCadena("Genero: ", videoteca[cantidad].genero, 20);

                videoteca[cantidad].anio = leerNumero("Anio: ", 1, 9999999); //No se me ocurrio mejor forma de arreglarlo 

                videoteca[cantidad].numDirectores = leerNumero("Numero de directores (1-2): ", 1, NUM_DIR);

                for (int j = 0; j < videoteca[cantidad].numDirectores; j++) {
                    char msg[40];
                    sprintf(msg, "Nombre del director %d: ", j + 1);
                    leerCadena(msg, videoteca[cantidad].directores[j], 20);
                }

                cantidad++;
                printf("La pelicula se agrego correctamente.\n");
                pausar();
                break;

            case 2:
                LIMPIAR;
                printf("\n--- Peliculas en videoteca ---\n");
                if (cantidad == 0) {
                    printf("A1 hay peliculas registradas.\n");
                } else {
                    for (int i = 0; i < cantidad; i++) {
                        mostrarPelicula(videoteca[i]);
                    }
                }
                pausar();
                break;

            case 3: {
                LIMPIAR;
                printf("\nBuscar por:\n1. Nombre\n2. Anio\n3. Genero\n4. Director\n");
                int criterio = leerNumero("Seleccione criterio: ", 1, 4);

                char busqueda[20];
                int encontrados = 0;

                switch (criterio) {
                    case 1:
                        leerCadena("Ingrese nombre: ", busqueda, 20);
                        for (int i = 0; i < cantidad; i++)
                            if (strcmp(videoteca[i].nombre, busqueda) == 0)
                                mostrarPelicula(videoteca[i]), encontrados++;
                        break;
                    case 2: {
                        int anioBuscado = leerNumero("Ingrese anio: ", 1, 9999);
                        for (int i = 0; i < cantidad; i++)
                            if (videoteca[i].anio == anioBuscado)
                                mostrarPelicula(videoteca[i]), encontrados++;
                        break;
                    }
                    case 3:
                        leerCadena("Ingresa el genero: ", busqueda, 20);
                        for (int i = 0; i < cantidad; i++)
                            if (strcmp(videoteca[i].genero, busqueda) == 0)
                                mostrarPelicula(videoteca[i]), encontrados++;
                        break;
                    case 4:
                        leerCadena("Ingresa nombre del director: ", busqueda, 20);
                        for (int i = 0; i < cantidad; i++)
                            for (int j = 0; j < videoteca[i].numDirectores; j++)
                                if (strcmp(videoteca[i].directores[j], busqueda) == 0)
                                    mostrarPelicula(videoteca[i]), encontrados++;
                        break;
                }

                if (!encontrados) printf("No hay coincidencias. :<\n");
                pausar();
                break;
            }

            case 0:
                LIMPIAR;
                printf("SALIENDO DEL PROGRAMA WAIT A MOMENT....\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}


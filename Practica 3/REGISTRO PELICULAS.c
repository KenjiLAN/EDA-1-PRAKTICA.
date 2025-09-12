#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

int esnumero(char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isdigit(cadena[i])) return 0;
    }
    return 1;
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
    printf("\n Presiona ENTER para continuar...");
    getchar();
}

int main() {
    struct pelicula videoteca[MAX_PELIS];
    int cantidad = 0;
    int opcion;
    char opcionStr[10];

    do {
        LIMPIAR;
        printf("\n===== MENU DE VIDEOTECA =====\n");
        printf("1. Ingresa una pelicula\n");
        printf("2. Ver peliculas agregadas\n");
        printf("3. Buscar pelicula\n");
        printf("0. Salir\n");
        printf("Selecciona una opcion: ");
        fgets(opcionStr, sizeof(opcionStr), stdin);
        opcionStr[strcspn(opcionStr, "\n")] = '\0';

        if (!esnumero(opcionStr)) {
            printf("Sintax Error Ingresa solo numeros!!!.\n");
            pausar();
            continue;
        }

        opcion = atoi(opcionStr);

        switch (opcion) {
            case 1:
                LIMPIAR;
                if (cantidad >= MAX_PELIS) {
                    printf("El limite de peliculasha sido alcanzado.\n");
                    pausar();
                    break;
                }

                printf("\n--- Ingresar nueva pelicula ---\n");
                printf("Nombre: ");
                fgets(videoteca[cantidad].nombre, 20, stdin);
                videoteca[cantidad].nombre[strcspn(videoteca[cantidad].nombre, "\n")] = '\0';

                printf("Genero: ");
                fgets(videoteca[cantidad].genero, 20, stdin);
                videoteca[cantidad].genero[strcspn(videoteca[cantidad].genero, "\n")] = '\0';

                char aniostr[10];
                do {
                    printf("Anio: ");
                    fgets(aniostr, 10, stdin);
                    aniostr[strcspn(aniostr, "\n")] = '\0';
                    if (!esnumero(aniostr)) {
                        printf("Sintax ERROR!! Ingresa solo numeros.\n");
                    }
                } while (!esnumero(aniostr));
                videoteca[cantidad].anio = atoi(aniostr);

                char numDirStr[10];
                do {
                    printf("Numero de directores (1 o 2): ");
                    fgets(numDirStr, sizeof(numDirStr), stdin);
                    numDirStr[strcspn(numDirStr, "\n")] = '\0';

                    if (!esnumero(numDirStr)) {
                        printf("Entrada invalida. Ingresa solo numeros.\n");
                        continue;
                    }

                    videoteca[cantidad].numDirectores = atoi(numDirStr);
                } while (videoteca[cantidad].numDirectores < 1 || videoteca[cantidad].numDirectores > NUM_DIR);

                for (int j = 0; j < videoteca[cantidad].numDirectores; j++) {
                    printf("Nombre del director %d: ", j + 1);
                    fgets(videoteca[cantidad].directores[j], 20, stdin);
                    videoteca[cantidad].directores[j][strcspn(videoteca[cantidad].directores[j], "\n")] = '\0';
                }

                cantidad++;
                printf("LA PELICULA SE AGREGO CORRECTAMENTE.\n");
                pausar();
                break;

            case 2:
                LIMPIAR;
                printf("\n--- Peliculas en videoteca ---\n");
                if (cantidad == 0) {
                    printf("No hay peliculas registradas.\n");
                } else {
                    for (int i = 0; i < cantidad; i++) {
                        mostrarPelicula(videoteca[i]);
                    }
                }
                pausar();
                break;

            case 3: {
                LIMPIAR;
                char criterioStr[10];
                int criterio;
                printf("\nBuscar por:\n");
                printf("1. Nombre\n2. Anio\n3. Genero\n4. Director\n");
                printf("Seleccione criterio: ");
                fgets(criterioStr, sizeof(criterioStr), stdin);
                criterioStr[strcspn(criterioStr, "\n")] = '\0';

                if (!esnumero(criterioStr)) {
                    printf("Entrada invalida. Ingresa solo numeros.\n");
                    pausar();
                    break;
                }

                criterio = atoi(criterioStr);

                char busqueda[20];
                int anioBuscado;
                int encontrados = 0;

                switch (criterio) {
                    case 1:
                        printf("Ingrese nombre: ");
                        fgets(busqueda, 20, stdin);
                        busqueda[strcspn(busqueda, "\n")] = '\0';
                        for (int i = 0; i < cantidad; i++) {
                            if (strcmp(videoteca[i].nombre, busqueda) == 0) {
                                mostrarPelicula(videoteca[i]);
                                encontrados++;
                            }
                        }
                        break;

                    case 2:
                        do {
                            printf("Ingrese anio: ");
                            fgets(busqueda, 10, stdin);
                            busqueda[strcspn(busqueda, "\n")] = '\0';
                            if (!esnumero(busqueda)) {
                                printf("! Error: Ingrese solo numeros.\n");
                            }
                        } while (!esnumero(busqueda));
                        anioBuscado = atoi(busqueda);
                        for (int i = 0; i < cantidad; i++) {
                            if (videoteca[i].anio == anioBuscado) {
                                mostrarPelicula(videoteca[i]);
                                encontrados++;
                            }
                        }
                        break;

                    case 3:
                        printf("Ingrese genero: ");
                        fgets(busqueda, 20, stdin);
                        busqueda[strcspn(busqueda, "\n")] = '\0';
                        for (int i = 0; i < cantidad; i++) {
                            if (strcmp(videoteca[i].genero, busqueda) == 0) {
                                mostrarPelicula(videoteca[i]);
                                encontrados++;
                            }
                        }
                        break;

                    case 4:
                        printf("Ingrese nombre del director: ");
                        fgets(busqueda, 20, stdin);
                        busqueda[strcspn(busqueda, "\n")] = '\0';
                        for (int i = 0; i < cantidad; i++) {
                            for (int j = 0; j < videoteca[i].numDirectores; j++) {
                                if (strcmp(videoteca[i].directores[j], busqueda) == 0) {
                                    mostrarPelicula(videoteca[i]);
                                    encontrados++;
                                    break;
                                }
                            }
                        }
                        break;

                    default:
                        printf("La opcion no es valida.\n");
                }

                if (encontrados == 0) {
                    printf("No hay coincidencias. :<\n");
                }
                pausar();
                break;
            }

            case 0:
                LIMPIAR;
                printf("SALIENDO DEL PROGRAMA\n");
                break;

            default:
                LIMPIAR;
                printf("La opcion no es valida, intemta de nuevo\n");
                pausar();
        }

    } while (opcion != 0);

    return 0;
}


//Y TODO POR HACER UN MALDITO MMENU DIOS MIO.... AYUDAME POR FAVOR 

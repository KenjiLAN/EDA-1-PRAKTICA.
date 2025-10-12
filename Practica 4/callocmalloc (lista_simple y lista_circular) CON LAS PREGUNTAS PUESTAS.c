#include <stdio.h>
#include <stdlib.h>

void limpiarBuffer() {
    while (getchar() != '\n');
}

int main() {
    int n, m;
    int *arr, *arr2;

    printf("=== PRACTICA 4: ALMACENAMIENTO DINAMICO ===\n\n");

	printf("USANDO Malloc\n");
	printf("Cuantos enteros quieres guardar con malloc? ");
	scanf("%d", &n);

	arr = (int *)malloc(n * sizeof(int));
	if (arr == NULL) {
    printf("ERROR No se pudo reservar memoria con malloc.\n");
    return 1;  //NO PUSE SCANF AQUI PARA QUE SE MUESTRE QUE SI FUNCIONA EL ERROR DE QUE NO SE PUDO RESERVAR MEMORIA PARA MALLOC
}

printf("\nValores iniciales con malloc (pueden ser basura):\n");
for (int i = 0; i < n; i++) {
    printf("  arr[%d] = %d\n", i, arr[i]);
}

    printf("\n USANDO Calloc\n");
    arr2 = (int *)calloc(n, sizeof(int));
    if (arr2 == NULL) {
        printf("No se pudo reservar memoria con calloc.\n");
        free(arr);
        return 1;
    }

    printf("\nValores iniciales con calloc (deben ser ceros):\n");
    for (int i = 0; i < n; i++) {
        printf("  arr2[%d] = %d\n", i, arr2[i]);
    }

    printf("\n Llenar arreglo\n");
    printf("Ingresa %d valores para llenar el arr2:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Valor para arr2[%d]: ", i);
        if (scanf("%d", &arr2[i]) != 1) {
            printf("SOLO PERMITIMOS NUMEROS AQUI.\n");
            limpiarBuffer();
            free(arr);
            free(arr2);
            return 1;
        }
    }

    printf("\n USANDO Realloc\n");
    printf("Nuevo tamanio del arreglo (arr)? ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        printf(" QUE SOLO PERMITIMOS NUMEROS AQUI..!!!.\n");
        limpiarBuffer();
        free(arr);
        free(arr2);
        return 1;
    }

    if (m < n) {
        printf("WARNING!!!: Estas reduciendo TU arreglo de %d a %d elementos\n", n, m);
        printf("   Se perderan los ultimos %d valores\n", n - m);
        
        printf("\nValores que se conservaran:\n");
        for (int i = 0; i < m; i++) {
            printf("  arr2[%d] = %d\n", i, arr2[i]);
        }
        
        printf("Valores que se perderan:\n");
        for (int i = m; i < n; i++) {
            printf("  arr2[%d] = %d\n", i, arr2[i]);
        }
        
        printf("\n QUIERES CONTINUAR..? (1 = Si, 0 = No): ");
        int continuar;
        if (scanf("%d", &continuar) != 1 || (continuar != 0 && continuar != 1)) {
            printf("1 PARA SI 0 PARA NO... ES TAN DIFICIL??.\n");
            limpiarBuffer();
            free(arr);
            free(arr2);
            return 1;
        }

        if (!continuar) {
            printf("Operacion cancelada.\n");
            free(arr);
            free(arr2);
            return 0;
        }
    }

    int *temp = (int *)realloc(arr2, m * sizeof(int));
    if (temp == NULL) {
        printf("No se pudo redimensionar el arreglo.\n");
        free(arr);
        free(arr2);
        return 1;
    }
    arr2 = temp;

    if (m > n) {
        printf("\n El arreglo ahora es mas grande. Ingresa %d ahora ingresa valores nuevos:\n", m - n);
        for (int i = n; i < m; i++) {
            printf("  Valor para arr2[%d]: ", i);
            if (scanf("%d", &arr2[i]) != 1) {
                printf("YA TE DIJE SOLO PERMITIMOS NUMEROS AQUI..!!.\n");
                limpiarBuffer();
                free(arr);
                free(arr2);
                return 1;
            }
        }
    }

    printf("\nValores finales de MALLOC:\n");
    for (int i = 0; i < n; i++) {
        printf("  arr[%d] = %d\n", i, arr[i]);
    }
    printf("\nValores finales de CALLOC:\n");
    for (int i = 0; i < m; i++) {
        printf("  arr2[%d] = %d\n", i, arr2[i]);
    }

    printf("\n LIBERANDOP MEMORIA \n");
    free(arr);
    free(arr2);
    printf("Memoria liberada correctamente.\n");

    return 0;
}

//1. ¿Qué diferencia observaron entre los valores iniciales con malloc y calloc?
// r= MALLOC me dejo valores basura despues solo me dijeron que rimensionara el de calloc malloc que quedo igual que al inicio con basura calloc se llevo toda la practica, la redimencion de arreglo 2 y el nuevo dato

//2. ¿Qué sucede si en realloc piden un tamaño más grande que el original? ¿y más pequeño?
//R= aqui si me di cuenta que al aumentar se le agrego que me pidiera un nuevo digito pero al reducirlo me daba error al inicio pero agregue una confirmacion que me advirtiera qye se me perderian valores y ya por gusto agregue cuales se perderian ya que en un mundo donde se llegue a usar en una oficina incluso saber que perdiste es importante parta reponerlo en caso de un accidente

//3. ¿Qué pasa si olvidan llamar a free?
//Lo intente al hacer pruebas y testeos con mi programa y tecnicamente no paso nada.. igaul me dio miedo.. pero se supone que la memoria no se libera el programa consume cada vez más RAM si se repite muchas veces, mi sistema se puede quedar sin memoria



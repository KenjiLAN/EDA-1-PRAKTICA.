#include <stdio.h>

int main() {
    int n;
    int a[5]; 
    int suma = 0, resta = 0;
    float promedio;
    int min, max;
    
    printf("Cuantos numeros vas a ingresar? maximo 5 numeros:\n");
    scanf("%i", &n);
    if (n > 5 || n <= 0) {
        printf("Caracter no valido debe ser un numero del 1 al 5.\n");
        return 0;
    }
    
    printf("Ingresa %i numeros:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Numero %i: ", i);
        scanf("%i", &a[i]);
        suma += a[i];
        if (i == 0) {
            min = max = a[i]; 
            resta = a[i];     // la res
        } else {
            if (a[i] < min) min = a[i];
            if (a[i] > max) max = a[i];
            resta -= a[i];
        }
    }

    promedio = (float)suma/n;

    // mostrar donde andan mis arreglos en la memoria
    printf("\nLos elementos del arreglo son:\n");
    for (int i = 0; i < n; i++) {
        printf("a[%i] = %i\n", i, a[i]);
    }

    // mostrar resultados de mis operaciones primarias 
    printf("\nSuma: %i\n", suma);
    printf("Resta: %i\n", resta);
    printf("Promedio: %.2f\n", promedio);
    printf("Minimo: %i\n", min);
    printf("Maximo: %i\n", max);

    //donde aparece el minimo y maximo en cada arreglo
    printf("\nDonde aparece el minimo es en el arreglo..:\n");
    for (int i = 0; i < n; i++) {
        if (a[i] == min) {
            printf("a[%i]\n", i);
        }
    }

    printf("Donde aparece el maximo es en el arreglo..:\n");
    for (int i = 0; i < n; i++) {
        if (a[i] == max) {
            printf("a[%i]\n", i);
        }
    }

    // Arreglo invert
    printf("\nArreglo invertido:\n");
    for (int i = n - 1; i >= 0; i--) {
        printf("a[%i] = %i\n", i, a[i]);
    }

    return 0;
}
// suma resta promedio minimo maximo del arreglo indicando indices de aparicion invertir el arreglo

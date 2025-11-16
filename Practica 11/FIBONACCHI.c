#include <stdio.h>

long long int memoria[95];

long long int fibonacci(int n) {
    if (memoria[n] != -1)
        return memoria[n];

    memoria[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return memoria[n];
}

int main() {
    for (int i = 0; i < 95; i++)
        memoria[i] = -1;
        
///////////////////////////

    memoria[1] = 0;
    memoria[2] = 1;

    int posiciones[] = {7, 21, 40, 71, 94};
    int n = 5;

    printf("La sucesion de Fibonachi:\n");
    for (int i = 0; i < n; i++) {
        int p = posiciones[i];
        printf("Valor(%d) = %lld\n", p, fibonacci(p));
    }
    return 0;
}

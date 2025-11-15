#include <stdio.h>
#define MAX 5

typedef struct {
    int datos[MAX];
    int frente;
    int final;
    int tamanio;
} ColaCircular;

void inicializarCola(ColaCircular *c) {
    c->frente = 0;
    c->final = -1; 
    c->tamanio = 0;
    printf("Cola circular inicializada\n");
}

int isEmpty(ColaCircular *c) {
    return c->tamanio == 0;
}

int isFull(ColaCircular *c) {
    return c->tamanio == MAX;
}

void enqueue(ColaCircular *c, int valor) {
    if (isFull(c)) {
        printf("Error La cola está llena, no se puede encolar %d\n", valor);
        return;
    }
    c->final = (c->final + 1) % MAX;  
    c->datos[c->final] = valor;  
    c->tamanio++;
    printf("Encolado: %d\n", valor);
}

int dequeue(ColaCircular *c) {
    if (isEmpty(c)) {
        printf("Error La cola vacia\n");
        return -1;
    }
    int valor = c->datos[c->frente];
    c->frente = (c->frente + 1) % MAX;
    c->tamanio--;
    printf("Desencolado: %d\n", valor);
    return valor;
}

int peek(ColaCircular *c) {
    if (isEmpty(c)) {
        printf("Cola vacia\n");
        return -1;
    }
    return c->datos[c->frente];
}

void printQueue(ColaCircular *c) {
    printf("\n=== ESTADO DE LA COLA ===\n");
    printf("Contenido: [");
    int i = c->frente;
    for (int cont = 0; cont < c->tamanio; cont++) {
        printf("%d", c->datos[i]);
        i = (i + 1) % MAX;
        if (cont < c->tamanio - 1) printf(", ");
    }
    printf("]\n");
    printf("Frente: %d, Final: %d, Tamanio: %d/%d\n", 
           c->frente, c->final, c->tamanio, MAX);
    printf("Vacia: %s, Llena: %s\n", 
           isEmpty(c) ? "Si" : "No", 
           isFull(c) ? "Si" : "No");
    printf("===============================\n\n");
}
//menu pa que se maneje mejor
void mostrarMenu() {
    printf("\n=== COLA CIRCULAR ===\n");
    printf("1. Encolar (enqueue)\n");
    printf("2. Desencolar (dequeue)\n");
    printf("3. Ver frente (peek)\n");
    printf("4. Mostrar cola\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
}
int main() {
    ColaCircular cola;
    inicializarCola(&cola);
    int opcion, valor;
    
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                printf("Ingrese valor a encolar: ");
                scanf("%d", &valor);
                enqueue(&cola, valor);
                break;
            case 2:
                dequeue(&cola);
                break;
            case 3:
                valor = peek(&cola);
                if (valor != -1) {
                    printf("Frente de la cola: %d\n", valor);
                }
                break;
            case 4:
                printQueue(&cola);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf(" Sorry opcion inválida\n");
        }
    } while (opcion != 5);
    
    return 0;
}

//1. ¿Por qué en la cola circular no se desperdician posiciones como en la cola lineal?
//Porque cuando llegas al final del arreglo, vuelves a empezar desde el principio. Es como un círculo donde cuando terminas, empiezas otra vez.
//2. ¿Qué pasa cuando el índice final llega al final del arreglo?
//Simplemente salta al inicio y sigue usando los espacios que ya se liberaron antes,es como simplemente dar la vuelta.
//3. ¿Qué sucede si intentas encolar cuando la cola está llena?
//En mi caso te dice "Error: Cola llena" y no deja meter más numeros o datos

#include <stdio.h>
#define MAX 5

typedef struct {
    int datos[MAX];
    int frente;
    int tamano;
} Deque;





void inicializarDeque(Deque *d) {
    d->frente = 0;
    d->tamano = 0;
    printf("Deque inicializado\n");
}

int isEmptyDeque(Deque *d) {
    return d->tamano == 0;
}

int isFullDeque(Deque *d) {
    return d->tamano == MAX;
}

int rearIndex(Deque *d) {
    return (d->frente + d->tamano - 1) % MAX;
}

void insert_front(Deque *d, int valor) {
    if (isFullDeque(d)) {
        printf("Error EL Deque esta lleno, no se puede insertar %d al frente\n", valor);
        return;
    }
    d->frente = (d->frente - 1 + MAX) % MAX;
    d->datos[d->frente] = valor;
    d->tamano++;
    printf("Insertado al frente: %d\n", valor);
}

void insert_rear(Deque *d, int valor) {
    if (isFullDeque(d)) {
        printf("ERROR EL DEQUEUE esta lleno, no se puede insertar %d al final\n", valor);
        return;
    }
    int rear = (d->frente + d->tamano) % MAX;
    d->datos[rear] = valor;
    d->tamano++;
    printf("Insertado al final: %d\n", valor);
}

int delete_front(Deque *d) {
    if (isEmptyDeque(d)) {
        printf("Error el Deque esta vacio vacio\n");
        return -1;
    }
    int valor = d->datos[d->frente];
    d->frente = (d->frente + 1) % MAX;
    d->tamano--;
    printf("Eliminado del frente: %d\n", valor);
    return valor;
}

int delete_rear(Deque *d) {
    if (isEmptyDeque(d)) {
        printf("Error el Dequeue esta vacio\n");
        return -1;
    }
    int rear = rearIndex(d);
    int valor = d->datos[rear];
    d->tamano--;
    printf("Eliminado de la parte final: %d\n", valor);
    return valor;
}

int peek_front(Deque *d) {
    if (isEmptyDeque(d)) {
        printf("Deque está vacio :<\n");
        return -1;
    }
    return d->datos[d->frente];
}

int peek_rear(Deque *d) {
    if (isEmptyDeque(d)) {
        printf("Deque vacio :< \n");
        return -1;
    }
    return d->datos[rearIndex(d)];
}

void printDeque(Deque *d) {
    printf("\n=== ESTADO ACTUAL DEL DEQUE ===\n");
    printf("Contenido: [");
    for (int i = 0; i < d->tamano; i++) {
        int index = (d->frente + i) % MAX;
        printf("%d", d->datos[index]);
        if (i < d->tamano - 1) printf(", ");
    }
    printf("]\n");
    printf("Frente: %d, Final: %d, Tamano es de: %d/%d\n", 
           d->frente, rearIndex(d), d->tamano, MAX);
    printf("Vacio: %s, Lleno: %s\n", 
           isEmptyDeque(d) ? "Si" : "No", 
           isFullDeque(d) ? "Si" : "No");
    printf("================================\n\n");
}

void mostrarMenuDeque() {
    printf("\n=== COLA DOBLE (DEQUE) ===\n");
    printf("1. Insertar al frente\n");
    printf("2. Insertar al final\n");
    printf("3. Eliminar del frente\n");
    printf("4. Eliminar del final\n");
    printf("5. Ver frente\n");
    printf("6. Ver final\n");
    printf("7. Mostrar deque\n");
    printf("8. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    Deque deque;
    inicializarDeque(&deque);
    int opcion, valor;
    
    do {
        mostrarMenuDeque();
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                printf("Ingrese valor a insertar al frente: ");
                scanf("%d", &valor);
                insert_front(&deque, valor);
                break;
            case 2:
                printf("Ingrese valor a insertar al final: ");
                scanf("%d", &valor);
                insert_rear(&deque, valor);
                break;
            case 3:
                delete_front(&deque);
                break;
            case 4:
                delete_rear(&deque);
                break;
            case 5:
                valor = peek_front(&deque);
                if (valor != -1) {
                    printf("Frente del deque: %d\n", valor);
                }
                break;
            case 6:
                valor = peek_rear(&deque);
                if (valor != -1) {
                    printf("Final del deque: %d\n", valor);
                }
                break;
            case 7:
                printDeque(&deque);
                break;
            case 8:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != 8);
    
    return 0;
}

//1. ¿Qué diferencia tiene el deque frente a la cola circular normal?
//La cola normal solo deja meter por atrás y sacar por delante. El deque deja meter y sacar por AMBOS lados por delante y por atrás.

//2. ¿Qué operaciones permiten simular tanto FIFO como LIFO?
//Para simular FIFO (como cola normal): insert_rear() + delete_front()
//Para simular LIFO (como pila):insert_rear() + delete_rear() o tambien insert_front() + delete_front()

//3. Investiga que aplicaciones prácticas tiene deque.
//El historial del navegador (adelante/atrás), El undo/redo de los programas, Cuando en un juego los jugadores VIP pasan primero, En cualquier cosa donde necesites ir para adelante y para atrás

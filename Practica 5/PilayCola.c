#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  //SE USÓ PARA EL SSCANF
#define MAX 5

typedef struct {
    int datos[MAX];
    int tope;
} Pila;

typedef struct {
    int datos[MAX];
    int frente;
    int final;
} Cola;

// Funciones para la pila
void inicializarPila(Pila *p) {
    p->tope = -1;
    printf("Pila inicializada vacia.\n");
}

int estaLlenaPila(Pila *p) {
    return p->tope == MAX - 1;
}

int estaVaciaPila(Pila *p) {
    return p->tope == -1;
}

void push(Pila *p, int valor) {
    if (estaLlenaPila(p)) {
        printf("La pila esta llena.\n");
        return;
    }
    p->datos[++(p->tope)] = valor;
    printf("Elemento %d apilado EXITOSAMENTE!!.\n", valor);
}

int pop(Pila *p) {
    if (estaVaciaPila(p)) {
        printf("Sorry la pila esta vacia.\n");
        return -1;
    }
    return p->datos[(p->tope)--];
}

void mostrarPila(Pila *p) {
    printf("\n Estado de la pila: ");
    for (int i = 0; i <= p->tope; i++) {
        printf("%d ", p->datos[i]);
    }
    printf("\n");
}

// Funciones para la cola
void inicializarCola(Cola *c) {
    c->frente = 0;
    c->final = -1;
    printf("\n Cola inicializada vacia.\n");
}

int estaLlenaCola(Cola *c) {
    return c->final == MAX - 1;
}

int estaVaciaCola(Cola *c) {
    return c->frente > c->final;
}

void enqueue(Cola *c, int valor) {
    if (estaLlenaCola(c)) {
        printf("La cola esta llena.\n");
        return;
    }
    c->datos[++(c->final)] = valor;
    printf("\n Elemento %d encolado EXITOSAMENTE.!!!.\n", valor);
}

int dequeue(Cola *c) {
    if (estaVaciaCola(c)) {
        printf("Sorry la cola esta vacia.\n");
        return -1;
    }
    return c->datos[(c->frente)++];
}

void mostrarCola(Cola *c) {
    printf("\n Estado de la cola: ");
    for (int i = c->frente; i <= c->final; i++) {
        printf("%d ", c->datos[i]);
    }
    printf("\n");
}

// Mi validacion para que sean solo numeros
int leerEnteroSeguro() {
    int valor;
    char entrada[100];
    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin)) {
            if (sscanf(entrada, "%d", &valor) == 1) { //CTYPE SE USA PARA VALIDAR SI ES UN DIGITO POR LO QUE USE EL SSCANF
                return valor;
            } else {
                printf("\n APOCO ESTAMOS TRABAJANDO CON LETRAS??? \n INTENTA DE NUEVO: ");
            }
        }
    }
}

// Validacion para que nno exista error al (MAXIMO 5)
int leerCantidadMaxima() {
    int cantidad;
    while (1) {
        printf("Cuantos elementos quieres Apilar? (maximo %d): ", MAX);
        cantidad = leerEnteroSeguro();
        if (cantidad > MAX) {
            printf("TE DIJE QUE SOLO %d!!!\n", MAX);
        } else if (cantidad <= 0) {
            printf("Debes ingresar al menos 1 elemento.\n");
        } else {
            return cantidad;
        }
    }
}

// Programa principal
int main() {
    Pila pila;
    Cola cola;
    int n, valor;
    int pilaIngresados[MAX], colaIngresados[MAX];
    int pilaCount = 0, colaCount = 0;

    // Parte de la pila
    inicializarPila(&pila);
    n = leerCantidadMaxima();
    for (int i = 0; i < n; i++) {
        printf("\n Elemento #%d: ", i + 1);
        valor = leerEnteroSeguro();
        push(&pila, valor);
        pilaIngresados[pilaCount++] = valor;
        mostrarPila(&pila);
    }

    printf("\n Cuantos elementos quieres desapilar?: ");
    n = leerEnteroSeguro();
    for (int i = 0; i < n; i++) {
        int extraido = pop(&pila);
        if (extraido != -1) {
            printf("\n Elemento desapilado EXITOSAMENTE: %d\n", extraido);
            mostrarPila(&pila);
        }
    }

    // Parte de la cola
    inicializarCola(&cola);
    n = leerCantidadMaxima();
    for (int i = 0; i < n; i++) {
        printf("\n Elemento #%d: ", i + 1);
        valor = leerEnteroSeguro();
        enqueue(&cola, valor);
        colaIngresados[colaCount++] = valor;
        mostrarCola(&cola);
    }

    printf("\n Cuantos elementos quieres desencolar?: ");
    n = leerEnteroSeguro();
    for (int i = 0; i < n; i++) {
        int extraido = dequeue(&cola);
        if (extraido != -1) {
            printf("Elemento desencolado: %d\n", extraido);
            mostrarCola(&cola);
        }
    }

    // Resumen
    printf("\n Resumen:\n");

    printf("\n Pila - LIFO (El Ultimo en entrar, primero en salir).\n");
    printf("Orden de entrada: ");
    for (int i = 0; i < pilaCount; i++) {
        printf("%d ", pilaIngresados[i]);
    }
    if (pilaCount > 0)
        printf("\n El elemento que se saca primero en LIFO es: %d\n", pilaIngresados[pilaCount - 1]);
    else
        printf("\n(No se ingresaron elementos en la pila)\n");

    printf("\n Cola - FIFO (El Primero en entrar, Primero en salir).\n");
    printf("Orden de entrada: ");
    for (int i = 0; i < colaCount; i++) {
        printf("%d ", colaIngresados[i]);
    }
    if (colaCount > 0)
        printf("\nEl elemento que se saca primero en FIFO es: %d\n", colaIngresados[0]);
    else
        printf("\n(No se ingresaron elementos en la cola)\n");

    return 0;
}

//1. ¿Qué diferencias notaron entre el orden de salida de la pila y de la cola?
// EN LA PILA ME SACA LOS ULTIMOS DATOS COMO LO EXPLIQUE AL FINAL DE MI PROGRAMA, Y LA COLA ME SACA LOS PRIMEROS DATOS INGRESADOS.. 
//2. ¿Qué sucede si intentan hacer pop en una pila vacía o dequeue en una cola vacía?
// En mi programa aparece un mensaje Sorry la pila/cola Estan vacias
//3. ¿Qué sucede si intentan insertar más elementos que la capacidad máxima?
//Aparece el mensaje la cola está llena, aunque en mi programa evito eso tecnicamente haciendo la evaluacion desde un inicio para evitar esa cuestion.

#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo *siguiente;
};

void insertarInicio(struct Nodo **cabeza, int valor) {
    struct Nodo *nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = *cabeza;
    *cabeza = nuevoNodo;
    printf("Valor %d insertado al inicio.\n", valor);
}

void recorrer(struct Nodo *cabeza) {
    struct Nodo *actual = cabeza;
    if (actual == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    
    printf("Contenido de la lista: ");
    while (actual != NULL) {
        printf("%d", actual->dato);
        if (actual->siguiente != NULL) {
            printf(" -> ");
        }
        actual = actual->siguiente;
    }
    printf(" -> NULL\n");
}

void eliminar(struct Nodo **cabeza, int valor) {
    if (*cabeza == NULL) {
        printf("La lista esta vacia. No se puede eliminar.\n");
        return;
    }
    
    struct Nodo *actual = *cabeza;
    struct Nodo *anterior = NULL;
    
    while (actual != NULL && actual->dato != valor) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL) {
        printf("Valor %d no esta en la lista.\n", valor);
        return;
    }
    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    }
    else {
        anterior->siguiente = actual->siguiente;
    }
    free(actual);
    printf("Valor %d eliminado de la lista.\n", valor);
}

void liberar(struct Nodo *cabeza) {
    struct Nodo *actual = cabeza;
    struct Nodo *siguiente;
    while (actual !=NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    
    printf("La memoria ha sido liberada correctamente.\n");
}
int main() {
    struct Nodo *cabeza = NULL;
    int opcion, valor, cantidad, i;
    
    printf("=== LISTA ENLAZADA SIMPLE ===\n\n");
    printf("Cuantos valores desea insertar al inicio? ");
    scanf("%d", &cantidad);
    
    for (i = 0; i < cantidad; i++) {
        printf("Ingrese el valor %d: ", i + 1);
        scanf("%d", &valor);
        insertarInicio(&cabeza, valor);
        recorrer(cabeza);
        printf("\n");
    }
    
    printf("\n--- Recorrido completo de la lista ---\n");
    recorrer(cabeza);
    printf("\nQue valor quieres eliminar? ");
    scanf("%d", &valor);
    eliminar(&cabeza, valor);
    
    printf("\nLista despues de eliminar:\n");
    recorrer(cabeza);
    
    printf("\n--- Liberando memoria ---\n");
    liberar(cabeza);
    cabeza = NULL;
    
    return 0;
}

//1. ¿Por qué las listas enlazadas no necesitan tamaño fijo como los arrays?
//Porque cada nodo se crea cuando lo necesitas, como ir agregando argollas a una cadena en cambio en un array tienes que establecer desde el principio lo que vas a usar por ejemplo "voy a usar 10 casillas", pero con listas simplemente vas pidiendo memoria para cada nuevo dato.

//2. ¿Qué diferencia hay entre mover la cabeza y cambiar punteros internos?
//Mover la cabeza cambia el inicio de la lista, mientras que modificar punteros internos mantiene la cabeza pero cambia las conexiones entre nodos existentes.
//Es como cambiar al primer jugador de un equipo afectara a toda la lista. 
//Mientras que cambiar punteros internos es como hacer que dos jugadores se pasen la pelota entre ellos, sin afectar al primero.

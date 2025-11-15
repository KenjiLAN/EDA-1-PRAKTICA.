#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo *siguiente;
};

void insertarInicioCircular(struct Nodo **cabeza, struct Nodo **ultimo, int valor) {
    struct Nodo *nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = valor;
    
    if (*cabeza == NULL) {
        nuevoNodo->siguiente = nuevoNodo;
        *cabeza = nuevoNodo;
        *ultimo = nuevoNodo;
    } else {
        nuevoNodo->siguiente = *cabeza;
        *cabeza = nuevoNodo;
        (*ultimo)->siguiente = *cabeza;
    }
    
    printf("Valor %d insertado al inicio.\n", valor);
}

void recorrerCircular(struct Nodo *cabeza) {
    if (cabeza == NULL) {
        printf("La lista circular esta vacia.\n");
        return;
    }
    struct Nodo *actual = cabeza;
    printf("Contenido de la lista circular: ");
    do {
        printf("%d", actual->dato);
        actual = actual->siguiente;
        if (actual != cabeza) {
            printf(" -> ");
        }
    } while (actual !=cabeza);
    
    printf(" ? (vuelve a %d)\n", cabeza->dato);
}
void eliminarCircular(struct Nodo **cabeza, struct Nodo **ultimo, int valor) {
    if (*cabeza == NULL) {
        printf("La lista circular esta vacia. No se puede eliminar.\n");
        return;
    }
    
    struct Nodo *actual = *cabeza;
    struct Nodo *anterior = *ultimo;
    int encontrado = 0;
    
    do {
        if (actual->dato == valor) {
            encontrado = 1;
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    } while (actual != *cabeza);
    if (!encontrado) {
        printf("Valor %d no encontrado en la lista circular.\n", valor);
        return;
    }
    
    if (actual == *cabeza && actual->siguiente == *cabeza) {
        *cabeza = NULL;
        *ultimo = NULL;
    }

    else if (actual == *cabeza) {
        *cabeza = (*cabeza)->siguiente;
        (*ultimo)->siguiente = *cabeza;
    }
    else if (actual == *ultimo) {
        *ultimo = anterior;
        (*ultimo)->siguiente = *cabeza;
    }
    else {
        anterior->siguiente = actual->siguiente;
    }
    
    if (actual == *ultimo && actual != *cabeza) {
        *ultimo = anterior;
    }
    
    free(actual);
    printf("Valor %d fue eliminado de la lista circular.\n", valor);
}

void liberarCircular(struct Nodo **cabeza, struct Nodo **ultimo) {
    if (*cabeza == NULL) {
        printf("La lista circular ya esta vacia.\n");
        return;
    }
    
    struct Nodo *actual = *cabeza;
    struct Nodo *siguiente;
    (*ultimo)->siguiente = NULL;
    
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    
    *cabeza = NULL;
    *ultimo = NULL;
    
    printf("Memoria de la lista circular liberada correctamente.\n");
}


int main() {
    struct Nodo *cabeza = NULL;
    struct Nodo *ultimo = NULL;
    int opcion, valor, cantidad, i;
    
    printf("=== LISTA ENLAZADA CIRCULAR ===\n\n");
    printf("Cuantos valores desea insertar al inicio? ");
    scanf("%d", &cantidad);
    for (i = 0; i < cantidad; i++) {
        printf("Ingrese el valor %d: ", i + 1);
        scanf("%d", &valor);
        insertarInicioCircular(&cabeza, &ultimo, valor);
        recorrerCircular(cabeza);
        printf("\n");
    }
    
    // Paso B3: error linea 
    printf("\n--- Recorrido completo de la lista circular ---\n");
    recorrerCircular(cabeza);

    if (cabeza != NULL) {
        printf("Cabeza: %d\n", cabeza->dato);
        printf("Ultimo: %d\n", ultimo->dato);
        printf("Ultimo apunta a: %d\n", ultimo->siguiente->dato);
    }
    
    // B4: terminar falta la 122
    printf("\nQue valor desea eliminar? ");
    scanf("%d", &valor);
    eliminarCircular(&cabeza, &ultimo, valor);
    printf("\nLista circular actualizada despues de eliminar:\n");
    recorrerCircular(cabeza);
    if (cabeza != NULL) {
        printf("Cabeza: %d, Ultimo: %d\n", cabeza->dato, ultimo->dato);
    }
    printf("\n--- Liberando memoria ---\n");
    liberarCircular(&cabeza, &ultimo);
    
    return 0;
}

//1. ¿Qué ventaja tiene la lista circular frente a la simple?
//La principal es que nunca termina, después del últimodato vuelves al primero omo un círculo que nos proporciona de datos continuos mientras la lista simple es una calle sin salida o una tira de papel finita 

//2. ¿Qué error puede causar un bucle infinito en una lista circular?
//No actualizar punteros correctamente o Perder la referencia a cabeza o usar while(actual != NULL) en vez de while(actual != cabeza) ya que en una lista circular no hay null

//3. ¿Qué estructuras o programas del mundo real se basan en listas circulares?
//Buffers de audio para streaming, almacenamiento temporal en videojuegos, turnos de jugadores en juegos de mesa o rol y Listas de reproducción de música


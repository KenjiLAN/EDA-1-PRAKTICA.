#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo *anterior;
    struct Nodo *siguiente;
};

struct Nodo *inicio = NULL;

void insertarInicio(struct Nodo **inicio, int valor) {
    struct Nodo *nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo->dato = valor;
    nuevo->anterior = NULL;
    nuevo->siguiente = *inicio;
    
    if (*inicio != NULL) {
        (*inicio)->anterior = nuevo;
    }
    
    *inicio = nuevo;
    printf("Valor %d insertado al inicio.\n", valor);
}

void insertarFinal(struct Nodo **inicio, int valor) {
    struct Nodo *nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    
    if (*inicio == NULL) {
        nuevo->anterior = NULL;
        *inicio = nuevo;
    } else {
        struct Nodo *temp = *inicio;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
        nuevo->anterior = temp;
    }
    printf("Valor %d insertado al final.\n", valor);
}

void recorrerAdelante(struct Nodo *inicio) {
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    //delante
    struct Nodo *temp = inicio;
    printf("Lista (adelante): ");
    while (temp != NULL) {
        printf("%d ", temp->dato);
        temp = temp->siguiente;
    }
    printf("\n");
}

void recorrerAtras(struct Nodo *inicio) {
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    
    struct Nodo *temp = inicio;
    while (temp->siguiente != NULL) {
        temp = temp->siguiente;
    }
    //atras
    printf("Lista (atras): ");
    while (temp != NULL) {
        printf("%d ", temp->dato);
        temp = temp->anterior;
    }
    printf("\n");
}

void eliminar(struct Nodo **inicio, int valor) {
    if (*inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    
    struct Nodo *temp = *inicio;
    
    while (temp != NULL && temp->dato != valor) {
        temp = temp->siguiente;
    }
    if (temp == NULL) {
        printf("Valor %d no encontrado en la lista.\n", valor);
        return;
    }
    
    //primero
    if (temp->anterior == NULL) {
        *inicio = temp->siguiente;
        if (*inicio != NULL) {
            (*inicio)->anterior = NULL;
        }
    }
    //ultimo
    else if (temp->siguiente == NULL) {
        temp->anterior->siguiente = NULL;
    }
    //medio
    else {
        temp->anterior->siguiente = temp->siguiente;
        temp->siguiente->anterior = temp->anterior;
    }
    free(temp);
    printf("Valor %d eliminado correctamente.\n", valor);
}

void liberar(struct Nodo *inicio) {
    struct Nodo *temp = inicio;
    struct Nodo *siguiente;
    while (temp != NULL) {
        siguiente = temp->siguiente;
        free(temp);
        temp = siguiente;
    }
    printf("Memoria liberada correctamente.\n");
}

// ya lo demas es del menu si no si me quedaria en las 125 lineas de codigo ayuda
void mostrarMenu() {
    printf("\n=== MENU DE LA LISTA DOBLEMENTE LIGADA ===\n");
    printf("1. Insertar al inicio\n");
    printf("2. Insertar al final\n");
    printf("3. Recorrer hacia adelante\n");
    printf("4. Recorrer hacia atras\n");
    printf("5. Eliminar valor\n");
    printf("6. Liberar memoria y salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    int opcion, valor, cantidad, i;
    printf("=== IMPLEMENTACION DE LISTA DOBLEMENTE LIGADA ===\n");
    printf("\n--- Insercion al inicio ---\n");
    printf("Cuantos valores desea insertar al inicio? ");
    scanf("%d", &cantidad);
    
    for (i = 0; i < cantidad; i++) {
        printf("Ingrese el valor %d: ", i + 1);
        scanf("%d", &valor);
        insertarInicio(&inicio, valor);
    }
    
    recorrerAdelante(inicio);
    recorrerAtras(inicio);
    
    printf("\n--- Insercion al final ---\n");
    printf("Cuantos valores desea insertar al final? ");
    scanf("%d", &cantidad);
    
    for (i = 0; i < cantidad; i++) {
        printf("Ingrese el valor %d: ", i + 1);
        scanf("%d", &valor);
        insertarFinal(&inicio, valor);
    }
    
    recorrerAdelante(inicio);
    recorrerAtras(inicio);
    
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Ingrese el valor a insertar al inicio: ");
                scanf("%d", &valor);
                insertarInicio(&inicio, valor);
                break;     
            case 2:
                printf("Ingrese el valor a insertar al final: ");
                scanf("%d", &valor);
                insertarFinal(&inicio, valor);
                break;
            case 3:
                recorrerAdelante(inicio);
                break;
            case 4:
                recorrerAtras(inicio);
                break;
            case 5:
                printf("Ingrese el valor a eliminar: ");
                scanf("%d", &valor);
                eliminar(&inicio, valor);
                break;
            case 6:
                liberar(inicio);
                inicio = NULL;
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 6);
    
    return 0;
}

//1.	¿Por qué es más fácil eliminar un nodo intermedio en una lista doblemente ligada que en una lista simple?
//Porque en una lista doblemente ligada, cada nodo tiene referencias tanto al nodo anterior como al siguiente esto nos permite acceder directamente al nodo anterior desde cualquier nodo, no recorrer la lista desde el inicio para encontrar el nodo anterior y realizar la eliminación en tiempo constante una vez localizado el nodo

//2.	¿Qué sucede si se olvida actualizar alguno de los punteros anterior o siguiente?
//Pueden pasar 3 cosas
//Si se olvida actualizar el puntero anterior el nodo anterior al eliminado seguirá apuntando a memoria liberada, causando un acceso inválido.
//Si se olvida actualizar el puntero siguiente el nodo siguiente al eliminado perderá la conexión con el resto de la lista.
//Ya se son ambos casos se nos producen memory leaks, segmentation faults, y la lista queda en estado inconsistente y podría en casos expremos causarnos un colapso en el todo el programa

//3. ¿En qué escenarios prácticos se usa una lista doblemente ligada?
// Navegadores web, Editores de texto, Reproductores multimedia, sistemas operativos y en Juegos



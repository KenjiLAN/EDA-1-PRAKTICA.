#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo *anterior;
    struct Nodo *siguiente;
};

struct Nodo *inicio = NULL;

void insertarInicioCircular(struct Nodo **inicio, int valor) {
    struct Nodo *nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo->dato = valor;
    
    if (*inicio == NULL) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        *inicio = nuevo;
        printf("Valor %d insertado (primer nodo de lista circular).\n", valor);
    } else {
        struct Nodo *ultimo = (*inicio)->anterior;
        
        nuevo->siguiente = *inicio;
        nuevo->anterior = ultimo;
        
        ultimo->siguiente = nuevo;
        (*inicio)->anterior = nuevo;
        
        *inicio = nuevo;
        printf("Valor %d insertado al inicio.\n", valor);
    }
}

void insertarFinalCircular(struct Nodo **inicio, int valor) {
    struct Nodo *nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo->dato = valor;
    
    if (*inicio == NULL) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        *inicio = nuevo;
        printf("Valor %d insertado (primer nodo de lista circular).\n", valor);
    } else {
        struct Nodo *ultimo = (*inicio)->anterior;
        
        nuevo->siguiente = *inicio;
        nuevo->anterior = ultimo;
        
        ultimo->siguiente = nuevo;
        (*inicio)->anterior = nuevo;
        printf("Valor %d insertado al final.\n", valor);
    }
}

void recorrerAdelanteCircular(struct Nodo *inicio) {
    if (inicio == NULL) {
        printf("La lista circular esta vacia.\n");
        return;
    }
    
    struct Nodo *temp = inicio;
    printf("Lista circular (adelante): ");
    
    do {
        printf("%d ", temp->dato);
        temp = temp->siguiente;
    } while (temp != inicio);
    
    printf("\n");
}

void recorrerAtrasCircular(struct Nodo *inicio) {
    if (inicio == NULL) {
        printf("La lista circular esta vacia.\n");
        return;
    }
    
    struct Nodo *temp = inicio->anterior;
    printf("Lista circular (atras): ");
    
    struct Nodo *fin = temp; 
    do {
        printf("%d ", temp->dato);
        temp = temp->anterior;
    } while (temp != fin);
    
    printf("\n");
}

void eliminarCircular(struct Nodo **inicio, int valor) {
    if (*inicio == NULL) {
        printf("La lista circular esta vacia.\n");
        return;
    }
    
    struct Nodo *temp = *inicio;
    struct Nodo *aEliminar = NULL;
    
    do {
        if (temp->dato == valor) {
            aEliminar = temp;
            break;
        }
        temp = temp->siguiente;
    } while (temp != *inicio);
    
    if (aEliminar == NULL) {
        printf("ERROR: Valor %d no encontrado en la lista.\n", valor);
        return;
    }
    if (aEliminar->siguiente == aEliminar && aEliminar->anterior == aEliminar) {
        *inicio = NULL;
        free(aEliminar);
        printf("Valor %d eliminado (era el unico nodo lol).\n", valor);
        return;
    }
    if (aEliminar == *inicio) {
        *inicio = (*inicio)->siguiente;
    }
    aEliminar->anterior->siguiente = aEliminar->siguiente;
    aEliminar->siguiente->anterior = aEliminar->anterior;
    
    free(aEliminar);
    printf("Valor %d eliminado correctamente.\n", valor);
}

void liberarCircular(struct Nodo *inicio) {
    if (inicio == NULL) {
        printf("La lista circular ya esta vacia.\n");
        return;
    }
    
    struct Nodo *actual = inicio;
    struct Nodo *siguiente;
    struct Nodo *ultimo = inicio->anterior;
    ultimo->siguiente = NULL;
    
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    printf("Memoria de lista circular liberada correctamente.\n");
}

void mostrarInfoCircular(struct Nodo *inicio) {
    if (inicio == NULL) {
        printf("Lista circular: VACIA\n");
        return;
    }
    
    printf("\n--- INFORMACION DE LA LISTA CIRCULAR ---\n");
    printf("Primer nodo: %d\n", inicio->dato);
    printf("Ultimo nodo: %d\n", inicio->anterior->dato);
    printf("Primer->Siguiente: %d\n", inicio->siguiente->dato);
    printf("Primer->Anterior: %d\n", inicio->anterior->dato);

    if (inicio->anterior->siguiente == inicio && inicio->siguiente->anterior == inicio) {
        printf("? Circularidad verificada correctamente\n");
    } else {
        printf("? ERROR en circularidad\n");
    }
}

void mostrarMenuCircular() {
    printf("\n=== MENU LISTA CIRCULAR DOBLEMENTE LIGADA ===\n");
    printf("1. Insertar al inicio\n");
    printf("2. Insertar al final\n");
    printf("3. Recorrer hacia adelante\n");
    printf("4. Recorrer hacia atras\n");
    printf("5. Eliminar valor\n");
    printf("6. Mostrar informacion de la lista\n");
    printf("7. Liberar memoria y salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    int opcion, valor, cantidad, i;
    
    printf("=== IMPLEMENTACION DE LISTA DOBLEMENTE LIGADA CIRCULAR ===\n");
    printf("\n--- Insercion al final (circular) ---\n");
    printf("Cuantos valores desea insertar al final? ");
    scanf("%d", &cantidad);
    
    for (i = 0; i < cantidad; i++) {
        printf("Ingrese el valor %d: ", i + 1);
        scanf("%d", &valor);
        insertarFinalCircular(&inicio, valor);
    }
    
    recorrerAdelanteCircular(inicio);
    mostrarInfoCircular(inicio);
    printf("\n--- Insercion al inicio (circular) ---\n");
    printf("Cuantos valores desea insertar al inicio? ");
    scanf("%d", &cantidad);
    
    for (i = 0; i < cantidad; i++) {
        printf("Ingrese el valor %d: ", i + 1);
        scanf("%d", &valor);
        insertarInicioCircular(&inicio, valor);
    }
    
    recorrerAdelanteCircular(inicio);
    recorrerAtrasCircular(inicio);
    mostrarInfoCircular(inicio);
    
    do {
        mostrarMenuCircular();
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Ingrese el valor a insertar al inicio: ");
                scanf("%d", &valor);
                insertarInicioCircular(&inicio, valor);
                break;
                
            case 2:
                printf("Ingrese el valor a insertar al final: ");
                scanf("%d", &valor);
                insertarFinalCircular(&inicio, valor);
                break;
                
            case 3:
                recorrerAdelanteCircular(inicio);
                break;
                
            case 4:
                recorrerAtrasCircular(inicio);
                break;
                
            case 5:
                printf("Ingrese el valor a eliminar: ");
                scanf("%d", &valor);
                eliminarCircular(&inicio, valor);
                if (inicio != NULL) {
                    recorrerAdelanteCircular(inicio);
                }
                break;
                
            case 6:
                mostrarInfoCircular(inicio);
                break;
                
            case 7:
                liberarCircular(inicio);
                inicio = NULL;
                printf("Saliendo del programa.\n");
                break;
                
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 7);
    
    return 0;
}

//1. ¿Qué diferencia hay entre una lista doblemente ligada y una circular doblemente ligada?
//Lista normal:
//Primer nodo ? anterior = NULL
//Último nodo ? siguiente = NULL

//Lista circular:
//Primer nodo ? anterior = ÚLTIMO nodo
//Último nodo ? siguiente = PRIMER nodo
// Y forma un círculo completo

//2. ¿Qué errores pueden causar ciclos infinitos al recorrer una lista circular?
//Usar while(temp != NULL) en vez de while(temp != inicio)
//No verificar si la lista está vacía
//Punteros mal conectados al insertar/eliminar
//No romper el círculo al liberar memoria

//3. ¿Qué tipo de aplicaciones reales usan este tipo de listas?
//Listas de reproducción en bucle de música o yutub
//En los navegadores en los botones anterior y siguiente en historial
//En Juegos de selección circular de armas o personajes como en fortnite o the lasto of us 

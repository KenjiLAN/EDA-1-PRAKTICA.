#include <stdio.h>

typedef struct {
    int dato;
} Nodo;

int main() {
    Nodo nl;    // Un nodo normal
    Nodo *p;    // Un puntero a Nodo
    p = &nl;    // 'p' apunta a 'nl'

    // TODO: Completar con . o ->

    // 1) Guardar el valor 10 en 'dato' usando nl
    nl.dato = 10;

    // 2) Guardar el valor 20 en 'dato' usando p
    p->dato = 20;

    // 3) Imprimir el contenido de 'dato' con nl
    printf("%d\n", nl.dato);

    // 4) Imprimir el contenido de 'dato' con p
    printf("%d\n", p->dato);


//Solo me imprime el numero 20 ya que en el programa primero me escribe 10 pero se reemplaza con 20 en el proceso de ejecucion final si quisiera que me pusiera los datos 10 y 20 separados sin perder de vista el nl.dato y p->dato mi propuesta es:

    printf("\n=== MI PROPUESTA 10 y 20 (variables diferentes) ===\n");
    
    Nodo n2;
    p = &n2;  // Ahora p apunta a n2

    nl.dato = 10;
    p->dato = 20;
    printf("%d\n", nl.dato);  
    printf("%d\n", p->dato);

	return 0;
}

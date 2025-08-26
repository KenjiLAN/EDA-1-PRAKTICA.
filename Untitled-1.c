#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para la función sleep()
#include <time.h>   // Para la función rand()

#define WIDTH 20
#define HEIGHT 20

int x, y, fruitX, fruitY, score;
int gameOver;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;

void Setup() {
    srand(time(0)); // Inicializamos la semilla aleatoria
    gameOver = 0;   // El juego no ha terminado
    dir = STOP;     // La dirección inicial es STOP
    x = WIDTH / 2;  // Posición inicial de la cabeza de la serpiente
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH; // Posición aleatoria de la fruta
    fruitY = rand() % HEIGHT;
    score = 0;
}

void Draw() {
    // Imprimir el tablero con la serpiente y la fruta
    system("clear");  // Usa "cls" si estás en Windows. "clear" es para Linux/Mac

    for (int i=0; i<WIDTH+2;i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O");  // Cabeza de la serpiente
            else if (i == fruitY && j == fruitX)
                printf("F");  // Fruta
            else
                printf(" ");
            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    printf("Score: %d\n", score);
}

void Input() {
    // Leemos la entrada del usuario
    char input;
    printf("Mover (w/a/s/d para moverte, x para salir): ");
    scanf(" %c", &input);

    switch (input) {
    case 'a':
        dir = LEFT;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'w':
        dir = UP;
        break;
    case 's':
        dir = DOWN;
        break;
    case 'x':
        gameOver = 1; // Termina el juego si presionas 'x'
        break;
    default:
        break;
    }
}

void Logic() {
    // Movemos la serpiente según la dirección
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Reaparecemos por el otro lado si la serpiente sale del borde
    if (x >= WIDTH) x = 0; else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0; else if (y < 0) y = HEIGHT - 1;

    // Si la serpiente come la fruta
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

int main() {
    Setup(); // Configuramos el juego

    // Bucle principal del juego
    while (!gameOver) {
        Draw();  // Dibuja el tablero
        Input(); // Captura la entrada del usuario
        Logic(); // Actualiza la lógica del juego
        sleep(1);  // Pausa para que no vaya tan rápido (1 segundo)
    }

    printf("Juego terminado. Puntuación final: %d\n", score);
    return 0;
    
}

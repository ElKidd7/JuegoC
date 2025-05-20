/*Realizar un juego de ajedrez que implemente las siguientes reglas:

El tablero será de 6x6, cada jugador tendrá 8 piezas:
4 Peones (P)

1 Torre (T)

1 Alfil (A)

1 Caballo (C)

1 Dama (D)

1 Rey (R)

Formación inicial personalizada (por fila):
Fila 1 (Negras – parte superior):
P T D R A C P

Fila 2 (Peones negros):
  - - P P - -


Fila 5 (Peones blancos):
- - P P - -

Fila 6 (Blancas – parte inferior):
P T D R A C P

Movimiento de piezas básico:

Peón (P): avanza 1 casilla adelante (no retrocede ni captura en diagonal).

Torre (T): líneas rectas (vertical y horizontal).

Alfil (A): diagonales.

Caballo (C): en "L" (2+1).

Dama (D): combinación de torre y alfil.

Rey (R): una casilla en cualquier dirección.


Condiciones de victoria:

Si un jugador deja al rey enemigo en jaque al menos 2 veces GANA automáticamente.

Si un jugador captura al rey enemigo GANA.

También se puede salir manualmente del juego.

Turnos: Empiezan las blancas. Se alternan por movimiento válido.

Jaque mínimo implementado:

Después de cada movimiento, se analiza si el rey enemigo está bajo amenaza real.

No se obliga a defenderse del jaque, solo se cuenta el número.
*/


#include <stdio.h>
#include <stdlib.h>// para rand y srand
#include <time.h>// para time
#include <math.h>

#define FILAS 6
#define COLUMNAS 6

struct Piezas 
{
    char tipo;
    char color; // 'B' para blancas, 'N' para negras
};

struct Piezas tablero [FILAS][COLUMNAS];
int jaque_blancas = 0;
int jaque_negras = 0;

void iniciarTablero()
{
    int i, j;
    for (i = 0; i < FILAS; i++){
        for (j = 0; j < COLUMNAS; j++){
            tablero[i][j].tipo = ' ';
            tablero[i][j].color = ' ';
        }
    }
    /*====================Negras======================*/
    tablero[0][0].tipo = 'P'; tablero[0][0].color = 'N';
    tablero[0][1].tipo = 'T'; tablero[0][1].color = 'N';
    tablero[0][2].tipo = 'D'; tablero[0][2].color = 'N';
    tablero[0][3].tipo = 'R'; tablero[0][3].color = 'N';
    tablero[0][4].tipo = 'A'; tablero[0][4].color = 'N';
    tablero[0][5].tipo = 'C'; tablero[0][5].color = 'N';

    tablero[1][2].tipo = 'P'; tablero[1][2].color = 'N';
    tablero[1][3].tipo = 'P'; tablero[1][3].color = 'N';
    /*====================Negras======================*/


    /*====================Blancas======================*/
    tablero[5][0].tipo = 'P'; tablero[5][0].color = 'B';
    tablero[5][1].tipo = 'T'; tablero[5][1].color = 'B';
    tablero[5][2].tipo = 'D'; tablero[5][2].color = 'B';
    tablero[5][3].tipo = 'R'; tablero[5][3].color = 'B';
    tablero[5][4].tipo = 'A'; tablero[5][4].color = 'B';
    tablero[5][5].tipo = 'C'; tablero[5][5].color = 'B';

    tablero[4][2].tipo = 'P'; tablero[4][2].color = 'B';
    tablero[4][3].tipo = 'P'; tablero[4][3].color = 'B';

    /*====================Blancas======================*/
}

void imprimir_tablero() {
    printf("\033[1;37m\n  A B C D E F\n\033[0m");
    for (int i = 0; i < FILAS; i++) {
        printf("\033[1;37m%d \033[0m", i + 1);
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j].tipo == ' ') {
                printf(". ");
            } else if (tablero[i][j].color == 'B') {
                printf("\033[1;32m%c \033[0m", tablero[i][j].tipo);  // Azul para blancas
            } else {
                printf("\033[1;31m%c \033[0m", tablero[i][j].tipo);  // Rojo para negras
            }
        }
        printf("\n");
    }
}




void limiparPantalla()
{
    system("cls");
}



int main()
{
    return 0;
}
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
    char piezas;
};

struct Jugador
{
    char nombre[50];
    int piezasRestantes;
    int jaquesRealizados;
    int jaquesRecibidos;
    struct Piezas tablero[FILAS][COLUMNAS];

};




int main()
{
    return 0;
}
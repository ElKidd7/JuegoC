#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define FILAS 6
#define COLUMNAS 6

// Estructura para representar las piezas de ajedrez
struct Piezas 
{
    char tipo;
    char color; // 'B' para blancas, 'N' para negras
};

struct Piezas tablero[FILAS][COLUMNAS];
int jaque_blancas = 0;
int jaque_negras = 0;

// Inicializa el tablero con las piezas en sus posiciones iniciales
void iniciarTablero()
{
    int i, j;
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLUMNAS; j++) {
            tablero[i][j].tipo = ' ';
            tablero[i][j].color = ' ';
        }
    }

    // Piezas Negras
    tablero[0][0] = (struct Piezas){'P', 'N'};
    tablero[0][1] = (struct Piezas){'T', 'N'};
    tablero[0][2] = (struct Piezas){'D', 'N'};
    tablero[0][3] = (struct Piezas){'R', 'N'};
    tablero[0][4] = (struct Piezas){'A', 'N'};
    tablero[0][5] = (struct Piezas){'C', 'N'};
    tablero[1][2] = (struct Piezas){'P', 'N'};
    tablero[1][3] = (struct Piezas){'P', 'N'};

    // Piezas Blancas
    tablero[5][0] = (struct Piezas){'P', 'B'};
    tablero[5][1] = (struct Piezas){'T', 'B'};
    tablero[5][2] = (struct Piezas){'D', 'B'};
    tablero[5][3] = (struct Piezas){'R', 'B'};
    tablero[5][4] = (struct Piezas){'A', 'B'};
    tablero[5][5] = (struct Piezas){'C', 'B'};
    tablero[4][2] = (struct Piezas){'P', 'B'};
    tablero[4][3] = (struct Piezas){'P', 'B'};
}

// Imprime el tablero en consola con colores para distinguir piezas
void imprimir_tablero() {
    printf("\033[1;37m\n  A B C D E F\n\033[0m");
    for (int i = 0; i < FILAS; i++) {
        printf("\033[1;37m%d \033[0m", i + 1);
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j].tipo == ' ') {
                printf(". ");
            } else if (tablero[i][j].color == 'B') {
                printf("\033[1;32m%c \033[0m", tablero[i][j].tipo); // Verde: blancas
            } else {
                printf("\033[1;31m%c \033[0m", tablero[i][j].tipo); // Rojo: negras
            }
        }
        printf("\n");
    }
}

// Valida que una posición esté dentro del tablero
int validarPosicion(int filas, int columnas)
{
    return filas >= 0 && filas < FILAS && columnas >= 0 && columnas < COLUMNAS;
}

// Valida el movimiento según el tipo de pieza (reglas básicas)
int movimientoValido(int fi, int ci, int ff, int cf)
{
    char tipo = tablero[fi][ci].tipo;
    char color = tablero[fi][ci].color;
    int dFila = ff - fi;
    int dCol = cf - ci;
    int absFila = abs(dFila), absCol = abs(dCol);

    switch (tipo) {
        case 'P': // Peón
            if (color == 'B') return (dFila == -1 && (dCol == 0 || absCol == 1));
            else return (dFila == 1 && (dCol == 0 || absCol == 1));
        case 'T': // Torre
            return (fi == ff || ci == cf);
        case 'A': // Alfil
            return (absFila == absCol);
        case 'D': // Reina
            return (fi == ff || ci == cf || absFila == absCol);
        case 'C': // Caballo
            return (absFila == 2 && absCol == 1) || (absFila == 1 && absCol == 2);
        case 'R': // Rey
            return (absFila <= 1 && absCol <= 1);
        default:
            return 0;
    }
}

// Detecta si el rey contrario está en jaque por alguna pieza del color dado
int jaqueRey(char color)
{
    int filaRey = -1, columnaRey = -1;

    // Buscar el rey enemigo
    for (int i = 0 ; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j].tipo == 'R' && tablero[i][j].color != color) {
                filaRey = i;
                columnaRey = j;
                break;
            }
        }
    }

    if (filaRey == -1) return 0;

    // Verificar si alguna pieza del color actual puede atacarlo
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j].color == color) {
                if (movimientoValido(i, j, filaRey, columnaRey)) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

// Mueve la pieza si la jugada es válida
void moverPieza(int fi, int ci, int ff, int cf, char turno)
{
    if (!validarPosicion(fi, ci) || !validarPosicion(ff, cf)) {
        printf("Movimiento fuera de rango\n");
        return;
    }

    if (tablero[fi][ci].color != turno) {
        printf("No es tu turno\n");
        return;
    }

    if (!movimientoValido(fi, ci, ff, cf)) {
        printf("Movimiento inválido para la pieza\n");
        return;
    }

    // Impedir capturar tus propias piezas
    if (tablero[ff][cf].color == turno) {
        printf("No puedes capturar tu propia pieza\n");
        return;
    }

    // Realiza el movimiento
    tablero[ff][cf] = tablero[fi][ci];
    tablero[fi][ci] = (struct Piezas){' ', ' '};

    // Comprobar si el movimiento provocó un jaque
    if (jaqueRey(turno)) {
        if (turno == 'B') jaque_blancas++;
        else jaque_negras++;
        printf("\033[1;33mHas puesto al rey enemigo en jaque!\033[0m\n");
    }
}

// Convierte letra de columna (ej. 'A') a índice de matriz
int convertirColumna(char columna)
{
    if (columna >= 'A' && columna <= 'F') return columna - 'A';
    if (columna >= 'a' && columna <= 'f') return columna - 'a';
    return -1;
}

// Lógica principal de juego (turnos, entrada, finalización)
void partida()
{
    char turno = 'B';
    char entrada[10];
    int colInicial, filaInicial, colFinal, filaFinal;

    while (1) {
        imprimir_tablero();

        // Condiciones de victoria
        if (jaque_blancas >= 2) {
            printf("\033[1;32mBlancas ganan por jaque x2\033[0m\n");
            break;
        } else if (jaque_negras >= 2) {
            printf("\033[1;31mNegras ganan por jaque x2\033[0m\n");
            break;
        }

        // Selección de pieza
        do {
            printf("Turno de %s. Elige pieza a mover (ej. A2, q para salir): ", turno == 'B' ? "Blancas (Verde)" : "Negras (Rojo)");
            fgets(entrada, sizeof entrada, stdin);
            if (entrada[0] == 'q') return;

            colInicial = convertirColumna(entrada[0]);
            filaInicial = entrada[1] - '1';

            if (!validarPosicion(filaInicial, colInicial) ||
                tablero[filaInicial][colInicial].tipo == ' ' ||
                tablero[filaInicial][colInicial].color != turno) {
                printf("Origen inválido. Intenta de nuevo.\n");
                continue;
            }
            break;
        } while (1);

        // Selección de destino
        do {
            printf("\nPeon: Movimiento hacia adelante o diagonal(1 casilla)\n");
            printf("\nAlfil: Movimiento diagonal\n");
            printf("\nTorre: Movimiento horizontal o vertical\n");
            printf("\nCaballo: Movimiento en L\n");
            printf("\nRey: Movimiento en cualquier dirección (1 casilla)\n");
            printf("\nReina: Movimiento en cualquier dirección (combinacion torre y alfil)\n");
            printf("\nDestino para %c%d (ej. B3): ", entrada[0], filaInicial + 1);
            fgets(entrada, sizeof entrada, stdin);
            colFinal = convertirColumna(entrada[0]);
            filaFinal = entrada[1] - '1';

            if (!validarPosicion(filaFinal, colFinal)) {
                printf("Destino fuera de rango. Intenta otra vez.\n");
                continue;
            }
            if (filaFinal == filaInicial && colFinal == colInicial) {
                printf("No puedes mover a la misma casilla.\n");
                continue;
            }
            break;
        } while (1);

        moverPieza(filaInicial, colInicial, filaFinal, colFinal, turno);
        turno = (turno == 'B') ? 'N' : 'B';
    }
}

// Limpia la pantalla en sistemas Windows
void limiparPantalla()
{
    system("cls");
}

// Función principal del programa
int main()
{
    iniciarTablero();
    partida();
    imprimir_tablero();
    limiparPantalla();
    return 0;
}

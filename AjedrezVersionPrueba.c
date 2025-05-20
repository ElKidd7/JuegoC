#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define FILAS 6
#define COLUMNAS 6

struct Pieza {
    char tipo;   // P, T, D, R, A, C
    char color;  // 'B' (blancas), 'N' (negras)
};

struct Pieza tablero[FILAS][COLUMNAS];
int jaques_blancas = 0;
int jaques_negras = 0;

void inicializar_tablero() {
    int i, j;
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLUMNAS; j++) {
            tablero[i][j].tipo = ' ';
            tablero[i][j].color = ' ';
        }
    }

    // Negras
    tablero[0][0].tipo = 'P'; tablero[0][0].color = 'N';
    tablero[0][1].tipo = 'T'; tablero[0][1].color = 'N';
    tablero[0][2].tipo = 'D'; tablero[0][2].color = 'N';
    tablero[0][3].tipo = 'R'; tablero[0][3].color = 'N';
    tablero[0][4].tipo = 'A'; tablero[0][4].color = 'N';
    tablero[0][5].tipo = 'C'; tablero[0][5].color = 'N';

    tablero[1][2].tipo = 'P'; tablero[1][2].color = 'N';
    tablero[1][3].tipo = 'P'; tablero[1][3].color = 'N';

    // Blancas
    tablero[5][0].tipo = 'P'; tablero[5][0].color = 'B';
    tablero[5][1].tipo = 'T'; tablero[5][1].color = 'B';
    tablero[5][2].tipo = 'D'; tablero[5][2].color = 'B';
    tablero[5][3].tipo = 'R'; tablero[5][3].color = 'B';
    tablero[5][4].tipo = 'A'; tablero[5][4].color = 'B';
    tablero[5][5].tipo = 'C'; tablero[5][5].color = 'B';

    tablero[4][2].tipo = 'P'; tablero[4][2].color = 'B';
    tablero[4][3].tipo = 'P'; tablero[4][3].color = 'B';
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

int es_valida(int fila, int col) {
    return fila >= 0 && fila < FILAS && col >= 0 && col < COLUMNAS;
}

int rey_en_jaque(char color) {
    int rey_fila = -1, rey_col = -1;

    // Buscar al rey del color contrario
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j].tipo == 'R' && tablero[i][j].color != color) {
                rey_fila = i;
                rey_col = j;
                break;
            }
        }
    }

    if (rey_fila == -1) return 0;  // Rey no está en el tablero

    // Revisar si alguna pieza amenaza al rey
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j].color == color) {
                // Simula movimiento para ver si puede atacar al rey
                int dx = abs(i - rey_fila);
                int dy = abs(j - rey_col);
                char tipo = tablero[i][j].tipo;
                if ((tipo == 'D' && (dx == dy || i == rey_fila || j == rey_col)) ||
                    (tipo == 'A' && dx == dy) ||
                    (tipo == 'T' && (i == rey_fila || j == rey_col)) ||
                    (tipo == 'C' && ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) ||
                    (tipo == 'P' && color == 'B' && rey_fila == i - 1 && rey_col == j) ||
                    (tipo == 'P' && color == 'N' && rey_fila == i + 1 && rey_col == j)) {
                        return 1;
                }
            }
        }
    }
    return 0;
}

void mover_pieza(int f1, int c1, int f2, int c2, char turno) {
    if (!es_valida(f1, c1) || !es_valida(f2, c2)) {
        printf("Movimiento fuera de rango.\n");
        return;
    }
    if (tablero[f1][c1].color != turno) {
        printf("No puedes mover una pieza enemiga.\n");
        return;
    }

    // Mover la pieza
    tablero[f2][c2] = tablero[f1][c1];
    tablero[f1][c1].tipo = ' ';
    tablero[f1][c1].color = ' ';

    // Comprobar jaque
    if (rey_en_jaque(turno)) {
        if (turno == 'B') jaques_blancas++;
        else jaques_negras++;
        printf("\033[1;33mHas puesto al rey enemigo en jaque!\033[0m\n");
    }
}

int convertir_columna(char c) {
    if (c >= 'A' && c <= 'F') return c - 'A';
    if (c >= 'a' && c <= 'f') return c - 'a';
    return -1;
}

void jugar() {
    char turno = 'B';
    char entrada[10];
    while (1) {
        imprimir_tablero();
        if (jaques_blancas >= 2) {
            printf("\033[1;32m\nBlancas ganan por jaque x2!\033[0m\n");
            break;
        }
        if (jaques_negras >= 2) {
            printf("\033[1;32m\nNegras ganan por jaque x2!\033[0m\n");
            break;
        }

        printf("Turno de %s. Ingresa movimiento (ej. A2 A3): ", turno == 'B' ? "Blancas" : "Negras");
        fgets(entrada, sizeof(entrada), stdin);

        if (entrada[0] == 'q') break;

        int col1 = convertir_columna(entrada[0]);
        int fil1 = entrada[1] - '1';
        int col2 = convertir_columna(entrada[3]);
        int fil2 = entrada[4] - '1';

        mover_pieza(fil1, col1, fil2, col2, turno);
        turno = (turno == 'B') ? 'N' : 'B';
    }
}

int main() {
    inicializar_tablero();
    jugar();
    return 0;
}

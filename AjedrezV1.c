

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
                printf("\033[1;32m%c \033[0m", tablero[i][j].tipo);  // Verde para blancas
            } else {
                printf("\033[1;31m%c \033[0m", tablero[i][j].tipo);  // Rojo para negras
            }
        }
        printf("\n");
    }
}

int validarPosicion (int filas, int columnas)
{
    return filas >= 0 && filas < FILAS && columnas >= 0 && columnas < COLUMNAS;
}

int jaqueRey (int color)
{
    int filaRey = -1, columnaRey = -1;

    //Buscar color del rey contrario
    for (int i = 0 ; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            if (tablero[i][j].tipo == 'R' && tablero[i][j].color != color)
            {
                filaRey = i;
                columnaRey = j;
                break;
            }
        }
    }
    if (filaRey == -1 || columnaRey == -1) //El rey ya no está en el tablero
    {
        return 0;
    }
    //Revisar si alguna pieza amenaza al rey
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            if (tablero[i][j].color == color)
            {
                //Simular movimiento para ver si el rey se encuentra en jaque
                for (int i = 0; i < FILAS; i++) {
                    for (int j = 0; j < COLUMNAS; j++) {
                        if (tablero[i][j].color == color) {
            // Calculamos las diferencias de fila y columna entre esta pieza y el rey
                        int dx = abs(i - filaRey);
                        int dy = abs(j - columnaRey);
            // Tomamos el tipo de pieza ('D', 'A', 'T', 'C' o 'P')
                        char tipo = tablero[i][j].tipo;

            // Comprobamos, según el tipo de pieza, si puede atacar la posición del rey
                        if ((tipo == 'D' && (dx == dy || i == filaRey || j == columnaRey)) ||
                            (tipo == 'A' && dx == dy) ||
                            (tipo == 'T' && (i == filaRey || j == columnaRey)) ||
                            (tipo == 'C' && ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) ||
                            (tipo == 'P' && color == 'B' && filaRey == i - 1 && columnaRey == j) ||
                            (tipo == 'P' && color == 'N' && filaRey == i + 1 && columnaRey == j))
                {
                return 1;
                }
            }
        }
    }
// Si ninguna pieza amenazó al rey, devolvemos 0
    return 0;

            }
        }
    }
}

void moverPieza(int filaInicial, int columnaInicial, int filaFinal, int columnaFinal, char turno)
{
    if (!validarPosicion (filaInicial, columnaInicial) || !validarPosicion (filaFinal, columnaFinal))
    {
           printf("Movimiento fuera de rango\n");
           return; 
    }

    if (tablero[filaInicial][columnaInicial].color != turno)
    {
        printf("No es tu turno\n");
        return;
    }

    // Mover la pieza
    tablero[filaFinal][columnaFinal] = tablero[filaInicial][columnaInicial];

    // Limpiar la casilla origen, no la destino
    tablero[filaInicial][columnaInicial].tipo  = ' ';
    tablero[filaInicial][columnaInicial].color = ' ';



    //Comprobar jaque

    if (jaqueRey(turno))
    {
        if (turno == 'B') jaque_blancas++;
        else jaque_negras++;
        printf("\033[1;33mHas puesto al rey enemigo en jaque!\033[0m\n");
    }  
}

int convertirColumna (char columna)
{
    if (columna >= 'A' && columna <= 'F')
    {
        return columna - 'A';
    }
    if (columna >= 'a' && columna <= 'f')
    {
        return columna - 'a';
    }
return -1;
}


void partida()
{
    char turno = 'B';
    char entrada [10];
    int colInicial, flaInicial, colFinal, flaFinal;

    while (1)
    {
        imprimir_tablero();
        if (jaque_blancas >= 2)
        {
            printf("\033[1;32mBlancas ganan por jaque x2\033[0m\n");
            break;
        } else if (jaque_negras >= 2)
        {
            printf("\033[1;31mNegras ganan por jaque x2\033[0m\n");
            break;
        }

         do {
            printf("Turno de %s. Elige pieza a mover (ej. A2, q para salir): ", turno == 'B' ? "Blancas (Verde)" : "Negras(Rojas)");
            fgets(entrada, sizeof entrada, stdin);
            if (entrada[0] == 'q') return;

            colInicial = convertirColumna(entrada[0]);
            flaInicial = entrada[1] - '1';
            // validamos rango, que haya pieza y que sea de tu color
            if (!validarPosicion(flaInicial, colInicial) ||
                tablero[flaInicial][colInicial].tipo == ' ' ||
                tablero[flaInicial][colInicial].color != turno)
            {
                printf("Origen inválido. Intenta de nuevo.\n");
                continue;
            }
            break;
        } while (1);

        // 2) Leemos y validamos destino
        do {
            printf("\nPeon: Movimiento hacia adelante o diagonal(1 casilla)\n");
            printf("\nAlfil: Movimiento diagonal\n");
            printf("\nTorre: Movimiento horizontal o vertical\n");
            printf("\nCaballo: Movimiento en L\n");
            printf("\nRey: Movimiento en cualquier dirección (1 casilla)\n");
            printf("\nReina: Movimiento en cualquier dirección (combinacion torre y alfil)\n");
            printf("Destino para %c%d (ej. A3): \n", entrada[0], flaInicial+1);
            fgets(entrada, sizeof entrada, stdin);
            colFinal = convertirColumna(entrada[0]);
            flaFinal = entrada[1] - '1';

            if (!validarPosicion(flaFinal, colFinal)) {
                printf("Fuera de rango. Intenta otra vez.\n");
                continue;
            }
            if (flaFinal == flaInicial && colFinal == colInicial) {
                printf("No puedes mover a la misma casilla. Elige otro destino.\n");
                continue;
            }
            // aquí podrías añadir más validaciones: jaque, colisión, reglas por pieza...
            break;
        } while (1);

        // 3) Ejecutamos el movimiento
        moverPieza(flaInicial, colInicial, flaFinal, colFinal, turno);
        turno = (turno == 'B') ? 'N' : 'B';
    }
}
    
void limiparPantalla()
{
    system("cls");
}



int main()
{
    iniciarTablero();
    partida();
    imprimir_tablero();
    limiparPantalla();
    return 0;
}
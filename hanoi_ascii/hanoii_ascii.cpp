#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void imprimimPiramides(int *tab, int fil, int col, int ultNum)
{
    int esp;
    char bloque = 219;
    for (int i = 0; i < col * 8; i++)
    {
        cout << "_";
    }
    cout << "\n"
         << endl;
    for (int i = col - 1; i >= 0; i--)
    {
        for (int j = 0; j < fil; j++)
        {
            esp = (ultNum - tab[col * j + i]) / 2;
            // Espacios a la izquierda
            for (int k = 0; k < esp; k++)
                cout << " ";

            // Imprime los bloques
            for (int l = 0; l < tab[col * j + i]; l++)
                cout << bloque;

            // Espacios a la derecha
            for (int m = 0; m < esp; m++)
                cout << " ";

            cout << "\t";
        }
        cout << "|";
        cout << "\n";
    }
    for (int i = 0; i < col * 8; i++)
    {
        cout << "_";
    }
    cout << "\n"
         << endl;
}

void moverDiscosDePiramides(int *tab, int fil, int col, int ultNum, int agujaOrigen, int agujaDestino)
{
    int _origen = col - 1, _destino = col - 1;

    // Se busca el disco que se encuentre mas arriba y por lo tanto el mas pequeño de la fila de origen.
    while (_origen >= 0 && tab[col * agujaOrigen + _origen] == 0)
    {
        _origen--;
    };
    if (_origen < 0)
        _origen = 0;

    // Ahora se calcula cual es la posición libre mas arriba de la fila de destino
    while (_destino >= 0 && tab[col * agujaDestino + _destino] == 0)
    {
        _destino--;
    }

    // Se mueve el disco de la fila de origen a la de destino:
    tab[col * agujaDestino + _destino + 1] = tab[col * agujaOrigen + _origen];
    tab[col * agujaOrigen + _origen] = 0;

    // Se imprime el tablero:
    imprimimPiramides(tab, fil, col, ultNum);
}

void hanoi(int *tab, int fil, int col, int disc, int ultNum, int origen, int auxiliar, int destino)
{
    if (disc == 1)
    {
        cout << "\n";
        moverDiscosDePiramides(tab, fil, col, ultNum, origen, destino);
    }
    else
    {
        hanoi(tab, fil, col, disc - 1, ultNum, origen, destino, auxiliar);

        cout << "\n";
        moverDiscosDePiramides(tab, fil, col, ultNum, origen, destino);

        hanoi(tab, fil, col, disc - 1, ultNum, auxiliar, origen, destino);
    }
}

int main()
{
    int fil = 3, col, *tablero = NULL;
    int f, c, disc = 1, ultNum;

    cout << "Numero discos: ";
    cin >> col;

    tablero = (int *)malloc(sizeof(int) * fil * col);
    for (f = 0; f < fil; f++)
        for (c = col - 1; c >= 0; c--)
            if (f == 0)
            {
                tablero[col * f + c] = disc;
                disc += 2;
            }
            else
                tablero[col * f + c] = 0;

    ultNum = disc;

    cout << "\n";
    imprimimPiramides(tablero, fil, col, ultNum);
    cout << "\n";

    hanoi(tablero, fil, col, col, ultNum, 0, 1, 2);
    return 0;
}
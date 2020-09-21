#include <iostream>
#include <string>
#include <curses.h>
#include <vector>
using namespace std;

void hanoi(vector<WINDOW *>, vector<WINDOW *>, vector<WINDOW *>, int, int, int);

int main(int argc, char *argv[])
{
    bool fin = true;
    int contadorTurnos = 0;
    int discos = stoi(argv[1]);
    int MaxX, MaxY;
    //vector<WINDOW *> _discos;
    vector<WINDOW *> aguja1;
    vector<WINDOW *> aguja2;
    vector<WINDOW *> aguja3;
    WINDOW **tablero = NULL;
    initscr();
    getmaxyx(stdscr, MaxY, MaxX);
    if (!has_colors())
    {
        endwin();
        return 1;
    }
    WINDOW *ventana = newwin(MaxY, MaxX, 0, 0);
    refresh();
    cbreak();
    noecho();
    nonl();
    intrflush(ventana, FALSE);
    keypad(ventana, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_YELLOW);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
    init_pair(5, COLOR_WHITE, COLOR_CYAN);
    init_pair(6, COLOR_WHITE, COLOR_GREEN);
    init_pair(7, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(8, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));
    wrefresh(ventana);
    while (fin)
    {
        if (getch() == 27)
        {
            fin = false;
        }
        else
        {
            if (contadorTurnos == 0)
            {
                box(ventana, ACS_VLINE, ACS_HLINE);
                mvwprintw(ventana, 0, (MaxX / 2) - 16, " T O R R E S   D E   H A N O I ");
                mvwprintw(ventana, MaxY - 1, (MaxX / 2) - 15, " P R O G R A M A C I O N   I I I ");
                WINDOW *encabezado = subwin(ventana, 1, ((MaxX / 4) * 2) + 6, 3, (MaxX / 4) - 3);
                wbkgd(encabezado, COLOR_PAIR(2));
                mvwprintw(encabezado, 0, ((encabezado->_maxx) / 2) - 18, " MUESTRA DE MOVIMIENTOS PASO A PASO ");
                mvwprintw(ventana, 4, (MaxX / 2) - 8, "MOVIMIENTO # 000");
                WINDOW *baseTablero = subwin(ventana, 1, (MaxX / 3) * 2, ((MaxY / 3) * 2), MaxX / 6);
                wbkgd(baseTablero, COLOR_PAIR(2));
                mvwprintw(baseTablero, 0, (baseTablero->_maxx / 2) - (MaxX / 4), "1");
                mvwprintw(baseTablero, 0, (baseTablero->_maxx / 2), "2");
                mvwprintw(baseTablero, 0, (baseTablero->_maxx / 2) + (MaxX / 4), "3");
                WINDOW *_1aguja = subwin(ventana, (MaxY / 3), 1, (MaxY / 3), (MaxX / 4));
                WINDOW *_2aguja = subwin(ventana, (MaxY / 3), 1, (MaxY / 3), (MaxX / 2));
                WINDOW *_3aguja = subwin(ventana, (MaxY / 3), 1, (MaxY / 3), 3 * (MaxX / 4));
                wbkgd(_1aguja, COLOR_PAIR(2));
                wbkgd(_2aguja, COLOR_PAIR(2));
                wbkgd(_3aguja, COLOR_PAIR(2));
                int auxParaUbicarDiscos = discos;
                tablero = (WINDOW *)malloc(sizeof(WINDOW *) * 3 * discos);
                for (int i = 0; i < discos; i++)
                {
                    for (int j = discos - 1; j >= 0; j++)
                    {
                        if (i == 0)
                        {
                            WINDOW *aux;
                            tablero[j] = aux;
                        }
                        else
                        {
                            tablero[discos * i + j] = NULL;
                        }
                    }
                }

                for (int i = 0; i < discos; i++)
                {
                    WINDOW *aux;
                    aguja1.push_back(aux);
                }
                try
                {
                    for (int i = 0; i < discos; i++)
                    {
                        aguja1.at(i) = subwin(ventana, 1, (i * 2) + 3, (2 * (MaxY / 3)) - (auxParaUbicarDiscos), (MaxX / 4) - (i + 1));
                        if (i > 5)
                        {
                            wbkgd(aguja1.at(i), COLOR_PAIR((i - 6) + 3));
                        }
                        else
                        {
                            wbkgd(aguja1.at(i), COLOR_PAIR(i + 3));
                        }
                        auxParaUbicarDiscos--;
                    }
                }
                catch (exception &e)
                {
                    cout << "la regaste bro";
                }
                WINDOW *instrucciones = subwin(ventana, 1, (MaxX / 3) * 2, MaxY - 5, MaxX / 6);
                wbkgd(instrucciones, COLOR_PAIR(2));
                mvwprintw(instrucciones, 0, (instrucciones->_maxx / 2) - 31, " Presione cualquier tecla para continuar o ESC para finalizar ");
                mvwprintw(ventana, MaxY - 4, (MaxX / 2) - 20, "Desarrollado por Andres Nuila (11811045)");
                wrefresh(encabezado);
                wrefresh(ventana);
                contadorTurnos++;
            }
            else
            {
                hanoi(aguja1, aguja2, aguja3, discos, MaxX, MaxY);
            }
        }
    }
    endwin();
    return 0;
}
void hanoi(vector<WINDOW *> origen, vector<WINDOW *> auxiliar, vector<WINDOW *> destino, int discosTotales, int MaxX, int MaxY)
{
    if (discosTotales == 1)
    {
        destino.push_back(origen.at(0));
        origen.pop_back();
        cout << "aber";
    }
    else
    {
        hanoi(origen, destino, auxiliar, discosTotales - 1, MaxX, MaxY);
        destino.push_back(origen.back());
        origen.pop_back();
        cout << "aber";
        hanoi(auxiliar, origen, destino, discosTotales - 1, MaxX, MaxY);
    }
}

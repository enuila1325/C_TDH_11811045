#include <iostream>
#include <string>
#include <cstring>
#include <curses.h>
#include <vector>
using namespace std;

void hanoi(vector<WINDOW *>, vector<WINDOW *>, vector<WINDOW *>, vector<WINDOW *>, int, WINDOW *, int);
vector<WINDOW *> moverDiscos(vector<WINDOW *>, vector<WINDOW *>, vector<WINDOW *>, vector<WINDOW *>, int, WINDOW *);
void imprimirDiscos(WINDOW *, vector<WINDOW *>, vector<WINDOW *>, vector<WINDOW *>, vector<WINDOW *>);

int main(int argc, char *argv[])
{
    bool fin = true;
    int contadorTurnos = 0;
    int discos = stoi(argv[1]);
    int MaxX, MaxY;
    vector<WINDOW *> _discos;
    vector<WINDOW *> aguja1;
    vector<WINDOW *> aguja2;
    vector<WINDOW *> aguja3;
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

    wrefresh(ventana);

    WINDOW *instrucciones = subwin(ventana, 1, (MaxX / 3) * 2, MaxY - 5, MaxX / 6);
    wbkgd(instrucciones, COLOR_PAIR(2));
    mvwprintw(instrucciones, 0, (instrucciones->_maxx / 2) - 31, " Presione cualquier tecla para continuar o ESC para finalizar ");
    mvwprintw(ventana, MaxY - 4, (MaxX / 2) - 20, "Desarrollado por Andres Nuila (11811045)");
    wrefresh(instrucciones);
    wrefresh(encabezado);
    wrefresh(ventana);

    wrefresh(ventana);
    wrefresh(_1aguja);
    wrefresh(_2aguja);
    wrefresh(_3aguja);
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

                int auxParaUbicarDiscos = discos;

                for (int i = 0; i < discos; i++)
                {
                    WINDOW *aux = subwin(ventana, 1, (i * 2) + 3, (2 * (MaxY / 3)) - (auxParaUbicarDiscos), (MaxX / 4) - (i + 1));
                    auxParaUbicarDiscos--;
                    _discos.push_back(aux);
                }
                try
                {
                    for (int i = 0; i < discos; i++)
                    {
                        if (i > 5)
                        {
                            wbkgd(_discos.at(i), COLOR_PAIR((i - 6) + 3));
                        }
                        else
                        {
                            wbkgd(_discos.at(i), COLOR_PAIR(i + 3));
                        }
                        wrefresh(_discos.at(i));
                    }
                    wrefresh(ventana);
                    wrefresh(_1aguja);
                    wrefresh(_2aguja);
                    wrefresh(_3aguja);
                }
                catch (exception &e)
                {
                    cout << "la regaste bro";
                }
                wrefresh(ventana);
                contadorTurnos++;
            }
            else
            {
                hanoi(_discos, aguja1, aguja2, aguja3, discos, ventana, discos);
                char aux[100];
                string headerMovs = "MOVIMIENTO #";

                if (contadorTurnos >= 10)
                {
                    headerMovs += " 0" + to_string(contadorTurnos);
                    const string &cabecera = headerMovs;
                    int longitud = cabecera.size();
                    longitud = (longitud < 100 ? longitud : 100 - 1);
                    cabecera.copy(aux, longitud);
                    aux[longitud] = '\0';
                    mvwprintw(ventana, 4, (MaxX / 2) - 8, aux);
                    wrefresh(ventana);
                }
                else if (contadorTurnos >= 100)
                {
                    headerMovs += to_string(contadorTurnos);
                    const string &cabecera = headerMovs;
                    int longitud = cabecera.size();
                    longitud = (longitud < 100 ? longitud : 100 - 1);
                    cabecera.copy(aux, longitud);
                    aux[longitud] = '\0';
                    mvwprintw(ventana, 4, (MaxX / 2) - 8, aux);
                    wrefresh(ventana);
                }
                else
                {
                    headerMovs += " 00" + to_string(contadorTurnos);
                    const string &cabecera = headerMovs;
                    int longitud = cabecera.size();
                    longitud = (longitud < 100 ? longitud : 100 - 1);
                    cabecera.copy(aux, longitud);
                    aux[longitud] = '\0';
                    mvwprintw(ventana, 4, (MaxX / 2) - 8, aux);
                    wrefresh(ventana);
                }
                wrefresh(ventana);
                cout << aguja3.size();
                for (int i = 0; i < _discos.size(); i++)
                {
                    werase(_discos.at(i));
                    //delwin(_discos.at(i));
                    wrefresh(_discos.at(i));
                }
            }
        }
    }
    endwin();
    return 0;
}
void imprimirDiscos(WINDOW *principal, vector<WINDOW *> origen, vector<WINDOW *> auxiliar, vector<WINDOW *> destino, vector<WINDOW *> conjunto)
{
    for (size_t i = 0; i < origen.size(); i++)
    {
        //cout << "discos del 1 ->" << origen.at(i)->_maxx << endl;
        mvwin(origen.at(i), origen.at(i)->_begy, (principal->_maxx / 4) - (origen.at(i)->_maxx / 2));
        wrefresh(destino.at(i));
        wrefresh(principal);
        werase(conjunto.at(i));
        //delwin(conjunto.at(i));
        wrefresh(conjunto.at(i));
        wrefresh(principal);
    }
    //cout << "siguiente disco" << endl;
    //cout << endl;
    for (size_t i = 0; i < auxiliar.size(); i++)
    {
        //cout << "discos del 2 ->" << auxiliar.at(i)->_maxx << endl;
        mvwin(auxiliar.at(i), auxiliar.at(i)->_begy, (principal->_maxx / 2) - (origen.at(i)->_maxx / 2));
        wrefresh(destino.at(i));
        wrefresh(principal);
        werase(conjunto.at(i));
        //delwin(conjunto.at(i));
        wrefresh(conjunto.at(i));
        wrefresh(principal);
    }
    //cout << "siguiente disco" << endl;
    //cout << endl;
    for (size_t i = 0; i < destino.size(); i++)
    {
        //cout << "discos del 3 ->" << destino.at(i)->_maxx << endl;
        mvwin(destino.at(i), destino.at(i)->_begy, 3 * (principal->_maxx / 4) - (destino.at(i)->_maxx / 2));
        wrefresh(destino.at(i));
        wrefresh(principal);
        werase(conjunto.at(i));
        //delwin(conjunto.at(i));
        wrefresh(conjunto.at(i));
        wrefresh(principal);
    }
    cout << "Una movida realizada" << endl;
}
vector<WINDOW *> moverDiscos(vector<WINDOW *> conjuntoDiscos, vector<WINDOW *> origen, vector<WINDOW *> auxiliar, vector<WINDOW *> agujaDestino, int discoAMover, WINDOW *principal)
{
    //cout << agujaDestino.size() << "--";
    int pos = discoAMover - 1;
    if (pos < 0)
    {
        pos = 0;
    }
    WINDOW *aux = conjuntoDiscos.at(pos);
    agujaDestino.push_back(aux);
    imprimirDiscos(principal, origen, auxiliar, agujaDestino, conjuntoDiscos);

    return agujaDestino;
}
void hanoi(vector<WINDOW *> conjuntoDeDiscos, vector<WINDOW *> origen, vector<WINDOW *> auxiliar, vector<WINDOW *> destino, int discosTotales, WINDOW *principal, int controlador)
{
    while (getch() != 27)
    {
        if (discosTotales == 1)
        {
            destino = moverDiscos(conjuntoDeDiscos, origen, auxiliar, destino, discosTotales, principal);
            imprimirDiscos(principal, origen, auxiliar, destino, conjuntoDeDiscos);
            //tipo = 1;
        }
        else
        {
            hanoi(conjuntoDeDiscos, origen, destino, auxiliar, discosTotales - 1, principal, controlador);
            destino = moverDiscos(conjuntoDeDiscos, origen, auxiliar, destino, discosTotales, principal);
            imprimirDiscos(principal, origen, auxiliar, destino, conjuntoDeDiscos);
            hanoi(conjuntoDeDiscos, auxiliar, origen, destino, discosTotales - 1, principal, controlador);
        }
    }
}

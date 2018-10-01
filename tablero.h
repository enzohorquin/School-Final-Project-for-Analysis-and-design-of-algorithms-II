#ifndef TABLERO_H
#define TABLERO_H
#include <set>
#include <QPair>
#include "ficha.h"

using namespace std;

class Tablero
{
public:
    Tablero();
    void setFicha(int fila, int columna, Ficha token);
    Ficha getFicha(int fila, int columna);
    bool hayFicha(int fila, int columna);
    QList<QPair<int,int> > getPosicionesFichasAGirar(int fila, int col, QChar colorJugador);
    set<QPair<int,int> > getMovimientosPosibles(QChar colorJugador);
    void clear();

private:
    void Prueba(QList<QList<QPair<int, int> > >  fichasACambiar, QChar turno);
    Ficha board[8][8];
    set<QPair<int,int> > conjuntoCasillasVacias;
    bool esPosible(int fila, int col, QChar colorJugador);
    bool existeMovimiento(int fila, int col, QChar colorCorte, char direccionMovimiento, QList<QPair<int, int> >  &fichasACambiar);
    QList<char> devuelveDireccionesPosibles(int fila, int col, QChar colorContrario);

};

#endif // TABLERO_H

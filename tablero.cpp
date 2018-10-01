#include "tablero.h"
#include <QDebug>

Tablero::Tablero()
{
    Ficha ficha('t');
    QPair<int,int> pos;
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++)
        {
            if (((i==3) && (j==3)) || ((i==4) && (j==4)))
                ficha.setColor('b');
            else if (((i==3) && (j==4)) || ((i==4) && (j==3)))
                ficha.setColor('n');
            else
            {
                ficha.setColor('t');
                pos.first =i;
                pos.second =j;
                conjuntoCasillasVacias.insert(pos);
            }
            board[i][j]= ficha;
        }
}

void Tablero::setFicha(int fila, int columna, Ficha token)
{
    board[fila][columna] = token;
    QPair<int,int> posicionFicha(fila, columna);
    if (token.getColor() != 't')
        conjuntoCasillasVacias.erase(posicionFicha);
    else
        conjuntoCasillasVacias.insert(posicionFicha);
}

Ficha Tablero::getFicha(int fila, int columna)
{
    return board[fila][columna];
}

bool Tablero::hayFicha(int fila, int columna)
{
    if ((board[fila][columna].getColor() == 'b') || (board[fila][columna].getColor() == 'n'))
        return 1;
    else
        return 0;
}

set<QPair<int, int> > Tablero::getMovimientosPosibles(QChar colorJugador)
{
    set<QPair<int,int> > movimientosPosibles;
    set<QPair<int,int> >::const_iterator it = conjuntoCasillasVacias.begin();
    while (it != conjuntoCasillasVacias.end())
    {
        if (esPosible(it->first, it->second, colorJugador))
            movimientosPosibles.insert(*it);
        it++;
    }

    return movimientosPosibles;
}

void Tablero::clear()
{
    conjuntoCasillasVacias.clear();
    Ficha ficha('t');
    QPair<int,int> pos;
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++)
        {
            if (((i==3) && (j==3)) || ((i==4) && (j==4)))
                ficha.setColor('b');
            else if (((i==3) && (j==4)) || ((i==4) && (j==3)))
                ficha.setColor('n');
            else
            {
                ficha.setColor('t');
                pos.first =i;
                pos.second =j;
                conjuntoCasillasVacias.insert(pos);
            }
            board[i][j]= ficha;
        }
}

bool Tablero::esPosible(int fila, int col, QChar colorJugador)
{
    bool hayMov = 0;
    QChar colorContrario;
    if (colorJugador == 'b')
        colorContrario = 'n';
    else
        colorContrario = 'b';
    QList<char> direccionesPosibles = devuelveDireccionesPosibles(fila, col, colorContrario);
    QList<char>::const_iterator it = direccionesPosibles.begin();
    QList<QPair<int, int> >  fichasACambiar;
    while (it != direccionesPosibles.end() && ( hayMov==0) )
    {
        hayMov = existeMovimiento(fila, col, colorJugador, *it,fichasACambiar);
        it++;
    }
    return hayMov;
}

QList<QPair<int, int> > Tablero::getPosicionesFichasAGirar(int fila, int col, QChar colorJugador)
{
    QList<QPair<int,int> > fichasACambiar;
    QChar colorContrario;
        if (colorJugador == 'b')
            colorContrario = 'n';
        else
            colorContrario = 'b';

        QList<char> direccionesPosibles = devuelveDireccionesPosibles(fila, col, colorContrario);
        QList<char>::const_iterator it = direccionesPosibles.begin();
        while (it != direccionesPosibles.end())
        {

            existeMovimiento(fila, col, colorJugador, *it,fichasACambiar);
            it++;
        }
        return fichasACambiar;
}

bool Tablero::existeMovimiento(int fila, int col, QChar colorCorte, char direccionMovimiento, QList<QPair<int,int> >  & fichasACambiar)
{
    QPair<int,int> Aux;
    int cantFichasGiradas = 0;
    switch (direccionMovimiento)
    {
        case 'd': // DOWN (ABAJO)
        {
            fila++;
            while ((fila < 8) && (board[fila][col].getColor() != 't') && (board[fila][col].getColor() != colorCorte))
            {
                Aux.first=fila;
                Aux.second=col;
                fichasACambiar.push_back(Aux);
                cantFichasGiradas++;
                fila++;
            }
                break;
        }
        case 'u': // UP (ARRIBA)
        {
            fila--;
            while ((fila >= 0) && (board[fila][col].getColor() != 't') && (board[fila][col].getColor() != colorCorte))
            {
                Aux.first=fila;
                Aux.second=col;
                fichasACambiar.push_back(Aux);
                cantFichasGiradas++;
                fila--;
            }
            break;
        }
        case 'l': // LEFT (IZQ)
        {
            col--;
            while ((col >= 0) && (board[fila][col].getColor() != 't') && (board[fila][col].getColor() != colorCorte))
            {
                Aux.first=fila;
                Aux.second=col;
                fichasACambiar.push_back(Aux);
                cantFichasGiradas++;
                col--;
            }
            break;
        }
        case 'r': // RIGHT (DERECHA)
        {
            col++;
            while ((col < 8) && (board[fila][col].getColor() != 't') && (board[fila][col].getColor() != colorCorte))
            {
                Aux.first=fila;
                Aux.second=col;
                fichasACambiar.push_back(Aux);
                cantFichasGiradas++;
                col++;
            }
            break;
        }
        case '0': // DIAGONAL IZQUIERDA ARRIBA
        {
            fila--; col--;
            while ((fila >= 0) && (col >= 0) && (board[fila][col].getColor() != 't') && (board[fila][col].getColor() != colorCorte))
            {
                Aux.first=fila;
                Aux.second=col;
                fichasACambiar.push_back(Aux);
                cantFichasGiradas++;
                fila--;
                col--;
            }
            break;
        }
        case '1': // DIAGONAL IZQUIERDA ABAJO
        {
            fila++; col--;
            while ((fila < 8) && (col >= 0) && (board[fila][col].getColor() != 't') && (board[fila][col].getColor() != colorCorte))
            {
                Aux.first=fila;
                Aux.second=col;
                fichasACambiar.push_back(Aux);
                cantFichasGiradas++;
                fila++;
                col--;
            }
            break;
        }
        case '2': // DIAGONAL DERECHA ARRIBA
        {
            fila--; col++;
            while ((fila >= 0) && (col < 8) && (board[fila][col].getColor() != 't') && (board[fila][col].getColor() != colorCorte))
            {
                Aux.first=fila;
                Aux.second=col;
                fichasACambiar.push_back(Aux);
                cantFichasGiradas++;
                fila--;
                col++;
            }
            break;
        }
        case '3': // DIAGONAL DERECHA ABAJO
        {
            fila++; col++;
            while ((fila < 8) && (col < 8) && (board[fila][col].getColor() != 't') && (board[fila][col].getColor() != colorCorte))
            {
                Aux.first=fila;
                Aux.second=col;
                fichasACambiar.push_back(Aux);
                cantFichasGiradas++;
                fila++;
                col++;
            }
            break;
        }
    }
    if (board[fila][col].getColor() == colorCorte)
    {
        return 1;
    }
    else
    {
        while (cantFichasGiradas > 0)
        {
            fichasACambiar.pop_back();
            cantFichasGiradas--;
        }
        return 0;
    }
}

QList<char> Tablero::devuelveDireccionesPosibles(int fila, int col, QChar colorContrario)
{
    QList<char> direccionesPosibles;
    if ((fila == 0) && (col == 0)) //
    {
        if (board[fila+1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('d');
        if (board[fila][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('r');
        if (board[fila+1][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('3');
    }
    else if ((fila == 7) && (col == 0)) //
    {
        if (board[fila-1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('u');
        if (board[fila-1][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('2');
        if (board[fila][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('r');
    }
    else if ((fila == 0) && (col == 7)) //
    {
        if (board[fila][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('l');
        if (board[fila+1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('d');
        if (board[fila+1][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('1');
    }
    else if ((fila == 7) && (col == 7)) //
    {
        if (board[fila-1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('u');
        if (board[fila][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('l');
        if (board[fila-1][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('0');
    }
    else if (fila == 0)
    {
        if (board[fila][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('l');
        if (board[fila][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('r');
        if (board[fila+1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('d');
        if (board[fila+1][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('1');
        if (board[fila+1][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('3');
    }
    else if (fila == 7)
    {
        if (board[fila-1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('u');
        if (board[fila][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('r');
        if (board[fila][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('l');
        if (board[fila-1][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('0');
        if (board[fila-1][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('2');
    }
    else if (col == 0)
    {
        if (board[fila+1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('d');
        if (board[fila][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('r');
        if (board[fila-1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('u');
        if (board[fila-1][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('2');
        if (board[fila+1][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('3');
    }
    else if (col == 7)
    {
        if (board[fila+1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('d');
        if (board[fila-1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('u');
        if (board[fila][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('l');
        if (board[fila-1][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('0');
        if (board[fila+1][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('1');
    }
    else
    {
        if (board[fila+1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('d');
        if (board[fila-1][col].getColor() == colorContrario)
            direccionesPosibles.push_back('u');
        if (board[fila][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('l');
        if (board[fila][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('r');
        if (board[fila-1][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('0');
        if (board[fila+1][col-1].getColor() == colorContrario)
            direccionesPosibles.push_back('1');
        if (board[fila-1][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('2');
        if (board[fila+1][col+1].getColor() == colorContrario)
            direccionesPosibles.push_back('3');
    }
    return direccionesPosibles;
}

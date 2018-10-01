#include "celda.h"
#include "juego.h"
#include <QDebug>

Celda::Celda()
{
    //ctor
}

Celda::Celda(int x, int y, int w, int h, QPen pen, QBrush brush, Juego *j):QGraphicsRectItem(x,y,w,h)
{
    pos.setX(x);
    pos.setY(y);
    juego = j;
    setPen(pen);
    setBrush(brush);
    setAcceptHoverEvents(true);
    entroHover = 0;
    finalizaJuego = 0;
}

void Celda::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPair<int,int> posicion(pos.y()/65,pos.x()/65);
    set<QPair<int,int> > movPosibles = juego->getMovimientosPosibles(juego->getTurno());   
    if (movPosibles.find(posicion) != movPosibles.end())
    {
        p = pen();
        QPen newPen(Qt::SolidLine);
        newPen.setWidth(3);
        setPen(newPen);
        entroHover = 1;
    }
}

void Celda::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (entroHover)
        setPen(p);
    entroHover =0;
}

void Celda::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (entroHover)
    {
        QList<QPair<int,int> > fichasACambiar = juego->getPosicionesFichasAGirar(pos.y()/65,pos.x()/65,juego->getTurno());
        cambiaFichas(fichasACambiar);
        bool hayTurno = juego->cambiarTurno();
        if (hayTurno)
        {
            QPair<int,int> mejorMovimiento = juego->tabuSearch();
            pos.setX(mejorMovimiento.second*65);
            pos.setY(mejorMovimiento.first*65);
            cambiaFichas(juego->getPosicionesFichasAGirar(mejorMovimiento.first, mejorMovimiento.second, 'b'));
            juego->cambiarTurno();
        }
        setPen(p);
        entroHover = 0;
    }
}

void Celda::cambiaFichas(QList<QPair<int, int> > fichasACambiar)
{
    juego->addFicha(pos);
    QList<QPair<int,int > > :: const_iterator ite=fichasACambiar.begin();
    while(ite!=fichasACambiar.end())
    {
        QPoint Aux;
        Aux.setX(ite->second*65);
        Aux.setY(ite->first*65);
        juego->giraFicha(Aux);
        ite++;
    }
}

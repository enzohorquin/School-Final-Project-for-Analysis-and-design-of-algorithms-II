#ifndef CELDA_H
#define CELDA_H
#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>
#include "tablero.h"
#include <windows.h>
class Juego;

class Celda : public QGraphicsRectItem
{
public:
    Celda();
    Celda(int x, int y, int w, int h, QPen pen, QBrush brush, Juego * j);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QPoint pos;
    QPen p;
    Juego * juego;
    bool entroHover;
    bool finalizaJuego;
    void cambiaFichas(QList<QPair<int,int> > fichasACambiar);
};

#endif // CELDA_H

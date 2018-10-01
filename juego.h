#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMessageBox>
#include <QPixmap>
#include "celda.h"
#include "tablero.h"

namespace Ui {
class Juego;
}

class Juego : public QMainWindow
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = 0);
    ~Juego();
    void addFicha(QPoint point);
    void giraFicha(QPoint pos);
    bool cambiarTurno();
    QPair<int,int> tabuSearch();
    QChar getTurno();
    set<QPair<int,int> > getMovimientosPosibles(QChar turno);
    QList<QPair<int,int> > getPosicionesFichasAGirar(int x , int y , QChar turno);

private slots:

    void on_botonInstrucciones_clicked();

    void on_botonJuegoNuevo_clicked();

protected:

private:
    Ui::Juego *ui;
    QGraphicsScene *escena;
    Tablero board;
    Ficha fichaPrivada;
    int puntajeBlanco, puntajeNegro;
    int fichasColocadas;
    QList<QPair<int,int> > listaTabu;
    void mostrarTablero();
    void configuraVentana();
    void inicializaTablero();
    void finalizarJuego();
    void vuelveAtras(int fila, int col, QList<QPair<int,int> > fichasAGirarBlanco);
    void simulaFichas(int fila, int col, QList<QPair<int,int> > fichasAGirarBlanco);
    void imprimeConjunto(set<QPair<int,int> > conjunto);
    void imprimeLista(QList<QPair<int,int> > lista);
};

#endif // JUEGO_H

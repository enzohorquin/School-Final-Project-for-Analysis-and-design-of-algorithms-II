#include "juego.h"
#include "ui_juego.h"
#include "tablero.h"
#include <QDebug>

Juego::Juego(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Juego)
{
    ui->setupUi(this);
    puntajeBlanco = 2;
    puntajeNegro = 2;
    fichasColocadas = 4;
    fichaPrivada.setColor('n');
    configuraVentana();
    mostrarTablero();
    inicializaTablero();
}

Juego::~Juego()
{
    delete ui;
}

void Juego::addFicha(QPoint point)
{
    QGraphicsPixmapItem * token = NULL;
    if (fichaPrivada.getColor() == 'b')
    {
        token = new QGraphicsPixmapItem(QPixmap(":/iconos/fichaBlanca.png"));
        board.setFicha(point.y()/65, point.x()/65, fichaPrivada);
        puntajeBlanco++;
        ui->labelPuntajeBlanco->setText("x " + QString::number(puntajeBlanco));
    }
    else
    {
        token = new QGraphicsPixmapItem(QPixmap(":/iconos/fichaNegra.png"));
        board.setFicha(point.y()/65, point.x()/65, fichaPrivada);
        puntajeNegro++;
        ui->labelPuntajeNegro->setText("x " + QString::number(puntajeNegro));
    }
    token->setScale(0.08);
    token->setPos(point+QPoint(8,8));
    ui->graphicsViewTablero->scene()->addItem(token);
    fichasColocadas++;
}

set<QPair<int, int> > Juego::getMovimientosPosibles(QChar turno)
{
    if (turno == 'n')
        return board.getMovimientosPosibles('n');
    else
        return board.getMovimientosPosibles('b');
}

QChar Juego::getTurno()
{
    return fichaPrivada.getColor();
}

QList<QPair<int, int> > Juego::getPosicionesFichasAGirar(int x, int y, QChar turno)
{
   QList<QPair<int,int> > Aux= board.getPosicionesFichasAGirar(x,y,turno);
   return Aux;
}

void Juego::giraFicha(QPoint pos)
{
    QGraphicsPixmapItem * token = NULL;
    Ficha f;
    if (fichaPrivada.getColor() == 'b')
    {
        token = new QGraphicsPixmapItem(QPixmap(":/iconos/fichaBlanca.png"));
        f.setColor('b');
        puntajeBlanco++;
        puntajeNegro--;
        ui->labelPuntajeBlanco->setText("x " + QString::number(puntajeBlanco));
        ui->labelPuntajeNegro->setText("x " + QString::number(puntajeNegro));
    }
    else
    {
        token = new QGraphicsPixmapItem(QPixmap(":/iconos/fichaNegra.png"));
        f.setColor('n');
        puntajeBlanco--;
        puntajeNegro++;
        ui->labelPuntajeBlanco->setText("x " + QString::number(puntajeBlanco));
        ui->labelPuntajeNegro->setText("x " + QString::number(puntajeNegro));
    }
    token->setScale(0.08);
    token->setPos(pos + QPoint(8,8));
    ui->graphicsViewTablero->scene()->addItem(token);
    board.setFicha(pos.y()/65, pos.x()/65, f);
}

bool Juego::cambiarTurno()
{
    if ((fichasColocadas == 64) || (puntajeBlanco == 0) || (puntajeNegro==0) || ((board.getMovimientosPosibles('b').empty()) && (board.getMovimientosPosibles('n').empty())))
    {
        finalizarJuego();
        return 0;
    }
    else
    {
        if (fichaPrivada.getColor() == 'n')
        {
            fichaPrivada.setColor('b');
            ui->labelTurno->setText("Turno blanco");
        }
        else
        {
            fichaPrivada.setColor('n');
            ui->labelTurno->setText("Turno negro");
        }
        if (board.getMovimientosPosibles(fichaPrivada.getColor()).empty())
        {
            if (fichaPrivada.getColor() == 'b')
            {
                QMessageBox::information(this, "No hay movimiento", "El jugador blanco no tiene movimientos posibles", QMessageBox::Ok);
                fichaPrivada.setColor('n');
                ui->labelTurno->setText("Turno negro");
                return 0;
            }
            else
            {
                QMessageBox::information(this, "No hay movimiento", "El jugador negro no tiene movimientos posibles", QMessageBox::Ok);
                fichaPrivada.setColor('b');
                ui->labelTurno->setText("Turno blanco");
            }
        }
    }
    return 1;
}

QPair<int, int> Juego::tabuSearch()
{
    set<QPair<int,int> > movPosiblesBlanco = board.getMovimientosPosibles('b');
    set<QPair<int,int> >::const_iterator it = movPosiblesBlanco.begin();
    int mejorPromedio = -64;
    QPair<int,int> mejorMovimiento;
    while (it != movPosiblesBlanco.end())
    {
        QList<QPair<int,int> > fichasAGirarBlanco = board.getPosicionesFichasAGirar(it->first, it->second, 'b');
        int fichasGiradasBlanco = fichasAGirarBlanco.size();
        simulaFichas(it->first, it->second, fichasAGirarBlanco);
        set<QPair<int,int> > movPosiblesNegro = board.getMovimientosPosibles('n');
        set<QPair<int,int> >::const_iterator itMovNegro = movPosiblesNegro.begin();
        int masFichasGiradasNegro = -64;
        while (itMovNegro != movPosiblesNegro.end())
        {
            int cantFichasNegro = board.getPosicionesFichasAGirar(itMovNegro->first, itMovNegro->second, 'n').size();
            if (cantFichasNegro > masFichasGiradasNegro)
                masFichasGiradasNegro = cantFichasNegro;
            itMovNegro++;
        }
        vuelveAtras(it->first, it->second, fichasAGirarBlanco);
        int promedioFichas = fichasGiradasBlanco - masFichasGiradasNegro;
        if (promedioFichas > mejorPromedio)
        {
            mejorPromedio = promedioFichas;
            mejorMovimiento = *it;
        }
        it++;
    }
    return mejorMovimiento;
}

void Juego::finalizarJuego()
{
    qDebug() << fichasColocadas;
    if (puntajeBlanco > puntajeNegro)
        QMessageBox::information(this, "Fin del juego", "El jugador blanco ha ganado el juego", QMessageBox::Ok);
    else if (puntajeNegro > puntajeBlanco)
        QMessageBox::information(this, "Fin del juego", "El jugador negro ha ganado el juego", QMessageBox::Ok);
    else
        QMessageBox::information(this, "Fin del juego", "Ambos jugadores han empatado", QMessageBox::Ok);
}

void Juego::vuelveAtras(int fila, int col, QList<QPair<int, int> > fichasAGirarBlanco)
{
    //it->first y it->second se vuelve transparente. Recorremos de nuevo FichasAGirarBlanco y las hacemos negras.
    Ficha auxFicha('t');
    board.setFicha(fila, col, auxFicha);
    auxFicha.setColor('n');
    QList<QPair<int,int> >::const_iterator it = fichasAGirarBlanco.begin();
    while (it != fichasAGirarBlanco.end())
    {
        board.setFicha(it->first, it->second, auxFicha);
        it++;
    }
}

void Juego::simulaFichas(int fila, int col, QList<QPair<int, int> > fichasAGirarBlanco)
{
    Ficha fichaBlanca('b');
    board.setFicha(fila, col, fichaBlanca);
    QList<QPair<int,int> >::const_iterator it2 = fichasAGirarBlanco.begin();
    while (it2 != fichasAGirarBlanco.end())
    {
        board.setFicha(it2->first, it2->second, fichaBlanca);
        it2++;
    }
}

void Juego::imprimeConjunto(set<QPair<int, int> > conjunto)
{
    qDebug() << "Conjunto:";
    set<QPair<int,int> >::const_iterator it = conjunto.begin();
    while (it != conjunto.end())
    {
        qDebug() << *it;
        it++;
    }
}

void Juego::imprimeLista(QList<QPair<int, int> > lista)
{
    qDebug() << "LISTA:";
    QList<QPair<int,int> >::const_iterator it = lista.begin();
    while (it != lista.end())
    {
        qDebug() << *it;
        it++;
    }
}

void Juego::mostrarTablero()
{
    escena = new QGraphicsScene();
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    QColor colorBorde(250,255,189);
    pen.setColor(colorBorde);
    pen.setWidth(3);
    for (int i = 0; i < 8 ; i++)
        for (int j = 0; j < 8; j++)
        {
            QBrush brush;
            if (i%2 == 0)
                if (j%2 == 0)
                {
                    brush.setStyle(Qt::SolidPattern);
                    brush.setColor(QColor(Qt::darkGreen));
                }
                else
                {
                    brush.setStyle(Qt::SolidPattern);
                    brush.setColor(QColor(Qt::green));
                }
            else
                if (j%2 != 0)
                {
                    brush.setStyle(Qt::SolidPattern);
                    brush.setColor(QColor(Qt::darkGreen));
                }
                else
                {
                    brush.setStyle(Qt::SolidPattern);
                    brush.setColor(QColor(Qt::green));
                }
            escena->addItem(new Celda(65*j,65*i,62,62,pen,brush,this));
        }
    ui->graphicsViewTablero->setScene(escena);
    ui->graphicsViewTablero->setFixedHeight(8*65+5);
    ui->graphicsViewTablero->setFixedWidth(8*65+5);
}

void Juego::configuraVentana()
{
    this->setFixedSize(800,592);
    ui->labelTurno->move(560, 480);
    ui->labelResultado->move(550, 100);
    ui->labelResultado->setFixedSize(230, 350);
    ui->labelFichaNegra->move(620, 215);
    ui->labelPuntajeNegro->move(660,215);
    ui->labelPuntajeNegro->setText("x " + QString::number(puntajeNegro));
    ui->labelFichaBlanca->move(620, 330);
    ui->labelPuntajeBlanco->move(660, 330);
    ui->labelPuntajeBlanco->setText("x " + QString::number(puntajeBlanco));
    ui->labelTurno->setText("Turno negro");
}

void Juego::inicializaTablero()
{
    // Interfaz tablero
    QGraphicsPixmapItem * ficha = new QGraphicsPixmapItem(QPixmap(":/iconos/fichaBlanca.png"));
    ficha->setScale(0.08); ficha->setPos(65*3+8, 65*3+8);
    ui->graphicsViewTablero->scene()->addItem(ficha);
    ficha = new QGraphicsPixmapItem(QPixmap(":/iconos/fichaBlanca.png"));
    ficha->setScale(0.08); ficha->setPos(65*4+8, 65*4+8);
    ui->graphicsViewTablero->scene()->addItem(ficha);
    ficha = new QGraphicsPixmapItem(QPixmap(":/iconos/fichaNegra.png"));
    ficha->setScale(0.08); ficha->setPos(65*3+8, 65*4+8);
    ui->graphicsViewTablero->scene()->addItem(ficha);
    ficha = new QGraphicsPixmapItem(QPixmap(":/iconos/fichaNegra.png"));
    ficha->setScale(0.08); ficha->setPos(65*4+8, 65*3+8);
    ui->graphicsViewTablero->scene()->addItem(ficha);
}

void Juego::on_botonInstrucciones_clicked()
{
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            qDebug() << i << "," << j << ":" << board.getFicha(i,j).getColor();
}

void Juego::on_botonJuegoNuevo_clicked()
{
    board.clear();
    puntajeBlanco = 2;
    puntajeNegro = 2;
    fichasColocadas = 4;
    fichaPrivada.setColor('n');
    configuraVentana();
    mostrarTablero();
    inicializaTablero();
}

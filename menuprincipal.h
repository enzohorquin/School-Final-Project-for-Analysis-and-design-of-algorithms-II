#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QMainWindow>
#include <QGraphicsView>
#include "juego.h"
#include "tablero.h"

namespace Ui {
class MenuPrincipal;
}

class MenuPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuPrincipal(QWidget *parent = 0);
    ~MenuPrincipal();

private slots:
    void on_botonJugar_clicked();

    void on_botonInstrucciones_clicked();

    void on_botonAtras_clicked();

private:
    Ui::MenuPrincipal *ui;
};

#endif // MENUPRINCIPAL_H

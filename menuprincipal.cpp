#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include <QDebug>

MenuPrincipal::MenuPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuPrincipal)
{
    ui->setupUi(this);
    this->setFixedSize(400, 450);
    ui->textBrowser->setFixedSize(580, 550);
    ui->textBrowser->move(10,40);
    ui->botonAtras->move(10,5);
    ui->botonAtras->setFixedSize(40,30);
    ui->botonAtras->hide();
    ui->textBrowser->hide();
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

void MenuPrincipal::on_botonJugar_clicked()
{
    Juego * juego = new Juego();
    juego->show();
    this->close();
}

void MenuPrincipal::on_botonInstrucciones_clicked()
{
    ui->labelImagen->hide();
    ui->labelTitulo->hide();
    ui->botonInstrucciones->hide();
    ui->botonJugar->hide();
    ui->textBrowser->show();
    ui->botonAtras->show();
    this->setFixedSize(600, 600);
}

void MenuPrincipal::on_botonAtras_clicked()
{
    this->setFixedSize(400, 450);
    ui->botonAtras->hide();
    ui->textBrowser->hide();
    ui->labelImagen->show();
    ui->labelTitulo->show();
    ui->botonInstrucciones->show();
    ui->botonJugar->show();
}

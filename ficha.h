#ifndef FICHA_H
#define FICHA_H
#include <QPair>
#include <QString>

class Ficha
{
public:
    Ficha();
    Ficha(QChar color);
    void setColor(QChar color);
    QChar getColor();

private:
    QChar token;
};

#endif // FICHA_H

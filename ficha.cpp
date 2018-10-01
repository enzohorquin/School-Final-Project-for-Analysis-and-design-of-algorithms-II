#include "ficha.h"

Ficha::Ficha()
{
    //ctor
}

Ficha::Ficha(QChar color)
{
    token = color;
}

void Ficha::setColor(QChar color)
{
    token = color;
}

QChar Ficha::getColor()
{
    return token;
}


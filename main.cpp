#include "menuprincipal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuPrincipal w;
    w.show();

    return a.exec();
}

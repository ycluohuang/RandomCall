#include "widdget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widdget w;
    w.show();
    return a.exec();
}

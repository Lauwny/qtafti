#include "mainwindow.h"
#include "liste_entreprise.h"
#include "companychart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    liste_entreprise w;
    w.show();
    return a.exec();
}

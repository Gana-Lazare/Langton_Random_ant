//	TP_Qt2 L3 EEA - 2019

#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main(int argc, char *argv[])
{
    srand(time(nullptr));       // initialisation du générateur aléatoire
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("PSG_tag");
    a.setApplicationName("MaReader");
    MainWindow w;
    w.init(&a);
    w.show();

    return a.exec();
}

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow ventanaPrincipal;
    ventanaPrincipal.show();

    return app.exec();
}

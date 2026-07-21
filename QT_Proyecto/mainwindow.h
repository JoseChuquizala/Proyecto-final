#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void ingresarComoEmpleado();
    void ingresarComoCliente();
};

#endif // MAINWINDOW_H

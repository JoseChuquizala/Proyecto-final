#include "mainwindow.h"
#include "login.h"
#include "productos.h"
#include "ordenes.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("EPN.tech");
    resize(360, 220);

    QLabel *titulo = new QLabel("Bienvenido a EPN.tech", this);
    titulo->setStyleSheet("font-size: 16pt; font-weight: bold;");
    titulo->setAlignment(Qt::AlignCenter);

    QPushButton *botonEmpleado = new QPushButton("1. Ingresar como empleado", this);
    QPushButton *botonCliente  = new QPushButton("2. Ingresar como cliente", this);
    QPushButton *botonSalir    = new QPushButton("3. Salir", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titulo);
    layout->addSpacing(20);
    layout->addWidget(botonEmpleado);
    layout->addWidget(botonCliente);
    layout->addWidget(botonSalir);

    connect(botonEmpleado, &QPushButton::clicked, this, &MainWindow::ingresarComoEmpleado);
    connect(botonCliente,  &QPushButton::clicked, this, &MainWindow::ingresarComoCliente);
    connect(botonSalir,    &QPushButton::clicked, this, &QWidget::close);
}

void MainWindow::ingresarComoEmpleado()
{
    LoginDialog dialogo(this);

    if (dialogo.exec() == QDialog::Accepted)
    {

        VentanaProductos *ventana = new VentanaProductos;
        ventana->setAttribute(Qt::WA_DeleteOnClose);
        ventana->show();
    }
    else
    {
        QMessageBox::information(this, "Acceso", "No tiene permiso para ingresar.");
    }
}

void MainWindow::ingresarComoCliente()
{
    VentanaOrdenes *ventana = new VentanaOrdenes;
    ventana->setAttribute(Qt::WA_DeleteOnClose);
    ventana->show();
}

#include "login.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

// ============================================================
// login.cpp
// Igual que la version de consola: compara contra un usuario
// y clave fijos. Si son correctos, cierra el dialogo con accept()
// (equivale al "return true" del login() original).
// ============================================================

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Acceso de empleado - EPN.tech");
    setFixedWidth(320);

    campoUsuario = new QLineEdit(this);
    campoClave   = new QLineEdit(this);
    campoClave->setEchoMode(QLineEdit::Password);

    QFormLayout *formulario = new QFormLayout;
    formulario->addRow("Usuario:", campoUsuario);
    formulario->addRow("Clave:", campoClave);

    QPushButton *botonIngresar = new QPushButton("Ingresar", this);
    QPushButton *botonCancelar = new QPushButton("Cancelar", this);

    QHBoxLayout *filaBotones = new QHBoxLayout;
    filaBotones->addWidget(botonIngresar);
    filaBotones->addWidget(botonCancelar);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->addWidget(new QLabel("Bienvenido a EPN.tech"));
    layoutPrincipal->addLayout(formulario);
    layoutPrincipal->addLayout(filaBotones);

    connect(botonIngresar, &QPushButton::clicked, this, &LoginDialog::verificarLogin);
    connect(botonCancelar, &QPushButton::clicked, this, &QDialog::reject);

    // Permite dar "Enter" en el campo de clave para ingresar
    connect(campoClave, &QLineEdit::returnPressed, this, &LoginDialog::verificarLogin);
}

void LoginDialog::verificarLogin()
{
    const QString usuarioCorrecto = "user";
    const QString claveCorrecta   = "epn2026";

    if (campoUsuario->text() == usuarioCorrecto &&
        campoClave->text()   == claveCorrecta)
    {
        accept(); // equivalente a "return true"
    }
    else
    {
        QMessageBox::warning(this, "Acceso denegado",
                              "Usuario o clave incorrectos.");
        campoClave->clear();
    }
}

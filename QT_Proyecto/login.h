#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

class QLineEdit;

// ============================================================
// login.h
// Ventana (QDialog) para que el empleado ingrese usuario/clave.
// Mismo usuario/clave que el proyecto original: user / epn2026
// ============================================================
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);

private slots:
    void verificarLogin();

private:
    QLineEdit *campoUsuario;
    QLineEdit *campoClave;
};

#endif // LOGIN_H

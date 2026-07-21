#ifndef ORDENES_H
#define ORDENES_H

#include <QWidget>
#include <QVector>
#include "estructura.h"

class QTableWidget;
class QLineEdit;
class QSpinBox;

// ============================================================
// ordenes.h
// Ventana del menu del cliente. Reemplaza a menuOrdenes():
// ver productos, comprar, ver/buscar/modificar/eliminar ordenes.
// ============================================================
class VentanaOrdenes : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaOrdenes(QWidget *parent = nullptr);

private slots:
    void comprarProducto();
    void mostrarMisOrdenes();
    void buscarOrden();
    void modificarOrden();
    void eliminarOrden();

private:
    void refrescarTablaProductos();
    int  generarCodigoOrden() const;

    QTableWidget *tablaProductos;
    QTableWidget *tablaOrdenes;

    QLineEdit *campoCliente;
    QLineEdit *campoCodigoProducto;
    QSpinBox  *campoCantidad;

    QLineEdit *campoCodigoOrden;
};

#endif // ORDENES_H

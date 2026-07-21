#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <QWidget>
#include <QVector>
#include "estructura.h"

class QTableWidget;
class QLineEdit;
class QDoubleSpinBox;
class QSpinBox;

// ============================================================
// productos.h
// Ventana del CRUD de productos (para el empleado).
// Reemplaza al menuProductos() de consola: agregar, mostrar,
// buscar, modificar y eliminar productos.
// ============================================================
class VentanaProductos : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaProductos(QWidget *parent = nullptr);

    // Utilidad usada tambien por el modulo de ordenes
    static bool obtenerProducto(int codigo, Producto &producto);

private slots:
    void agregarProducto();
    void modificarProducto();
    void eliminarProducto();
    void buscarProducto();
    void limpiarFormulario();
    void filaSeleccionada(int fila, int columna);

private:
    void refrescarTabla();
    void cargarFormularioDesdeFila(int fila);

    QTableWidget   *tabla;
    QLineEdit      *campoCodigo;
    QLineEdit      *campoNombre;
    QLineEdit      *campoCategoria;
    QDoubleSpinBox *campoPrecio;
    QSpinBox       *campoStock;

    QVector<Producto> productos;
};

#endif // PRODUCTOS_H

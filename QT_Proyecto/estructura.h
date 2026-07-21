#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include <QString>

// ============================================================
// estructura.h
// Aqui van SOLO las "formas" de los datos que usa el programa.
// No hay logica aqui, solo la definicion de que campos tiene
// un Producto y que campos tiene una Orden.
// ============================================================

// Representa un producto del inventario
struct Producto
{
    int     codigo   = 0;
    QString nombre;
    QString categoria;
    double  precio   = 0.0;
    int     stock    = 0;
};

// Representa una orden/compra hecha por un cliente
struct Orden
{
    int     codOrden    = 0;
    QString cliente;
    int     codProducto = 0;
    int     cantidad    = 0;
    double  total       = 0.0;
};

#endif // ESTRUCTURA_H

#include "archivos.h"

#include <QFile>
#include <QTextStream>
#include <QDir>

// ============================================================
// archivos.cpp
// Aqui esta la logica real de guardar/leer los .txt.
// Cada producto/orden se guarda en 5 lineas seguidas, igual
// que en la version de consola (codigo, nombre, categoria,
// precio, stock / codOrden, cliente, codProducto, cantidad, total).
// ============================================================

static const QString ARCHIVO_PRODUCTOS = "productos.txt";
static const QString ARCHIVO_ORDENES   = "ordenes.txt";

// ---------------------------------------------------------------
// PRODUCTOS
// ---------------------------------------------------------------
QVector<Producto> cargarProductos()
{
    QVector<Producto> lista;

    QFile archivo(ARCHIVO_PRODUCTOS);
    if (!archivo.exists())
        return lista; // todavia no hay productos guardados

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return lista;

    QTextStream in(&archivo);
    while (!in.atEnd())
    {
        Producto p;

        QString lineaCodigo = in.readLine();
        if (lineaCodigo.isNull())
            break;

        p.codigo    = lineaCodigo.toInt();
        p.nombre    = in.readLine();
        p.categoria = in.readLine();
        p.precio    = in.readLine().toDouble();
        p.stock     = in.readLine().toInt();

        lista.append(p);
    }

    archivo.close();
    return lista;
}

void guardarProductos(const QVector<Producto> &productos)
{
    QFile archivo(ARCHIVO_PRODUCTOS);
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&archivo);
    for (const Producto &p : productos)
    {
        out << p.codigo    << "\n";
        out << p.nombre    << "\n";
        out << p.categoria << "\n";
        out << p.precio    << "\n";
        out << p.stock     << "\n";
    }

    archivo.close();
}

// ---------------------------------------------------------------
// ORDENES
// ---------------------------------------------------------------
QVector<Orden> cargarOrdenes()
{
    QVector<Orden> lista;

    QFile archivo(ARCHIVO_ORDENES);
    if (!archivo.exists())
        return lista;

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return lista;

    QTextStream in(&archivo);
    while (!in.atEnd())
    {
        Orden o;

        QString lineaCodigo = in.readLine();
        if (lineaCodigo.isNull())
            break;

        o.codOrden    = lineaCodigo.toInt();
        o.cliente     = in.readLine();
        o.codProducto = in.readLine().toInt();
        o.cantidad    = in.readLine().toInt();
        o.total       = in.readLine().toDouble();

        lista.append(o);
    }

    archivo.close();
    return lista;
}

void guardarOrdenes(const QVector<Orden> &ordenes)
{
    QFile archivo(ARCHIVO_ORDENES);
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&archivo);
    for (const Orden &o : ordenes)
    {
        out << o.codOrden    << "\n";
        out << o.cliente     << "\n";
        out << o.codProducto << "\n";
        out << o.cantidad    << "\n";
        out << o.total       << "\n";
    }

    archivo.close();
}

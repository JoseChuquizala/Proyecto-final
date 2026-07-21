#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <QVector>
#include "estructura.h"

// ============================================================
// archivos.h
// Declara las funciones encargadas de leer y escribir los
// archivos de texto (productos.txt y ordenes.txt).
// La logica real esta en archivos.cpp
// ============================================================

// ---- Productos ----
QVector<Producto> cargarProductos();
void               guardarProductos(const QVector<Producto> &productos);

// ---- Ordenes ----
QVector<Orden> cargarOrdenes();
void            guardarOrdenes(const QVector<Orden> &ordenes);

#endif // ARCHIVOS_H

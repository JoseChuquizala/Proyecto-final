#include "productos.h"
#include "archivos.h"

#include <QTableWidget>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>

// ============================================================
// productos.cpp
// Misma logica que el productos.cpp original de consola, pero
// en vez de cin/cout se usa la tabla y el formulario. Los datos
// se guardan siempre completos con guardarProductos() (que
// reescribe productos.txt), igual que antes se hacia con el
// archivo temporal + rename en modificar/eliminar.
// ============================================================

VentanaProductos::VentanaProductos(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("CRUD de productos - EPN.tech");
    resize(700, 480);

    // ---- Tabla ----
    tabla = new QTableWidget(this);
    tabla->setColumnCount(5);
    tabla->setHorizontalHeaderLabels({"Codigo", "Nombre", "Categoria", "Precio", "Stock"});
    tabla->horizontalHeader()->setStretchLastSection(true);
    tabla->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ---- Formulario ----
    campoCodigo    = new QLineEdit(this);
    campoNombre    = new QLineEdit(this);
    campoCategoria = new QLineEdit(this);
    campoPrecio    = new QDoubleSpinBox(this);
    campoPrecio->setMaximum(999999);
    campoPrecio->setDecimals(2);
    campoStock     = new QSpinBox(this);
    campoStock->setMaximum(999999);

    QFormLayout *formulario = new QFormLayout;
    formulario->addRow("Codigo:", campoCodigo);
    formulario->addRow("Nombre:", campoNombre);
    formulario->addRow("Categoria:", campoCategoria);
    formulario->addRow("Precio:", campoPrecio);
    formulario->addRow("Stock:", campoStock);

    QGroupBox *cajaFormulario = new QGroupBox("Datos del producto", this);
    cajaFormulario->setLayout(formulario);

    // ---- Botones ----
    QPushButton *botonAgregar    = new QPushButton("Agregar", this);
    QPushButton *botonModificar  = new QPushButton("Modificar", this);
    QPushButton *botonEliminar   = new QPushButton("Eliminar", this);
    QPushButton *botonBuscar     = new QPushButton("Buscar por codigo", this);
    QPushButton *botonLimpiar    = new QPushButton("Limpiar", this);

    QVBoxLayout *columnaBotones = new QVBoxLayout;
    columnaBotones->addWidget(botonAgregar);
    columnaBotones->addWidget(botonModificar);
    columnaBotones->addWidget(botonEliminar);
    columnaBotones->addWidget(botonBuscar);
    columnaBotones->addWidget(botonLimpiar);
    columnaBotones->addStretch();

    QHBoxLayout *filaInferior = new QHBoxLayout;
    filaInferior->addWidget(cajaFormulario, 2);
    filaInferior->addLayout(columnaBotones, 1);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->addWidget(new QLabel("========== CRUD DE PRODUCTOS =========="));
    layoutPrincipal->addWidget(tabla, 2);
    layoutPrincipal->addLayout(filaInferior);

    connect(botonAgregar,   &QPushButton::clicked, this, &VentanaProductos::agregarProducto);
    connect(botonModificar, &QPushButton::clicked, this, &VentanaProductos::modificarProducto);
    connect(botonEliminar,  &QPushButton::clicked, this, &VentanaProductos::eliminarProducto);
    connect(botonBuscar,    &QPushButton::clicked, this, &VentanaProductos::buscarProducto);
    connect(botonLimpiar,   &QPushButton::clicked, this, &VentanaProductos::limpiarFormulario);
    connect(tabla, &QTableWidget::cellClicked, this, &VentanaProductos::filaSeleccionada);

    productos = cargarProductos();
    refrescarTabla();
}

void VentanaProductos::refrescarTabla()
{
    tabla->setRowCount(0);

    for (const Producto &p : productos)
    {
        int fila = tabla->rowCount();
        tabla->insertRow(fila);
        tabla->setItem(fila, 0, new QTableWidgetItem(QString::number(p.codigo)));
        tabla->setItem(fila, 1, new QTableWidgetItem(p.nombre));
        tabla->setItem(fila, 2, new QTableWidgetItem(p.categoria));
        tabla->setItem(fila, 3, new QTableWidgetItem(QString::number(p.precio, 'f', 2)));
        tabla->setItem(fila, 4, new QTableWidgetItem(QString::number(p.stock)));
    }
}

void VentanaProductos::filaSeleccionada(int fila, int)
{
    cargarFormularioDesdeFila(fila);
}

void VentanaProductos::cargarFormularioDesdeFila(int fila)
{
    if (fila < 0 || fila >= productos.size())
        return;

    const Producto &p = productos.at(fila);
    campoCodigo->setText(QString::number(p.codigo));
    campoNombre->setText(p.nombre);
    campoCategoria->setText(p.categoria);
    campoPrecio->setValue(p.precio);
    campoStock->setValue(p.stock);
}

void VentanaProductos::limpiarFormulario()
{
    campoCodigo->clear();
    campoNombre->clear();
    campoCategoria->clear();
    campoPrecio->setValue(0);
    campoStock->setValue(0);
    tabla->clearSelection();
}

// ---- Agregar (equivale a agregarProductos() de consola) ----
void VentanaProductos::agregarProducto()
{
    bool ok = false;
    int codigo = campoCodigo->text().toInt(&ok);

    if (!ok || campoCodigo->text().isEmpty())
    {
        QMessageBox::warning(this, "Datos invalidos", "Ingrese un codigo numerico valido.");
        return;
    }

    for (const Producto &p : productos)
    {
        if (p.codigo == codigo)
        {
            QMessageBox::warning(this, "Codigo repetido",
                                  "Ya existe un producto con ese codigo.");
            return;
        }
    }

    Producto nuevo;
    nuevo.codigo    = codigo;
    nuevo.nombre    = campoNombre->text();
    nuevo.categoria = campoCategoria->text();
    nuevo.precio    = campoPrecio->value();
    nuevo.stock     = campoStock->value();

    productos.append(nuevo);
    guardarProductos(productos);
    refrescarTabla();
    limpiarFormulario();

    QMessageBox::information(this, "Listo", "Producto guardado correctamente.");
}

// ---- Modificar (equivale a modificarProductos() de consola) ----
void VentanaProductos::modificarProducto()
{
    bool ok = false;
    int codigo = campoCodigo->text().toInt(&ok);

    if (!ok)
    {
        QMessageBox::warning(this, "Datos invalidos", "Ingrese el codigo del producto a modificar.");
        return;
    }

    for (Producto &p : productos)
    {
        if (p.codigo == codigo)
        {
            p.nombre    = campoNombre->text();
            p.categoria = campoCategoria->text();
            p.precio    = campoPrecio->value();
            p.stock     = campoStock->value();

            guardarProductos(productos);
            refrescarTabla();
            QMessageBox::information(this, "Listo", "Producto modificado correctamente.");
            return;
        }
    }

    QMessageBox::warning(this, "No encontrado", "Producto no encontrado.");
}

// ---- Eliminar (equivale a eliminarProductos() de consola) ----
void VentanaProductos::eliminarProducto()
{
    bool ok = false;
    int codigo = campoCodigo->text().toInt(&ok);

    if (!ok)
    {
        QMessageBox::warning(this, "Datos invalidos", "Ingrese el codigo del producto a eliminar.");
        return;
    }

    for (int i = 0; i < productos.size(); ++i)
    {
        if (productos.at(i).codigo == codigo)
        {
            productos.removeAt(i);
            guardarProductos(productos);
            refrescarTabla();
            limpiarFormulario();
            QMessageBox::information(this, "Listo", "Producto eliminado correctamente.");
            return;
        }
    }

    QMessageBox::warning(this, "No encontrado", "Producto no encontrado.");
}

// ---- Buscar (equivale a buscarProductos() de consola) ----
void VentanaProductos::buscarProducto()
{
    bool ok = false;
    int codigo = campoCodigo->text().toInt(&ok);

    if (!ok)
    {
        QMessageBox::warning(this, "Datos invalidos", "Ingrese el codigo a buscar.");
        return;
    }

    for (int i = 0; i < productos.size(); ++i)
    {
        if (productos.at(i).codigo == codigo)
        {
            cargarFormularioDesdeFila(i);
            tabla->selectRow(i);
            return;
        }
    }

    QMessageBox::warning(this, "No encontrado", "Producto no encontrado.");
}

// ---- Utilidad compartida (equivale a obtenerProducto() de ordenes.cpp) ----
bool VentanaProductos::obtenerProducto(int codigo, Producto &producto)
{
    QVector<Producto> lista = cargarProductos();

    for (const Producto &p : lista)
    {
        if (p.codigo == codigo)
        {
            producto = p;
            return true;
        }
    }

    return false;
}

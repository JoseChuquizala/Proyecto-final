#include "ordenes.h"
#include "archivos.h"
#include "productos.h"

#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QTabWidget>

// ============================================================
// ordenes.cpp
// Misma logica que ordenes.cpp original, pero con formularios
// Qt en vez de cin/cout. Usa VentanaProductos::obtenerProducto()
// para revisar el producto igual que antes, y guardarOrdenes()
// para persistir todo el archivo (equivalente al viejo esquema
// de archivo temporal + rename usado en modificar/eliminar).
// ============================================================

VentanaOrdenes::VentanaOrdenes(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Menu de cliente - EPN.tech");
    resize(750, 520);

    // ---- Tabla de productos disponibles (opcion 1 del menu original) ----
    tablaProductos = new QTableWidget(this);
    tablaProductos->setColumnCount(5);
    tablaProductos->setHorizontalHeaderLabels({"Codigo", "Nombre", "Categoria", "Precio", "Stock"});
    tablaProductos->horizontalHeader()->setStretchLastSection(true);
    tablaProductos->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ---- Formulario para comprar (opcion 2) ----
    campoCliente        = new QLineEdit(this);
    campoCodigoProducto = new QLineEdit(this);
    campoCantidad       = new QSpinBox(this);
    campoCantidad->setMinimum(1);
    campoCantidad->setMaximum(999999);

    QFormLayout *formularioCompra = new QFormLayout;
    formularioCompra->addRow("Nombre del cliente:", campoCliente);
    formularioCompra->addRow("Codigo del producto:", campoCodigoProducto);
    formularioCompra->addRow("Cantidad:", campoCantidad);

    QPushButton *botonComprar = new QPushButton("Comprar producto", this);
    connect(botonComprar, &QPushButton::clicked, this, &VentanaOrdenes::comprarProducto);

    QGroupBox *cajaCompra = new QGroupBox("Nueva orden", this);
    QVBoxLayout *layoutCompra = new QVBoxLayout(cajaCompra);
    layoutCompra->addLayout(formularioCompra);
    layoutCompra->addWidget(botonComprar);

    QWidget *pestanaProductos = new QWidget;
    QVBoxLayout *layoutProductos = new QVBoxLayout(pestanaProductos);
    layoutProductos->addWidget(new QLabel("Productos disponibles:"));
    layoutProductos->addWidget(tablaProductos);
    layoutProductos->addWidget(cajaCompra);

    // ---- Tabla y opciones de "mis ordenes" (opciones 3, 4, 5, 6) ----
    tablaOrdenes = new QTableWidget(this);
    tablaOrdenes->setColumnCount(5);
    tablaOrdenes->setHorizontalHeaderLabels({"Codigo orden", "Cliente", "Cod. Producto", "Cantidad", "Total"});
    tablaOrdenes->horizontalHeader()->setStretchLastSection(true);
    tablaOrdenes->setEditTriggers(QAbstractItemView::NoEditTriggers);

    campoCodigoOrden = new QLineEdit(this);

    QPushButton *botonVerMisOrdenes = new QPushButton("Mostrar mis ordenes (por nombre)", this);
    QPushButton *botonBuscarOrden   = new QPushButton("Buscar orden por codigo", this);
    QPushButton *botonModificar     = new QPushButton("Modificar orden seleccionada", this);
    QPushButton *botonEliminar      = new QPushButton("Eliminar orden", this);

    connect(botonVerMisOrdenes, &QPushButton::clicked, this, &VentanaOrdenes::mostrarMisOrdenes);
    connect(botonBuscarOrden,   &QPushButton::clicked, this, &VentanaOrdenes::buscarOrden);
    connect(botonModificar,     &QPushButton::clicked, this, &VentanaOrdenes::modificarOrden);
    connect(botonEliminar,      &QPushButton::clicked, this, &VentanaOrdenes::eliminarOrden);

    QFormLayout *formularioOrden = new QFormLayout;
    formularioOrden->addRow("Codigo de orden:", campoCodigoOrden);

    QHBoxLayout *filaBotonesOrden = new QHBoxLayout;
    filaBotonesOrden->addWidget(botonBuscarOrden);
    filaBotonesOrden->addWidget(botonModificar);
    filaBotonesOrden->addWidget(botonEliminar);

    QWidget *pestanaOrdenes = new QWidget;
    QVBoxLayout *layoutOrdenes = new QVBoxLayout(pestanaOrdenes);
    layoutOrdenes->addWidget(botonVerMisOrdenes);
    layoutOrdenes->addWidget(tablaOrdenes);
    layoutOrdenes->addLayout(formularioOrden);
    layoutOrdenes->addLayout(filaBotonesOrden);
    layoutOrdenes->addWidget(new QLabel(
        "Nota: para modificar, use primero \"Buscar orden por codigo\",\n"
        "luego escriba el nuevo cliente/producto/cantidad en la pestaña de compra\n"
        "y presione \"Modificar orden seleccionada\"."));

    QTabWidget *pestanas = new QTabWidget(this);
    pestanas->addTab(pestanaProductos, "Comprar");
    pestanas->addTab(pestanaOrdenes, "Mis ordenes");

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->addWidget(new QLabel("========== MENU DE CLIENTE =========="));
    layoutPrincipal->addWidget(pestanas);

    refrescarTablaProductos();
}

void VentanaOrdenes::refrescarTablaProductos()
{
    QVector<Producto> productos = cargarProductos();

    tablaProductos->setRowCount(0);
    for (const Producto &p : productos)
    {
        int fila = tablaProductos->rowCount();
        tablaProductos->insertRow(fila);
        tablaProductos->setItem(fila, 0, new QTableWidgetItem(QString::number(p.codigo)));
        tablaProductos->setItem(fila, 1, new QTableWidgetItem(p.nombre));
        tablaProductos->setItem(fila, 2, new QTableWidgetItem(p.categoria));
        tablaProductos->setItem(fila, 3, new QTableWidgetItem(QString::number(p.precio, 'f', 2)));
        tablaProductos->setItem(fila, 4, new QTableWidgetItem(QString::number(p.stock)));
    }
}

int VentanaOrdenes::generarCodigoOrden() const
{
    QVector<Orden> ordenes = cargarOrdenes();

    int maximo = 0;
    for (const Orden &o : ordenes)
        if (o.codOrden > maximo)
            maximo = o.codOrden;

    return maximo + 1;
}

// ---- Comprar (equivale a comprarProducto() de consola) ----
void VentanaOrdenes::comprarProducto()
{
    if (campoCliente->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Dato faltante", "Ingrese el nombre del cliente.");
        return;
    }

    bool ok = false;
    int codigoProducto = campoCodigoProducto->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Dato invalido", "Ingrese un codigo de producto valido.");
        return;
    }

    Producto producto;
    if (!VentanaProductos::obtenerProducto(codigoProducto, producto))
    {
        QMessageBox::warning(this, "No encontrado", "Producto no encontrado.");
        return;
    }

    Orden nueva;
    nueva.codOrden    = generarCodigoOrden();
    nueva.cliente     = campoCliente->text();
    nueva.codProducto = codigoProducto;
    nueva.cantidad    = campoCantidad->value();
    nueva.total       = producto.precio * nueva.cantidad;

    QVector<Orden> ordenes = cargarOrdenes();
    ordenes.append(nueva);
    guardarOrdenes(ordenes);

    QMessageBox::information(this, "Compra registrada",
        QString("Producto: %1\nTotal a pagar: %2\nCodigo de orden: %3")
            .arg(producto.nombre)
            .arg(nueva.total, 0, 'f', 2)
            .arg(nueva.codOrden));

    campoCodigoProducto->clear();
    campoCantidad->setValue(1);
}

// ---- Mostrar mis ordenes (equivale a mostrarOrdenes() de consola) ----
void VentanaOrdenes::mostrarMisOrdenes()
{
    if (campoCliente->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Dato faltante",
                              "Escriba su nombre en el campo 'Nombre del cliente' (pestaña Comprar).");
        return;
    }

    QVector<Orden> ordenes = cargarOrdenes();
    QString nombreBuscado = campoCliente->text();

    tablaOrdenes->setRowCount(0);
    for (const Orden &o : ordenes)
    {
        if (o.cliente == nombreBuscado)
        {
            int fila = tablaOrdenes->rowCount();
            tablaOrdenes->insertRow(fila);
            tablaOrdenes->setItem(fila, 0, new QTableWidgetItem(QString::number(o.codOrden)));
            tablaOrdenes->setItem(fila, 1, new QTableWidgetItem(o.cliente));
            tablaOrdenes->setItem(fila, 2, new QTableWidgetItem(QString::number(o.codProducto)));
            tablaOrdenes->setItem(fila, 3, new QTableWidgetItem(QString::number(o.cantidad)));
            tablaOrdenes->setItem(fila, 4, new QTableWidgetItem(QString::number(o.total, 'f', 2)));
        }
    }

    if (tablaOrdenes->rowCount() == 0)
        QMessageBox::information(this, "Sin resultados", "No tiene ordenes registradas.");
}

// ---- Buscar orden (equivale a buscarOrden() de consola) ----
void VentanaOrdenes::buscarOrden()
{
    bool ok = false;
    int codigo = campoCodigoOrden->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Dato invalido", "Ingrese el codigo de la orden.");
        return;
    }

    QVector<Orden> ordenes = cargarOrdenes();

    for (const Orden &o : ordenes)
    {
        if (o.codOrden == codigo)
        {
            tablaOrdenes->setRowCount(0);
            int fila = tablaOrdenes->rowCount();
            tablaOrdenes->insertRow(fila);
            tablaOrdenes->setItem(fila, 0, new QTableWidgetItem(QString::number(o.codOrden)));
            tablaOrdenes->setItem(fila, 1, new QTableWidgetItem(o.cliente));
            tablaOrdenes->setItem(fila, 2, new QTableWidgetItem(QString::number(o.codProducto)));
            tablaOrdenes->setItem(fila, 3, new QTableWidgetItem(QString::number(o.cantidad)));
            tablaOrdenes->setItem(fila, 4, new QTableWidgetItem(QString::number(o.total, 'f', 2)));

            // precarga el formulario de compra para permitir modificar
            campoCliente->setText(o.cliente);
            campoCodigoProducto->setText(QString::number(o.codProducto));
            campoCantidad->setValue(o.cantidad);
            return;
        }
    }

    QMessageBox::warning(this, "No encontrado", "Orden no encontrada.");
}

// ---- Modificar orden (equivale a modificarOrden() de consola) ----
void VentanaOrdenes::modificarOrden()
{
    bool ok = false;
    int codigo = campoCodigoOrden->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Dato invalido",
                              "Primero busque la orden por codigo.");
        return;
    }

    QVector<Orden> ordenes = cargarOrdenes();

    for (Orden &o : ordenes)
    {
        if (o.codOrden == codigo)
        {
            Producto producto;
            int nuevoCodProducto = campoCodigoProducto->text().toInt();

            if (!VentanaProductos::obtenerProducto(nuevoCodProducto, producto))
            {
                QMessageBox::warning(this, "No encontrado", "Producto no encontrado.");
                return;
            }

            o.cliente     = campoCliente->text();
            o.codProducto = nuevoCodProducto;
            o.cantidad    = campoCantidad->value();
            o.total       = producto.precio * o.cantidad;

            guardarOrdenes(ordenes);
            QMessageBox::information(this, "Listo", "Orden modificada correctamente.");
            buscarOrden();
            return;
        }
    }

    QMessageBox::warning(this, "No encontrado", "Orden no encontrada.");
}

// ---- Eliminar orden (equivale a eliminarOrden() de consola) ----
void VentanaOrdenes::eliminarOrden()
{
    bool ok = false;
    int codigo = campoCodigoOrden->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Dato invalido", "Ingrese el codigo de la orden a eliminar.");
        return;
    }

    QVector<Orden> ordenes = cargarOrdenes();

    for (int i = 0; i < ordenes.size(); ++i)
    {
        if (ordenes.at(i).codOrden == codigo)
        {
            ordenes.removeAt(i);
            guardarOrdenes(ordenes);
            tablaOrdenes->setRowCount(0);
            QMessageBox::information(this, "Listo", "Orden eliminada correctamente.");
            return;
        }
    }

    QMessageBox::warning(this, "No encontrado", "Orden no encontrada.");
}

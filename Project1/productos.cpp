#include <iostream>
#include <fstream>
#include <cstring>
#include "productos.h"
#include "archivos.h"
#include <cstdio>

using namespace std;
/*Menu*/
void menuProductos(){
	
	int seleccion;
	
	do{
		cout<<"========== CRUD DE PRODUCTOS ==========\n";
		cout<<"1. Agregar producto\n";
		cout<<"2. Mostrar productos\n";
		cout<<"3. Buscar producto\n";
		cout<<"4. Modificar producto\n";
		cout<<"5. Eliminar producto\n";
		cout<<"6. Regresar\n";
		cout<<"Seleccione una opción: ";
		cin>>seleccion;
		
		switch (seleccion) {
		case 1:
			agregarProductos();
			break;
		case 2:
			mostrarProductos();
			break;
		case 3:
			buscarProductos();
			break;
		case 4:
			modificarProductos();
			break;
		case 5:
			eliminarProductos();
			break;
		case 6:
			cout<<"SALIENDO...";
			break;
		default:
			cout<<"Ingrese una opcion valida";
			break;
		}
		
	}while(seleccion!=6);
	
}
//Agregar
void agregarProductos(){
	
	Producto producto;
	
	cout << "AGREGAR PRODUCTO " << endl;
	
	cout << "Codigo: ";
	cin >> producto.codigo;
	
	cout << "Nombre: ";
	cin.ignore();
	cin.getline(producto.nombre, 50);
	
	cout << "Categoria: ";
	cin.getline(producto.categoria, 30);
	
	cout << "Precio: ";
	cin >> producto.precio;
	
	cout << "Stock: ";
	cin >> producto.stock;
	
	guardarProducto(producto);
}
//Mostrar
void mostrarProductos(){
	ifstream archivo("productos.txt");
	
	Producto producto;
	
	if(archivo.is_open())
	{
		cout << "===== LISTA DE PRODUCTOS =====" << endl;
		
		while(archivo >> producto.codigo)
		{
			archivo.ignore();
			
			archivo.getline(producto.nombre, 50);
			archivo.getline(producto.categoria, 30);
			
			archivo >> producto.precio;
			archivo >> producto.stock;
			
			cout << "\nCodigo: " << producto.codigo << endl;
			cout << "Nombre: " << producto.nombre << endl;
			cout << "Categoria: " << producto.categoria << endl;
			cout << "Precio: " << producto.precio << endl;
			cout << "Stock: " << producto.stock << endl;
			cout << "----------------------------" << endl;
		}
		
		archivo.close();
	}
	else
	{
		cout << "No se pudo abrir el archivo." << endl;
	}
}
//Buscar
void buscarProductos(){
	ifstream archivo("productos.txt");
	
	Producto producto;
	bool encontrado = false;
	int codigo;
	
	cout << "Ingrese el codigo del producto: ";
	cin >> codigo;
	
	if(archivo.is_open())
	{
		while(archivo >> producto.codigo)
		{
			archivo.ignore();
			
			archivo.getline(producto.nombre, 50);
			archivo.getline(producto.categoria, 30);
			
			archivo >> producto.precio;
			archivo >> producto.stock;
			
			if(producto.codigo == codigo)
			{
				cout << "\n===== PRODUCTO ENCONTRADO =====" << endl;
				cout << "Codigo: " << producto.codigo << endl;
				cout << "Nombre: " << producto.nombre << endl;
				cout << "Categoria: " << producto.categoria << endl;
				cout << "Precio: " << producto.precio << endl;
				cout << "Stock: " << producto.stock << endl;
				
				encontrado = true;
				break;
			}
		}
		
		archivo.close();
		
		if(!encontrado)
		{
			cout << "Producto no encontrado." << endl;
		}
	}
	else
	{
		cout << "Error al abrir el archivo." << endl;
	}
}
//Mostrar
void modificarProductos(){
	ifstream archivo("productos.txt");
	ofstream temporal("temporal.txt");
	
	Producto producto;
	bool encontrado = false;
	int codigo;
	
	cout << "Ingrese el codigo del producto a modificar: ";
	cin >> codigo;
	
	if(archivo.is_open() && temporal.is_open())
	{
		while(archivo >> producto.codigo)
		{
			archivo.ignore();
			
			archivo.getline(producto.nombre, 50);
			archivo.getline(producto.categoria, 30);
			
			archivo >> producto.precio;
			archivo >> producto.stock;
			
			if(producto.codigo == codigo)
			{
				cout << "\n===== MODIFICAR PRODUCTO =====" << endl;
				
				cout << "Nuevo nombre: ";
				cin.ignore();
				cin.getline(producto.nombre, 50);
				
				cout << "Nueva categoria: ";
				cin.getline(producto.categoria, 30);
				
				cout << "Nuevo precio: ";
				cin >> producto.precio;
				
				cout << "Nuevo stock: ";
				cin >> producto.stock;
				
				encontrado = true;
			}
			
			temporal << producto.codigo << endl;
			temporal << producto.nombre << endl;
			temporal << producto.categoria << endl;
			temporal << producto.precio << endl;
			temporal << producto.stock << endl;
		}
		
		archivo.close();
		temporal.close();
		
		remove("productos.txt");
		rename("temporal.txt", "productos.txt");
		
		if(encontrado)
		{
			cout << "Producto modificado correctamente." << endl;
		}
		else
		{
			cout << "Producto no encontrado." << endl;
		}
	}
	else
	{
		cout << "Error al abrir los archivos." << endl;
	}
}
//Eliminar
void eliminarProductos(){
	ifstream archivo("productos.txt");
	ofstream temporal("temporal.txt");
	
	Producto producto;
	bool eliminado = false;
	int codigo;
	
	cout << "Ingrese el codigo del producto a eliminar: ";
	cin >> codigo;
	
	if(archivo.is_open() && temporal.is_open())
	{
		while(archivo >> producto.codigo)
		{
			archivo.ignore();
			
			archivo.getline(producto.nombre, 50);
			archivo.getline(producto.categoria, 30);
			
			archivo >> producto.precio;
			archivo >> producto.stock;
			
			if(producto.codigo == codigo)
			{
				eliminado = true;
				continue;
			}
			
			temporal << producto.codigo << endl;
			temporal << producto.nombre << endl;
			temporal << producto.categoria << endl;
			temporal << producto.precio << endl;
			temporal << producto.stock << endl;
		}
		
		archivo.close();
		temporal.close();
		
		remove("productos.txt");
		rename("temporal.txt", "productos.txt");
		
		if(eliminado)
		{
			cout << "Producto eliminado correctamente." << endl;
		}
		else
		{
			cout << "Producto no encontrado." << endl;
		}
	}
	else
	{
		cout << "Error al abrir los archivos." << endl;
	}
}

#include <iostream>
#include <fstream>
#include "archivos.h"

using namespace std;

void crearArchivoProductos(){
	ofstream archivo("productos.txt");
	
	if(archivo)
	{
		cout << "Archivo de productos listo." << endl;
	}
	else
	{
		cout << "Error al crear el archivo." << endl;
	}
	
	archivo.close();
}

void guardarProducto(Producto p){
	ofstream archivo("productos.txt", ios::app);
	
	if(archivo.is_open())
	{
		archivo << p.codigo << endl;
		archivo << p.nombre << endl;
		archivo << p.categoria << endl;
		archivo << p.precio << endl;
		archivo << p.stock << endl;
		
		archivo.close();
		
		cout << "Producto guardado correctamente." << endl;
	}
	else
	{
		cout << "Error al abrir el archivo." << endl;
	}
}

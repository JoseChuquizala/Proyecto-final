#include <iostream>
#include "login.h"
#include "productos.h"
using namespace std;

int main() {
	
	int opcion;
	
	do{
		cout<<"Bienvenido a EPN.tech\n";
		cout<<"1.Ingresar como empleado\n";
		cout<<"2.Ingresar como cliente\n";
		cout<<"3.Salir\n";
		
		cin>>opcion;
		
		switch (opcion) {
		case 1:
			if (login()) //llama a la funcion login guardada en login.h
			{
				menuProductos();
			}
			else
			{
				cout << "No tiene permiso para ingresar." << endl;
			}
			break;
		case 2:
			//TODO
			break;
		case 3:
			cout<<"Saliendo....";
			break;
		default:
			cout<<"Ingrese una opcion valida";
			break;
		}
		
	}while(opcion !=3);
	
	return 0;
}

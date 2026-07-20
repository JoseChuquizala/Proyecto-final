#include <iostream>
#include "login.h"

using namespace std;

bool login() { //este bool para que retorne verdadero o falso
	
	string	user="user",	
			contrasenia="epn2026",
			usuario,
			clave;
	
	cout<<"Ingresar usaurio: ";
	cin>>usuario;
	
	cout<<"Ingresar clave: ";
	cin>>clave;
	
	  if (usuario == user && clave == contrasenia)
	  {
		  cout << "\nAcceso concedido.\n";
		  return true;
	  }
	else
	{
		cout << "\nAcceso denegado.\n";
		return false;
	}
	
}


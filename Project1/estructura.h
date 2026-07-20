#ifndef	ESTRUCTURA_H /*If Not Defined evitar que el archivo se incluya mas de una vez*/
#define ESTRUCTURA_H /*El compilador ve  que el archivo esta cargado y no lo vuelve a leer*/

using namespace std;

//Datos del productos
struct Producto{
	
	int 	codigo;
	char 	nombre[50];
	char 	categoria[30];
	float 	precio;
	int 	stock;
	
};

//Datos de la orden
struct Orden{
	
	int 	codORDEN;
	char 	cliente[50];
	int 	codProducto;
	int 	cantidad;
	float	total;
};

#endif /*Marca el final del bloque inciaado con #ifndef*/

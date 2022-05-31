#include <iostream>
#include <conio.h>
#include "Metadata.h"

//#include "MapaBits.h"

using namespace std;

int main()
{
	//Metadata::
	
	string comando;
	string comandoUnico;
	int cantidad;
	string nombre;
	int opcion;
	do {
		printf("1- Crear disco\n");
		printf("2- Mostrar Disco\n");
		printf("3- ------------- \n");
		printf("4- ------------- \n");
		printf("5- Salir\n");
		printf("ingrese su opcion:\n");

		scanf_s("%i", &opcion);
		if (opcion == 1)
		{
			cout << "$ ";
			cin >> comandoUnico>>nombre>>cantidad;
			cout << comandoUnico << endl << nombre << endl<< cantidad << endl;
			Metadata test(nombre.c_str(), cantidad);
			test.abrirDisco(nombre.c_str());
			test.guardarDisco();
			test.guardarMapaBits();
			test.read("test.bin");
		}
		else if (opcion == 2)
		{
			//test.abrirDisco("test.bin");
			
		
		}
		else if (opcion == 3)
		{

		}
		else if (opcion == 4)
		{

		}
	} while (opcion != 5);
		return 0;
	
}

	


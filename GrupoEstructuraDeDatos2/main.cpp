#include <stdio.h>
#include <conio.h>
#include<stdlib.h>
#include "Cuentas.h"

//This is just for testing


int main()
{
	Cuentas test;
	int opcion;
	do {
		printf("1- Crear cuenta de cliente\n");
		printf("2- Depositar o retirar\n");
		printf("3- Mostrar cuentas \n");
		printf("4- Mostrar transacciones \n");
		printf("5- Salir del programa\n");
		printf("ingrese su opcion:\n");

		scanf_s("%i", &opcion);
		switch (opcion)
		{
		case 1:
			test.agregarEmpleados();
			break;
		case 2:
			test.actualizarSaldo();
			break;
		case 3:
			test.leer();
			break;
		case 4:
			test.historialTransacciones();
			break;
		}

	} while (opcion != 5);
	return 0;

}
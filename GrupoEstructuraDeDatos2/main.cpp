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
		printf("1- crear cuenta de cliente\n");
		printf("2- depositar o retirar\n");
		printf("3- mostrar cuentas \n");
		printf("4- salir del programa\n");
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
		}

	} while (opcion != 4);
	return 0;

}
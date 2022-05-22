#include <iostream>
#include <conio.h>
#include "Metadata.h"

//#include "MapaBits.h"

using namespace std;
int main()
{
	Metadata test;
	//Metadata::


	char crearDisco[28];
	int opcion;
	do {
		printf("1- Crear disco\n");
		printf("2- Mostrar Disco\n");
		printf("3- ------------- \n");
		printf("4- ------------- \n");
		printf("5- Salir\n");
		printf("ingrese su opcion:\n");

		scanf_s("%i", &opcion);
		switch (opcion)
		{
		case 1:
			/*cout << "$ ";
			cin >> crearDisco;*/
			test.crearDisco();
			test.guardarDisco();
			break;
		case 2:
			test.read("miDiscoA.bin");

			

			break;
		case 3:
			break;
		case 4:
			break;
		}

	} while (opcion != 5);
	return 0;

	//time_t rawtime;
	//struct tm ltm;
	//time(&rawtime);
	//localtime_s(&ltm, &rawtime);
	//std::ostringstream ss;
	//ss << std::put_time(&ltm, "%d%m%Y");
	//std::cout << ss.str() << endl;
   

}

//void convertir()
//{
//
//}
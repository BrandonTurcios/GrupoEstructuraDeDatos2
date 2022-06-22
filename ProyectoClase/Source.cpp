#include <iostream>
#include <conio.h>
using namespace std;
#include "Metadata.h"
int main() 
{
	int opcion = 1, int cantidadDirectorios;
	char tempDirectorio[30] = "undefined",char currentDirectorio[30] = "undefined",char direccion[20],char comando[20],char nombreDisco[20];
	
	std::cout << "$";
	std::cin >> comando >> nombreDisco >> cantidadDirectorios;
	std::cout << comando << endl << nombreDisco << endl << cantidadDirectorios << endl;

	long B1 = (((cantidadDirectorios * 33308) % 8 == 0) ? (cantidadDirectorios * 33308) / 8 : ((cantidadDirectorios * 33308) / 8) + 1);
	long B2 = ((((cantidadDirectorios * 2081) % 8 == 0)) ? (cantidadDirectorios * 2081) / 8 : ((cantidadDirectorios * 2081) / 8) + 1);
	long B3 = (((cantidadDirectorios * 65) % 8 == 0) ? (cantidadDirectorios * 65) / 8 : ((cantidadDirectorios * 65) / 8) + 1);
	long B4 = (((cantidadDirectorios * 1) % 8 == 0) ? (cantidadDirectorios * 1) / 8 : ((cantidadDirectorios * 1) / 8) + 1);
	long Res = B1 + B2 + B3 + B4;

	do {

		if (strcmp(comando, "createdisk") == 0) 
		{
			Metadata test(nombreDisco, cantidadDirectorios);
			test.guardarDisco();
			test.abrirDisco(nombreDisco);
			test.guardarMapaBits();
			test.read(nombreDisco);
		}
		else if (strcmp(comando, "mkdir") == 0) 
		{
			EntradasDirectorio* temp = new EntradasDirectorio(nombreDisco, cantidadDirectorios);
			temp->setMkdir(nombreDisco, Res, direccion, currentDirectorio);
			temp->read(nombreDisco, Res);
			if (strcmp(currentDirectorio, "undefined") == 0) {
				memcpy(currentDirectorio, direccion, strlen(direccion) + 1);
			}
		}
		else if (strcmp(comando, "cd") == 0) {
			if (strcmp(currentDirectorio, "undefined") == 0) {
				std::cout << "ERROR" << endl;
			}
			else {
				EntradasDirectorio* temp = new EntradasDirectorio(nombreDisco, cantidadDirectorios);
				std::cout << "Ingresar nuevo directorio: " << endl;
				if (strcmp(direccion, "..") == 0) {
					if (temp->existe(nombreDisco, Res, tempDirectorio)) {
						memcpy(currentDirectorio, tempDirectorio, strlen(tempDirectorio) + 1);
					}
					else {
						std::cout << "ERROR" << endl;
					}
				}
				else {
					if (temp->existe(nombreDisco, Res, direccion)) {
						memcpy(currentDirectorio, direccion, strlen(direccion) + 1);
					}
					else {
						std::cout << "ERROR" << endl;
					}
				}
			}
		}
		else if (strcmp(comando, "ls") == 0) {
			if (strcmp(currentDirectorio, "undefined") == 0) {
				std::cout << "ERROR Primero debe crear un directorio " << endl;
			}
			else {
				EntradasDirectorio* temp = new EntradasDirectorio(nombreDisco, cantidadDirectorios);

				std::cout << "Informacion: " << currentDirectorio << endl;
				temp->comandoLS(nombreDisco, Res, currentDirectorio);
			}
		}
		std::cout << "$";
		std::cin >> comando >> direccion;
		std::cout << comando << endl << direccion << endl;

	} while (true);


}
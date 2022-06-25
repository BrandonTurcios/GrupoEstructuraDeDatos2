#include <iostream>
#include "Metadata.h"
#include <conio.h>
using namespace std;


int main() {

	int opcion = 1; int cantidadDirectorios;
	char tempDirectorio[30] = "00000"; char currentDirectorio[30] = "00000"; char path[20]; char comandoCadena[20]; char nombreDisco[20];
	
	std::cout << "$	";
	std::cin >> comandoCadena >> nombreDisco >> cantidadDirectorios;

	//obtener valores para mapa bits
	long B1 = (((cantidadDirectorios * 33308) % 8 == 0) ? (cantidadDirectorios * 33308) / 8 : ((cantidadDirectorios * 33308) / 8) + 1);
	long B2 = ((((cantidadDirectorios * 2081) % 8 == 0)) ? (cantidadDirectorios * 2081) / 8 : ((cantidadDirectorios * 2081) / 8) + 1);
	long B3 = (((cantidadDirectorios * 65) % 8 == 0) ? (cantidadDirectorios * 65) / 8 : ((cantidadDirectorios * 65) / 8) + 1);
	long B4 = (((cantidadDirectorios * 1) % 8 == 0) ? (cantidadDirectorios * 1) / 8 : ((cantidadDirectorios * 1) / 8) + 1);
	long totalBloques = B1 + B2 + B3 + B4;


	do {

		if (strcmp(comandoCadena, "createdisk") == 0) 
		{

			Metadata proyectoClase(nombreDisco, cantidadDirectorios);
			proyectoClase.guardarDisco();
			proyectoClase.abrirDisco(nombreDisco);
			proyectoClase.read();
		}
		else if (strcmp(comandoCadena, "mkdir") == 0) 
		{
			EntradasDirectorio* ED = new EntradasDirectorio(nombreDisco, cantidadDirectorios);
			ED->comandoMKDIR(nombreDisco, totalBloques, path, currentDirectorio);
			ED->read(nombreDisco, totalBloques);

			if (strcmp(currentDirectorio, "00000") == 0) 
			{
				memcpy(currentDirectorio, path, strlen(path) + 1);
			}
		}
		else if (strcmp(comandoCadena, "cd") == 0) 
		{
			if (strcmp(currentDirectorio, "00000") == 0) 
			{
				std::cout << "ERROR" << endl;
			}
			else 
			{
				EntradasDirectorio* ED = new EntradasDirectorio(nombreDisco, cantidadDirectorios);
				if (strcmp(path, "..") == 0) 
				{
					if (ED->existe(nombreDisco, totalBloques, tempDirectorio) != -1) 
					{
						memcpy(currentDirectorio, tempDirectorio, strlen(tempDirectorio) + 1);
					}
					else 
					{
						std::cout << "Directorio No Existe!" << endl;
					}
				}
				else 
				{
					if (ED->existe(nombreDisco, totalBloques, path)) 
					{
						memcpy(tempDirectorio, currentDirectorio, strlen(currentDirectorio) + 1);
						memcpy(currentDirectorio, path, strlen(path) + 1);

					}
					else {
						std::cout << "Directorio No Existe!" << endl;
					}
				}
			}
		}
		std::cout << "$	";
		std::cin >> comandoCadena;

		if (strcmp(comandoCadena, "ls") == 0) 
		{
			if (strcmp(currentDirectorio, "00000") == 0) 
			{
				std::cout << "ERROR" << endl;
			}
			else 
			{
				EntradasDirectorio* ED = new EntradasDirectorio(nombreDisco, cantidadDirectorios);
				std::cout << "::::::::::DIRECTORIO:::::::::" << currentDirectorio << endl;
				ED->comandoLS(nombreDisco, totalBloques, currentDirectorio);
			}
		}
		else {
			std::cin >> path;
		}

	} while (true);


}
#include "Metadata.h"

Metadata::Metadata(const char nombre[], const char fecha[], int entradas, unsigned int tamano, int bloquesD, int bloquesI1, int bloquesI2, int bloquesI3): cantidadBloquesDirectos(bloquesD),cantidadBloquesInd1Nivel(bloquesI1),cantidadBloquesInd2Nivel(bloquesI2),cantidadBloquesInd3Nivel(bloquesI3)
{
		memcpy(nombreDisco, nombre, strlen(nombre) + 1);
		memcpy(fechaCreacion, fecha, strlen(fecha) + 1);
}

Metadata::Metadata()
{
}

char* Metadata::toChar()
{
	char* charResult = new char[sizeof(Metadata)];
	memcpy(&charResult[0], &nombreDisco, sizeof(nombreDisco));
	memcpy(&charResult[sizeof(nombreDisco)], fechaCreacion, sizeof(fechaCreacion));
	memcpy(&charResult[sizeof(nombreDisco) + sizeof(fechaCreacion)], &cantidadEntradasDirectorio, sizeof(cantidadEntradasDirectorio));
	memcpy(&charResult[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio)], &tamanoBloque, sizeof(tamanoBloque));
	memcpy(&charResult[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio) + sizeof(tamanoBloque)], &cantidadBloquesDirectos, sizeof(cantidadBloquesDirectos));
	memcpy(&charResult[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio) + sizeof(tamanoBloque) + sizeof(cantidadBloquesDirectos)], &cantidadBloquesInd1Nivel, sizeof(cantidadBloquesInd1Nivel));
	memcpy(&charResult[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio) + sizeof(tamanoBloque) + sizeof(cantidadBloquesDirectos) + sizeof(cantidadBloquesInd1Nivel)], &cantidadBloquesInd2Nivel, sizeof(cantidadBloquesInd2Nivel));
	memcpy(&charResult[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio) + sizeof(tamanoBloque) + sizeof(cantidadBloquesDirectos) + sizeof(cantidadBloquesInd1Nivel) + sizeof(cantidadBloquesInd3Nivel)], &tamanoBloque, sizeof(cantidadBloquesInd3Nivel));

	return charResult;

}

void Metadata::fromChar(char* readChar)
{
	memcpy(&nombreDisco, &readChar[0], sizeof(nombreDisco));
	memcpy(fechaCreacion, &readChar[sizeof(nombreDisco)], sizeof(fechaCreacion));
	memcpy(&cantidadEntradasDirectorio, &readChar[sizeof(nombreDisco) + sizeof(fechaCreacion)], sizeof(cantidadEntradasDirectorio));
	memcpy(&tamanoBloque, &readChar[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio)], sizeof(tamanoBloque));
	memcpy(&cantidadBloquesDirectos, &readChar[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio) + sizeof(tamanoBloque)], sizeof(cantidadBloquesDirectos));
	memcpy(&cantidadBloquesInd1Nivel, &readChar[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio) + sizeof(tamanoBloque) + sizeof(cantidadBloquesDirectos)], sizeof(cantidadBloquesInd1Nivel));
	memcpy(&cantidadBloquesInd2Nivel, &readChar[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio) + sizeof(tamanoBloque) + sizeof(cantidadBloquesDirectos) + sizeof(cantidadBloquesInd1Nivel)], sizeof(cantidadBloquesInd2Nivel));
	memcpy(&cantidadBloquesInd3Nivel, &readChar[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio) + sizeof(tamanoBloque) + sizeof(cantidadBloquesDirectos) + sizeof(cantidadBloquesInd1Nivel) + sizeof(cantidadBloquesInd2Nivel)], sizeof(cantidadBloquesInd3Nivel));
}

void Metadata::crearDisco()
{
	file = new DataFile("miDisco.bin");
}

void Metadata::guardarDisco()
{
	file->open("w");
	Metadata* newname = new Metadata("miDisco.bin","18/12/21",100,100,123 ,1,2,3);
	file->write(newname->toChar(), 0, newname->getSizeOf());

	//Metadata* newname = new Metadata("test.bin","18/12/21",100,405540,123 ,1,2,3);
	//file->write(newname->toChar(), newname->getSizeOf(), newname->getSizeOf());

	/*newname = new Employee(102, "Miguel Alvarado", 1500);;
	file->write(newname->toChar(), newname->getSizeOf() * 2, newname->getSizeOf());*/
	file->close();
}

int Metadata::getSizeOf()
{
	return sizeof(Metadata);
}

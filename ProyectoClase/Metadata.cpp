#include "Metadata.h"

Metadata::Metadata(const char nombre[], int entradas): cantidadEntradasDirectorio(entradas),tamanoBloque(4096),cantidadBloquesDirectos(33308*entradas),cantidadBloquesInd1Nivel(2081 *entradas),cantidadBloquesInd2Nivel(65*entradas),cantidadBloquesInd3Nivel(entradas)
{
		const char* fecha = "15052022";
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
	memcpy(&charResult[sizeof(nombreDisco) + sizeof(fechaCreacion) + sizeof(cantidadEntradasDirectorio) + sizeof(tamanoBloque) + sizeof(cantidadBloquesDirectos) + sizeof(cantidadBloquesInd1Nivel) + sizeof(cantidadBloquesInd3Nivel)], &cantidadBloquesInd3Nivel, sizeof(cantidadBloquesInd3Nivel));

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
	file = new DataFile("miDiscoA.bin");
}

void Metadata::guardarDisco()
{
	file->open("w");
	Metadata* newname = new Metadata("miDiscoA.bin",8);
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

void Metadata::read(const char* _nombre)
{
	Metadata* toFind = new Metadata();
	int CurrentPosition = 0;
	file->open("r");
	toFind->fromChar(file->read(CurrentPosition, toFind->getSizeOf()));
	bool found = false;
	CurrentPosition += toFind->getSizeOf();
	while (!file->isEOF())
	{

		//strcmp(toFind->getNombre(), _nombre) == 0
		if (strcmp(toFind->getNombre(), _nombre) == 0)
		{
			toFind->print();
			found = true;
			break;
		}
		toFind->fromChar(file->read(CurrentPosition, toFind->getSizeOf()));
		CurrentPosition += toFind->getSizeOf();

	}
	if (!found)
		cout << "Not found";

	file->close();
}

void Metadata::print()
{
	cout << "Disco{ nombre:" << nombreDisco << ", fecha:" << fechaCreacion << " cantidad:" << cantidadEntradasDirectorio << " tamano:" << tamanoBloque << " bloqueD:" << cantidadBloquesDirectos << " bloqueI1:" << cantidadBloquesInd1Nivel << " bloqueI2:" << cantidadBloquesInd2Nivel << " bloqueI3:" << cantidadBloquesInd3Nivel << "}\n";
}

const char* Metadata::getNombre()
{
	return nombreDisco;
}



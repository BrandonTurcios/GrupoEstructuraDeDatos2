#include "Metadata.h"


Metadata::Metadata(const char nombre[], int entradas): cantidadEntradasDirectorio(entradas),tamanoBloque(4096),cantidadBloquesDirectos(33308*entradas),cantidadBloquesInd1Nivel(2081 *entradas),cantidadBloquesInd2Nivel(65*entradas),cantidadBloquesInd3Nivel(entradas)
{
		abrirDisco(nombre);
		const char* fecha;
		std::string fecha_;
		time_t rawtime;
		struct tm ltm;
		time(&rawtime);
		localtime_s(&ltm, &rawtime);
		std::ostringstream ss;
		ss << std::put_time(&ltm, "%d%m%Y");
		fecha_ = ss.str();
		fecha = fecha_.c_str();

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

void Metadata::abrirDisco(const char nombre[20])
{
	file = new DataFile(nombre);
	
}

void Metadata::guardarDisco()
{
	file->open("w");

	Metadata* newone = new Metadata(nombreDisco,cantidadEntradasDirectorio);
	file->write(newone->toChar(), 0, newone->getSizeOf());
	file->close();
}

void Metadata::guardarMapaBits()
{
	MapaBits* mapa = new MapaBits(nombreDisco,cantidadBloquesDirectos, cantidadBloquesInd1Nivel, cantidadBloquesInd2Nivel, cantidadBloquesInd3Nivel);
	mapa->establecerMapaBits(nombreDisco);
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

	MapaBits* mapa = new MapaBits(nombreDisco);
	mapa->leerMapaBits(nombreDisco,cantidadBloquesDirectos, cantidadBloquesInd1Nivel, cantidadBloquesInd2Nivel, cantidadBloquesInd3Nivel);

	file->close();
}

void Metadata::print()
{
	cout << "Metadata{ nombre:" << nombreDisco << ", fecha:" << fechaCreacion << " cantidad:" << cantidadEntradasDirectorio << " tamano:" << tamanoBloque << " bloqueD:" << cantidadBloquesDirectos << " bloqueI1:" << cantidadBloquesInd1Nivel << " bloqueI2:" << cantidadBloquesInd2Nivel << " bloqueI3:" << cantidadBloquesInd3Nivel << "}\n";
}

const char* Metadata::getNombre()
{
	return nombreDisco;
}

//--------------------------------------------------------------------------------------------
MapaBits::MapaBits_BD::MapaBits_BD()
{
}

MapaBits::MapaBits_BD::MapaBits_BD(int numeroBloquesDirectos)
{
	ptrs = new char[numeroBloquesDirectos + 1];
	for (int i = 0; i < numeroBloquesDirectos; i++)
	{
		ptrs[i] = '0';
	}
	ptrs[numeroBloquesDirectos] = '\0';

}

void MapaBits::MapaBits_BD::fromChar(char* readChar)
{

	ptrs = readChar;

}

char* MapaBits::MapaBits_BD::toChar()
{
	return ptrs;
}

// -----------------------------------------------------------------
MapaBits::MapaBits_BI1::MapaBits_BI1()
{
}

MapaBits::MapaBits_BI1::MapaBits_BI1(int numeroBloquesIndirectos1)
{
	ptrs = new char[numeroBloquesIndirectos1 + 1];
	for (int i = 0; i < numeroBloquesIndirectos1; i++)
	{
		ptrs[i] = '0';
	}
	ptrs[numeroBloquesIndirectos1] = '\0';
}

void MapaBits::MapaBits_BI1::fromChar(char* readChar)
{
	ptrs = readChar;
}

char* MapaBits::MapaBits_BI1::toChar()
{
	return ptrs;
}

//------------------------------------------------------------------
MapaBits::MapaBits_BI2::MapaBits_BI2()
{
}

MapaBits::MapaBits_BI2::MapaBits_BI2(int nBloquesBI2)
{
	ptrs = new char[nBloquesBI2 + 1];
	for (int i = 0; i < nBloquesBI2; i++)
	{
		ptrs[i] = '0';
	}
	ptrs[nBloquesBI2] = '\0';
}

void MapaBits::MapaBits_BI2::fromChar(char* readChar)
{
	ptrs = readChar;
}

char* MapaBits::MapaBits_BI2::toChar()
{
	return ptrs;
}

//------------------------------------------------------------------

MapaBits::MapaBits_BI3::MapaBits_BI3()
{
}

MapaBits::MapaBits_BI3::MapaBits_BI3(int numeroBloquesIndirectos3)
{
	ptrs = new char[numeroBloquesIndirectos3 + 1];
	for (int i = 0; i < numeroBloquesIndirectos3; i++)
	{
		ptrs[i] = '0';
	}
	ptrs[numeroBloquesIndirectos3] = '\0';
}

void MapaBits::MapaBits_BI3::fromChar(char* readChar)
{
	ptrs = readChar;
}

char* MapaBits::MapaBits_BI3::toChar()
{
	return ptrs;
}

//----------------------------------------------------------------------

MapaBits::MapaBits(char nombre[20],int numBloquesDirectos, int numBloquesIndirectos1, int numeroBloquesIndirectos2, int numeroBloquesIndirectos3) : bloque1(((numBloquesDirectos / 8) % 2 == 0) ? numBloquesDirectos / 8 : numBloquesDirectos / 8 + 1), bloque2(((numBloquesIndirectos1 / 8) % 2 == 0) ? numBloquesIndirectos1 / 8 : numBloquesIndirectos1 / 8 + 1), bloque3(((numeroBloquesIndirectos2 / 8) % 2 == 0) ? numeroBloquesIndirectos2 / 8 : numeroBloquesIndirectos2 / 8 + 1), bloque4(((numeroBloquesIndirectos3 / 8) % 2 == 0) ? numeroBloquesIndirectos3 / 8 : numeroBloquesIndirectos3 / 8 + 1)
{
	file = new DataFile(nombre);

	MapaBits_BD* bloqueDirecto = new MapaBits_BD(bloque1);
	MapaBits_BI1* bloqueI1 = new MapaBits_BI1(bloque2);

	MapaBits_BI2* bloqueI2 = new MapaBits_BI2(bloque3);
	MapaBits_BI3* bloqueI3 = new MapaBits_BI3(bloque4);
	char* charResult = new char[sizeof(Metadata)];

	ptrsCombinados = new char[bloque1 + bloque2 + bloque3 + bloque4 + 1];

	memcpy(&ptrsCombinados[0], (bloqueDirecto->toChar()), bloque1);
	memcpy(&ptrsCombinados[bloque1], bloqueI1->toChar(), bloque2);
	memcpy(&ptrsCombinados[bloque1 + bloque2], bloqueI2->toChar(), bloque3);
	memcpy(&ptrsCombinados[bloque1 + bloque2 + bloque3], bloqueI3->toChar(), bloque4 + 1);

	ptrsCombinados[bloque1 + bloque2 + bloque3 + bloque4] = '\0';
}

MapaBits::MapaBits(char nombre[20])
{
	file = new DataFile(nombre);

	ptrsCombinados = new char[bloque1 + bloque2 + bloque3 + bloque4 + 1];
}

void MapaBits::leerMapaBits(char nombre[20],int MBD, int MBI1, int MBI2, int MBI3)
{
	int currentPosition = sizeof(Metadata);
	file->open("r");

	MapaBits* toFind = new MapaBits(nombre);

	toFind->bloque1 = (((MBD / 8) % 2 == 0) ? MBD / 8 : MBD / 8 + 1);
	toFind->bloque2 = (((MBI1 / 8) % 2 == 0) ? MBI1 / 8 : MBI1 / 8 + 1);
	toFind->bloque3 = (((MBI2 / 8) % 2 == 0) ? MBI2 / 8 : MBI2 / 8 + 1);
	toFind->bloque4 = (((MBI3 / 8) % 2 == 0) ? MBI3 / 8 : MBI3 / 8 + 1);

	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
	currentPosition += sizeof(Metadata);
	bool Found= false;

	while (!file->isEOF()) {


		toFind->printMapa();
		Found = true;
		break;
		toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
		currentPosition += toFind->getSizeOf();
	}

	if (!Found) {
		cout << "Employee not found" << endl;
	}
	file->close();
}

void MapaBits::printMapa()
{
	cout << "Mapa { " << ptrsCombinados << "}"<<endl;
}

void MapaBits::establecerMapaBits(char nombre[20])
{ 
	file->open("w");

	MapaBits* newone = new MapaBits(nombre,bloque1 * 8, bloque2 * 8, bloque3 * 8, bloque4 * 8);

	file->write(newone->toChar(), sizeof(Metadata), newone->getSizeOf());
	file->close();
}

char* MapaBits::toChar()
{
	return ptrsCombinados;
}

void MapaBits::fromChar(char* _ptrsCombinados)
{
	ptrsCombinados = _ptrsCombinados;
	ptrsCombinados[getSizeOf()] = '\0';
}

int MapaBits::getSizeOf()
{
	return (bloque1 + bloque2 + bloque3 + bloque4);
}

#include "Metadata.h"


Metadata::Metadata(const char nombre[], int entradas): cantidadEntradasDirectorio(entradas),tamanoBloque(4096),cantidadBloquesDirectos(33308*entradas),cantidadBloquesInd1Nivel(2081 *entradas),cantidadBloquesInd2Nivel(65*entradas),cantidadBloquesInd3Nivel(entradas)
{
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
	cout << "Metada{ nombre:" << nombreDisco << ", fecha:" << fechaCreacion << " cantidad:" << cantidadEntradasDirectorio << " tamano:" << tamanoBloque << " bloqueD:" << cantidadBloquesDirectos << " bloqueI1:" << cantidadBloquesInd1Nivel << " bloqueI2:" << cantidadBloquesInd2Nivel << " bloqueI3:" << cantidadBloquesInd3Nivel << "}\n";
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

void MapaBits::MapaBits_BI1::fromChar(char* _mb)
{
	ptrs = _mb;
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

void MapaBits::MapaBits_BI2::fromChar(char* _mb)
{
	ptrs = _mb;
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

void MapaBits::MapaBits_BI3::fromChar(char* _meb)
{
	ptrs = _meb;
}

char* MapaBits::MapaBits_BI3::toChar()
{
	return ptrs;
}


//----------------------------------------------------------------------

MapaBits::MapaBits(int numBloquesDirectos, int numBloquesIndirectos1, int numeroBloquesIndirectos2, int numeroBloquesIndirectos3) : B1(((numBloquesDirectos / 8) % 2 == 0) ? numBloquesDirectos / 8 : numBloquesDirectos / 8 + 1), B2(((numBloquesIndirectos1 / 8) % 2 == 0) ? numBloquesIndirectos1 / 8 : numBloquesIndirectos1 / 8 + 1), B3(((numeroBloquesIndirectos2 / 8) % 2 == 0) ? numeroBloquesIndirectos2 / 8 : numeroBloquesIndirectos2 / 8 + 1), B4(((numeroBloquesIndirectos3 / 8) % 2 == 0) ? numeroBloquesIndirectos3 / 8 : numeroBloquesIndirectos3 / 8 + 1)
{


	file = new DataFile("miDiscoA.bin");

	MapaBits_BD* BD = new MapaBits_BD(B1);
	MapaBits_BI1* BI1 = new MapaBits_BI1(B2);

	MapaBits_BI2* BI2 = new MapaBits_BI2(B3);
	MapaBits_BI3* BI3 = new MapaBits_BI3(B4);
	char* charResult = new char[sizeof(Metadata)];

	ptrsCompleto = new char[B1 + B2 + B3 + B4 + 1];

	memcpy(&ptrsCompleto[0], (BD->toChar()), B1);
	memcpy(&ptrsCompleto[B1], BI1->toChar(), B2);
	memcpy(&ptrsCompleto[B1 + B2], BI2->toChar(), B3);
	memcpy(&ptrsCompleto[B1 + B2 + B3], BI3->toChar(), B4 + 1);

	ptrsCompleto[B1 + B2 + B3 + B4] = '\0';
}

void MapaBits::LeerMapaBits(int MBD, int MBI1, int MBI2, int MBI3)
{
	cout << "Test Lectura" << endl;

	int currentPosition = sizeof(Metadata);



	file->open("R");

	MapaBits* toFind = new MapaBits();

	toFind->B1 = (((MBD / 8) % 2 == 0) ? MBD / 8 : MBD / 8 + 1);

	toFind->B2 = (((MBI1 / 8) % 2 == 0) ? MBI1 / 8 : MBI1 / 8 + 1);
	toFind->B3 = (((MBI2 / 8) % 2 == 0) ? MBI2 / 8 : MBI2 / 8 + 1);
	toFind->B4 = (((MBI3 / 8) % 2 == 0) ? MBI3 / 8 : MBI3 / 8 + 1);

	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
	currentPosition += sizeof(Metadata);
	bool Founded = false;

	while (!file->isEOF()) {


		toFind->imprimirMapaBits();
		Founded = true;
		break;
		toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
		currentPosition += toFind->getSizeOf();
	}

	if (!Founded) {
		cout << "Employee not found" << endl;
	}
	file->close();
}

MapaBits::MapaBits() {
	file = new DataFile("miDiscoA.bin");

	ptrsCompleto = new char[B1 + B2 + B3 + B4 + 1];
}

void MapaBits::GuardarMapaBits()
{
	file->open("W");

	MapaBits* newone = new MapaBits(B1 * 8, B2 * 8, B3 * 8, B4 * 8);

	file->write(newone->toChar(), sizeof(Metadata), newone->getSizeOf());
	file->close();
}

void MapaBits::imprimirMapaBits()
{
	cout << ptrsCompleto << endl;
}

int MapaBits::getSizeOf()
{
	return (B1 + B2 + B3 + B4);
}

char* MapaBits::toChar()
{
	return ptrsCompleto;
}

void MapaBits::fromChar(char* _ptrsCompleto)
{
	ptrsCompleto = _ptrsCompleto;
	ptrsCompleto[getSizeOf()] = '\0';
}

#include "Metadata.h"

Metadata::Metadata(char nombre[20], int entradas) : cantidadEntradasDirectorio(entradas), tamanoBloque(4096), cantidadBloquesDirectos(33308 * entradas), cantidadBloquesInd1Nivel(2081 * entradas), cantidadBloquesInd2Nivel(65 * entradas), cantidadBloquesInd3Nivel(entradas)
{
	file = new DataFile(nombre);
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
	memcpy(nombreDisco, "undefined", strlen("undefined") + 1);
	memcpy(fechaCreacion, "00000000", strlen("00000000")+1);
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

void Metadata::abrirDisco(char nombre[20])
{
	MapaBits* MB = new MapaBits(nombre, cantidadBloquesDirectos, cantidadBloquesInd1Nivel, cantidadBloquesInd2Nivel, cantidadBloquesInd3Nivel);
	MB->establecerMapaBits(nombre);

	long B1 = (((cantidadBloquesDirectos) % 8 == 0) ? cantidadBloquesDirectos / 8 : cantidadBloquesDirectos / 8 + 1);
	long B2 = (((cantidadBloquesInd1Nivel) % 8 == 0) ? cantidadBloquesInd1Nivel / 8 : cantidadBloquesInd1Nivel / 8 + 1);
	long B3 = (((cantidadBloquesInd2Nivel) % 8 == 0) ? cantidadBloquesInd2Nivel / 8 : cantidadBloquesInd2Nivel / 8 + 1);
	long B4 = (((cantidadBloquesInd3Nivel) % 8 == 0) ? cantidadBloquesInd3Nivel / 8 : cantidadBloquesInd3Nivel / 8 + 1);

	EntradasDirectorio* ED = new EntradasDirectorio(nombre, cantidadEntradasDirectorio);
	long Res = B1 + B2 + B3 + B4;
	ED->write(nombre, Res);
	ED->read(nombre, Res);

	BloqueDirecto* BD = new BloqueDirecto(cantidadBloquesDirectos, nombre, Res, cantidadEntradasDirectorio);
	BloqueInd1Nivel* B1N = new BloqueInd1Nivel(nombre, cantidadEntradasDirectorio, Res);
	BloqueInd2Nivel* B2N = new BloqueInd2Nivel(nombre, cantidadEntradasDirectorio, Res);
	BloqueInd3Nivel* B3N = new BloqueInd3Nivel(nombre, cantidadEntradasDirectorio, Res);

}

void Metadata::guardarDisco()
{
	file->open("w");

	Metadata* newone = new Metadata(nombreDisco, cantidadEntradasDirectorio);
	file->write(newone->toChar(), 0, newone->getSizeOf());
	file->close();
}

int Metadata::getSizeOf()
{
	return sizeof(Metadata);
}

void Metadata::read()
{
	file->open("r");
	int currentPosition = 0;
	Metadata* toFind = new Metadata();

	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
	currentPosition += toFind->getSizeOf();
	bool Founded = false;

	while (!file->isEOF()) {

		toFind->print();
		Founded = true;
		break;

		toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
		currentPosition += toFind->getSizeOf();

	}

	if (!Founded) {
		cout << "Not Founded!" << endl;
	}


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
		ptrs[i] = 0;
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
		ptrs[i] = 0;
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
		ptrs[i] = 0;
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
		ptrs[i] = 0;
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

MapaBits::MapaBits(char nombre[20], int numBloquesDirectos, int numBloquesIndirectos1, int numeroBloquesIndirectos2, int numeroBloquesIndirectos3) : bloque1(((numBloquesDirectos / 8) % 2 == 0) ? numBloquesDirectos / 8 : numBloquesDirectos / 8 + 1), bloque2(((numBloquesIndirectos1 / 8) % 2 == 0) ? numBloquesIndirectos1 / 8 : numBloquesIndirectos1 / 8 + 1), bloque3(((numeroBloquesIndirectos2 / 8) % 2 == 0) ? numeroBloquesIndirectos2 / 8 : numeroBloquesIndirectos2 / 8 + 1), bloque4(((numeroBloquesIndirectos3 / 8) % 2 == 0) ? numeroBloquesIndirectos3 / 8 : numeroBloquesIndirectos3 / 8 + 1)
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

char* MapaBits::leerMapaBits(char nombre[20], int MBD, int MBI1, int MBI2, int MBI3)
{
	int currentPosition = sizeof(Metadata);
	file = new DataFile(nombre);
	file->open("r");
	MapaBits* toFind = new MapaBits(nombre);
	toFind->bloque1 = (((MBD / 8) % 2 == 0) ? MBD / 8 : MBD / 8 + 1);
	toFind->bloque2 = (((MBI1 / 8) % 2 == 0) ? MBI1 / 8 : MBI1 / 8 + 1);
	toFind->bloque3 = (((MBI2 / 8) % 2 == 0) ? MBI2 / 8 : MBI2 / 8 + 1);
	toFind->bloque4 = (((MBI3 / 8) % 2 == 0) ? MBI3 / 8 : MBI3 / 8 + 1);

	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
	currentPosition += sizeof(Metadata);
	bool Found = false;

	while (!file->isEOF()) 
	{
		for (int i = 0; i < toFind->bloque1; i++) 
		{
			char tmpByte;
			tmpByte = toFind->ptrsCombinados[i];

			for (int j = 1; j <= 8; j++) {
				cout << (tmpByte & (1 << 7) ? '1' : '0');
				tmpByte = tmpByte << 1;

			}

			cout << " ";

		}
		cout << " " << endl;

		for (int i = toFind->bloque1; i < toFind->bloque2 + toFind->bloque1; i++) {

			char tmpByte;
			tmpByte = toFind->ptrsCombinados[i];


			for (int j = 1; j <= 8; j++) 
			{
				cout << (tmpByte & (1 << 7) ? '1' : '0');
				tmpByte = tmpByte << 1;

			}
			cout << " ";
		}

		return toFind->ptrsCombinados;
		toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
		currentPosition += toFind->getSizeOf();
	}

	file->close();
	return NULL;
}

void MapaBits::printMapa()
{
	cout << "MapaBits { " << ptrsCombinados << "}" << endl;
}

void MapaBits::encender(int bloque)
{
	int posicion = bloque / 8;
	int inicio = posicion + 8;

	for (int i = inicio, shift = 7; i < inicio + 8; i++, shift--) 
	{
		if (bloque == i) 
		{
			ptrsCombinados[posicion] |= (1 << shift);
			break;
		}
	}
}

void MapaBits::apagar(char nombre[20], int bloque)
{
	ptrsCombinados = new char[bloque1 + bloque2 + bloque3 + bloque4 + 1];
	memcpy(&ptrsCombinados[0], leerMapaBits(nombre, bloque1 * 8, bloque2 * 8, bloque3 * 8, bloque4 * 8), bloque1 + bloque2 + bloque3 + bloque4 + 1);
	int posicion = bloque / 8;
	int inicio = posicion + 8;
	for (int i =inicio, shift = 7; i < inicio + 8; i++, shift--) 
	{
		if (bloque == i) 
		{
			ptrsCombinados[posicion] = ptrsCombinados[posicion] & ~(1 << shift);
			establecerMapaBits(nombre);
			break;
		}


	}
}

void MapaBits::establecerMapaBits(char nombre[20])
{
	file->open("w");
	MapaBits* newMB = new MapaBits(nombre, bloque1 * 8, bloque2 * 8, bloque3 * 8, bloque4 * 8);
	file->write(newMB->toChar(), sizeof(Metadata), newMB->getSizeOf());
	file->close();
}

int MapaBits::check(char byte, int bloque)
{
	int total = bloque % 8 == 0 ? (bloque / 8) + 1 : (bloque / 8) + 1;
	for (int j = 0; j <= 7; j++) {

		if ((8 - (total * 8 - bloque)) == j) {
			return (byte & (1 << 7) ? 1 : 0);
		}
		byte= byte << 1;
	}
	return -1;
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

//_____________________________________________

EntradasDirectorio::EntradasDirectorio(char nombre[20], int _cantidadEntradas) :nEntradasDirectorio(_cantidadEntradas)
{
	file = new DataFile(nombre);
	listaEntradas = new Entrada[nEntradasDirectorio];
}

void EntradasDirectorio::print()
{
	for (int i = 0; i < nEntradasDirectorio; i++)
	{
		
		cout << "nombreEntrada: " << listaEntradas[i].nombreEntrada << endl;
		cout << "esArchivo: " << listaEntradas[i].esArchivo << endl;
		cout << "tamanio: " << listaEntradas[i].tamanio << endl;
		cout << "fechaCreacion: " << listaEntradas[i].fechaCreacion << endl;
		cout << "indPadre: " << listaEntradas[i].indPadre << endl;
		cout << "indHijo: " << listaEntradas[i].indPrimerHijo << endl;
		cout << "indHermanoDerecho: " << listaEntradas[i].indHermanoDerecho << endl;


	}
}

int EntradasDirectorio::getSizeOf()
{
	return 109 * nEntradasDirectorio;
}

char* EntradasDirectorio::toChar()
{
	char* charResult = new char[109 * nEntradasDirectorio];
	long pointer = 0;
	for (int i = 0; i < nEntradasDirectorio; i++) {

		memcpy(&charResult[pointer], listaEntradas[i].nombreEntrada, sizeof(listaEntradas[i].nombreEntrada));
		memcpy(&charResult[pointer + sizeof(listaEntradas[i].nombreEntrada)], &listaEntradas[i].esArchivo, sizeof(listaEntradas[i].esArchivo));
		memcpy(&charResult[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo)], &listaEntradas[i].tamanio, sizeof(listaEntradas[i].tamanio));
		memcpy(&charResult[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio)], &listaEntradas[i].indPadre, sizeof(listaEntradas[i].indPadre));
		memcpy(&charResult[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre)], &listaEntradas[i].indPrimerHijo, sizeof(listaEntradas[i].indPrimerHijo));
		memcpy(&charResult[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo)], &listaEntradas[i].indHermanoDerecho, sizeof(listaEntradas[i].indHermanoDerecho));
		memcpy(&charResult[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo) + sizeof(listaEntradas[i].indHermanoDerecho)], listaEntradas[i].fechaCreacion, sizeof(listaEntradas[i].fechaCreacion));
		memcpy(&charResult[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo) + sizeof(listaEntradas[i].indHermanoDerecho) + sizeof(listaEntradas[i].fechaCreacion)], listaEntradas[i].ptrsBD, sizeof(listaEntradas[i].ptrsBD));
		memcpy(&charResult[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo) + sizeof(listaEntradas[i].indHermanoDerecho) + sizeof(listaEntradas[i].fechaCreacion) + sizeof(listaEntradas[i].ptrsBD)], listaEntradas[i].ptrsBDI, sizeof(listaEntradas[i].ptrsBDI));

		pointer += sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo) + sizeof(listaEntradas[i].indHermanoDerecho) + sizeof(listaEntradas[i].fechaCreacion) + sizeof(listaEntradas[i].fechaCreacion) + sizeof(listaEntradas[i].ptrsBDI);
	}
	return charResult;

}

void EntradasDirectorio::fromChar(char* charRead)
{
	long pointer = 0;
	for (int i = 0; i < nEntradasDirectorio; i++) 
	{
		memcpy(listaEntradas[i].nombreEntrada, &charRead[pointer], sizeof(listaEntradas[i].nombreEntrada));
		memcpy(&listaEntradas[i].esArchivo, &charRead[pointer + sizeof(listaEntradas[i].nombreEntrada)], sizeof(listaEntradas[i].esArchivo));
		memcpy(&listaEntradas[i].tamanio, &charRead[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo)], sizeof(listaEntradas[i].tamanio));
		memcpy(&listaEntradas[i].indPadre, &charRead[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio)], sizeof(listaEntradas[i].indPadre));
		memcpy(&listaEntradas[i].indPrimerHijo, &charRead[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre)], sizeof(listaEntradas[i].indPrimerHijo));
		memcpy(&listaEntradas[i].indHermanoDerecho, &charRead[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo)], sizeof(listaEntradas[i].indHermanoDerecho));
		memcpy(listaEntradas[i].fechaCreacion, &charRead[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo) + sizeof(listaEntradas[i].indHermanoDerecho)], sizeof(listaEntradas[i].fechaCreacion));
		memcpy(listaEntradas[i].ptrsBD, &charRead[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo) + sizeof(listaEntradas[i].indHermanoDerecho) + sizeof(listaEntradas[i].fechaCreacion)], sizeof(listaEntradas[i].ptrsBD));
		memcpy(listaEntradas[i].ptrsBDI, &charRead[pointer + sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo) + sizeof(listaEntradas[i].indHermanoDerecho) + sizeof(listaEntradas[i].fechaCreacion) + sizeof(listaEntradas[i].ptrsBD)], sizeof(listaEntradas[i].ptrsBDI));
		pointer += sizeof(listaEntradas[i].nombreEntrada) + sizeof(listaEntradas[i].esArchivo) + sizeof(listaEntradas[i].tamanio) + sizeof(listaEntradas[i].indPadre) + sizeof(listaEntradas[i].indPrimerHijo) + sizeof(listaEntradas[i].indHermanoDerecho) + sizeof(listaEntradas[i].fechaCreacion) + sizeof(listaEntradas[i].fechaCreacion) + sizeof(listaEntradas[i].ptrsBDI);


	}

}

void EntradasDirectorio::comandoMKDIR(char nombre[20], long mapaBits, char directorio[30], char currentDirectorio[30])
{
	file->open("rw");
	int currentPosition = sizeof(Metadata) + mapaBits;
	EntradasDirectorio* toFind = new EntradasDirectorio(nombre, nEntradasDirectorio);
	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
	short int padreTemporal = -1;
	short int primerHijoTemporal = -1;
	short int hermanoIzquierdoTemporal = -1;

	for (int i = 0; i < nEntradasDirectorio; i++)
	{

		if (strcmp(toFind->listaEntradas[i].nombreEntrada, currentDirectorio))
		{
			padreTemporal = i;



		}
		else if (toFind->listaEntradas[i].indPadre != -1 && ((strcmp(toFind->listaEntradas[toFind->listaEntradas[i].indPadre].nombreEntrada, currentDirectorio) == 0) && (toFind->listaEntradas[i].indHermanoDerecho == -1)))
		{
			padreTemporal = i;
		}


	}

		for (int i = 0; i < nEntradasDirectorio; i++)
		{

			if (strcmp(toFind->listaEntradas[i].nombreEntrada, "Indefinido") == 0) {


				memcpy(toFind->listaEntradas[i].nombreEntrada, directorio, strlen(directorio) + 1);

				toFind->listaEntradas[i].indPadre = padreTemporal;
				toFind->listaEntradas[i].indPrimerHijo = primerHijoTemporal;


				if (hermanoIzquierdoTemporal != -1) {
					toFind->listaEntradas[hermanoIzquierdoTemporal].indHermanoDerecho = i;
				}
				if ((padreTemporal >= 0 && toFind->listaEntradas[padreTemporal].indPrimerHijo == -1)) {
					toFind->listaEntradas[padreTemporal].indPrimerHijo = i;
				}


				time_t rawtime;
				struct tm ltm;
				time(&rawtime);
				localtime_s(&ltm, &rawtime);
				std::ostringstream ss;
				ss << std::put_time(&ltm, "%d%m%Y");
				memcpy(toFind->listaEntradas[i].fechaCreacion, ss.str().c_str(), strlen(ss.str().c_str()));
				file->write(toFind->toChar(), sizeof(Metadata) + mapaBits, toFind->getSizeOf());

				//	toFind->print();
				file->close();
				return;

			}

		}

		file->close();
	}

void EntradasDirectorio::write(char nombre[20], long mapaBits)
{
	file->open("w");
	EntradasDirectorio* newED = new EntradasDirectorio(nombre, nEntradasDirectorio);
	file->write(newED->toChar(), sizeof(Metadata) + mapaBits, newED->getSizeOf());
	file->close();

}

void EntradasDirectorio::read(char nombre[20], long mapaBits)
{
	file->open("r");
	int currentPosition = sizeof(Metadata) + mapaBits;

	EntradasDirectorio* toFind = new EntradasDirectorio(nombre, nEntradasDirectorio);
	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
	toFind->print();
	file->close();

}

void EntradasDirectorio::agregarLista(Entrada* lista, char nombre[20], long mapaBits, int espacio, char padre[30])
{
	file = new DataFile(nombre);
	int currentPosition = sizeof(Metadata) + mapaBits;

	file->open("rw");

	EntradasDirectorio* toFind = new EntradasDirectorio(nombre, nEntradasDirectorio);

	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));

	short int padreTemporal = -1;
	short int TempindPrimerHijo = -1;
	short int hermanoIzquierdoTemporal = -1;

	for (int i = 0; i < nEntradasDirectorio; i++)
	{
		if (strcmp(toFind->listaEntradas[i].nombreEntrada, padre) == 0) 
		{  

			padreTemporal = i;

		}
	}

	for (int i = 0; i < nEntradasDirectorio; i++) 
	{
		if (toFind->listaEntradas[i].indPadre != -1 && ((strcmp(toFind->listaEntradas[toFind->listaEntradas[i].indPadre].nombreEntrada, padre) == 0) && (toFind->listaEntradas[i].indHermanoDerecho == -1))) {
			hermanoIzquierdoTemporal = i;
		}
	}
	lista[espacio].indPadre = padreTemporal;
	if (hermanoIzquierdoTemporal != -1) 
	{
		toFind->listaEntradas[hermanoIzquierdoTemporal].indHermanoDerecho = espacio;
	}
	toFind->listaEntradas[espacio] = lista[espacio];
	file->write(toFind->toChar(), sizeof(Metadata) + mapaBits, toFind->getSizeOf());
	file->close();

}

EntradasDirectorio::Entrada* EntradasDirectorio::getLista(char nombre[20], long mapaBits)
{
	file = new DataFile(nombre);
	file->open("r");
	int currentPosition = sizeof(Metadata) + mapaBits;
	EntradasDirectorio* toFind = new EntradasDirectorio(nombre, nEntradasDirectorio);
	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
	file->close();
	return toFind->listaEntradas;
}

int EntradasDirectorio::existe(char nombre[20], long mapaBits, char nombreDirectorio[30])
{
	file->open("r");
	int currentPosition = sizeof(Metadata) + mapaBits;
	EntradasDirectorio* toFind = new EntradasDirectorio(nombre, nEntradasDirectorio);
	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));

	for (int i = 0; i < nEntradasDirectorio; i++)
	{
		if (strcmp(toFind->listaEntradas[i].nombreEntrada, nombreDirectorio) == 0)
		{
			return i;
		}
	}

	file->close();
	return -1;
}

void EntradasDirectorio::comandoLS(char nombre[20], long mapaBits, char nombreDirectorio[30])
{
	file->open("r");
	int currentPosition = sizeof(Metadata) + mapaBits;
	EntradasDirectorio* toFind = new EntradasDirectorio(nombre, nEntradasDirectorio);
	toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));

	int padre = -1;

	for (int i = 0; i < nEntradasDirectorio; i++) {
		if (strcmp(toFind->listaEntradas[i].nombreEntrada, nombreDirectorio) == 0) {

			padre = i;

			break;
		}
	}

	if (padre == -1) {
		return;
	}

	cout << "Padre: " << padre << endl;
	for (int i = 0; i < nEntradasDirectorio; i++) {
		if (toFind->listaEntradas[i].indPadre == padre) 
		{
			char FechaCreacion[9];
			cout << "DIRECTORIO" << endl;
			cout << "nombreEntrada: " << toFind->listaEntradas[i].nombreEntrada << endl;
			cout << "esArchivo: " << toFind->listaEntradas[i].esArchivo << endl;
			cout << "tamanio: " << toFind->listaEntradas[i].tamanio << endl;
			memcpy(FechaCreacion, toFind->listaEntradas[i].fechaCreacion, strlen(toFind->listaEntradas[i].fechaCreacion) + 1);

			cout << "fechaCreacion: " << toFind->listaEntradas[i].fechaCreacion << endl;

			cout << "indPadre: " << toFind->listaEntradas[i].indPadre << endl;
			cout << "indHijo: " << toFind->listaEntradas[i].indPrimerHijo << endl;
			cout << "Indice HermanoDerecho: " << toFind->listaEntradas[i].indHermanoDerecho << endl;
		}
	}
	file->close();
}

//_____________________________________________


BloqueDirecto::BloqueDirecto(int bloques, char nombre[20], long mapaBits, int _nEntradasDirectorio)
{
	file = new DataFile(nombre);
	insertarDatos();
	toChar();
	write(bloques, nombre, mapaBits);
}

BloqueDirecto::BloqueDirecto(char nombre[20])
{
	file = new DataFile(nombre);
	insertarDatos();
	nEntradasDirectorio = 0;
}

void BloqueDirecto::read(int bloques, char[20], long mapaBits)
{
	int currentPosition = mapaBits + sizeof(Metadata) + (nEntradasDirectorio * 109);
}

char* BloqueDirecto::toChar()
{
	return data;
}

void BloqueDirecto::insertarDatos()
{
	for (int i = 0; i < 4096; i++) {

		data[i] = '0';
	}
}

void BloqueDirecto::fromChar(char* charRead)
{
	memcpy(&data[0], &charRead[0], sizeof(data));
}

void BloqueDirecto::write(int bloques, char nombre[20], long MapaBits)
{
	file->open("w");
	BloqueDirecto* newBD = new BloqueDirecto(nombre);
	long Pointer = 0;
	for (int i = 0; i < bloques; i++)
	{
		file->write(newBD->toChar(), sizeof(Metadata) + MapaBits + (nEntradasDirectorio * 109) + Pointer, newBD->getsizeOf());
		Pointer += newBD->getsizeOf();
	}
	file->close();
}

int BloqueDirecto::getsizeOf()
{
	return sizeof(BloqueDirecto) - 8;
}

void BloqueDirecto::print()
{
	cout << data << endl;
}

//_____________________________________________

BloqueInd1Nivel::BloqueInd1Nivel(char nombre[20], int cantidad, long mapaBits)
{
	file = new DataFile(nombre);
	insertarDatos();
	write();
}

BloqueInd1Nivel::BloqueInd1Nivel()
{
	insertarDatos();
}

void BloqueInd1Nivel::fromChar(char* charRead)
{
	memcpy(&ptrs[0], &charRead[0], sizeof(ptrs));
}

void BloqueInd1Nivel::insertarDatos()
{
	for (int i = 0; i < 16; i++)
	{
		ptrs[i] = 0;

	}
}

char* BloqueInd1Nivel::toChar()
{
	char* charResult = new char[sizeof(BloqueInd1Nivel)];
	memcpy(&charResult[0], &ptrs, sizeof(ptrs));
	return charResult;
}

void BloqueInd1Nivel::write()
{
	file->open("w");
	BloqueInd1Nivel* newB1 = new BloqueInd1Nivel();
	long pointer = 0;
	for (int i = 0; i < nEntradasDirectorio * 2081; i++) {
		file->write(newB1->toChar(), mapaBits + sizeof(Metadata) + (nEntradasDirectorio * 109) + ((33308 * nEntradasDirectorio) * 4096) + pointer, sizeof(ptrs));
		pointer += sizeof(ptrs);
	}
	file->close();
}

void BloqueInd1Nivel::read()
{
	file->open("r");
	long currentPosition = mapaBits + sizeof(Metadata) + (nEntradasDirectorio * 109) + ((33308 * nEntradasDirectorio) * 4096);
	BloqueInd1Nivel* toFind = new BloqueInd1Nivel();
	toFind->fromChar(file->read(currentPosition, sizeof(ptrs)));
	currentPosition += sizeof(ptrs);

	while (!file->isEOF()) {

		for (int i = 0; i < 16; i++) {
			cout << i << toFind->ptrs[i] << endl;
		}
		toFind->fromChar(file->read(currentPosition, sizeof(ptrs)));
		currentPosition += sizeof(ptrs);

	}
	file->close();
}

//_____________________________________________

BloqueInd2Nivel::BloqueInd2Nivel()
{
	insertarDatos();
}

BloqueInd2Nivel::BloqueInd2Nivel(char nombre[20], int cantidad, long mapaBits)
{
	file = new DataFile(nombre);
	insertarDatos();
	write();
}

void BloqueInd2Nivel::write()
{
	file->open("w");
	BloqueInd2Nivel* newB2 = new BloqueInd2Nivel();
	long pointer = 0;
	for (int i = 0; i < nEntradasDirectorio * 65; i++)
	{
		file->write(newB2->toChar(), mapaBits + sizeof(Metadata) + (nEntradasDirectorio * 109) + (33308 * nEntradasDirectorio * 4096) + ((sizeof(BloqueInd1Nivel) - 8) * nEntradasDirectorio * 2081) + pointer, sizeof(ptrs));
		pointer += sizeof(ptrs);
	}

	file->close();
}

void BloqueInd2Nivel::read()
{
	file->open("r");
	long currentPosition = mapaBits + sizeof(Metadata) + (nEntradasDirectorio * 109) + (33308 * nEntradasDirectorio * 4096) + ((sizeof(BloqueInd1Nivel) - 8) * nEntradasDirectorio * 2081);
	BloqueInd2Nivel* toFind = new BloqueInd2Nivel();
	toFind->fromChar(file->read(currentPosition, sizeof(ptrs)));
	currentPosition += sizeof(ptrs);
	while (!file->isEOF())
	{
		for (int i = 0; i < 32; i++) {
			cout << i << " Prueba:  " << toFind->ptrs[i] << endl;
		}
		toFind->fromChar(file->read(currentPosition, sizeof(ptrs)));
		currentPosition += sizeof(ptrs);
	}
	file->close();
}

void BloqueInd2Nivel::insertarDatos()
{
	for (int i = 0; i < 32; i++)
	{
		ptrs[i] = 0;
	}
}

char* BloqueInd2Nivel::toChar()
{
	char* charResult = new char[sizeof(BloqueInd2Nivel)];
	memcpy(&charResult[0], &ptrs, sizeof(ptrs));
	return charResult;
}

void BloqueInd2Nivel::fromChar(char* charRead)
{
	memcpy(&ptrs[0], &charRead[0], sizeof(ptrs));
}

//_____________________________________________

BloqueInd3Nivel::BloqueInd3Nivel(char nombre[20], int cantidad, long mapaBits)
{
	file = new DataFile(nombre);
	insertarDatos();
	write();
}

BloqueInd3Nivel::BloqueInd3Nivel()
{
	insertarDatos();
}

void BloqueInd3Nivel::insertarDatos()
{
	for (int i = 0; i < 64; i++)
	{
		ptrs[i] = 0;
	}
}

char* BloqueInd3Nivel::toChar() {
	char* charResult = new char[sizeof(BloqueInd3Nivel)];
	memcpy(&charResult[0], &ptrs, sizeof(ptrs));
	return charResult;
}

void BloqueInd3Nivel::fromChar(char* charRead) {

	memcpy(&ptrs[0], &charRead[0], sizeof(ptrs));

}

void BloqueInd3Nivel::write()
{
	file->open("w");


	BloqueInd3Nivel* newB3 = new BloqueInd3Nivel();

	long pointer = 0;

	for (int i = 0; i < nEntradasDirectorio; i++) {

		file->write(newB3->toChar(), mapaBits + sizeof(Metadata) + (nEntradasDirectorio * 109) + (33308 * nEntradasDirectorio * 4096) + ((sizeof(BloqueInd1Nivel) - 8) * nEntradasDirectorio * 2081) + ((sizeof(BloqueInd2Nivel) - 8) * nEntradasDirectorio * 65) + pointer, sizeof(ptrs));
		pointer += sizeof(ptrs);
	}
	file->close();
}

void BloqueInd3Nivel::read()
{
	file->open("r");
	long currentPosition = mapaBits + sizeof(Metadata) + (nEntradasDirectorio * 109) + (33308 * nEntradasDirectorio * 4096) + ((sizeof(BloqueInd1Nivel) - 8) * nEntradasDirectorio * 2081) + ((sizeof(BloqueInd2Nivel) - 8) * nEntradasDirectorio * 65);
	BloqueInd3Nivel* toFind = new BloqueInd3Nivel();
	toFind->fromChar(file->read(currentPosition, sizeof(ptrs)));
	currentPosition += sizeof(ptrs);

	while (!file->isEOF()) {

		for (int i = 0; i < 64; i++) {
			cout << i << toFind->ptrs[i] << endl;
		}
		toFind->fromChar(file->read(currentPosition, sizeof(ptrs)));
		currentPosition += sizeof(ptrs);
	}
	file->close();
}


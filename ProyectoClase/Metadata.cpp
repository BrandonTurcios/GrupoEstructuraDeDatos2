#include "Metadata.h"

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

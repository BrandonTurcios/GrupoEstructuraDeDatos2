#include "DataFile.h"
#include <iostream>
#include<sstream>
#include <iomanip>

using namespace std;
class Metadata
{
private:
	DataFile* file;
	char nombreDisco[20];
	char fechaCreacion[9]; //ddMMyyyy
	//entradas de directorios
	int cantidadEntradasDirectorio; //dado por el usuario
	//bloques de datos
	unsigned int tamanoBloque; //4096
	int cantidadBloquesDirectos; //calculado
	int cantidadBloquesInd1Nivel; //calculado
	int cantidadBloquesInd2Nivel; //calculado
	int cantidadBloquesInd3Nivel; //1


public:
	Metadata(const char[20], int);
	Metadata();
	char* toChar();
	void fromChar(char*);
	void abrirDisco(const char[20]);
	void guardarMapaBits();
	void guardarDisco();
	int getSizeOf();
	void read(const char*);
	void print();
	const char* getNombre();

};


class MapaBits
{
private:
	DataFile* file;
	char* ptrsCombinados;
	int bloque1;
	int bloque2;
	int bloque3;
	int bloque4;

	class MapaBits_BD
	{
	public:
		MapaBits_BD(int nBloquesBD);
		MapaBits_BD();
		char* ptrs; // =new char[nb];

		char* toChar();
		void fromChar(char*);
	};
	class MapaBits_BI1
	{
	public:
		MapaBits_BI1(int nBloquesBI1);
		MapaBits_BI1();
		char* ptrs; // =new char[ca>lado];

		char* toChar();
		void fromChar(char*);
	};
	class MapaBits_BI2
	{
	public:
		MapaBits_BI2(int nBloquesBI2);
		MapaBits_BI2();
		char* ptrs; // =new char[calculado];

		char* toChar();
		void fromChar(char*);
	};
	class MapaBits_BI3
	{
	public:
		MapaBits_BI3(int nBloquesBI3);
		MapaBits_BI3();
		char* ptrs; //= new char[nbloquesI3 / 8];
		char* toChar();
		void fromChar(char*);

	};

public:

	MapaBits(char[], int, int, int, int);
	MapaBits(char[]);
	int getSizeOf();
	char* toChar();
	void fromChar(char*);
	void establecerMapaBits(char[]);
	void leerMapaBits(char[], int, int, int, int);
	void printMapa();

};



class EntradasDirectorio
{
private:
	DataFile* file;
	int nEntradasDirectorio;

	struct Entrada
	{
		char nombreEntrada[30];
		bool esArchivo; // 1->File, 0->Folder
		unsigned int tamanio;

		short int indPadre;
		short int indPrimerHijo;
		short int indHermanoDerecho;


		char fechaCreacion[8]; //ddMMyyyy
		//punterosabloques de datos (Importacion de archivos)
		unsigned int ptrsBD[12];
		unsigned int ptrsBDI[3]; //[0] -> BI1, [1] -> BI2, [2] -> BI3


	};

public:
	Entrada* listaEntradas;
	EntradasDirectorio(char[20], int);
	void print();
	int getSizeOf();

	char* toChar();
	void fromChar(char*);
	void setMkdir(char[20], long, char[30], char[30]);
	void write(char[20], long);
	void read(char[20], long);
	void agregarLista(Entrada*, char[20], long);
	Entrada* getLista(char[20], long);
	bool existe(char[20], long, char[30]);
	void comandoLS(char[20], long, char[30]);
};

class tipoBloque
{
public:
	tipoBloque();
	virtual char* toChar() = 0;
	virtual void fromChar(char*) = 0;
};

class BloqueDirecto :public tipoBloque
{
public:
	BloqueDirecto(int, char[20], long, int);
	BloqueDirecto(char[20]);
	void read(int, char[20], long);


private:
	int nEntradasDirectorio;
	DataFile* file;
	char data[4096];//4kb:
	char* toChar();
	void insertarDatos();
	void fromChar(char*);
	void write(int, char[20], long);
	int getsizeOf();
	void print();
};


class BloqueInd1Nivel : public tipoBloque
{
public:
	BloqueInd1Nivel();
	BloqueInd1Nivel(char[20], int, long);
	void write();
	void read();
	void insertarDatos();
	char* toChar();
	void fromChar(char*);

private:
	int nEntradasDirectorio;
	long mapaBits;
	DataFile* file;
	unsigned int ptrs[16];
};
//
class BloqueInd2Nivel : public tipoBloque
{
public:
	BloqueInd2Nivel(char[20], int, long);
	BloqueInd2Nivel();
	void write();
	void read();
	void insertarDatos();
	char* toChar();
	void fromChar(char*);

private:
	int nEntradasDirectorio;
	long mapaBits;
	DataFile* file;
	unsigned int ptrs[32];
};

class BloqueInd3Nivel :public tipoBloque
{
public:
	BloqueInd3Nivel(char[20], int, long);
	BloqueInd3Nivel();
	void write();
	void read();
	void insertarDatos();
	char* toChar();
	void fromChar(char*);

private:
	int nEntradasDirectorio;
	long mapaBits;
	DataFile* file;
	unsigned int ptrs[64];
};

class importExport
{
public:
	importExport(char nombre[20]);
	void importar(char[20], long, int);
	void exportar(char[20], long);
	DataFile* file;
	struct bloque
	{
		char data[4096];
		bloque()
		{
			for (int i = 0; i < 4096; i++)
			{
				data[i] = '0';
			}
		}
	};
};
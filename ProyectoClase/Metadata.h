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
	Metadata(char[20], int);
	Metadata();
	char* toChar();
	void fromChar(char*);
	void abrirDisco(char[20]);
	void guardarDisco();
	int getSizeOf();
	void read();
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
		char* ptrs; 

		char* toChar();
		void fromChar(char*);
	};
	class MapaBits_BI1
	{
	public:
		MapaBits_BI1(int nBloquesBI1);
		MapaBits_BI1();
		char* ptrs; 

		char* toChar();
		void fromChar(char*);
	};
	class MapaBits_BI2
	{
	public:
		MapaBits_BI2(int nBloquesBI2);
		MapaBits_BI2();
		char* ptrs; 

		char* toChar();
		void fromChar(char*);
	};
	class MapaBits_BI3
	{
	public:
		MapaBits_BI3(int nBloquesBI3);
		MapaBits_BI3();
		char* ptrs;
		char* toChar();
		void fromChar(char*);

	};

public:

	MapaBits(char[], int, int, int, int);
	MapaBits(char[]);
	int getSizeOf();
	void encender(int);
	void apagar(char[20], int);
	char* toChar();
	void fromChar(char*);
	void establecerMapaBits(char[]);
	char* leerMapaBits(char[], int, int, int, int);
	int check(char,int);
	long encontrarEspacio(char [20],int, int, int, int, int, int,int);
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
		bool esArchivo;
		unsigned int tamanio;

		short int indPadre;
		short int indPrimerHijo;
		short int indHermanoDerecho;


		char fechaCreacion[8]; 
	
		unsigned int ptrsBD[12];
		unsigned int ptrsBDI[3]; 


	};

public:
	Entrada* listaEntradas;
	EntradasDirectorio(char[20], int);
	void print();
	int getSizeOf();

	char* toChar();
	void fromChar(char*);
	void comandoMKDIR(char[20], long, char[30], char[30]);
	void write(char[20], long);
	void read(char[20], long);
	void agregarLista(Entrada*, char[20], long,int, char[30]);
	Entrada* getLista(char[20], long);
	int existe(char[20], long, char[30]);
	void comandoLS(char[20], long, char[30]);
};

class BloqueDirecto 
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


class BloqueInd1Nivel 
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
class BloqueInd2Nivel 
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

class BloqueInd3Nivel 
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

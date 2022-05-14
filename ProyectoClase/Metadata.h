#include <iostream>

class Metadata
{
private:
	char nombreDisco[20];
	char fechaCreacion[8]; //ddMMyyyy
	//entradas de directorios
	int cantidadEntradasDirectorio; //dado por el usuario
	//bloques de datos
	unsigned int tamanoBloque; //4096
	int cantidadBloquesDirectos; //calculado
	int cantidadBloquesInd1Nivel; //calculado
	int cantidadBloquesInd2Nivel; //calculado
	int cantidadBloquesInd3Nivel; //1


public:
	Metadata();
	char* toChar();
	void fromChar(char*);

};



class MapaBits
{
private:
	class MapaBits_BD
	{
	public:
		char* ptrs; // =new char[nb];

		char* toChar();
		void fromChar(char*);
	};
	class MapaBits_BI1
	{
	public:
		char* ptrs; // =new char[ca>lado];

		char* toChar();
		void fromChar(char*);
	};
	class MapaBits_BI2
	{
	public:
		char* ptrs; // =new char[calculado];

		char* toChar();
		void fromChar(char*);
	};
	class MapaBits_BI3
	{
	public:
		char* ptrs; //= new char[nbloquesI3 / 8];

		char* toChar();
		void fromChar(char*);
	};
};



class EntradasDirectorio
{
private:
	struct Entrada
	{
		char nombreEntrada[30];
		bool esArchivo; // 1->File, 0->Folder
		unsigned int tamanio;

		/////////////////////////////////////////////////////////////////////////////
		short int indPadre;
		short int indPrimerHijo;
		short int indHermanoDerecho;

		char fechaCreacion[8]; //ddMMyyyy
		//punterosabloques de datos (Importacion de archivos)
		unsigned int ptrsBD[12];
		unsigned int ptrsBDI[3]; //[0] -> BI1, [1] -> BI2, [2] -> BI3


	};

	Entrada* lista;
	EntradasDirectorio()
	{
		//comentado porque da error
		// lista = new Entrada[md.cantidadEntradasDirectorio];
	}

	void write()
	{

	}

};

class tipoBloque
{
public:
	virtual char* toChar() = 0;
	virtual void fromChar(char*) = 0;
};

class BloqueDirecto :public tipoBloque
{
private:
	char data[4096];//4kb:
};


class BloqueInd1Nivel : public tipoBloque
{
private:
	unsigned int ptrs[16]; // [0]
};

class BloqueInd2Nivel : public tipoBloque
{
private:
	unsigned int ptrs[32]; // [0]=di
};

class BloqueInd3Nivel :public tipoBloque
{
private:
	unsigned int ptrs[64];
};

//$ create disk "Disco" 100

//$ create disk "miDisco"
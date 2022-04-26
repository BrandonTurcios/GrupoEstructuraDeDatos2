#include "Cuentas.h"

#include <iostream>
#include <fstream>
using namespace std;

void Cuentas::agregarEmpleados()
{
	int nCuenta;
	char nombreCliente[30];
	float saldo;

	ofstream cuentas("cuentas.bin", ios::out | ios::app | ios::binary);

	if (!cuentas)
	{
		cout << "Error al intentar abrir el archivo cuentas.bin\n";
		return;
	}
	datos nuevo;

	cout << "Indique numero de cuenta: ";
	cin >> nuevo.nCuenta;
	cout << "Indique nombre del cliente: ";
	cin >> nuevo.nombreCliente;
	nuevo.saldo = 0;
	if (existe(nuevo.nCuenta))
	{
		cout << "Codigo invalido!\n";
	}
	else
	{
		cuentas.write(reinterpret_cast<const char*>(&nuevo), sizeof(datos));
		cout << "Cliente agregado!\n";
	}


}

void Cuentas::depositar()
{
	fstream archivoEmpleado("cuentas.bin", ios::in | ios::out | ios::binary);
	float montodepositar;
	int nCuenta;

	cout << "indique el numero de cuenta: ";
	cin >> nCuenta;

	if (!archivoEmpleado)
	{
		cout << "Error\n";
		return;
	}

	archivoEmpleado.seekg(0, ios::beg);
	long posicionArchivo = 0;
	datos actual;
	archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(datos));

	while (!archivoEmpleado.eof())
	{
		if (actual.nCuenta == nCuenta)
		{
			cout << "indique monto a depositar: ";
			cin >> montodepositar;
			actual.saldo += montodepositar;
			cout << "Monto depositado!\n";

			archivoEmpleado.seekp(posicionArchivo, ios::beg);
			archivoEmpleado.write(reinterpret_cast<const char*>(&actual), sizeof(datos));
			archivoEmpleado.close();
			return;
		}
		posicionArchivo = archivoEmpleado.tellg();
		archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(datos));
	}
	cout << "No encontrado\n";
	archivoEmpleado.close();
}

void Cuentas::retirar()
{
	/*float montoretirar;
	cout << "indique monto a retirar: ";
	cin >> montoretirar;*/

	fstream archivoEmpleado("cuentas.bin", ios::in | ios::out | ios::binary);
	float montoretirar;
	int nCuenta;

	cout << "indique el numero de cuenta: ";
	cin >> nCuenta;

	if (!archivoEmpleado)
	{
		cout << "Error\n";
		return;
	}

	archivoEmpleado.seekg(0, ios::beg);
	long posicionArchivo = 0;
	datos actual;
	archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(datos));

	while (!archivoEmpleado.eof())
	{
		if (actual.nCuenta == nCuenta)
		{
			cout << "indique monto a retirar: ";
			cin >> montoretirar;
			if (montoretirar > actual.saldo || montoretirar < 0)
			{
				cout << "Saldo insuficiente!\n";
				return;
			}
			else
			{
				actual.saldo = actual.saldo - montoretirar;
				cout << "Retiro completado!\n";

				archivoEmpleado.seekp(posicionArchivo, ios::beg);
				archivoEmpleado.write(reinterpret_cast<const char*>(&actual), sizeof(datos));
				archivoEmpleado.close();
				return;
			}
		}
		posicionArchivo = archivoEmpleado.tellg();
		archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(datos));
	}
	cout << "No encontrado\n";
	archivoEmpleado.close();

}

void Cuentas::actualizarSaldo()
{

	int opcion;

	cout << "presione 1 si desea depositar y presione 2 si desea retirar\n";
	cin >> opcion;

	switch (opcion)
	{
	case 1: depositar();
		break;
	case 2: retirar();
		break;
	}

}

void Cuentas::leer()
{
	ifstream cuentas("cuentas.bin", ios::in | ios::binary);

	if (!cuentas)
	{
		cout << "Error al intentar abrir el archivo cuentas.bin\n";
		return;
	}

	cuentas.seekg(0, ios::beg);

	datos actual;
	cuentas.read(reinterpret_cast<char*>(&actual), sizeof(datos));
	while (!cuentas.eof())
	{
		cout << "datos { codigo: " << actual.nCuenta << ", nombre: " <<
			actual.nombreCliente << ", saldo: " << actual.saldo <<
			" }\n";

		cuentas.read(reinterpret_cast<char*>(&actual), sizeof(datos));
	}

	cuentas.close();

}

bool Cuentas::existe(int codigo_)
{
	datos actual;

	ifstream ArchivoCuentas("cuentas.bin", ios::in | ios::binary);
	if (!ArchivoCuentas)
	{
		cout << "Error al intentar abrir el archivo cuentas.bin\n";
		return false;
	}
	ArchivoCuentas.seekg(0, ios::beg);
	do {

		ArchivoCuentas.read(reinterpret_cast<char*>(&actual), sizeof(datos));

		if (actual.nCuenta == codigo_) {
			ArchivoCuentas.close();
			return true;
		}

	} while (!ArchivoCuentas.eof());
	ArchivoCuentas.close();
	return false;
}

bool Cuentas::existeNombre(char nombre_[30])
{
	datos actual;

	ifstream ArchivoCuentas("cuentas.bin", ios::in | ios::binary);
	if (!ArchivoCuentas)
	{
		cout << "Error al intentar abrir el archivo cuentas.bin\n";
		return false;
	}
	ArchivoCuentas.seekg(0, ios::beg);
	do {

		ArchivoCuentas.read(reinterpret_cast<char*>(&actual), sizeof(datos));

		if (actual.nombreCliente == nombre_) {
			ArchivoCuentas.close();
			return true;
		}

	} while (!ArchivoCuentas.eof());
	ArchivoCuentas.close();
	return false;
}

void Cuentas::getSaldo()
{
	int _nCuenta;
	cout << "Ingresar numero de cuenta:" << endl;
	cin >> _nCuenta;

	datos actual;

	ifstream ArchivoCuentas("cuentas.bin", ios::in | ios::binary);
	if (!ArchivoCuentas)
	{
		cout << "Error al intentar abrir el archivo cuentas.bin\n";
	}
	ArchivoCuentas.seekg(0, ios::beg);
	do {

		ArchivoCuentas.read(reinterpret_cast<char*>(&actual), sizeof(datos));
		if (actual.nCuenta == _nCuenta) {
			cout << actual.saldo;
			ArchivoCuentas.close();
		}

	} while (!ArchivoCuentas.eof());
	ArchivoCuentas.close();
	//cout << "ErrorAAAA";

}

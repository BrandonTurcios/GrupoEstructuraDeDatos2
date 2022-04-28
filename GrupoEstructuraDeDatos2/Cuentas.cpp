#include "Cuentas.h"

#include <iostream>
#include <fstream>
using namespace std;

void Cuentas::agregarEmpleados()
{
	char nCuenta[5];
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
		return;
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
	char nCuenta[5];

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
		if (strcmp(actual.nCuenta,nCuenta)==0)
		{
			cout << "indique monto a depositar: ";
			cin >> montodepositar;
			actual.saldo += montodepositar;
	
			cout << "Monto depositado!\n";

			archivoEmpleado.seekp(posicionArchivo, ios::beg);
			archivoEmpleado.write(reinterpret_cast<const char*>(&actual), sizeof(datos));
			agregarHistorial(actual.nCuenta,0,montodepositar);
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
	char nCuenta[5];

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
		if (strcmp(actual.nCuenta, nCuenta) == 0)
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
				agregarHistorial(actual.nCuenta, 1, montoretirar);
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

	cout << "presione 0 si desea depositar y presione 1 si desea retirar\n";
	cin >> opcion;

	switch (opcion)
	{
	case 0: depositar();
		break;
	case 1: retirar();
		break;
	default:
		cout << "OPCION INVALIDA";
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

bool Cuentas::existe(char codigo_[5])
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

		if (strcmp(actual.nCuenta, codigo_) == 0)
		{
			return true;
			ArchivoCuentas.close();
			
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
	char _nCuenta[5];
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
		if (strcmp(actual.nCuenta, _nCuenta) == 0) {
			cout << actual.saldo;
			ArchivoCuentas.close();
		}

	} while (!ArchivoCuentas.eof());
	ArchivoCuentas.close();
	//cout << "ErrorAAAA";

}

void Cuentas::historialTransacciones()
{
	ifstream transacciones("transacciones.bin", ios::in | ios::binary);

	if (!transacciones)
	{
		cout << "Error al intentar abrir el archivo transacciones.bin\n";
		return;
	}

	transacciones.seekg(0, ios::beg);

	historial actual;
	transacciones.read(reinterpret_cast<char*>(&actual), sizeof(historial));
	while (!transacciones.eof())
	{
		cout << "datos { codigo: " << actual.nCuenta << ", tipo de transaccion: " <<
			actual.tipo << ", monto: " << actual.saldo <<
			" }\n";

		transacciones.read(reinterpret_cast<char*>(&actual), sizeof(historial));
	}

	transacciones.close();
}

void Cuentas::agregarHistorial(char nCuenta[5], bool tipo, float saldo)
{
	
	ofstream transacciones("transacciones.bin", ios::out | ios::app | ios::binary);

	if (!transacciones)
	{
		cout << "Error al intentar abrir el archivo transacciones.bin\n";
		return;
	}

	historial nuevo;
	strcpy_s(nuevo.nCuenta,strlen(nCuenta)+1 , nCuenta);
	nuevo.tipo = tipo;
	nuevo.saldo = saldo;
	transacciones.write(reinterpret_cast<const char*>(&nuevo), sizeof(historial));

}

#pragma once


class Cuentas
{
	struct datos {
		char nCuenta[5];
		char nombreCliente[30];
		float saldo;
	};
	struct historial {
		char nCuenta[5];
		bool tipo;
		float saldo;
	};
public:
	void agregarEmpleados();
	void leer();
	void actualizarSaldo();
	void depositar();
	void retirar();
	bool existe(char _nCuenta[5]);
	bool existeNombre(char[30]);
	void getSaldo();
	void historialTransacciones();
	void agregarHistorial(char[5], bool, float);
};
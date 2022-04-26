#pragma once


class Cuentas
{
	struct datos {
		int nCuenta;
		char nombreCliente[30];
		float saldo;
	};

public:
	void agregarEmpleados();
	void leer();
	void actualizarSaldo();
	void depositar();
	void retirar();
	bool existe(int _nCuenta);
	bool existeNombre(char[30]);
	void getSaldo();
};
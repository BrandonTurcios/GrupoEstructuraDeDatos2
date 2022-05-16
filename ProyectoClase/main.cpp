#include <iostream>
#include <conio.h>
#include "Metadata.h"
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;
int main()
{
	Metadata hola;

	hola.crearDisco();
	hola.guardarDisco();
	hola.read("miDiscoA.bin");
   

}
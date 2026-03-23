//
// Created by yaxkin on 3/22/26.
//
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void addIndexToOptions(std::vector<std::string>& options)
{
	int indexOption = 0;
	for (std::string& option : options)
	{
		option = std::to_string(indexOption) + ". " + option;
		indexOption++;
	}
}

void mostrarMenu(std::vector<std::string>& options)
{
	for (std::string& option : options)
	{
		std::cout << option << std::endl;
	}
}

void validarEntradaInt(int& opcion)
{
	std::string input;
	std::cin >> input;
	try {
		opcion = std::stoi(input);
	}
	catch (std::exception&) {
		std::cout << "Entrada no valida. Intente de nuevo." << std::endl;
		opcion = -1; // Opcion invalida
	}
}

void menuPrincipal() {
	std::cout << "------------------------------" << std::endl;
	std::vector<std::string> options ={
		"Cargar nuevo CSV",
		"Limpiar sistema",
		"Buscar en estructuras",
		"Eliminar en estructuras",
		"Salir"
	};
	addIndexToOptions(options);
	mostrarMenu(options);
}

void casesMenuPrincipal(bool& salir)
{
	int opcion;

	validarEntradaInt(opcion);

	switch (opcion) {
	case 0:
		//cargarCSV();
		break;
	case 1:
		//limpiarDatos();
		break;
	case 2:
		//menuBuscar();
		break;
	case 3:
		//menuEliminar();
		break;
	case 4:
		std::cout << "Saliendo de la aplicación" << std::endl;
		salir = true;
		break;
	default:
		std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
	}
}

int main() {
	bool salir = false;

	std::cout << "GESTION DE CATÁLOGO DE PRODUCTOS DE SUPERMERCADO 3000" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	while (!salir) {
		menuPrincipal();
		casesMenuPrincipal (salir);
	}
	return 0;
}
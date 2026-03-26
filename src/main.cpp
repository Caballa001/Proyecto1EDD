//
// Created by yaxkin on 3/22/26.
//
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "globals.h"
#include "export/generarDot.h"
#include "parsing/csvReader.h"
#include "parsing/loader.h"

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
	std::size_t pos; // solo int sin signo
	try {
		opcion = std::stoi(input, &pos);
		if (pos != input.length())
		{
			throw std::exception();
		}
	}
	catch (std::exception&) {
		std::cout << "Entrada no valida. Intente de nuevo." << std::endl;
		opcion = -1; // Opcion invalida
	}
}

void menuBuscarEstructura()
{
	bool salir = false;
	std::vector<Product> products;

	while (!salir)
	{
		std::cout << "------------------------------" << std::endl;
		std::vector<std::string> options ={
			"AVL: Buscar por nombre",
			"B+: Buscar por categoría",
			"B-: Buscar por caducidad",
			"Regresar"

		};

		addIndexToOptions(options);
		mostrarMenu(options);
		int opcion;
		validarEntradaInt(opcion);
		if (opcion == -1) continue;

		switch (opcion) {
		case 0:
			//BuscarAVL();
			break;
		case 1:
			//BuscarBplus();
			break;
		case 2:
			//BuscarBminus();
			break;
		case 3:
			std::cout << "Regresando al menu principal..." << std::endl;
			salir = true;
			break;
		default:
			std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
		}
	}
}

void menuEliminarEstructura()
{
	bool salir = false;
	std::vector<Product> products;

	while (!salir)
	{
		std::cout << "------------------------------" << std::endl;
		std::vector<std::string> options ={
			"Eliminar por Codigo de Barra",
			"Regresar"

		};

		addIndexToOptions(options);
		mostrarMenu(options);
		int opcion;
		validarEntradaInt(opcion);
		if (opcion == -1) continue;

		switch (opcion) {
		case 0:
			//BuscarAVL();
			break;
		case 1:
			std::cout << "Regresando al menu principal..." << std::endl;
			salir = true;
			break;
		default:
			std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
		}
	}
}

void menuMedicion()
{
	bool salir = false;
	std::vector<Product> products;

	while (!salir)
	{
		std::cout << "------------------------------" << std::endl;
		std::vector<std::string> options ={
			"Empezar Medicion de rendimiento (AVL vs Lista vs Lista Ordenada)",
			"Regresar"

		};

		addIndexToOptions(options);
		mostrarMenu(options);
		int opcion;
		validarEntradaInt(opcion);
		if (opcion == -1) continue;

		switch (opcion) {
		case 0:
			//MedicionRendimiento();
			break;
		case 1:
			std::cout << "Regresando al menu principal..." << std::endl;
			salir = true;
			break;
		default:
			std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
		}
	}
}

void menuVisualizar()
{
	bool salir = false;
	std::vector<Product> products;

	while (!salir)
	{
		std::cout << "------------------------------" << std::endl;
		std::vector<std::string> options ={
			"Visualizar Arboles. (.dot)",
			"AVL: Listar por nombre. in-order",
			"Regresar"

		};

		addIndexToOptions(options);
		mostrarMenu(options);
		int opcion;
		validarEntradaInt(opcion);
		if (opcion == -1) continue;

		switch (opcion) {
		case 0:
			generarDot(arbolAVL->getRaiz());
			break;
		case 1:
			arbolAVL->listarInorder(arbolAVL->getRaiz());
			break;
		case 2:
			std::cout << "Regresando al menu principal..." << std::endl;
			salir = true;
			break;
		default:
			std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
		}
	}
}

void menuPrincipal() {
	bool salir = false;
	std::vector<Product> products;

	while (!salir)
	{
		std::cout << "------------------------------" << std::endl;
		std::vector<std::string> options ={
			"Cargar nuevo CSV",
			"Limpiar sistema",
			"Buscar en estructuras",
			"Medicion de rendimiento",
			"Eliminar en estructuras",
			"Visualizar estructuras",
			"Salir"
		};

		addIndexToOptions(options);
		mostrarMenu(options);
		int opcion;
		validarEntradaInt(opcion);
		if (opcion == -1) continue;

		switch (opcion) {
		case 0:
			products = csvReader();
			loader(products);
			std::cout << "Archivo cargado con " << products.size() << " productos." << std::endl;
			break;
		case 1:
			limpiarDatos();
			break;
		case 2:
			menuBuscarEstructura();
			break;
		case 3:
			menuMedicion();
			break;
		case 4:
			menuEliminarEstructura();
			break;
		case 5:
			menuVisualizar();
			break;
		case 6:
			std::cout << "Saliendo de la aplicación" << std::endl;
			salir = true;
			break;
		default:
			std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
		}
	}
}

int main() {

	std::cout << "GESTION DE CATÁLOGO DE PRODUCTOS DE SUPERMERCADO 3000" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	menuPrincipal();
	return 0;
}

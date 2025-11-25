#pragma once

#include<iostream>
#include <string>
using namespace std;
class producto {

private:
	int ID;
	string nombre, categoria;
	double precio;
	long stock;
public:

	// Constructores
	producto() : ID(0), nombre(""), categoria(""), precio(0.0), stock(0) {}
	producto(int id, string nomb, string cat, double prec, long stk)
		: ID(id), nombre(nomb), categoria(cat), precio(prec), stock(stk) {
	}

	int getID()const;
	string getNombre()const;
	string getCategoria()const;
	double getPrecio()const;
	long getCantidadEnStock()const;

	//setters 
	void setID(int nuevoID);
	void setNombre(const string& nuevoNombre);
	void setCategoria(const string& nuevaCategoria);
	void setPrecio(double nuevoPrecio);
	void setStock(long nuevoStock);

	//actividades 
	void incrementarStock(long cantidad = 1);
	void disminuirStock(long cantidad = 1);
};

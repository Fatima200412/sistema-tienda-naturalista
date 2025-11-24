#include "producto.h"
#include <iostream>

using namespace std;

// Getters
int producto::getID() const { return ID; }
string producto::getNombre() const { return nombre; }
string producto::getCategoria() const { return categoria; }
double producto::getPrecio() const { return precio; }
long producto::getCantidadEnStock() const { return stock; }

// Setters
void producto::setID(int nuevoID) { ID = nuevoID; }
void producto::setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
void producto::setCategoria(const string& nuevaCategoria) { categoria = nuevaCategoria; }
void producto::setPrecio(double nuevoPrecio) { precio = nuevoPrecio; }
void producto::setStock(long nuevoStock) { stock = nuevoStock; }

// Metodos funcionales
void producto::incrementarStock(long cantidad) {
    stock += cantidad;
}

void producto::disminuirStock(long cantidad) {
    if (cantidad <= stock) {
        stock -= cantidad;
    }
}
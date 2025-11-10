#include "Producto.h"

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
    cout << "Stock incrementado. Nuevo total: " << stock << endl;
}

void producto::disminuirStock(long cantidad) {
    if (stock - cantidad >= 0) {
        stock -= cantidad;
        cout << "Stock disminuido. Nuevo total: " << stock << endl;
    }
    else {
        cout << "Error: stock insuficiente para disminuir " << cantidad << " unidades." << endl;
    }
}
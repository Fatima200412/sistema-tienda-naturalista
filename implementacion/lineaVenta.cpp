#include"lineaVenta.h"

//getters 
int lineaVenta::getProductoID()const {return productoID;}

string lineaVenta::getNombreProducto()const { return nombreProducto; }

int lineaVenta::getCantidad()const { return cantidad; }

double lineaVenta::getPrecioUnitario()const { return precioUnitario; }

///setters 

void lineaVenta::setCantidad(int cantidad) { this->cantidad = cantidad; }

void lineaVenta::setPrecioUnitario(double precioU) { this->precioUnitario = precioU; }

//subtotal
double lineaVenta:: subTotal()const{ return cantidad * precioUnitario; }
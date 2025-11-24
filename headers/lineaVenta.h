#pragma once
#include<string>
using namespace std;

class lineaVenta {
private: 
	int productoID, cantidad;
	string nombreProducto;
	double precioUnitario; 

public: 
	//constructores 
	lineaVenta()=default;
	lineaVenta(int id,string nomb,int qty,double precio):productoID(id),nombreProducto(nomb),cantidad(qty),precioUnitario(precio){}
	
	//getters
	
	int  getProductoID()const ;
	string getNombreProducto()const ;
	int  getCantidad()const;
	double getPrecioUnitario()const;

	//setters
	void setCantidad(int cantidad);
	void setPrecioUnitario(double preciou);
	double subTotal()const;

};


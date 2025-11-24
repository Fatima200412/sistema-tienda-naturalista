#pragma once
#include <vector>
#include<string>
#include"lineaVenta.h"
class inventario;
//desarrollod e clase venta
class venta {
private:
	int ID;
	string fecha;
	vector<lineaVenta> items;
	double total{0.0};
public:
	//constructor
	venta() = default;
	venta(int id, string date) :ID(id), fecha(date) {};
	venta(int id,string date,vector<lineaVenta>articulos,double tot):ID(id),fecha(date),items(articulos),total(tot){}

	//getters
	double getTotal() const { return total; }
	const vector<lineaVenta>& getItems() const { return items; }
	const string& getFecha() const { return fecha; }


	//metodos para clase venta

	void agregarItem(const lineaVenta& lv);
	double calcularTotal();//calcula y devuelve total
	bool confirmar(inventario& inv);//descuenta stock en el inventario



};
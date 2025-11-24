#pragma once
#include <vector>
#include<string>
#include"lineaVenta.h"
class inventario;
//desarrollod e clase venta 
class venta {
private:
	int ID{0};
	string fecha;
	string cliente;
	vector<lineaVenta> items;
	double total{0.0};
public:
	//constructor 
	venta() = default;
	venta(int id, string date, string clienteNombre = "") :ID(id), fecha(date), cliente(clienteNombre) {};
	venta(int id,string date,vector<lineaVenta>articulos,double tot,string clienteNombre = "")
		:ID(id),fecha(date),cliente(clienteNombre),items(articulos),total(tot){}

	//getters 
	int getId() const { return ID; }
	const string& getCliente() const { return cliente; }
	double getTotal() const { return total; }
	const vector<lineaVenta>& getItems() const { return items; }
	const string& getFecha() const { return fecha; }

	void setFecha(const string& nuevaFecha) { fecha = nuevaFecha; }
	void setCliente(const string& nuevoCliente) { cliente = nuevoCliente; }

	//metodos para clase venta

	void agregarItem(const lineaVenta& lv);
	double calcularTotal();//calcula y devuelve total
	bool confirmar(inventario& inv);//descuenta stock en el inventario
};
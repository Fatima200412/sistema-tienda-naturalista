#pragma once

#include<iostream>
#include<string>
#include<vector>
#include"venta.h"
class inventario;
//clase gestor de ventas
class gestorVentas {
private:
	vector<venta> historial;
public:
	gestorVentas() = default;
	gestorVentas(vector <venta>hist) :historial(hist) {}
	bool registrarVenta(venta& v, inventario& inv);
	vector<venta> ventasRango(const string& inicio, const string& fin)const;
	double totalVendidoRango(const string& inicio,const string& fin)const;
};
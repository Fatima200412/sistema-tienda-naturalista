#pragma once

#include<iostream>
#include<string>
using namespace std;
//clases que se utilizan en los metodos 
class gestorVentas;
class inventario;

class reportes {
public:
	reportes() = default;
    string reporteInventario(const inventario& inv) const;
    string reporteVentas(const gestorVentas& gv) const;
    void exportarReporte(const string& nombreArchivo,const string& contenido) const;
};
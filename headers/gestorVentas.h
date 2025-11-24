#pragma once

#include <string>
#include <vector>
#include "venta.h"
class inventario;

class gestorVentas {
private:
    std::vector<venta> lista;
public:
    bool registrarVenta(venta& v, inventario& inv);
    bool eliminarVenta(int id, inventario& inv);
    venta* buscarPorCliente(const std::string& cliente);
    const venta* buscarPorCliente(const std::string& cliente) const;
    bool modificarVenta(int id,const std::string& nuevaFecha,const std::string& nuevoCliente);
    void ordenarPorCliente();
    void mostrarVentas() const;
    double totalVendido() const;
    size_t totalRegistros() const { return lista.size(); }
};
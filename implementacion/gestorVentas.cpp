#include "gestorVentas.h"
#include "inventario.h"
#include "producto.h"
#include <algorithm>
#include <iostream>

bool gestorVentas::registrarVenta(venta& v, inventario& inv) {
    if (v.confirmar(inv)) {
        lista.push_back(v);
        return true;
    }
    return false;
}

bool gestorVentas::eliminarVenta(int id, inventario& inv) {
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        if (it->getId() == id) {
            for (const auto& linea : it->getItems()) {
                if (auto* prod = inv.obtenerPorId(linea.getProductoID())) {
                    prod->incrementarStock(linea.getCantidad());
                }
            }
            lista.erase(it);
            return true;
        }
    }
    return false;
}

venta* gestorVentas::buscarPorCliente(const std::string& cliente) {
    for (auto& v : lista) {
        if (v.getCliente() == cliente) {
            return &v;
        }
    }
    return nullptr;
}

const venta* gestorVentas::buscarPorCliente(const std::string& cliente) const {
    for (const auto& v : lista) {
        if (v.getCliente() == cliente) {
            return &v;
        }
    }
    return nullptr;
}

bool gestorVentas::modificarVenta(int id, const std::string& nuevaFecha, const std::string& nuevoCliente) {
    for (auto& v : lista) {
        if (v.getId() == id) {
            if (!nuevaFecha.empty()) {
                v.setFecha(nuevaFecha);
            }
            if (!nuevoCliente.empty()) {
                v.setCliente(nuevoCliente);
            }
            return true;
        }
    }
    return false;
}

void gestorVentas::ordenarPorCliente() {
    std::sort(lista.begin(), lista.end(), [](const venta& a, const venta& b) {
        return a.getCliente() < b.getCliente();
    });
}

void gestorVentas::mostrarVentas() const {
    if (lista.empty()) {
        std::cout << "\nSin ventas registradas\n";
        return;
    }
    std::cout << "\nVENTAS REGISTRADAS\n";
    for (const auto& v : lista) {
        std::cout << "ID: " << v.getId()
                  << " | Cliente: " << v.getCliente()
                  << " | Fecha: " << v.getFecha()
                  << " | Total: $" << v.getTotal() << "\n";
    }
}

double gestorVentas::totalVendido() const {
    double total = 0.0;
    for (const auto& v : lista) {
        total += v.getTotal();
    }
    return total;
}
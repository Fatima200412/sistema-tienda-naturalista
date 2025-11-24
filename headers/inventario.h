#pragma once
#include <string>
#include <vector>
#include "producto.h"

class inventario {
private:
    std::vector<producto> productos;
    const int MIN_STOCK = 3;

public:
    //constructores 
    inventario() = default;
    inventario(const std::vector<producto>& prod) : productos(prod) {}
  

    // m�todos
    void capturar(const producto& p);
    bool eliminar(const std::string& nombre);
    int  buscarPorNombre(const std::string& nombre) const;
    bool modificar(const std::string& nombre, const producto& nuevo);
    void ordenarPorNombre();
    void consultar() const;
    std::vector<producto> productosEnBajoStock() const;
    producto* obtenerPorId(int id);
    const producto* obtenerPorId(int id) const;
    size_t totalProductos() const { return productos.size(); }
};

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
  

    // métodos
    void capturar(const producto& p);
    bool eliminar(const std::string& nombre);
    int  buscarPorNombre(const std::string& nombre) const;
    bool modificar(const std::string& nombre, const producto& nuevo);
    void ordenarPorNombre();
    void consultar() const;
    void consultarPorNombre(const std::string& nombre) const;

    std::vector<producto> productosEnBajoStock() const;
    producto* obtenerPorId(int id);
    const producto* obtenerPorId(int id) const;
};

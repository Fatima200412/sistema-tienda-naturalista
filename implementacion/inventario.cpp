#include "inventario.h"
#include <iostream>

using std::cout;
using std::endl;

// CAPTURAR: agrega o reemplaza por nombre
void inventario::capturar(const producto& p) {
    int idx = buscarPorNombre(p.getNombre());
    if (idx >= 0) {
        productos[static_cast<size_t>(idx)] = p; // reemplaza
    }
    else {
        productos.push_back(p);                  // agrega
    }
}

// ELIMINAR: por nombre 
bool inventario::eliminar(const std::string& nombre) {
    for (size_t i = 0; i < productos.size(); ++i) {
        if (productos[i].getNombre() == nombre) {
            productos.erase(productos.begin() + static_cast<long>(i));
            return true;
        }
    }
    return false;
}

// BUSCAR POR NOMBRE: devuelve índice o -1 si no existe
int inventario::buscarPorNombre(const std::string& nombre) const {
    for (size_t i = 0; i < productos.size(); ++i) {
        if (productos[i].getNombre() == nombre) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// MODIFICAR: reemplaza producto encontrado por nombre
bool inventario::modificar(const std::string& nombre, const producto& nuevo) {
    int idx = buscarPorNombre(nombre);
    if (idx >= 0) {
        productos[static_cast<size_t>(idx)] = nuevo;
        return true;
    }
    return false;
}

// ORDENAR POR NOMBRE: metodo burbuja
void inventario::ordenarPorNombre() {
    if (productos.size() < 2) return;
    for (size_t i = 0; i < productos.size() - 1; ++i) {
        for (size_t j = 0; j < productos.size() - i - 1; ++j) {
            if (productos[j].getNombre() > productos[j + 1].getNombre()) {
                producto tmp = productos[j];
                productos[j] = productos[j + 1];
                productos[j + 1] = tmp;
            }
        }
    }
}

// CONSULTAR: muestra inventario y alertas de bajo stock
void inventario::consultar() const {
    cout << "--- inventario ---" << endl;
    if (productos.empty()) {
        cout << "(sin productos)" << endl;
    }
    else {
        for (const auto& p : productos) {
            cout << "ID: " << p.getID()
                << " | Nombre: " << p.getNombre()
                << " | Categoria: " << p.getCategoria()
                << " | Precio: $" << p.getPrecio()
                << " | Stock: " << p.getCantidadEnStock()
                << endl;
        }
    }

    auto bajos = productosEnBajoStock();
    if (!bajos.empty()) {
        cout << "\n--- ALERTAS (stock <= " << MIN_STOCK << ") ---" << endl;
        for (const auto& p : bajos) {
            cout << "ALERTA: " << p.getNombre()
                << " | Stock: " << p.getCantidadEnStock()
                << endl;
        }
    }
}
//CONSULTAR POR NOMBRE recibe el nombre a buscar 
void inventario::consultarPorNombre(const string& nombre) const {
    //usa el metodo buscar por nombre para obtener el indice 
    int idx = buscarPorNombre(nombre);
    if (idx >= 0) {
        const producto& p = productos[static_cast<size_t>(idx)];
        cout << "ID: " << p.getID()
            << " | Nombre: " << p.getNombre()
            << " | Categoria: " << p.getCategoria()
            << " | Precio: $" << p.getPrecio()
            << " | Stock: " << p.getCantidadEnStock()
            << endl;
    }//si encuentra el producto muestra la info
    else {
        cout << "Producto no encontrado." << endl;//si el producto no existe muestra este mensaje 
    }
}


// PRODUCTOS EN BAJO STOCK (<= MIN_STOCK)
std::vector<producto> inventario::productosEnBajoStock() const {
    std::vector<producto> res;
    for (const auto& p : productos) {
        if (p.getCantidadEnStock() <= MIN_STOCK) {
            res.push_back(p);
        }
    }
    return res;
}
producto* inventario::obtenerPorId(int id) {
    for (auto& p : productos) if (p.getID() == id) return &p;
    return nullptr;
}
//obtener producto por id 
const producto* inventario::obtenerPorId(int id) const {
    for (const auto& p : productos) if (p.getID() == id) return &p;
    return nullptr;
}
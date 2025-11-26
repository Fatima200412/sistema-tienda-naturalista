//headers necesarios:
#include "reportes.h"
#include "inventario.h"
#include "gestorVentas.h"
#include "producto.h"
#include "venta.h"
#include "lineaVenta.h"

//librerias necesarias 
#include <sstream>   
#include <fstream>   // libreria para manejar archivos 
#include <iostream> 
#include <string>

using namespace std;


//implementacion de los metodos de la clase reportes 

//reporte de inventario
/* recibe un inventario por referencia para leerlo y devuelve un string con el reporte */
string reportes::reporteInventario(const inventario& inv) const {
    ostringstream oss;//la clase ostringstream pertenece a la libreria sstream, sirve para guardar info en un string, todo se va almacenando en el objeto oss(output string stream)

    oss << "===== REPORTE DE INVENTARIO (BAJO STOCK) =====\n\n";

    // Usamos el metodo existente en inventario
    auto bajos = inv.productosEnBajoStock();

    if (bajos.empty()) {
        oss << "No hay productos con stock menor o igual al minimo.\n";
    }
    else {
        oss << "ID\tNombre\tCategoria\tPrecio\tStock\n";
        oss << "-----------------------------------------------\n";
        for (const auto& p : bajos) {
            oss << p.getID() << '\t'
                << p.getNombre() << '\t'
                << p.getCategoria() << '\t'
                << p.getPrecio() << '\t'
                << p.getCantidadEnStock() << '\n';
        }
    }

    oss << '\n';
    return oss.str();
}

//reporte de ventas 
/* al igual que reporteInventario utiliza la clase ostringstream para guardar
info en memoria en un string*/

string reportes::reporteVentas(const gestorVentas& gv) const {
    std::ostringstream oss;

    oss << "===== REPORTE DE VENTAS =====\n\n";

    // se piden  todas las ventas usando un rango muy amplio
    auto ventas = gv.ventasRango("0000-00-00", "9999-99-99");

    if (ventas.empty()) {
        oss << "No hay ventas registradas.\n";
        return oss.str();
    }

    double totalGlobal = 0.0;

    for (const auto& v : ventas) {//recorre items de cada venta 
        oss << "Fecha: " << v.getFecha() << '\n';
        oss << "Articulos:\n";

        const auto& items = v.getItems();
        for (const auto& it : items) {
            oss << "  - [" << it.getProductoID() << "] "
                << it.getNombreProducto()
                << " | Cantidad: " << it.getCantidad()
                << " | Precio unitario: $" << it.getPrecioUnitario()
                << " | Subtotal: $" << it.subTotal()
                << '\n';
        }

        oss << "Total de la venta: $" << v.getTotal() << "\n";
        oss << "----------------------------------------\n";

        totalGlobal += v.getTotal();
    }

    oss << "\nTOTAL GENERAL VENDIDO: $" << totalGlobal << "\n\n";
    return oss.str();
}


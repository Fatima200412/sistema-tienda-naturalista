#include "empleado.h"
#include "inventario.h"
#include "gestorVentas.h"
#include "venta.h"
#include "producto.h"

// Solo estas operaciones estan permitidas al empleado
bool empleado::tienePermiso(const std::string& operacion) {
    return (operacion == "registrarProducto" ||
        operacion == "registrarVenta" ||
        operacion == "consultarInventario" ||
        operacion == "mostrar" ||
        operacion == "buscar" ||
        operacion == "ordenarPorNombre");
}

void empleado::registrarProducto(inventario& inv, const producto& p) const {
    inv.capturar(p);
}

bool empleado::registrarVenta(gestorVentas& gv, inventario& inv, venta& v) const {
    return gv.registrarVenta(v, inv); // confirma y descuenta stock
}

void empleado::consultarInventario(const inventario& inv) const {
    inv.consultar(); // muestra inventario + alertas de bajo stock
}
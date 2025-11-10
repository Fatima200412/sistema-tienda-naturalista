#include "venta.h"
#include "inventario.h"
#include "producto.h"

// agrega un item a la venta
void venta::agregarItem(const lineaVenta& lv) {
    items.push_back(lv);
}

// suma cantidad * precioUnitario de cada linea y guarda en 'total'
double venta::calcularTotal() {
    total = 0.0;
    for (const auto& it : items) {
        total += it.subTotal();
    }
    return total;
}

// confirma la venta: verifica stock de TODOS los items y, si alcanza,
// descuenta del inventario y actualiza 'total'.
bool venta::confirmar(inventario& inv) {
    // --- PASO 1: verificar disponibilidad ---
    for (const auto& it : items) {
        // Requiere inventario::obtenerPorId(int)
        producto* p = inv.obtenerPorId(it.getProductoID());
        if (!p) return false;                               // no existe el producto
        if (p->getCantidadEnStock() < it.getCantidad())     // stock insuficiente
            return false;
    }

    // --- PASO 2: descontar stock ---
    for (const auto& it : items) {
        producto* p = inv.obtenerPorId(it.getProductoID());
        p->disminuirStock(it.getCantidad());
    }

    // --- PASO 3: calcular total ---
    calcularTotal();
    return true;
}
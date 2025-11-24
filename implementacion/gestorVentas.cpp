#include "gestorVentas.h"
#include "inventario.h"  


namespace {
    // comprobacion para las fechas 
    inline bool enRango(const std::string& f,
        const std::string& ini,
        const std::string& fin) {
        return (f >= ini && f <= fin);
    }
}

bool gestorVentas::registrarVenta(venta& v, inventario& inv) {
    // confirma (verifica stock y descuenta) y guarda en historial
    if (v.confirmar(inv)) {
        historial.push_back(v);
        return true;
    }
    return false;
}

std::vector<venta> gestorVentas::ventasRango(const std::string& inicio,
    const std::string& fin) const {
    std::vector<venta> res;
    for (const auto& ve : historial) {
        if (enRango(ve.getFecha(), inicio, fin)) {
            res.push_back(ve);
        }
    }
    return res;
}

double gestorVentas::totalVendidoRango(const std::string& inicio,
    const std::string& fin) const {
    double total = 0.0;
    for (const auto& ve : historial) {
        if (enRango(ve.getFecha(), inicio, fin)) {
            total += ve.getTotal();
        }
    }
    return total;
}
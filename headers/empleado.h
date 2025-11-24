#pragma once
#include <string>
#include "usuario.h"

// clases de las que empleado  hace uso
class inventario;
class gestorVentas;
class producto;
class venta;

class empleado : public usuario {
public:
    // constructor
    empleado(const string& nomb, int id)
        : usuario(nomb,"empleado",id) {
    }

    // permisos limitados del empleado
    bool tienePermiso(const string& operacion) override;

    // operaciones del empleado
    void registrarProducto(inventario& inv, const producto& p) const;
    bool registrarVenta(gestorVentas& gv, inventario& inv, venta& v) const;
    void consultarInventario(const inventario& inv) const;
};
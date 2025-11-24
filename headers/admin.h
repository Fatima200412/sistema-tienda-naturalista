#pragma once
#include "usuario.h"
#include <string>

class inventario;
class gestorVentas;
class reportes;
class autenticador;

class admin : public usuario {
public:
    // CONSTRUCTOR PARA USUARIO CON ROL DE ADMIN
    admin(const string& nomb, int id)
        : usuario(nomb, "admin", id) {
    }

    // el admin siempre tiene permiso
    bool tienePermiso(const string& operacion) override;

    // usa reportes + inventario + gestorVentas
    void generarReporte(reportes& rep,
        const inventario& inv,
        const gestorVentas& gv);

    // usa autenticador para gestionar usuarios
    void administrarUsuarios(autenticador& auth);
};
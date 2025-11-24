#include "admin.h"
#include "inventario.h"
#include "gestorVentas.h"
#include "reportes.h"
#include "autenticador.h"
#include "empleado.h"

#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

// el admin tiene permiso para cualquier operacion
bool admin::tienePermiso(const string& operacion) {
    cout << "El admin " << nombre
        << " tiene permiso para realizar: " << operacion << endl;
    return true;
}

// GENERAR REPORTES (inventario o ventas)
void admin::generarReporte(reportes& rep,
    const inventario& inv,
    const gestorVentas& gv) {
    int opcion;
    cout << "\n=== GENERAR REPORTE ===\n";
    cout << "1) Reporte de inventario (bajo stock)\n";
    cout << "2) Reporte de ventas\n";
    cout << "Opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1: {
        string texto = rep.reporteInventario(inv);
        cout << "\n" << texto;
        break;
    }
    case 2: {
        string texto = rep.reporteVentas(gv);
        cout << "\n" << texto;
        break;
    }
    default:
        cout << "Opcion no valida.\n";
        break;
    }
}

// ADMINISTRAR USUARIOS (ejemplo: registrar empleados y cerrar sesion)
void admin::administrarUsuarios(autenticador& auth) {
    int opcion;
    cout << "\n=== ADMINISTRACION DE USUARIOS ===\n";
    cout << "1) Registrar nuevo empleado\n";
    cout << "2) Cerrar sesion actual\n";
    cout << "Opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1: {
        string nomb;
        int id;
        cout << "Nombre del empleado: ";
        cin >> nomb;
        cout << "ID (tambien sera su contrasena): ";
        cin >> id;

        empleado* e = new empleado(nomb, id);
        auth.registrarUsuario(e);
        cout << "Empleado registrado correctamente.\n";
        break;
    }
    case 2:
        auth.logout();
        cout << "Sesion cerrada por el admin.\n";
        break;

    default:
        cout << "Opcion no valida.\n";
        break;
    }
}

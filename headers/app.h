
#pragma once

#include "inventario.h"
#include "gestorVentas.h"
#include "reportes.h"
#include "autenticador.h"

//clase aplicacion es el cerebro del sistema 
class app {
private:
    inventario inv;        // manejo de productos
    gestorVentas gv;       // historial de ventas
    reportes rep;          // generador de reportes
    autenticador auth;     // sistema de login

public:
    app();

    void run();                // ciclo principal
    void mostrarMenu();        // menú visible según rol
    void manejarOpcion(int op);// ejecuta la opción que elija el usuario
};
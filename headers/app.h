
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
    void mostrarMenu();        // men� visible seg�n rol
    void manejarOpcion(int op);// ejecuta la opci�n que elija el usuario
};
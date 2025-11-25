#include "app.h"
#include "admin.h"
#include "empleado.h"
#include "producto.h"
#include "venta.h"
#include <iostream>

using namespace std;

/*
====================================================================
 CONSTRUCTOR DE app
 - Inicializa la aplicaci�n.
 - Registra usuarios por defecto (admin y empleados).
 - Estos usuarios son gestionados por el autenticador (auth).
====================================================================
*/
app::app() {
    // Usuarios de ejemplo. El ID funciona como contrase�a.
    admin* a1 = new admin("admin", 111);
    empleado* e1 = new empleado("empleado1", 222);
    empleado* e2 = new empleado("empleado2", 333);

    auth.registrarUsuario(a1);
    auth.registrarUsuario(e1);
    auth.registrarUsuario(e2);
}

/*
====================================================================
 M�TODO run()
 - Es el ciclo principal del programa.
 - Primero obliga al usuario a iniciar sesi�n.
 - Despu�s muestra el men� repetidamente hasta que el usuario elija "0".
====================================================================
*/
void app::run() {
    cout << "===== SISTEMA DE TIENDA NATURISTA =====\n\n";

    string user, pass;

    // BUCLE DE AUTENTICACI�N
    while (!auth.estaAutenticado()) {
        cout << "Usuario: ";
        cin >> user;
        cout << "Contrasena (ID): ";
        cin >> pass;

        // Si login falla se pide intentar de nuevo.
        if (!auth.login(user, pass)) {
            cout << "\nIntentar de nuevo.\n";
        }
    }

    int opcion;

    // BUCLE PRINCIPAL DEL MENU
    do {
        mostrarMenu();      // Imprime el men� correspondiente al rol
        cout << "\nOpcion: ";
        cin >> opcion;
        manejarOpcion(opcion);  // Ejecuta la opcion seleccionada

    } while (opcion != 0);

    cout << "Saliendo del sistema...\n";
    auth.logout(); // Cierra sesi�n al terminar
}

/*
====================================================================
 M�TODO mostrarMenu()
 - Muestra opciones dependiendo del rol del usuario (admin/empleado).
 - Admin tiene opciones extra.
====================================================================
*/
void app::mostrarMenu() {
    usuario* u = auth.usuarioActual();

    cout << "\n===== MENU PRINCIPAL =====\n";
    cout << "Usuario: " << u->getNombre() << " (" << u->getRol() << ")\n\n";

    // Opciones disponibles para ambos roles
    cout << "1. Mostrar inventario\n";
    cout << "2. Capturar producto\n";
    cout << "3. Eliminar producto\n";
    cout << "4. Modificar producto\n";
    cout << "5. Ordenar inventario por nombre\n";
    cout << "6. Registrar venta\n";
    cout << "7. Generar reportes (solo admin)\n";
    cout << "8. Generar reporte de ventas (rapido)\n";

    // Opcion extra solo para admin
    if (u->getRol() == "admin") {
        cout << "9. Administrar usuarios (admin)\n";
    }

    // nueva opcion agregada: buscar producto por nombre
    cout << "10. Buscar producto por nombre\n";

    cout << "0. Salir\n";
}


/*
====================================================================
 M�TODO manejarOpcion(op)
 - Contiene toda la l�gica del men�.
 - Cada case corresponde a una opci�n del men�.
====================================================================
*/
void app::manejarOpcion(int op) {
    usuario* u = auth.usuarioActual();

    switch (op) {

        /*
        --------------------------------------------------------------
         1) Mostrar inventario completo con alerta de bajo stock
        --------------------------------------------------------------
        */
    case 1:
        inv.consultar();
        break;

        /*
        --------------------------------------------------------------
         2) Capturar producto
         - Solo permitido si el usuario tiene permiso.
        --------------------------------------------------------------
        */
    case 2: {
        if (!u->tienePermiso("registrarProducto")) {
            cout << "No tienes permiso.\n";
            return;
        }

        int id, stock;
        string nombre, categoria;
        double precio;

        // Captura de datos del producto
        cout << "ID: ";
        cin >> id;
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Categoria: ";
        cin >> categoria;
        cout << "Precio: ";
        cin >> precio;
        cout << "Stock: ";
        cin >> stock;

        producto p(id, nombre, categoria, precio, stock);
        inv.capturar(p);  // Se agrega o modifica producto

        cout << "Producto registrado.\n";
        break;
    }

          /*
          --------------------------------------------------------------
           3) Eliminar producto por nombre
          --------------------------------------------------------------
          */
    case 3: {
        string nombre;
        cout << "Nombre del producto a eliminar: ";
        cin >> nombre;
        if (inv.eliminar(nombre)) cout << "Eliminado.\n";
        else cout << "No existe.\n";
        break;
    }

          /*
          --------------------------------------------------------------
           4) Modificar producto
           - Reemplaza el producto que coincida con el nombre original.
          --------------------------------------------------------------
          */
    case 4: {
        string nombre;
        cout << "Nombre del producto a modificar: ";
        cin >> nombre;

        int id, stock;
        string categoria, newName;
        double precio;

        // Captura de nuevos datos
        cout << "Nuevo ID: ";
        cin >> id;
        cout << "Nuevo nombre: ";
        cin >> newName;
        cout << "Nueva categoria: ";
        cin >> categoria;
        cout << "Nuevo precio: ";
        cin >> precio;
        cout << "Nuevo stock: ";
        cin >> stock;

        producto nuevo(id, newName, categoria, precio, stock);

        if (inv.modificar(nombre, nuevo)) cout << "Modificado.\n";
        else cout << "No existe.\n";

        break;
    }

          /*
          --------------------------------------------------------------
           5) Ordenar productos por nombre (orden alfab�tico)
          --------------------------------------------------------------
          */
    case 5:
        inv.ordenarPorNombre();
        cout << "Inventario ordenado.\n";
        break;

        /*
        --------------------------------------------------------------
         6) Registrar una venta completa
         - Permite agregar varias lineas de venta
         - Verifica el stock al confirmar
        --------------------------------------------------------------
        */
    case 6: {
        int idProd, cantidad;
        string fecha;

        cout << "Fecha (AAAA-MM-DD): ";
        cin >> fecha;

        venta v(1, fecha); // ID simple para la venta

        // Agregar productos a la venta
        while (true) {
            cout << "ID producto (0 para terminar): ";
            cin >> idProd;
            if (idProd == 0) break;

            producto* p = inv.obtenerPorId(idProd);
            if (!p) {
                cout << "No existe el producto.\n";
                continue;
            }

            cout << "Cantidad: ";
            cin >> cantidad;

            // Crear l�nea de venta
            lineaVenta lv(idProd, p->getNombre(), cantidad, p->getPrecio());
            v.agregarItem(lv);
        }

        // Registrar la venta
        if (gv.registrarVenta(v, inv)) cout << "Venta registrada.\n";
        else cout << "Error: stock insuficiente.\n";

        break;
    }

          /*
          --------------------------------------------------------------
           7) Generar reportes (solo admin)
           - Llama directamente a admin::generarReporte()
          --------------------------------------------------------------
          */
    case 7: {
        if (u->getRol() != "admin") {
            cout << "Solo el administrador puede generar reportes.\n";
            break;
        }

        admin* a = dynamic_cast<admin*>(u);
        if (!a) {
            cout << "Error interno: el usuario no es admin.\n";
            break;
        }

        a->generarReporte(rep, inv, gv);
        break;
    }

          /*
          --------------------------------------------------------------
           8) Generar reporte r�pido de ventas (cualquier rol)
          --------------------------------------------------------------
          */
    case 8: {
        string repTxt = rep.reporteVentas(gv);
        cout << repTxt;
        break;
    }

          /*
          --------------------------------------------------------------
           9) Administrar usuarios (solo admin)
           - Llama admin::administrarUsuarios(auth)
          --------------------------------------------------------------
          */
    case 9: {
        if (u->getRol() != "admin") {
            cout << "Solo el administrador puede administrar usuarios.\n";
            break;
        }

        admin* a = dynamic_cast<admin*>(u);
        if (!a) {
            cout << "Error interno: el usuario no es admin.\n";
            break;
        }

        a->administrarUsuarios(auth);
        break;
    }
          // opcion 10: buscar un producto por nombre
    case 10: {
        string nombre;
        cout << "Nombre del producto a buscar: ";
        cin >> nombre;

        // llama al nuevo metodo del inventario para mostrar el producto
        inv.consultarPorNombre(nombre);
        break;
    }


          /*
          --------------------------------------------------------------
           0) Salir del programa
          --------------------------------------------------------------
          */
    case 0:
        break;

        /*
        --------------------------------------------------------------
         DEFAULT) Opcion inv�lida
        --------------------------------------------------------------
        */
    default:
        cout << "Opcion invalida.\n";
        break;
    }
}
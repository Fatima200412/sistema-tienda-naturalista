#include "app.h"
#include "admin.h"
#include "empleado.h"
#include "producto.h"
#include "venta.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// funcion auxiliar para leer un entero desde consola con validacion
int leerEntero(const string& mensaje) {
    string token;
    int valor = 0;
    bool ok = false;

    while (!ok) {
        cout << mensaje;
        cin >> token;

        if (token.empty()) {
            continue;
        }

        bool soloDigitos = true;
        for (char c : token) {
            if (c < '0' || c > '9') {
                soloDigitos = false;
                break;
            }
        }

        if (!soloDigitos) {
            cout << "Error: debe ingresar un numero entero.\n";
            continue;
        }

        // parseo manual
        valor = 0;
        for (char c : token) {
            valor = valor * 10 + (c - '0');
        }
        ok = true;
    }

    return valor;
}

// funcion auxiliar para leer un double desde consola con validacion simple
double leerDouble(const string& mensaje) {
    string token;
    double valor = 0.0;
    bool ok = false;

    while (!ok) {
        cout << mensaje;
        cin >> token;

        if (token.empty()) {
            continue;
        }

        bool formatoValido = true;
        bool puntoVisto = false;

        for (char c : token) {
            if (c == '.') {
                if (puntoVisto) {
                    formatoValido = false;
                    break;
                }
                puntoVisto = true;
            }
            else if (c < '0' || c > '9') {
                formatoValido = false;
                break;
            }
        }

        if (!formatoValido) {
            cout << "Error: debe ingresar un numero valido.\n";
            continue;
        }

        // parseo con istringstream
        std::istringstream iss(token);
        iss >> valor;
        ok = true;
    }

    return valor;
}

/*
CONSTRUCTOR DE app
- Inicializa la aplicacion.
- Registra usuarios por defecto (admin y empleados).
- Estos usuarios son gestionados por el autenticador (auth).
*/
app::app() {
    // Usuarios de ejemplo. El ID funciona como contrasena.
    admin* a1 = new admin("admin", 111);
    empleado* e1 = new empleado("empleado1", 222);
    empleado* e2 = new empleado("empleado2", 333);

    auth.registrarUsuario(a1);
    auth.registrarUsuario(e1);
    auth.registrarUsuario(e2);

    // Productos de ejemplo para que el inventario no inicie vacio
    inv.capturar(producto(1, "cafe", "bebidas", 49.9, 10));
    inv.capturar(producto(2, "maple", "dulces", 79.0, 5));
    inv.capturar(producto(3, "skwinkles", "dulces", 18.0, 45));
    inv.capturar(producto(4, "fuze_tea", "bebidas", 22.0, 25));
    inv.capturar(producto(5, "takis", "frituras", 22.0, 15));
}

/*
METODO run()
- Es el ciclo principal del programa.
- Primero obliga al usuario a iniciar sesion.
- Despues muestra el menu repetidamente hasta que el usuario elija "0".
*/
void app::run() {
    cout << "===== SISTEMA DE TIENDA NATURISTA =====\n\n";

    string user, pass;

    // BUCLE DE AUTENTICACION
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
        mostrarMenu();      // Imprime el menu correspondiente al rol
        cout << "\nOpcion: ";
        cin >> opcion;
        manejarOpcion(opcion);  // Ejecuta la opcion seleccionada

    } while (opcion != 0);

    cout << "Saliendo del sistema...\n";
    auth.logout(); // Cierra sesion al terminar
}

/*
METODO mostrarMenu()
- Muestra opciones dependiendo del rol del usuario (admin/empleado).
- Admin tiene opciones extra.
*/
void app::mostrarMenu() {
    usuario* u = auth.usuarioActual();

    cout << "\n===== MENU PRINCIPAL =====\n";
    cout << "Usuario: " << u->getNombre() << " (" << u->getRol() << ")\n\n";

    // Opciones disponibles para ambos roles
    cout << "1. Mostrar inventario\n";
    cout << "2. Capturar producto\n";
    cout << "3. Eliminar producto\n";
    cout << "4. Modificar producto(solo admin)\n";
    cout << "5. Ordenar inventario por nombre\n";
    cout << "6. Registrar venta\n";
    cout << "7. Generar reportes (solo admin)\n";

    // Opcion extra solo para admin
    if (u->getRol() == "admin") {
        cout << "8. Administrar usuarios (admin)\n";
    }

    // nueva opcion agregada: buscar producto por nombre
    cout << "9. Buscar producto por nombre\n";

    cout << "0. Salir\n";
}



/*
METODO manejarOpcion(op)
- Contiene toda la logica del menu.
- Cada case corresponde a una opcion del menu.
*/
void app::manejarOpcion(int op) {
    usuario* u = auth.usuarioActual();

    switch (op) {

        /*
        1) Mostrar inventario completo con alerta de bajo stock
        */
    case 1:
        inv.consultar();
        break;

        /*
        2) Capturar producto
        - Solo permitido si el usuario tiene permiso.
        */
    case 2: {
        if (!u->tienePermiso("registrarProducto")) {
            cout << "No tienes permiso.\n";
            return;
        }

        int id, stock;
        string nombre, categoria;
        double precio;

        // Captura de datos del producto con validacion
        id = leerEntero("ID: ");

        cout << "Nombre: ";
        cin >> nombre;

        cout << "Categoria: ";
        cin >> categoria;

        precio = leerDouble("Precio: ");

        stock = leerEntero("Stock: ");

        producto p(id, nombre, categoria, precio, stock);
        inv.capturar(p);  // Se agrega o modifica producto

        cout << "Producto registrado.\n";
        break;
    }

          /*
          3) Eliminar producto por nombre
          */
    case 3: {
        // solo admin puede eliminar productos
        if (u->getRol() != "admin") {
            cout << "Solo el administrador puede usar esta opcion.\n";
            break;
        }
        string nombre;
        cout << "Nombre del producto a eliminar: ";
        cin >> nombre;
        if (inv.eliminar(nombre)) cout << "Eliminado.\n";
        else cout << "No existe.\n";
        break;
    }

          /*
          4) Modificar producto
          - Reemplaza el producto que coincida con el nombre original.
          */
    case 4: {
        // Solo el administrador puede modificar productos
        if (u->getRol() != "admin") {
            cout << "Solo el administrador puede modificar productos.\n";
            break;
        }

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
          5) Ordenar productos por nombre (orden alfabético)
          */
    case 5:
        // solo admin puede ordenar inventario
        if (u->getRol() != "admin") {
            cout << "Solo el administrador puede usar esta opcion.\n";
            break;
        }
        inv.ordenarPorNombre();
        cout << "Inventario ordenado.\n";
        break;

        /*
        6) Registrar una venta completa
        - Permite agregar varias lineas de venta
        - Verifica el stock al confirmar
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

            // Crear línea de venta
            lineaVenta lv(idProd, p->getNombre(), cantidad, p->getPrecio());
            v.agregarItem(lv);
        }

        // Registrar la venta
        if (gv.registrarVenta(v, inv)) cout << "Venta registrada.\n";
        else cout << "Error: stock insuficiente.\n";

        break;
    }

          /*
          7) Generar reportes (solo admin)
          - Llama directamente a admin::generarReporte()
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
          9) Administrar usuarios (solo admin)
          - Llama admin::administrarUsuarios(auth)
          */
    case 8: {
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
          // opcion 9: buscar un producto por nombre (disponible para ambos)
    case 9: {
        string nombre;
        cout << "Nombre del producto a buscar: ";
        cin >> nombre;

        // llama al metodo del inventario para mostrar el producto
        inv.consultarPorNombre(nombre);
        break;
    }



          /*
          0) Salir del programa
          */
    case 0:
        break;

        /* DEFAULT) Opcion invalida */
    default:
        cout << "Opcion invalida.\n";
        break;
    }
}

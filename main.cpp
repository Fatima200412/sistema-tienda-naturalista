#include <iostream>
#include <iostream>
#include <string>
#include "headers/producto.h"
#include "headers/inventario.h"
#include "headers/venta.h"
#include "headers/lineaVenta.h"
#include "headers/gestorVentas.h"
#include "headers/autenticador.h"

using namespace std;

void pausar();
bool esAdmin(const usuario* u);
void menuEmpleados(autenticador& auth, usuario* u);
void menuProductos(inventario& inv, usuario* u);
void menuVentas(gestorVentas& gv, inventario& inv, usuario* u);

int siguienteProductoID = 1;
int siguienteVentaID = 1;

int main() {
    inventario inv;
    gestorVentas gv;
    autenticador auth;

    inv.capturar(producto(siguienteProductoID++, "vitamina c", "vitaminas", 150.0, 10));
    inv.capturar(producto(siguienteProductoID++, "omega 3", "suplementos", 320.0, 5));
    inv.capturar(producto(siguienteProductoID++, "te verde", "infusiones", 85.0, 3));

    cout << "SISTEMA DE TIENDA NATURALISTA" << endl;
    usuario* actual = nullptr;
    while (!actual) {
        int id; string rol;
        cout << "ID: ";
        cin >> id; cin.ignore();
        cout << "Rol (admin/empleado): ";
        getline(cin, rol);
        actual = auth.login(id, rol);
        if (!actual) cout << "Datos incorrectos, intente otra vez\n";
    }
    cout << "Bienvenido " << actual->getNombre() << " (" << actual->getRol() << ")\n";

    int opcion = 0;
    do {
        cout << "\nMENU PRINCIPAL\n";
        cout << "1. Empleados\n";
        cout << "2. Productos\n";
        cout << "3. Ventas\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion; cin.ignore();
        switch (opcion) {
            case 1: menuEmpleados(auth, actual); break;
            case 2: menuProductos(inv, actual); break;
            case 3: menuVentas(gv, inv, actual); break;
            case 4: cout << "Hasta pronto\n"; break;
            default: cout << "Opcion invalida\n"; break;
        }
    } while (opcion != 4);

    return 0;
}

bool esAdmin(const usuario* u) {
    return u && u->getRol() == "admin";
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

void menuEmpleados(autenticador& auth, usuario* u) {
    if (!esAdmin(u)) {
        cout << "Solo el administrador puede usar este menu\n";
        pausar();
        return;
    }

    int op = 0;
    do {
        cout << "\nMENU EMPLEADOS\n";
        cout << "1. Capturar\n";
        cout << "2. Mostrar\n";
        cout << "3. Eliminar\n";
        cout << "4. Buscar\n";
        cout << "5. Modificar\n";
        cout << "6. Ordenar por nombre\n";
        cout << "7. Consultar\n";
        cout << "8. Salir\n";
        cout << "Opcion: ";
        cin >> op; cin.ignore();

        switch (op) {
            case 1: {
                int id;
                string nombre;
                cout << "ID (0=auto): ";
                cin >> id; cin.ignore();
                cout << "Nombre: ";
                getline(cin, nombre);
                auto* nuevo = auth.agregarEmpleado(id, nombre);
                if (nuevo) cout << "Empleado guardado con ID " << nuevo->getId() << "\n";
                else cout << "No se pudo guardar\n";
                pausar();
                break;
            }
            case 2: {
                const auto& lista = auth.obtenerEmpleados();
                if (lista.empty()) cout << "Sin empleados\n";
                else {
                    for (const auto& e : lista) {
                        cout << "ID: " << e.getId() << " | Nombre: " << e.getNombre() << "\n";
                    }
                }
                pausar();
                break;
            }
            case 3: {
                string nombre;
                cout << "Nombre a eliminar: ";
                getline(cin, nombre);
                if (auth.eliminarEmpleado(nombre)) cout << "Empleado eliminado\n";
                else cout << "No existe\n";
                pausar();
                break;
            }
            case 4: {
                string nombre;
                cout << "Nombre a buscar: ";
                getline(cin, nombre);
                const empleado* emp = auth.buscarEmpleado(nombre);
                if (emp) cout << "Encontrado -> ID: " << emp->getId() << "\n";
                else cout << "No existe\n";
                pausar();
                break;
            }
            case 5: {
                string nombre;
                cout << "Nombre actual: ";
                getline(cin, nombre);
                int nuevoId;
                cout << "Nuevo ID (0=mantener): ";
                cin >> nuevoId; cin.ignore();
                string nuevoNom;
                cout << "Nuevo nombre: ";
                getline(cin, nuevoNom);
                if (auth.modificarEmpleado(nombre, nuevoId, nuevoNom)) cout << "Empleado modificado\n";
                else cout << "No se pudo modificar\n";
                pausar();
                break;
            }
            case 6: {
                auth.ordenarPorNombre();
                cout << "Lista ordenada\n";
                pausar();
                break;
            }
            case 7: {
                const auto& lista = auth.obtenerEmpleados();
                cout << "Total empleados: " << lista.size() << "\n";
                pausar();
                break;
            }
            case 8:
                cout << "Volviendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
                pausar();
        }

    } while (op != 8);
}

void menuProductos(inventario& inv, usuario* u) {
    bool admin = esAdmin(u);
    int op = 0;

    do {
        cout << "\nMENU PRODUCTOS\n";
        cout << "1. Capturar\n";
        cout << "2. Mostrar\n";
        cout << "3. Eliminar\n";
        cout << "4. Buscar\n";
        cout << "5. Modificar\n";
        cout << "6. Ordenar por nombre\n";
        cout << "7. Consultar\n";
        cout << "8. Salir\n";
        cout << "Opcion: ";
        cin >> op; cin.ignore();

        switch (op) {
            case 1: {
                int id;
                string nombre, categoria;
                double precio;
                long stock;
                cout << "ID (0=auto): ";
                cin >> id; cin.ignore();
                if (id == 0) id = siguienteProductoID++;
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "Categoria: ";
                getline(cin, categoria);
                cout << "Precio: ";
                cin >> precio;
                cout << "Stock: ";
                cin >> stock; cin.ignore();
                inv.capturar(producto(id, nombre, categoria, precio, stock));
                cout << "Producto guardado\n";
                pausar();
                break;
            }
            case 2: {
                inv.consultar();
                pausar();
                break;
            }
            case 3: {
                if (!admin) { cout << "Solo admin\n"; pausar(); break; }
                string nombre;
                cout << "Nombre a eliminar: ";
                getline(cin, nombre);
                if (inv.eliminar(nombre)) cout << "Eliminado\n"; else cout << "No encontrado\n";
                pausar();
                break;
            }
            case 4: {
                if (!admin) { cout << "Solo admin\n"; pausar(); break; }
                string nombre;
                cout << "Nombre a buscar: ";
                getline(cin, nombre);
                int pos = inv.buscarPorNombre(nombre);
                if (pos >= 0) cout << "Encontrado en posicion " << pos << "\n";
                else cout << "No existe\n";
                pausar();
                break;
            }
            case 5: {
                if (!admin) { cout << "Solo admin\n"; pausar(); break; }
                string buscar;
                cout << "Nombre actual: ";
                getline(cin, buscar);
                if (inv.buscarPorNombre(buscar) < 0) {
                    cout << "No existe\n";
                    pausar();
                    break;
                }
                int id;
                string nombre, categoria;
                double precio;
                long stock;
                cout << "Nuevo ID: ";
                cin >> id; cin.ignore();
                cout << "Nuevo nombre: ";
                getline(cin, nombre);
                cout << "Categoria: ";
                getline(cin, categoria);
                cout << "Precio: ";
                cin >> precio;
                cout << "Stock: ";
                cin >> stock; cin.ignore();
                inv.modificar(buscar, producto(id, nombre, categoria, precio, stock));
                cout << "Producto modificado\n";
                pausar();
                break;
            }
            case 6: {
                if (!admin) { cout << "Solo admin\n"; pausar(); break; }
                inv.ordenarPorNombre();
                cout << "Inventario ordenado\n";
                pausar();
                break;
            }
            case 7: {
                inv.consultar();
                cout << "Productos totales: " << inv.totalProductos() << "\n";
                pausar();
                break;
            }
            case 8:
                cout << "Volviendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
                pausar();
        }

    } while (op != 8);
}

void menuVentas(gestorVentas& gv, inventario& inv, usuario* u) {
    bool admin = esAdmin(u);
    int op = 0;

    do {
        cout << "\nMENU VENTAS\n";
        cout << "1. Capturar\n";
        cout << "2. Mostrar\n";
        cout << "3. Eliminar\n";
        cout << "4. Buscar\n";
        cout << "5. Modificar\n";
        cout << "6. Ordenar por nombre\n";
        cout << "7. Consultar\n";
        cout << "8. Salir\n";
        cout << "Opcion: ";
        cin >> op; cin.ignore();

        switch (op) {
            case 1: {
                string cliente, fecha;
                cout << "Cliente: ";
                getline(cin, cliente);
                cout << "Fecha (AAAA-MM-DD): ";
                getline(cin, fecha);
                venta v(siguienteVentaID++, fecha, cliente);
                char seguir = 's';
                while (seguir == 's' || seguir == 'S') {
                    int prodID, cantidad;
                    cout << "ID producto: ";
                    cin >> prodID;
                    const producto* prod = inv.obtenerPorId(prodID);
                    if (!prod) {
                        cout << "No existe ese producto\n";
                        cin.ignore();
                        continue;
                    }
                    cout << "Cantidad: ";
                    cin >> cantidad; cin.ignore();
                    if (cantidad <= 0 || cantidad > prod->getCantidadEnStock()) {
                        cout << "Cantidad no valida\n";
                        continue;
                    }
                    v.agregarItem(lineaVenta(prodID, prod->getNombre(), cantidad, prod->getPrecio()));
                    cout << "Agregar otro producto? (s/n): ";
                    cin >> seguir; cin.ignore();
                }
                if (gv.registrarVenta(v, inv)) cout << "Venta guardada. Total: $" << v.getTotal() << "\n";
                else cout << "No se pudo guardar\n";
                pausar();
                break;
            }
            case 2: {
                gv.mostrarVentas();
                pausar();
                break;
            }
            case 3: {
                if (!admin) { cout << "Solo admin\n"; pausar(); break; }
                int id;
                cout << "ID de la venta: ";
                cin >> id; cin.ignore();
                if (gv.eliminarVenta(id, inv)) cout << "Venta eliminada\n";
                else cout << "No se encontro\n";
                pausar();
                break;
            }
            case 4: {
                string cliente;
                cout << "Cliente a buscar: ";
                getline(cin, cliente);
                venta* ven = gv.buscarPorCliente(cliente);
                if (!ven) {
                    cout << "Sin registro\n";
                } else {
                    cout << "ID: " << ven->getId() << " | Fecha: " << ven->getFecha() << " | Total: $" << ven->getTotal() << "\n";
                    for (const auto& item : ven->getItems()) {
                        cout << "  - " << item.getNombreProducto() << " x" << item.getCantidad() << " ($" << item.getPrecioUnitario() << ")\n";
                    }
                }
                pausar();
                break;
            }
            case 5: {
                if (!admin) { cout << "Solo admin\n"; pausar(); break; }
                int id;
                cout << "ID venta: ";
                cin >> id; cin.ignore();
                string fecha, cliente;
                cout << "Nueva fecha (Enter = igual): ";
                getline(cin, fecha);
                cout << "Nuevo cliente (Enter = igual): ";
                getline(cin, cliente);
                if (gv.modificarVenta(id, fecha, cliente)) cout << "Venta actualizada\n";
                else cout << "No se encontro\n";
                pausar();
                break;
            }
            case 6: {
                if (!admin) { cout << "Solo admin\n"; pausar(); break; }
                gv.ordenarPorCliente();
                cout << "Ventas ordenadas\n";
                pausar();
                break;
            }
            case 7: {
                cout << "Ventas registradas: " << gv.totalRegistros() << "\n";
                cout << "Total vendido: $" << gv.totalVendido() << "\n";
                pausar();
                break;
            }
            case 8:
                cout << "Volviendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
                pausar();
        }

    } while (op != 8);
}
                    

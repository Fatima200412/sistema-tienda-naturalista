#include "autenticador.h"
#include <iostream>
#include <sstream>
#include <string>
//implementacion de los metodos

void autenticador::registrarUsuario(usuario* u) {
	if (u) {
		usuarios.push_back(u);//agrega usuarios
	}
}

// login sencillo: user = nombre, pass = ID convertido a string
bool autenticador::login(const string& user, const string& pass) {
    for (auto* u : usuarios) {
        if (!u) continue;

        // nombre debe coincidir
        if (u->getNombre() == user) {
            // contrase�a = ID como string
            string idComoTexto = std::to_string(u->getId());
            if (idComoTexto == pass) {
                actual = u;
                std::cout << "Inicio de sesion exitoso. Rol: "
                    << u->getRol() << '\n';
                return true;
            }
        }
    }

    // si no encontramos usuario de muestra error
    actual = nullptr;
    std::cout << "Error: usuario o contrasena incorrectos.\n";
    return false;
}

void autenticador::logout() {
    actual = nullptr;
    std::cout << "Sesion cerrada.\n";
}

usuario* autenticador::usuarioActual() {
    return actual;
}

const usuario* autenticador::usuarioActual() const {
    return actual;
}

bool autenticador::estaAutenticado() const {
    return actual != nullptr;
}


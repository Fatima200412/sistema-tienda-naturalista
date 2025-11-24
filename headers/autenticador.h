#pragma once

#include<vector>
#include<string>
#include"usuario.h"

class autenticador {
private: 
	vector <usuario*> usuarios;// usuarios registrados en el sistema 
	usuario* actual{ nullptr };//usuario que se esta autenticando 

public:
	autenticador() = default; //constructor 
	~autenticador() = default;//destructor 
	//metodos de la clase

	void registrarUsuario(usuario* u);//registro de usuarios en el sistema 

	bool login(const string& user, const string& pass);//inicio de sesion 

	void logout();// cerrar sesion 

	// devuelve el usuario autenticado (o nullptr si no hay sesion)
	usuario* usuarioActual();
	const usuario* usuarioActual() const;

	// indica si el  usuario esta autenticado
	bool estaAutenticado() const;

};

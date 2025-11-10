#pragma once

#include"usuario.h"

//la clase admin hereda de usuario

class admin : public usuario {
public:
	//CONSTRUCTOR PARA USUARIO CON ROL DE ADMIN 
	admin(string nomb, int id) :usuario(nombre, "admin", ID) {}
	//METODOS PARA EL ADMINISTRADOR
	bool tienePermiso(const string& operacion)override;
	void generarReporte(); 
	void administrarUsuarios();
};
#include"usuario.h"

//constructor
usuario::usuario (string nom, string rol, int id):nombre(nom),rol(rol),ID(id){}

//getters
	//getters necesarios
string usuario:: getNombre()const { return nombre; }
string usuario:: getRol()const { return rol; }
int usuario:: getId()const { return ID; }

//metodos
bool usuario::validarID(int id) {return this->ID == id;}
 bool usuario:: tienePermiso(const string& operacion){

    // En esta version base, no se definen permisos específicos.
    // Se puede sobreescribir en las clases derivadas (Admin, Empleado)
    cout << "El rol " << rol << " no tiene permisos definidos para la operacion: " << operacion << endl;
    return false;
}



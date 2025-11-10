#include "admin.h"

//la clase admin hereda de usuario 
// 
//METODOS PARA EL ADMINISTRADOR 
// 
// Metodo tienePermiso: el admin puede hacer cualquier operación 
bool admin::tienePermiso(const string& operacion) { 
	cout << "El admin tiene permiso para realizar: " << operacion << endl; return true; 
}
//metodo para generar reportes 
void admin::generarReporte(/*actualizar cuando exista clase reportes */) {
	cout << "Generando reporte de inventario y ventas..." << endl; 
} 
void admin::administrarUsuarios(/*actualizar cuando exista clase autenticador */) {
	cout << "admin administra usuarios " << endl;
}
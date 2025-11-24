#pragma once
#include "usuario.h"
class empleado : public usuario {
public:
    empleado(int i,const std::string& n):usuario(i,n,"empleado"){}
    void actualizar(int nuevoId, const std::string& nuevoNombre){
        id = nuevoId;
        nombre = nuevoNombre;
    }
};
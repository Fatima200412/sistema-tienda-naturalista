#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include "empleado.h"
#include "admin.h"

class autenticador {
private:
    admin adminGeneral;
    std::vector<empleado> lista;
    int sigId;
public:
    autenticador();
    usuario* login(int id,const std::string& rol);
    empleado* agregarEmpleado(int id,const std::string& nombre);
    bool eliminarEmpleado(const std::string& nombre);
    empleado* buscarEmpleado(const std::string& nombre);
    const empleado* buscarEmpleado(const std::string& nombre) const;
    bool modificarEmpleado(const std::string& nombre,int nuevoId,const std::string& nuevoNombre);
    void ordenarPorNombre();
    const std::vector<empleado>& obtenerEmpleados() const { return lista; }
};

inline autenticador::autenticador():adminGeneral(1,"admin"),sigId(2){
    lista.push_back(empleado(2,"ana"));
    lista.push_back(empleado(3,"luis"));
    sigId = 4;
}

inline usuario* autenticador::login(int id,const std::string& rol){
    if(rol == "admin" && adminGeneral.getId() == id){
        return &adminGeneral;
    }
    if(rol == "empleado"){
        for(auto& emp : lista){
            if(emp.getId() == id){
                return &emp;
            }
        }
    }
    return nullptr;
}

inline empleado* autenticador::agregarEmpleado(int id,const std::string& nombre){
    if(nombre.empty()) return nullptr;
    for(const auto& emp : lista){
        if(emp.getNombre() == nombre || emp.getId() == id) return nullptr;
    }
    if(id <= 0){
        id = sigId++;
    }
    lista.push_back(empleado(id,nombre));
    if(id >= sigId){
        sigId = id + 1;
    }
    // devolver puntero al elemento recien agregado
    return &lista.back();
}

inline bool autenticador::eliminarEmpleado(const std::string& nombre){
    for(auto it = lista.begin(); it != lista.end(); ++it){
        if(it->getNombre() == nombre){
            lista.erase(it);
            return true;
        }
    }
    return false;
}

inline empleado* autenticador::buscarEmpleado(const std::string& nombre){
    for(auto& emp : lista){
        if(emp.getNombre() == nombre) return &emp;
    }
    return nullptr;
}

inline const empleado* autenticador::buscarEmpleado(const std::string& nombre) const{
    for(const auto& emp : lista){
        if(emp.getNombre() == nombre) return &emp;
    }
    return nullptr;
}

inline bool autenticador::modificarEmpleado(const std::string& nombre,int nuevoId,const std::string& nuevoNombre){
    auto* emp = buscarEmpleado(nombre);
    if(!emp) return false;
    int idFinal = nuevoId > 0 ? nuevoId : emp->getId();
    std::string nombreFinal = nuevoNombre.empty() ? emp->getNombre() : nuevoNombre;
    emp->actualizar(idFinal,nombreFinal);
    if(idFinal >= sigId) sigId = idFinal + 1;
    return true;
}

inline void autenticador::ordenarPorNombre(){
    std::sort(lista.begin(), lista.end(), [](const empleado& a,const empleado& b){
        return a.getNombre() < b.getNombre();
    });
}
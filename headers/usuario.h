#pragma once
#include <string>
class usuario {
protected:
    int id;
    std::string nombre;
    std::string rol; // "admin" o "empleado"
public:
    usuario(int i,const std::string& n,const std::string& r):id(i),nombre(n),rol(r){}
    virtual ~usuario() = default;
    int getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getRol() const { return rol; }
    void setId(int nuevoId) { id = nuevoId; }
    void setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }
    void setRol(const std::string& nuevoRol) { rol = nuevoRol; }
};
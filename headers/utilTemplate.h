#pragma once
#include <iostream>
// Template sencillo para mostrar cualquier contenedor con for-each
// Cumple requisito de usar template
template <typename Contenedor>
void mostrarSimple(const Contenedor& c){
    for(const auto& elem : c){ std::cout << elem << "\n"; }
}

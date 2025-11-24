#pragma once
#include<iostream>
#include<string>
using namespace std;

class usuario {
protected:
	string nombre,rol;
	int ID;
public:
	//constructor 
	usuario(string nom, string rol, int id);
	//getters necesarios 
	string getNombre()const;
	string getRol()const;
	int getId()const;

	//metodos 
	bool validarID(int id);
	virtual bool tienePermiso(const string& operacion);

	//destructor 
	virtual ~usuario() = default;

};

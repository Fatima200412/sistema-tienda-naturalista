#pragma once
#include "usuario.h"
class admin : public usuario {
public:
    admin(int i,const std::string& n):usuario(i,n,"admin"){}
};
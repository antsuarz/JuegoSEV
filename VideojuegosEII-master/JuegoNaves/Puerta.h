#pragma once
#include "Actor.h"
class Puerta : public Actor
{
public:
	Puerta(string fichero, int ident, float x, float y,Game* game); 
	int ident;
};


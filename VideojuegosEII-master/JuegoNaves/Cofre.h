#pragma once
#include "Actor.h"
#include "Animation.h"
#include "Game.h"

class Cofre : public Actor
{
public:
	Cofre(float x, float y, Contenido c, Game* g); 
	void update();
	void draw(float scrollX);
	Animation* aOpening;
	Animation* aClose;
	Animation* aOpen;
	Animation* animation;
	bool open;
	int cont = 70;
	bool hasBeenOpened;

	Contenido contenido;
};


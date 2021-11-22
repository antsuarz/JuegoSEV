#pragma once

#include "Actor.h"
class BolaFuego : public Actor
{
public:
	BolaFuego(float x, float y, Game* game);
	void update();
};


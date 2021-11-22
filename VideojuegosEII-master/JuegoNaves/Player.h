#pragma once

#include "Actor.h"
#include "BolaFuego.h" 
#include "Animation.h" 
#include "Audio.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0) override;

	BolaFuego* cast();

	Animation* aClimbing;
	Animation* aIdleBot;
	Animation* aIdleTop;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aRunningTop;
	Animation* aRunningBot;
	Animation* aRunningRight;
	Animation* aRunningLeft; 
	Animation* aJumpingRight;
	Animation* aJumpingLeft;

	Animation* aShotingBot;
	Animation* aShotingTop;
	Animation* aShotingRight;
	Animation* aShotingLeft;

	Animation* animation; // Referencia a la animación mostrada
	
	int castCadence = 100;
	int castTime = 0;
	int life = 100;
	int armor = 10;
	int potions = 0;
	int atackDamage = 10;

	Orientation orientation = Orientation::RIGHT;
	States state = States::IDLE;
};


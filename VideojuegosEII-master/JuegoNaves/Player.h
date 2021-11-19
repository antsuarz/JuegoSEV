#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Animation.h" 
#include "Audio.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0) override; // Va a sobrescribir
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
	 

	//Combate
	int life = 100;
	int armor = 10;
	int potions = 0;
	int atackDamage = 10;

	Orientation orientation = Orientation::RIGHT;
	States state = States::IDLE;
};


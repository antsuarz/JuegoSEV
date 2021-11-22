#pragma once
#include "Actor.h"
#include "Animation.h"
class EnemyOverworld : public Actor
{
public:
	EnemyOverworld(string file, int ancho, int alto, int totalFrames,int anchoFrame, float x, float y, Game* game);
	void update();
	void draw(float scrollX = 0) override; 
	Animation* aIdle;
	Animation* animation;

	bool beated = false;
};


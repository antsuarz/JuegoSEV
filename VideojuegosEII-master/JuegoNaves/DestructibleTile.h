#pragma once
#include "Actor.h"
#include "Animation.h"
class DestructibleTile :
    public Actor
{
public:
	DestructibleTile(float x, float y, Game* game); 
	void update(); 
	void draw(float scrollX = 0) override;

	bool impact = false;
	bool hasBeenDestroyed = false;


	Animation* aDestroy;  
	Animation* aPilar;
	Animation* aPuddle;
	Animation* animation; 

};


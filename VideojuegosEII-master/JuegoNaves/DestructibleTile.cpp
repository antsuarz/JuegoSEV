#include "DestructibleTile.h"

DestructibleTile::DestructibleTile(float x, float y, Game* game)
	: Actor("res/Assets/PilarDestructible.png", x, y, 18, 41, game) {

															// float fileWidth, float fileHeight,int updateFrecuence, int totalFrames, bool loop, Game* game
	aDestroy = new Animation("res/Assets/Destruccion.png", width, height,198, 41, 4, 11, false, game);
	aPilar = new Animation("res/Assets/PilarDestructible.png", width, height, 18, 41, 6, 1, true, game);
	aPuddle = new Animation("res/Assets/charco.png", 16, 10, 32, 10, 20, 2, true, game);

	animation = aPilar;
}

void DestructibleTile::update() { 
	bool endAnimation = animation->update();
	
	if (endAnimation) {
		 
		if (impact) {
			hasBeenDestroyed = true;
		}
	}
	if (hasBeenDestroyed) {
		animation = aPuddle;
	}
	if (impact && !hasBeenDestroyed) {
		animation = aDestroy;	
	}
} 

void DestructibleTile::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}
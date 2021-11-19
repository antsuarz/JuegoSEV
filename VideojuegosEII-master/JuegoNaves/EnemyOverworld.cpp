#include "EnemyOverworld.h"

EnemyOverworld::EnemyOverworld(string filename,int ancho, int alto, int totalFrames, int anchoFrame, float x, float y, Game* g) : Actor("res/Assets/Saturnos.png", x, y, anchoFrame, 29, g) {

	aIdle = new Animation(filename,width, height, ancho, alto, 24, totalFrames, false, g);
	animation = aIdle;
}

void EnemyOverworld::update() {
	animation->update();
}

void EnemyOverworld::draw(float scrollX ) {
	animation->draw(x - scrollX, y);
}
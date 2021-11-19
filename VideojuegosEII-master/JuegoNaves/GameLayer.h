#pragma once

#include "Layer.h"
#include "Player.h"
#include "Audio.h" 
#include "Puerta.h"

#include "Background.h"
#include "EnemyOverworld.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "MovableTile.h"
#include "DraggableTile.h" 
#include "StairsTile.h"
#include "Space.h"
#include <list>
#include "Cofre.h"

#include "Pad.h"
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String



class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	int newEnemyTime = 0;
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	int mapWidth;
	list<Tile*> tiles;
	list<EnemyOverworld*> enemigos;
	list<MovableTile*> mtiles;
	list < DraggableTile* > dtiles; 
	list < StairsTile* > stiles;
	void calculateScroll();
	float scrollX;
	Space* space;
	Audio* audioBackground;
	Text* textArmor;
	Text* textWeapon;
	Text* textLifes;
	Text* textPotions; 
	int lifes; 
	Player* player;
	Background* background;
	Actor* backgroundPotions;
	Actor* backgroundLifes;
	Actor* backgroundArmor;
	Actor* backgroundWeapon;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;
	int counter =15;
	void teleportPlayer(int x, int y);
	Tile* salida;
	Tile* entrada; 

	list<Cofre*> cofres;
	 
	list<Projectile*> projectiles; 
	

};


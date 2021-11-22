#pragma once

#include "Layer.h"
#include "Player.h"
#include "Audio.h" 
#include "Puerta.h"

#include "Background.h"
#include "EnemyOverworld.h"
#include "BolaFuego.h"
#include "Text.h"
#include "Tile.h" 
#include "DraggableTile.h" 
#include "DestructibleTile.h" 
#include "StairsTile.h"
#include "Space.h"
#include <list>
#include "Cofre.h"
#include "BattleLayer.h"
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
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	void teleportPlayer(int x, int y);

	int mapWidth;
	int controlMoveY = 0;
	int controlMoveX = 0;
	int counter = 15;
	int lifes;

	float scrollX;

	bool controlShoot = false;

	Player* player;

	Space* space;

	Audio* audioBackground;

	Text* textArmor;
	Text* textWeapon;
	Text* textLifes;
	Text* textPotions; 
	
	Background* background;

	Actor* backgroundPotions;
	Actor* backgroundLifes;
	Actor* backgroundArmor;
	Actor* backgroundWeapon;
	
	Tile* salida;
	Tile* entrada; 

	list<Cofre*> cofres;
	list<BolaFuego*> projectiles; 
	list<Tile*> tiles;
	list<EnemyOverworld*> enemigos;
	list < DraggableTile* > dtiles;
	list < DestructibleTile* > destiles;
	list < StairsTile* > stiles;

};


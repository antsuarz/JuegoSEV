#pragma once

#include<stdlib.h>
#include<time.h>

#include "Layer.h"
#include "Actor.h" 
#include "Audio.h" 
#include "Animation.h"
#include "Background.h"
#include "Text.h"
class BattleLayer :public Layer
{
public:
	BattleLayer(int battleId, int attackDamage, int armor, int potions, Game* game);
	void init() override;
	void update();
	void draw() override;
	string enemyName;
	int id; 
	bool hasBeenHit;
	bool hasUseAPotion;
	bool hasBeenHeal;
	Background* background;
	Audio* audioBackground;
	Actor* enemy;
	Actor* player; 
	
	int frame;
	int playerFrames;

	int attackDamage;
	double armor;
	int armorBase;
	int potions;
	int life;
	int enemyLife;
	int contadorJugador;
	int contador;

	bool controlContinue;

	bool idle;
	bool cast;
	bool attack;
	bool hit;

	bool enemy_idle;
	bool enemy_cast;
	bool enemy_attack;
	bool enemy_hit;

	bool control;
	bool player_turn;
	bool continueFlag;
	void continueFight();

	void processControls() override;
	void keysToControls(SDL_Event event); 

	void EnemyIdle();
	void PlayerIdle();
	void EnemyCast();
	void PlayerCast();
	void EnemyAttack();
	void PlayerAttack();
	void EnemyHit();
	void PlayerHit();
	void UsePotion();
	void EnemyHeal();
	void EnemyTurn();

	Text* textArmor;
	Text* textWeapon;
	Text* textLifes;
	Text* textPotions;
	Text* textInfo;
	Actor* backgroundPotions;
	Actor* backgroundLifes;
	Actor* backgroundArmor;
	Actor* backgroundWeapon;
	Actor* borde;

	int idleH;
	int idleW;
};


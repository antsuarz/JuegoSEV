#include "BattleLayer.h"


BattleLayer::BattleLayer(int battle_id, int ad, int ar, int p,Game* game)
	: Layer(game) {
	id = battle_id;
	contador = 0;
	contadorJugador = 0;
	playerFrames = 30;

	life = 100;
	potions = 1;
	armor = ar/100;
	armorBase = ar;
	attackDamage = ad;
	player_turn = true;
	enemy_idle = true;
	idle = true;
	cast = false;
	attack = false;
	hit = false;
	control = false;
	hasBeenHit = false;
	hasUseAPotion = false;
	hasBeenHeal = false;
	init();
}
void BattleLayer::init() { 

	//Interfaz Vidas
	textLifes = new Text("100", WIDTH * 0.125, HEIGHT * 0.1, game);
	textLifes->content = to_string(life);
	backgroundLifes = new Actor("res/Assets/Iconos/IconoVidas.png", WIDTH * 0.09, HEIGHT * 0.1, 81, 36, game);
	//_________________________
	//Interfaz pociones
	textPotions = new Text("100", WIDTH * 0.108 , HEIGHT * 0.22, game);
	textPotions->content = to_string(potions);
	backgroundPotions = new Actor("res/Assets/Iconos/IconoPociones.png", WIDTH * 0.073, HEIGHT * 0.22, 64, 36, game);
	//__________________________
	//Interfaz Arma
	textWeapon = new Text("100", WIDTH * 0.305, HEIGHT * 0.1, game);
	textWeapon->content = to_string(attackDamage);
	backgroundWeapon = new Actor("res/Assets/Iconos/IconoArma.png", WIDTH * 0.275, HEIGHT * 0.1, 81, 36, game);
	//__________________________
	//Interfaz Armadura
	textArmor = new Text("100", WIDTH * 0.49, HEIGHT * 0.1, game);
	textArmor->content = to_string(armorBase);
	backgroundArmor = new Actor("res/Assets/Iconos/IconoArmadura.png", WIDTH * 0.46, HEIGHT * 0.1, 81, 36, game);
	//__________________________
    //Interfaz Informacion
	textInfo = new Text("100", WIDTH *0.5, HEIGHT * 0.96, game);
	textInfo ->content = "Atacar: q / Hechizo: e / Pocion: r ";
	borde = new Actor("res/Assets/Iconos/Borde.png", WIDTH * 0.5, HEIGHT * 0.95, 400, 35, game);

	//Jugador
	player = new Actor("res/Battle/Felix/Idle_0.png", WIDTH * 0.7, HEIGHT * 0.8, 41, 60, game);
	if (id == 0) {
		idleH = 53;
		idleW = 44;
		enemyName = "Karst";
		enemyLife = 50;
		frame = 30;
		background = new Background("res/Battle/Fondos/b1.gif", WIDTH * 0.5, 160, game); 
	}
	if (id == 1) {
		idleH = 58;
		idleW = 53;
		enemyLife = 300;
		enemyName = "Saturnos";
		frame = 30;
		background = new Background("res/Battle/Fondos/b2.gif", WIDTH * 0.5, HEIGHT*0.5, game);
	} 
	enemy = new Actor("res/Battle/" + enemyName + "/Idle_0.png", WIDTH * 0.4, HEIGHT * 0.7, 53, 58, game);
	 
}

void BattleLayer::update() {

	textLifes->content = to_string(life);
	textPotions->content = to_string(potions);
	if(idle)
		PlayerIdle();
	if (attack)
		PlayerAttack();
	if (cast)
		PlayerCast();
	if (hit)
		PlayerHit();
	if (enemy_idle)
		EnemyIdle();
	if (enemy_attack)
		EnemyAttack();
	if (enemy_hit)
		EnemyHit();
	if (enemy_cast)
		EnemyCast();
	if (!player_turn)
		EnemyTurn();
	if (contador == frame)
		contador = 0;
	if (contadorJugador == playerFrames)
		contadorJugador = 0;
	contador++; 
	contadorJugador++;
	draw();
}

void BattleLayer::EnemyTurn() {
	//srand(time(NULL));
	//int option = rand() % 6;

	if (id == 0) {
		if (enemyLife > 30) {
			EnemyAttack();
		} 
		else
			if(!hasBeenHeal)
				EnemyHeal();
	}
}

void BattleLayer::EnemyHeal() {
	textInfo = new Text("100", WIDTH * 0.7, HEIGHT * 0.96, game);
	textInfo->content = enemyName + " está en las últimas, se ha tomado una poción."; 
	continueFlag = true;
	enemyLife = enemyLife+ 50;
	hasBeenHeal = true;
	player_turn = true;
}
void BattleLayer::EnemyIdle() {
	if (contador <= 10)
		enemy = new Actor("res/Battle/" + enemyName + "/Idle_0.png", WIDTH * 0.4, HEIGHT * 0.7, idleW, idleH, game);
	if (contador > 10 && contador <= 20)
		enemy = new Actor("res/Battle/" + enemyName + "/Idle_1.png", WIDTH * 0.4, HEIGHT * 0.7, idleW, idleH, game);
	if (contador > 20)
		enemy = new Actor("res/Battle/" + enemyName + "/Idle_2.png", WIDTH * 0.4, HEIGHT * 0.7, idleW, idleH, game);
}

void BattleLayer::PlayerIdle() {
	if (contadorJugador <= 10)
		player = new Actor("res/Battle/Felix/Idle_0.png", WIDTH * 0.7, HEIGHT * 0.8, 41, 60, game);
	if (contadorJugador > 10 && contadorJugador <= 20)
		player = new Actor("res/Battle/Felix/Idle_1.png", WIDTH * 0.7, HEIGHT * 0.8, 41, 60, game);
	if (contadorJugador > 20)
		player = new Actor("res/Battle/Felix/Idle_2.png", WIDTH * 0.7, HEIGHT * 0.8, 41, 60, game);
}


void BattleLayer::EnemyAttack() { 
	textInfo = new Text("100", WIDTH * 0.25, HEIGHT * 0.96, game);
	textInfo->content = "¡"+enemyName + " ataca!";
	enemy_idle = false;
	enemy_attack = true;
	if (!control) {
		if (contador <= 7)
			enemy = new Actor("res/Battle/" + enemyName + "/Ataque_0.gif", WIDTH * 0.53, HEIGHT * 0.75, 64, 64, game);
		if (contador > 7 && contador <= 15)
			enemy = new Actor("res/Battle/" + enemyName + "/Ataque_0.gif", WIDTH * 0.65, HEIGHT * 0.80, 64, 64, game);
	}
	if (contador > 15) {
		enemy = new Actor("res/Battle/" + enemyName + "/Ataque_1.gif", WIDTH * 0.65, HEIGHT * 0.8, 64, 64, game);
		control = true;
		if (id == 0)
			if (!hasBeenHit) {
				life = life - (20);
				hasBeenHit = true;
			}
		else
			if (!hasBeenHit) {
				life = life - (30 * armor);
				hasBeenHit = true;
			}
		PlayerHit();
	}
}

void BattleLayer::PlayerAttack() {
	textInfo = new Text("100", WIDTH * 0.25, HEIGHT * 0.96, game);
	textInfo->content = "¡Felix ataca!";
	idle = false;
	attack = true;
	if(!control)
		if (contadorJugador <= 10)
			player = new Actor("res/Battle/Felix/Ataque_1.gif", WIDTH * 0.6, HEIGHT * 0.75, 64, 60, game);
	if (contadorJugador > 10) {
		player = new Actor("res/Battle/Felix/Ataque_2.gif", WIDTH * 0.45, HEIGHT * 0.72, 64, 60, game);
		control = true;
		if (!hasBeenHit) {
			enemyLife = enemyLife - (attackDamage);
			hasBeenHit = true;
		}
		EnemyHit(); 
	}
}


void BattleLayer::EnemyCast() {
	 
}

void BattleLayer::PlayerCast(){
	 
}


void BattleLayer::EnemyHit() {
	enemy_idle = false;
	enemy_hit = true; 
	enemy = new Actor("res/Battle/" + enemyName + "/Hit.png", WIDTH * 0.31, HEIGHT * 0.69, 64, 64, game);
}

void BattleLayer::PlayerHit() { 
	idle = false;
	hit = true;
	player = new Actor("res/Battle/Felix/Hit.png", WIDTH * 0.73, HEIGHT * 0.81, 64, 64, game);
	
}
void BattleLayer::UsePotion() {
	if (potions > 0) { 
		textInfo = new Text("100", WIDTH * 0.55, HEIGHT * 0.96, game);
		textInfo->content = "Felix usa una hierba y recupera salud";
		if (life + 50 > 100)
			life = 100;
		else
			life + 50;
		potions--; 
		continueFlag = true;
		hasUseAPotion = true;
	}
}
void BattleLayer::continueFight() {
	
	if (!continueFlag) {
		if (player_turn)
			player_turn = false;
		else
			player_turn = true;
		textInfo = new Text("100", WIDTH * 0.5, HEIGHT * 0.96, game);
		enemy_idle = true;
		enemy_attack = false;
		enemy_cast = false;
		enemy_hit = false;
		idle = true;
		cast = false;
		attack = false;
		hit = false;
		control = false;
		contador = 0;
		contadorJugador = 0;
		hasBeenHit = false;
		hasUseAPotion = false;
		textLifes->content = to_string(life);
		textInfo->content = "Atacar: q / Hechizo: e / Pocion: r ";
	}
	else {
		if (hasUseAPotion) {
			player_turn = false;
			hasUseAPotion = false;
		}
		continueFlag = false;
		textInfo = new Text("100", WIDTH * 0.5, HEIGHT * 0.96, game);
		textInfo->content = "Atacar: q / Hechizo: e / Pocion: r ";
	}
}



void BattleLayer::processControls() { 
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		} 
	} 
	if (controlContinue) { 
		game->layer = game->gameLayer;
		controlContinue = false;
	}
}

void BattleLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_q:
			contadorJugador = 0;
			control = false;
			if (player_turn)
				PlayerAttack();
			break;
		case SDLK_r:
			contadorJugador = 0;
			control = false;
			if (player_turn)
				UsePotion(); 
			break;
		case SDLK_e:
			if (player_turn)
				PlayerCast();
			break;
		case SDLK_d:
			//defenderse
			break;
		case SDLK_SPACE:
			continueFight();
			break;
		}
	}
}

void BattleLayer::draw() {
	background->draw();
	enemy->draw();
	player->draw();


	backgroundPotions->draw();
	textPotions->draw(0, 255, 0, 1);
	backgroundLifes->draw();
	textLifes->draw(255, 50, 50,1);
	backgroundWeapon->draw();
	textWeapon->draw(0, 0, 0,1);
	backgroundArmor->draw();
	textArmor->draw(200, 200, 200,1);
	borde->draw();
	textInfo->draw(250,250,250,1.7);

	SDL_RenderPresent(game->renderer);
}
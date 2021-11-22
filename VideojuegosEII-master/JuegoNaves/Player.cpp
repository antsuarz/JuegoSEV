#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 35, 35, game) {
	 
	aClimbing = new Animation("res/Assets/Trepando.png",18, 30,
		72, 29, 6, 4, true, game);

	aIdleTop = new Animation("res/Assets/Felix_Idle_Frente.png", 16, 30,
		160, 29, 20, 10, true, game);
	aIdleBot = new Animation("res/Assets/Felix_Idle_Back.png", 16, 29,
		64, 29, 20, 4, true, game);
	aIdleRight = new Animation("res/Assets/Felix_Idle_Derecha.png", 15, 29,
		140,29 , 20, 10, true, game);
	aIdleLeft = new Animation("res/Assets/Felix_Idle_Izquierda.png", 15, 29,
		140, 30, 20, 10, true, game);

	aRunningTop = new Animation("res/Assets/Felix_Walk_Top.png", 17, 30,
		108, 30,2, 6, true, game);
	aRunningBot = new Animation("res/Assets/Felix_Walk_Down.png", 16, 30,
		95.5, 30, 2, 6, true, game);
	aRunningRight = new Animation("res/Assets/Felix_Walk_Right.png", 19, 30,
		108, 30, 2, 6, true, game);
	aRunningLeft = new Animation("res/Assets/Felix_Walk_Left.png", 19, 30,
		108, 30, 2, 6, true, game);

	aShotingLeft = new Animation("res/Assets/Lanzar_Hechizo_Izquierda.png", 19, 30, 44, 30, 6, 2, false, game);
	aShotingRight = new Animation("res/Assets/Lanzar_Hechizo_Derecha.png", 19, 30, 44, 30, 6, 2, false, game); 

	animation = aIdleRight;
	orientation = Orientation::RIGHT;
 
}

void Player::update() {
	if (vy > 0) {
		orientation = Orientation::TOP;
	}
	if (vy < 0) {
		orientation = Orientation::BOT;
	}
	if (vx > 0) {
		orientation = Orientation::RIGHT;
	}
	if (vx < 0) {
		orientation = Orientation::LEFT;
	}
	  
	bool hasAnimationEnded = animation->update();
	
		
	
	if (state == States::CAST) {
		if (orientation == Orientation::RIGHT) {
			animation = aShotingRight;
		}
		if (orientation == Orientation::LEFT) {
			animation = aShotingLeft;
		} 
	}
	if (hasAnimationEnded)
		if(state == States::CAST)
			state = States::IDLE;

	if (state == States::CLIMBING || state == States::MOVING || state == States::IDLE) {
		
		if (vx != 0 || vy != 0) {
			if (orientation == Orientation::TOP) {

				if (state == States::CLIMBING) {
					animation = aClimbing;
				}

				else{
					animation = aRunningBot;
					state = States::MOVING;
				}
			}
			if (orientation == Orientation::BOT) {
				if (state == States::CLIMBING) { 
					animation = aClimbing;
				}
				 
				else {
					animation = aRunningTop;
					state = States::MOVING;
				}
			}
			if (orientation == Orientation::RIGHT) {
				state = States::MOVING;
				animation = aRunningRight;
			}
			if (orientation == Orientation::LEFT) {
				animation = aRunningLeft;
				state = States::MOVING;
			}
		}
		if (vx == 0 && vy == 0) {
			if (orientation == Orientation::TOP) {
				animation = aIdleTop; 
			}
			if (orientation == Orientation::BOT) {
				animation = aIdleBot; 
			}
			if (orientation == Orientation::RIGHT) { 
				animation = aIdleRight; 
			}
			if (orientation == Orientation::LEFT) {
				animation = aIdleLeft; 
			}
		}
	}

	if (castTime != 0)
		castTime--;

}

 


void Player::moveX(float axis) {
	 
		vx = axis * 3;
	 
}

void Player::moveY(float axis) {
	 
		vy = axis * 3;
	 
}

BolaFuego* Player::cast() { 
	if (castTime == 0) { 
		state = States::CAST;
		castTime = castCadence;
		auto proyectile = new BolaFuego(x, y, game);
		if (orientation == Orientation::LEFT) {
			proyectile->vy = 0;
			proyectile->vx = -9;
		} 
		else if (orientation == Orientation::RIGHT) {
			proyectile->vy = 0;
			proyectile->vx = 9;
		}
		else if (orientation == Orientation::TOP) {
			proyectile->vy =9;
			proyectile->vx = 0;
		}
		else if (orientation == Orientation::BOT) {
			proyectile->vy = -9;
			proyectile->vx = 0;
		}
		return proyectile;
	}
	else {
		return NULL;
	}

}

void Player::draw(float scrollX) {
	
	animation->draw(x - scrollX, y);
	
}

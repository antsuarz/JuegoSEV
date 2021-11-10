#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 35, 35, game) {

	onAir = false;
	audioShoot = new Audio("res/efecto_disparo.wav", false);

	aShootingRight = new Animation("res/jugador_disparando_derecha.png",
		width, height, 160, 40, 6, 4, false, game);
	aShootingLeft = new Animation("res/jugador_disparando_izquierda.png",
		width, height, 160, 40, 6, 4, false, game);

	aJumpingRight = new Animation("res/jugador_saltando_derecha.png",
		width, height, 160, 40, 6, 4, false, game);
	aJumpingLeft = new Animation("res/jugador_saltando_izquierda.png",
		width, height, 160, 40, 6, 4, false, game);

	aIdleRight = new Animation("res/Assets/Felix_Idle_Derecha.png", 18, 29,
		140,29 , 6, 10, true, game);
	aIdleLeft = new Animation("res/Assets/Felix_Idle_Izquierda.png", 18, 29,
		140, 30, 6, 10, true, game);
	aRunningRight = new Animation("res/Assets/Felix_Walk_Right.png", 19, 30,
		108, 30, 6, 6, true, game);
	aRunningLeft = new Animation("res/Assets/Felix_Walk_Left.png", 19, 30,
		108, 30, 6, 6, true, game);
	animation = aIdleRight;
	orientation = Orientation::RIGHT;
 
}

void Player::update() {
	if (invulTime > 0) {
		invulTime--;
	}
	if (vx > 0) {
		orientation = Orientation::RIGHT;
	}
	if (vx < 0) {
		orientation = Orientation::LEFT;
	}
	if (collisionDown == true) {
		onAir = false;
	}
	else {
		onAir = true;
	}

	if (onAir) {
		state = States::JUMPING;
	}
	else {
		state = States::MOVING;
	}

	bool hasAnimationEnded = animation->update();
	if (hasAnimationEnded) {
		// Estaba disparando
		if (state == States::SHOOTING) {
			state = States::MOVING;
		}
	}

	// Selección de animación basada en estados
	if (state == States::JUMPING) {
		if (orientation == Orientation::RIGHT) {
			animation = aJumpingRight;
		}
		if (orientation == Orientation::LEFT) {
			animation = aJumpingLeft;
		}
	}
	if (state == States::SHOOTING) {
		if (orientation ==Orientation::RIGHT) {
			animation = aShootingRight;
		}
		if (orientation == Orientation::LEFT) {
			animation = aShootingLeft;
		}
	}
	
	if (state == States::MOVING || state == States::IDLE) {
		if (vx != 0) {
			if (orientation == Orientation::RIGHT) {
				animation = aRunningRight;
			}
			if (orientation == Orientation::LEFT) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0) {
			if (orientation == Orientation::RIGHT) {
				animation = aIdleRight;
				state = States::IDLE;
			}
			if (orientation == Orientation::LEFT) {
				animation = aIdleLeft;
				state = States::IDLE;
			}
		}
	}


	if (shootTime > 0) {
		shootTime--;
	}
}

void Player::jump() {
	if (!onAir) {
		vy = -16;
		onAir = true;
	}

}


void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		audioShoot->play();
		state = States::SHOOTING;
		shootTime = shootCadence;
		auto proyectile = new Projectile(x, y, game);
		if (orientation == Orientation::LEFT) {
			proyectile->vx *= -1;
		}
		return proyectile;
	}
	else {
		return NULL;
	}

}

void Player::draw(float scrollX) {
	if (invulTime == 0) {
		animation->draw(x - scrollX, y);
		return;
	}
	if(invulTime % 10 >= 0 && invulTime % 10 <= 5) {
		animation->draw(x - scrollX, y);
	}
}

void Player::loseLife() {
	if (invulTime > 0 || lifes <= 0) {
		return;
	}
	lifes--;
	invulTime = 100;
}
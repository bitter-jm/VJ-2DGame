#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

# define M_PI 3.14159265358979323846  /* pi */

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define RUN_VELOCITY 3
#define SHOT_VELOCITY 8
#define UPGRADE_WEAPON_X 2600

enum PlayerAnims
{
	STAND_LEFT_POINT_LEFT, STAND_RIGHT_POINT_RIGHT, MOVE_LEFT_POINT_LEFT, MOVE_RIGHT_POINT_RIGHT, JUMP_LEFT, JUMP_RIGHT,
	STAND_LEFT_POINT_UP, STAND_LEFT_POINT_DOWN, STAND_RIGHT_POINT_UP, STAND_RIGHT_POINT_DOWN,
	MOVE_LEFT_POINT_UP, MOVE_LEFT_POINT_DOWN, MOVE_RIGHT_POINT_UP, MOVE_RIGHT_POINT_DOWN,

	STAND_LEFT_POINT_LEFT_SHOOT, STAND_RIGHT_POINT_RIGHT_SHOOT, MOVE_LEFT_POINT_LEFT_SHOOT, MOVE_RIGHT_POINT_RIGHT_SHOOT,
	STAND_LEFT_POINT_UP_SHOOT, STAND_LEFT_POINT_DOWN_SHOOT, STAND_RIGHT_POINT_UP_SHOOT, STAND_RIGHT_POINT_DOWN_SHOOT,
	MOVE_LEFT_POINT_UP_SHOOT, MOVE_LEFT_POINT_DOWN_SHOOT, MOVE_RIGHT_POINT_UP_SHOOT, MOVE_RIGHT_POINT_DOWN_SHOOT,

	DYING_LEFT, DEAD_LEFT, DYING_RIGHT, DEAD_RIGHT
};

enum BasicAnimations
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, OTHERS
};

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.1, 0.1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(32);
	
		sprite->setAnimationSpeed(STAND_LEFT_POINT_LEFT, 3);
		sprite->addKeyframe(STAND_LEFT_POINT_LEFT, glm::vec2(0.7f, 0.f));
		sprite->addKeyframe(STAND_LEFT_POINT_LEFT, glm::vec2(0.6f, 0.f));

		sprite->setAnimationSpeed(STAND_LEFT_POINT_UP, 3);
		sprite->addKeyframe(STAND_LEFT_POINT_UP, glm::vec2(0.6f, 0.3f));

		sprite->setAnimationSpeed(STAND_LEFT_POINT_DOWN, 3);
		sprite->addKeyframe(STAND_LEFT_POINT_DOWN, glm::vec2(0.6f, 0.5f));
		
		sprite->setAnimationSpeed(STAND_RIGHT_POINT_RIGHT, 3);
		sprite->addKeyframe(STAND_RIGHT_POINT_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_RIGHT_POINT_RIGHT, glm::vec2(0.1f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT_POINT_UP, 3);
		sprite->addKeyframe(STAND_RIGHT_POINT_UP, glm::vec2(0.1f, 0.3f));

		sprite->setAnimationSpeed(STAND_RIGHT_POINT_DOWN, 3);
		sprite->addKeyframe(STAND_RIGHT_POINT_DOWN, glm::vec2(0.1f, 0.5f));

		sprite->setAnimationSpeed(MOVE_LEFT_POINT_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT, glm::vec2(0.7f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT, glm::vec2(0.6f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT, glm::vec2(0.5f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT, glm::vec2(0.4f, 0.1f));

		sprite->setAnimationSpeed(MOVE_LEFT_POINT_UP, 8);
		sprite->addKeyframe(MOVE_LEFT_POINT_UP, glm::vec2(0.7f, 0.3f));
		sprite->addKeyframe(MOVE_LEFT_POINT_UP, glm::vec2(0.6f, 0.3f));
		sprite->addKeyframe(MOVE_LEFT_POINT_UP, glm::vec2(0.5f, 0.3f));
		sprite->addKeyframe(MOVE_LEFT_POINT_UP, glm::vec2(0.4f, 0.3f));

		sprite->setAnimationSpeed(MOVE_LEFT_POINT_DOWN, 8);
		sprite->addKeyframe(MOVE_LEFT_POINT_DOWN, glm::vec2(0.7f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT_POINT_DOWN, glm::vec2(0.6f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT_POINT_DOWN, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT_POINT_DOWN, glm::vec2(0.4f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT_POINT_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT_POINT_RIGHT, glm::vec2(0.0f, 0.1f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_RIGHT, glm::vec2(0.1f, 0.1f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_RIGHT, glm::vec2(0.2f, 0.1f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_RIGHT, glm::vec2(0.3f, 0.1f));

		sprite->setAnimationSpeed(MOVE_RIGHT_POINT_UP, 8);
		sprite->addKeyframe(MOVE_RIGHT_POINT_UP, glm::vec2(0.0f, 0.3f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_UP, glm::vec2(0.1f, 0.3f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_UP, glm::vec2(0.2f, 0.3f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_UP, glm::vec2(0.3f, 0.3f));

		sprite->setAnimationSpeed(MOVE_RIGHT_POINT_DOWN, 8);
		sprite->addKeyframe(MOVE_RIGHT_POINT_DOWN, glm::vec2(0.0f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_DOWN, glm::vec2(0.1f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_DOWN, glm::vec2(0.2f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_DOWN, glm::vec2(0.3f, 0.5f));

		sprite->setAnimationSpeed(JUMP_LEFT, 12);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.7f, 0.7f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.6f, 0.7f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.5f, 0.7f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.4f, 0.7f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 12);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.0f, 0.7f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.1f, 0.7f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.2f, 0.7f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.3f, 0.7f));

		// SHOOTING

		sprite->setAnimationSpeed(STAND_LEFT_POINT_LEFT_SHOOT, 8); // DONE
		sprite->addKeyframe(STAND_LEFT_POINT_LEFT_SHOOT, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(STAND_LEFT_POINT_LEFT_SHOOT, glm::vec2(0.7f, 0.f));
		sprite->addKeyframe(STAND_LEFT_POINT_LEFT_SHOOT, glm::vec2(0.6f, 0.f));
		sprite->addKeyframe(STAND_LEFT_POINT_LEFT_SHOOT, glm::vec2(0.7f, 0.f));

		sprite->setAnimationSpeed(STAND_LEFT_POINT_UP_SHOOT, 8); // DONE
		sprite->addKeyframe(STAND_LEFT_POINT_UP_SHOOT, glm::vec2(0.6f, 0.4f));
		sprite->addKeyframe(STAND_LEFT_POINT_UP_SHOOT, glm::vec2(0.6f, 0.3f));
		sprite->addKeyframe(STAND_LEFT_POINT_UP_SHOOT, glm::vec2(0.6f, 0.3f));
		sprite->addKeyframe(STAND_LEFT_POINT_UP_SHOOT, glm::vec2(0.6f, 0.3f));

		sprite->setAnimationSpeed(STAND_LEFT_POINT_DOWN_SHOOT, 8); // DONE
		sprite->addKeyframe(STAND_LEFT_POINT_DOWN_SHOOT, glm::vec2(0.6f, 0.6f));
		sprite->addKeyframe(STAND_LEFT_POINT_DOWN_SHOOT, glm::vec2(0.6f, 0.5f));
		sprite->addKeyframe(STAND_LEFT_POINT_DOWN_SHOOT, glm::vec2(0.6f, 0.5f));
		sprite->addKeyframe(STAND_LEFT_POINT_DOWN_SHOOT, glm::vec2(0.6f, 0.5f));

		sprite->setAnimationSpeed(STAND_RIGHT_POINT_RIGHT_SHOOT, 8); // DONE
		sprite->addKeyframe(STAND_RIGHT_POINT_RIGHT_SHOOT, glm::vec2(0.2f, 0.f));
		sprite->addKeyframe(STAND_RIGHT_POINT_RIGHT_SHOOT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_RIGHT_POINT_RIGHT_SHOOT, glm::vec2(0.1f, 0.f));
		sprite->addKeyframe(STAND_RIGHT_POINT_RIGHT_SHOOT, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(STAND_RIGHT_POINT_UP_SHOOT, 8); // DONE
		sprite->addKeyframe(STAND_RIGHT_POINT_UP_SHOOT, glm::vec2(0.1f, 0.4f));
		sprite->addKeyframe(STAND_RIGHT_POINT_UP_SHOOT, glm::vec2(0.1f, 0.3f));
		sprite->addKeyframe(STAND_RIGHT_POINT_UP_SHOOT, glm::vec2(0.1f, 0.3f));
		sprite->addKeyframe(STAND_RIGHT_POINT_UP_SHOOT, glm::vec2(0.1f, 0.3f));

		sprite->setAnimationSpeed(STAND_RIGHT_POINT_DOWN_SHOOT, 8); // DONE
		sprite->addKeyframe(STAND_RIGHT_POINT_DOWN_SHOOT, glm::vec2(0.1f, 0.6f));
		sprite->addKeyframe(STAND_RIGHT_POINT_DOWN_SHOOT, glm::vec2(0.1f, 0.5f));
		sprite->addKeyframe(STAND_RIGHT_POINT_DOWN_SHOOT, glm::vec2(0.1f, 0.5f));
		sprite->addKeyframe(STAND_RIGHT_POINT_DOWN_SHOOT, glm::vec2(0.1f, 0.5f));

		sprite->setAnimationSpeed(MOVE_LEFT_POINT_LEFT_SHOOT, 8); // DONE
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT_SHOOT, glm::vec2(0.7f, 0.2f));
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT_SHOOT, glm::vec2(0.6f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT_SHOOT, glm::vec2(0.5f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT_SHOOT, glm::vec2(0.4f, 0.1f));

		sprite->setAnimationSpeed(MOVE_LEFT_POINT_UP_SHOOT, 8); // DONE
		sprite->addKeyframe(MOVE_LEFT_POINT_UP_SHOOT, glm::vec2(0.7f, 0.4f));
		sprite->addKeyframe(MOVE_LEFT_POINT_UP_SHOOT, glm::vec2(0.6f, 0.3f));
		sprite->addKeyframe(MOVE_LEFT_POINT_UP_SHOOT, glm::vec2(0.5f, 0.3f));
		sprite->addKeyframe(MOVE_LEFT_POINT_UP_SHOOT, glm::vec2(0.4f, 0.3f));

		sprite->setAnimationSpeed(MOVE_LEFT_POINT_DOWN_SHOOT, 8); // DONE
		sprite->addKeyframe(MOVE_LEFT_POINT_DOWN_SHOOT, glm::vec2(0.7f, 0.6f));
		sprite->addKeyframe(MOVE_LEFT_POINT_DOWN_SHOOT, glm::vec2(0.6f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT_POINT_DOWN_SHOOT, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT_POINT_DOWN_SHOOT, glm::vec2(0.4f, 0.5f));

		sprite->setAnimationSpeed(MOVE_RIGHT_POINT_RIGHT_SHOOT, 8); // DONE
		sprite->addKeyframe(MOVE_RIGHT_POINT_RIGHT_SHOOT, glm::vec2(0.0f, 0.2f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_RIGHT_SHOOT, glm::vec2(0.1f, 0.1f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_RIGHT_SHOOT, glm::vec2(0.2f, 0.1f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_RIGHT_SHOOT, glm::vec2(0.3f, 0.1f));

		sprite->setAnimationSpeed(MOVE_RIGHT_POINT_UP_SHOOT, 8); // DONE
		sprite->addKeyframe(MOVE_RIGHT_POINT_UP_SHOOT, glm::vec2(0.0f, 0.4f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_UP_SHOOT, glm::vec2(0.1f, 0.3f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_UP_SHOOT, glm::vec2(0.2f, 0.3f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_UP_SHOOT, glm::vec2(0.3f, 0.3f));

		sprite->setAnimationSpeed(MOVE_RIGHT_POINT_DOWN_SHOOT, 8); // DONE
		sprite->addKeyframe(MOVE_RIGHT_POINT_DOWN_SHOOT, glm::vec2(0.0f, 0.6f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_DOWN_SHOOT, glm::vec2(0.1f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_DOWN_SHOOT, glm::vec2(0.2f, 0.5f));
		sprite->addKeyframe(MOVE_RIGHT_POINT_DOWN_SHOOT, glm::vec2(0.3f, 0.5f));
		
		sprite->setAnimationSpeed(DYING_LEFT, 5);
		sprite->addKeyframe(DYING_LEFT, glm::vec2(0.5f, 0.8f));
		sprite->addKeyframe(DYING_LEFT, glm::vec2(0.4f, 0.8f));
		sprite->addKeyframe(DYING_LEFT, glm::vec2(0.3f, 0.8f));

		sprite->setAnimationSpeed(DEAD_LEFT, 1);
		sprite->addKeyframe(DEAD_LEFT, glm::vec2(0.3f, 0.8f));

		sprite->setAnimationSpeed(DYING_RIGHT, 5);
		sprite->addKeyframe(DYING_RIGHT, glm::vec2(0.0f, 0.8f));
		sprite->addKeyframe(DYING_RIGHT, glm::vec2(0.1f, 0.8f));
		sprite->addKeyframe(DYING_RIGHT, glm::vec2(0.2f, 0.8f));

		sprite->setAnimationSpeed(DEAD_RIGHT, 1);
		sprite->addKeyframe(DEAD_RIGHT, glm::vec2(0.2f, 0.8f));
		
	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::changeBasicAction(int basicAnimation, int deltaTime)
{
	if (dead) return;

	//cout << glutGet(GLUT_WINDOW_WIDTH) << " / " << glutGet(GLUT_WINDOW_HEIGHT) << endl;

	posMouseX = Game::instance().getPosMouseX();
	posMouseY = Game::instance().getPosMouseY();
	int windowSizeX = glutGet(GLUT_WINDOW_WIDTH);
	int windowSizeY = glutGet(GLUT_WINDOW_HEIGHT);
	bool lookingRight = false;
	if (posMouseX > windowSizeX / 2) lookingRight = true;

	//PLAYER -> Y = posPlayer.y	+ 24	sobre [0, 512] 
	//MOUSE -> Y = posMouseY			sobre [0, windowSizeY]
	//PLAYER -> X = windowSizeX / 2		sobre [0, windowSizeX]
	//MOUSE -> X = posMouseX			sobre [0, windowSizeX]

	// double angulo = atan2(MOUSE.Y - PLAYER.Y, MOUSE.X - PLAYER.X) * 180 / M_PI;
	double angulo = atan2(posMouseY - (int)((float)posPlayer.y + (float)24) * ((float)windowSizeY / (float)512), posMouseX - windowSizeX / 2) * 180 / M_PI;
	angulo = -angulo;

	// CURRENT TIME -> glutGet(GLUT_ELAPSED_TIME)
	// LAST SHOOTED -> lastShot
	// CURRENTLY SHOOTING -> shooting

	if (!shooting && Game::instance().isMousePressed() && lastShot + 400 <= glutGet(GLUT_ELAPSED_TIME) && basicAction != OTHERS) {
		// Initial shoot action
		shooting = true;
		lastShot = glutGet(GLUT_ELAPSED_TIME);
		shoot(angulo, posPlayer.x, posPlayer.y);
	}
	else if (lastShot < glutGet(GLUT_ELAPSED_TIME) && lastShot + 75 >= glutGet(GLUT_ELAPSED_TIME) && basicAction != OTHERS) {
		// Shooting animation
		shooting = true;
	}
	else {
		shooting = false;
	}

	this->basicAction = basicAnimation;
	if (basicAnimation == STAND_LEFT) {
		if (!shooting) {
			if (angulo > 90 && angulo < 157 && sprite->animation() != STAND_LEFT_POINT_UP) sprite->changeAnimation(STAND_LEFT_POINT_UP);
			else if ((angulo >= 157 || angulo <= -157) && sprite->animation() != STAND_LEFT_POINT_LEFT) sprite->changeAnimation(STAND_LEFT_POINT_LEFT);
			else if (angulo < -90 && angulo > -157 && sprite->animation() != STAND_LEFT_POINT_DOWN) sprite->changeAnimation(STAND_LEFT_POINT_DOWN);
			else if (((angulo <= 90 && angulo > 0) || (angulo <= 0 && angulo >= -90)) && sprite->animation() != STAND_LEFT_POINT_LEFT) sprite->changeAnimation(STAND_LEFT_POINT_LEFT);
		}
		else {
			if (angulo > 90 && angulo < 157 ) sprite->changeAnimation(STAND_LEFT_POINT_UP_SHOOT);
			else if ((angulo >= 157 || angulo <= -157) ) sprite->changeAnimation(STAND_LEFT_POINT_LEFT_SHOOT);
			else if (angulo < -90 && angulo > -157 ) sprite->changeAnimation(STAND_LEFT_POINT_DOWN_SHOOT);
			else if (((angulo <= 90 && angulo > 0) || (angulo <= 0 && angulo >= -90)) ) sprite->changeAnimation(STAND_LEFT_POINT_LEFT_SHOOT);
		}
	}
	else if (basicAnimation == STAND_RIGHT) {
		if (!shooting) {
			if (angulo > 22 && angulo < 90 && sprite->animation() != STAND_RIGHT_POINT_UP) sprite->changeAnimation(STAND_RIGHT_POINT_UP);
			else if (angulo >= -22 && angulo <= 22 && sprite->animation() != STAND_RIGHT_POINT_RIGHT) sprite->changeAnimation(STAND_RIGHT_POINT_RIGHT);
			else if (angulo > -90 && angulo < -22 && sprite->animation() != STAND_RIGHT_POINT_DOWN) sprite->changeAnimation(STAND_RIGHT_POINT_DOWN);
			else if ((angulo >= 90 || angulo <= -90) && sprite->animation() != STAND_RIGHT_POINT_RIGHT) sprite->changeAnimation(STAND_RIGHT_POINT_RIGHT);
		}
		else {
			if (angulo > 22 && angulo < 90) sprite->changeAnimation(STAND_RIGHT_POINT_UP_SHOOT);
			else if (angulo >= -22 && angulo <= 22) sprite->changeAnimation(STAND_RIGHT_POINT_RIGHT_SHOOT);
			else if (angulo > -90 && angulo < -22) sprite->changeAnimation(STAND_RIGHT_POINT_DOWN_SHOOT);
			else if ((angulo >= 90 || angulo <= -90)) sprite->changeAnimation(STAND_RIGHT_POINT_RIGHT_SHOOT);
		}
	}
	else if (basicAnimation == MOVE_LEFT) {
		if (!shooting) {
			if (angulo > 90 && angulo < 157 && sprite->animation() != MOVE_LEFT_POINT_UP) sprite->changeAnimation(MOVE_LEFT_POINT_UP);
			else if ((angulo >= 157 || angulo <= -157) && sprite->animation() != MOVE_LEFT_POINT_LEFT) sprite->changeAnimation(MOVE_LEFT_POINT_LEFT);
			else if (angulo < -90 && angulo > -157 && sprite->animation() != MOVE_LEFT_POINT_DOWN) sprite->changeAnimation(MOVE_LEFT_POINT_DOWN);
			else if (((angulo <= 90 && angulo > 0) || (angulo <= 0 && angulo >= -90)) && sprite->animation() != MOVE_LEFT_POINT_LEFT) sprite->changeAnimation(MOVE_LEFT_POINT_LEFT);
		}
		else {
			if (angulo > 90 && angulo < 157) sprite->changeAnimation(MOVE_LEFT_POINT_UP_SHOOT);
			else if ((angulo >= 157 || angulo <= -157)) sprite->changeAnimation(MOVE_LEFT_POINT_LEFT_SHOOT);
			else if (angulo < -90 && angulo > -157) sprite->changeAnimation(MOVE_LEFT_POINT_DOWN_SHOOT);
			else if (((angulo <= 90 && angulo > 0) || (angulo <= 0 && angulo >= -90))) sprite->changeAnimation(MOVE_LEFT_POINT_LEFT_SHOOT);
		}
	}
	else if (basicAnimation == MOVE_RIGHT) {
		if (!shooting) {
			if (angulo > 22 && angulo < 90 && sprite->animation() != MOVE_RIGHT_POINT_UP) sprite->changeAnimation(MOVE_RIGHT_POINT_UP);
			else if (angulo >= -22 && angulo <= 22 && sprite->animation() != MOVE_RIGHT_POINT_RIGHT) sprite->changeAnimation(MOVE_RIGHT_POINT_RIGHT);
			else if (angulo > -90 && angulo < -22 && sprite->animation() != MOVE_RIGHT_POINT_DOWN) sprite->changeAnimation(MOVE_RIGHT_POINT_DOWN);
			else if ((angulo >= 90 || angulo <= -90) && sprite->animation() != MOVE_RIGHT_POINT_RIGHT) sprite->changeAnimation(MOVE_RIGHT_POINT_RIGHT);
		}
		else {
			if (angulo > 22 && angulo < 90) sprite->changeAnimation(MOVE_RIGHT_POINT_UP_SHOOT);
			else if (angulo >= -22 && angulo <= 22) sprite->changeAnimation(MOVE_RIGHT_POINT_RIGHT_SHOOT);
			else if (angulo > -90 && angulo < -22) sprite->changeAnimation(MOVE_RIGHT_POINT_DOWN_SHOOT);
			else if ((angulo >= 90 || angulo <= -90)) sprite->changeAnimation(MOVE_RIGHT_POINT_RIGHT_SHOOT);
		}
	}

}

void Player::update(int deltaTime)
{
	if (currentGun == 1 && posPlayer.x > UPGRADE_WEAPON_X) currentGun = 2;
	if (dead && deathTime + 500 >= glutGet(GLUT_ELAPSED_TIME)) {
		if (basicAction == STAND_LEFT || basicAction == MOVE_LEFT || sprite->animation() == JUMP_LEFT || sprite->animation() == DYING_LEFT) {
			if (sprite->animation() != DYING_LEFT) {
				sprite->changeAnimation(DYING_LEFT);
			}
		}
		else if (basicAction == STAND_RIGHT || basicAction == MOVE_RIGHT || sprite->animation() == JUMP_RIGHT || sprite->animation() == DYING_RIGHT) {
			if (sprite->animation() != DYING_RIGHT) {
				sprite->changeAnimation(DYING_RIGHT);
			}
		} 
	}
	else if (dead) {
		if (sprite->animation() == DYING_LEFT)
		{
			sprite->changeAnimation(DEAD_LEFT);
			deathFinished = true;
		}
		else if (sprite->animation() == DYING_RIGHT)
		{
			sprite->changeAnimation(DEAD_RIGHT);
			deathFinished = true;
		}
	}
	   
	changeBasicAction(basicAction, deltaTime);
	
	sprite->update(deltaTime);

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && bJumping == false && !dead) {
		posPlayer.y += 2;
	}
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !dead)
	{
		if(basicAction != MOVE_LEFT && bJumping == false)
			changeBasicAction(MOVE_LEFT, deltaTime);
		posPlayer.x -= RUN_VELOCITY;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(48, 48)))
		{
			posPlayer.x += RUN_VELOCITY;
			changeBasicAction(STAND_LEFT, deltaTime);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !dead)
	{
		if(basicAction != MOVE_RIGHT && bJumping == false)
			changeBasicAction(MOVE_RIGHT, deltaTime);
		posPlayer.x += RUN_VELOCITY;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(48, 48)))
		{
			posPlayer.x -= RUN_VELOCITY;
			changeBasicAction(STAND_RIGHT, deltaTime);
		}
	}
	else if (!dead)
	{
		if(basicAction == MOVE_LEFT)
			changeBasicAction(STAND_LEFT, deltaTime);
		else if(basicAction == MOVE_RIGHT)
			changeBasicAction(STAND_RIGHT, deltaTime);
	}
	
	if(bJumping && !dead)
	{
		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && sprite->animation() != JUMP_RIGHT) {
			changeBasicAction(OTHERS, deltaTime);
			sprite->changeAnimation(JUMP_RIGHT);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && sprite->animation() != JUMP_LEFT) {
			changeBasicAction(OTHERS, deltaTime);
			sprite->changeAnimation(JUMP_LEFT);
		}
		else if (basicAction == STAND_RIGHT && sprite->animation() != JUMP_RIGHT) {
			changeBasicAction(OTHERS, deltaTime);
			sprite->changeAnimation(JUMP_RIGHT);
		}
		else if (basicAction == STAND_LEFT && sprite->animation() != JUMP_LEFT) {
			changeBasicAction(OTHERS, deltaTime);
			sprite->changeAnimation(JUMP_LEFT);
		}

		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(48, 48), &posPlayer.y);
		}

		if (bJumping == false && sprite->animation() == JUMP_RIGHT) {
			changeBasicAction(STAND_RIGHT, deltaTime);
		}
		else if (bJumping == false && sprite->animation() == JUMP_LEFT) {
			changeBasicAction(STAND_LEFT, deltaTime);
		}

	}
	else
	{
		if (posPlayer.y < 455) {
			posPlayer.y += FALL_STEP;
			if (map->collisionMoveDown(posPlayer, glm::ivec2(48, 48), &posPlayer.y))
			{
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
		}
		else if (!dead) kill();
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Player::getPosition()
{
	return posPlayer;
}

void Player::shoot(double angulo, int x, int y) 
{
	cout << "SHOT FIRED: Angle=" << angulo << " X=" << x << " Y=" << y << " Type=" << currentGun << endl;
	shootedProjectile = true;
	projectileCoords.x = x+22;
	projectileCoords.y = y;
	if (basicAction == STAND_LEFT || basicAction == MOVE_LEFT) projectileCoords.x -= 20;
	else projectileCoords.x += 20;
	projectileType = currentGun;
	projectileVelocity = SHOT_VELOCITY;
	//projectileAngle = angulo;
	if ((basicAction == STAND_LEFT || basicAction == MOVE_LEFT) && angulo < 90 && angulo > -90) projectileAngle = 180;
	else if ((basicAction == STAND_RIGHT || basicAction == MOVE_RIGHT) && (angulo > 90 || angulo < -90)) projectileAngle = 0;
	else if (angulo > -22 && angulo < 22) projectileAngle = 0;
	else if (angulo >= 22 && angulo <= 90) projectileAngle = 45;
	else if (angulo >= -90 && angulo <= -22) projectileAngle = -45;
	else if (angulo >= 90 && angulo <= 157) projectileAngle = 135;
	else if (angulo >= -157 && angulo <= -90) projectileAngle = -135;
	else if (angulo >= 157 || angulo <= -157) projectileAngle = 180;

	if (projectileAngle > 0 && projectileAngle != 180)  projectileCoords.y -= 20;
	else if (projectileAngle < 0 && projectileAngle != -180)  projectileCoords.y += 20;
}

void Player::kill() {
	deathTime = glutGet(GLUT_ELAPSED_TIME);
	dead = true;
}

bool Player::isDead() {
	return deathFinished;
}

bool Player::hasShootedProjectile() {
	if (shootedProjectile) {
		shootedProjectile = false;
		return true;
	}
	else return false;
}
glm::ivec2 Player::getProjectileCoords() {
	return projectileCoords;
}
int Player::getProjectileAngle() {
	return projectileAngle;
}
int Player::getProjectileVelocity() {
	return projectileVelocity;
}
int Player::getProjectileType() {
	return projectileType;
}
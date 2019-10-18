#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

# define M_PI           3.14159265358979323846  /* pi */

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define RUN_VELOCITY 3


enum PlayerAnims
{
	STAND_LEFT_POINT_LEFT, STAND_RIGHT_POINT_RIGHT, MOVE_LEFT_POINT_LEFT, MOVE_RIGHT_POINT_RIGHT, JUMP_LEFT, JUMP_RIGHT,
	STAND_LEFT_POINT_UP, STAND_LEFT_POINT_DOWN, STAND_RIGHT_POINT_UP, STAND_RIGHT_POINT_DOWN,
	MOVE_LEFT_POINT_UP, MOVE_LEFT_POINT_DOWN, MOVE_RIGHT_POINT_UP, MOVE_RIGHT_POINT_DOWN
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
	sprite->setNumberAnimations(14);
	
		sprite->setAnimationSpeed(STAND_LEFT_POINT_LEFT, 3);
		sprite->addKeyframe(STAND_LEFT_POINT_LEFT, glm::vec2(0.7f, 0.f));
		sprite->addKeyframe(STAND_LEFT_POINT_LEFT, glm::vec2(0.6f, 0.f));

		sprite->setAnimationSpeed(STAND_LEFT_POINT_UP, 2);
		sprite->addKeyframe(STAND_LEFT_POINT_UP, glm::vec2(0.6f, 0.3f));

		sprite->setAnimationSpeed(STAND_LEFT_POINT_DOWN, 2);
		sprite->addKeyframe(STAND_LEFT_POINT_DOWN, glm::vec2(0.6f, 0.5f));
		
		sprite->setAnimationSpeed(STAND_RIGHT_POINT_RIGHT, 3);
		sprite->addKeyframe(STAND_RIGHT_POINT_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_RIGHT_POINT_RIGHT, glm::vec2(0.1f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT_POINT_UP, 2);
		sprite->addKeyframe(STAND_RIGHT_POINT_UP, glm::vec2(0.1f, 0.3f));

		sprite->setAnimationSpeed(STAND_RIGHT_POINT_DOWN, 2);
		sprite->addKeyframe(STAND_RIGHT_POINT_DOWN, glm::vec2(0.1f, 0.5f));

		sprite->setAnimationSpeed(MOVE_LEFT_POINT_LEFT, 4);
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT, glm::vec2(0.7f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT, glm::vec2(0.6f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT, glm::vec2(0.5f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT_POINT_LEFT, glm::vec2(0.4f, 0.1f));

		sprite->setAnimationSpeed(MOVE_LEFT_POINT_UP, 4);
		sprite->addKeyframe(MOVE_LEFT_POINT_UP, glm::vec2(0.7f, 0.3f));
		sprite->addKeyframe(MOVE_LEFT_POINT_UP, glm::vec2(0.6f, 0.3f));
		sprite->addKeyframe(MOVE_LEFT_POINT_UP, glm::vec2(0.5f, 0.3f));
		sprite->addKeyframe(MOVE_LEFT_POINT_UP, glm::vec2(0.4f, 0.3f));

		sprite->setAnimationSpeed(MOVE_LEFT_POINT_DOWN, 4);
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
		

		
	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::changeBasicAction(int basicAnimation)
{
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

	this->basicAction = basicAnimation;
	if (basicAnimation == STAND_LEFT) {
		if (!shooting) {
			if (angulo > 90 && angulo < 157 && sprite->animation() != STAND_LEFT_POINT_UP) sprite->changeAnimation(STAND_LEFT_POINT_UP);
			else if ((angulo >= 157 || angulo <= -157) && sprite->animation() != STAND_LEFT_POINT_LEFT) sprite->changeAnimation(STAND_LEFT_POINT_LEFT);
			else if (angulo < -90 && angulo > -157 && sprite->animation() != STAND_LEFT_POINT_DOWN) sprite->changeAnimation(STAND_LEFT_POINT_DOWN);
			else if (((angulo <= 90 && angulo > 0) || (angulo <= 0 && angulo >= -90)) && sprite->animation() != STAND_LEFT_POINT_LEFT) sprite->changeAnimation(STAND_LEFT_POINT_LEFT);
		}
	}
	else if (basicAnimation == STAND_RIGHT) {
		if (!shooting) {
			if (angulo > 22 && angulo < 90 && sprite->animation() != STAND_RIGHT_POINT_UP) sprite->changeAnimation(STAND_RIGHT_POINT_UP);
			else if (angulo >= -22 && angulo <= 22 && sprite->animation() != STAND_RIGHT_POINT_RIGHT) sprite->changeAnimation(STAND_RIGHT_POINT_RIGHT);
			else if (angulo > -90 && angulo < -22 && sprite->animation() != STAND_RIGHT_POINT_DOWN) sprite->changeAnimation(STAND_RIGHT_POINT_DOWN);
			else if ((angulo >= 90 || angulo <= -90) && sprite->animation() != STAND_RIGHT_POINT_RIGHT) sprite->changeAnimation(STAND_RIGHT_POINT_RIGHT);
		}
	}
	else if (basicAnimation == MOVE_LEFT) {
		if (!shooting) {
			if (angulo > 90 && angulo < 157 && sprite->animation() != MOVE_LEFT_POINT_UP) sprite->changeAnimation(MOVE_LEFT_POINT_UP);
			else if ((angulo >= 157 || angulo <= -157) && sprite->animation() != MOVE_LEFT_POINT_LEFT) sprite->changeAnimation(MOVE_LEFT_POINT_LEFT);
			else if (angulo < -90 && angulo > -157 && sprite->animation() != MOVE_LEFT_POINT_DOWN) sprite->changeAnimation(MOVE_LEFT_POINT_DOWN);
			else if (((angulo <= 90 && angulo > 0) || (angulo <= 0 && angulo >= -90)) && sprite->animation() != MOVE_LEFT_POINT_LEFT) sprite->changeAnimation(MOVE_LEFT_POINT_LEFT);
		}
	}
	else if (basicAnimation == MOVE_RIGHT) {
		if (!shooting) {
			if (angulo > 22 && angulo < 90 && sprite->animation() != MOVE_RIGHT_POINT_UP) sprite->changeAnimation(MOVE_RIGHT_POINT_UP);
			else if (angulo >= -22 && angulo <= 22 && sprite->animation() != MOVE_RIGHT_POINT_RIGHT) sprite->changeAnimation(MOVE_RIGHT_POINT_RIGHT);
			else if (angulo > -90 && angulo < -22 && sprite->animation() != MOVE_RIGHT_POINT_DOWN) sprite->changeAnimation(MOVE_RIGHT_POINT_DOWN);
			else if ((angulo >= 90 || angulo <= -90) && sprite->animation() != MOVE_RIGHT_POINT_RIGHT) sprite->changeAnimation(MOVE_RIGHT_POINT_RIGHT);
		}
	}

}

void Player::update(int deltaTime)
{

	changeBasicAction(basicAction);
	

	sprite->update(deltaTime);

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && bJumping == false) {
		posPlayer.y += 2;
	}
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(basicAction != MOVE_LEFT && bJumping == false)
			changeBasicAction(MOVE_LEFT);
		posPlayer.x -= RUN_VELOCITY;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(48, 48)))
		{
			posPlayer.x += RUN_VELOCITY;
			changeBasicAction(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(basicAction != MOVE_RIGHT && bJumping == false)
			changeBasicAction(MOVE_RIGHT);
		posPlayer.x += RUN_VELOCITY;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(48, 48)))
		{
			posPlayer.x -= RUN_VELOCITY;
			changeBasicAction(STAND_RIGHT);
		}
	}
	else
	{
		if(basicAction == MOVE_LEFT)
			changeBasicAction(STAND_LEFT);
		else if(basicAction == MOVE_RIGHT)
			changeBasicAction(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && sprite->animation() != JUMP_RIGHT) {
			changeBasicAction(OTHERS);
			sprite->changeAnimation(JUMP_RIGHT);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && sprite->animation() != JUMP_LEFT) {
			changeBasicAction(OTHERS);
			sprite->changeAnimation(JUMP_LEFT);
		}
		else if (basicAction == STAND_RIGHT && sprite->animation() != JUMP_RIGHT) {
			changeBasicAction(OTHERS);
			sprite->changeAnimation(JUMP_RIGHT);
		}
		else if (basicAction == STAND_LEFT && sprite->animation() != JUMP_LEFT) {
			changeBasicAction(OTHERS);
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
			changeBasicAction(STAND_RIGHT);
		}
		else if (bJumping == false && sprite->animation() == JUMP_LEFT) {
			changeBasicAction(STAND_LEFT);
		}

	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(48, 48), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
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


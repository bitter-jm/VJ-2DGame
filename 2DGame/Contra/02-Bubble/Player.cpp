#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT
	/*STAND_LEFT,  STAND_LEFT_POINT_UP, STAND_LEFT_POINT_DOWN, 
	STAND_RIGHT, STAND_RIGHT_POINT_UP, STAND_RIGHT_POIN_DOWN,
	MOVE_LEFT, MOVE_LEFT_POINT_UP, MOVE_LEFT_POINT_DOWN,
	MOVE_RIGHT, MOVE_RIGHT_POINT_UP, MOVE_RIGHT_POINT_DOWN,
	JUMP*/
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.1, 0.1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
		sprite->setAnimationSpeed(STAND_LEFT, 2);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.7f, 0.f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.6f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 2);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.1f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 4);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.7f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.1f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.4f, 0.1f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.1f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.1f, 0.1f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.1f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.3f, 0.1f));

		sprite->setAnimationSpeed(JUMP_LEFT, 8);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.7f, 0.7f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.6f, 0.7f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.5f, 0.7f));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.4f, 0.7f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 8);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.0f, 0.7f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.1f, 0.7f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.2f, 0.7f));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.3f, 0.7f));
		

		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{

	sprite->update(deltaTime);

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && bJumping == false) {
		posPlayer.y += 2;
	}
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT && bJumping == false)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT && bJumping == false)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && sprite->animation() != JUMP_RIGHT) {
			sprite->changeAnimation(JUMP_RIGHT);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && sprite->animation() != JUMP_LEFT) {
			sprite->changeAnimation(JUMP_LEFT);
		}
		else if (sprite->animation() == STAND_RIGHT && sprite->animation() != JUMP_RIGHT) {
			sprite->changeAnimation(JUMP_RIGHT);
		}
		else if (sprite->animation() == STAND_LEFT && sprite->animation() != JUMP_LEFT) {
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
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}

		if (bJumping == false && sprite->animation() == JUMP_RIGHT) {
			sprite->changeAnimation(STAND_RIGHT);
		}
		else if (bJumping == false && sprite->animation() == JUMP_LEFT) {
			sprite->changeAnimation(STAND_LEFT);
		}

	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
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





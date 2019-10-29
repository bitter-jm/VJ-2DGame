#include "Boss.h"

#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include<iostream>

#define M_PI 3.13

enum BossAnim {
	FULL, 
	FULL_EXPLODE, LEFT_AND_BODY_EXPLODE, RIGHT_AND_BODY_EXPLODE, BODY_EXPLODE,
	LEFT_EXPLODE, WITHOUT_LEFT, WITHOUT_LEFT_EXPLODE_RIGHT, ONLY_BODY,
	RIGHT_EXPLODE, WITHOUT_RIGHT, WITHOUT_RIGHT_EXPLODE_LEFT
};

void Boss::shootMain(float time) {
	if (time - lastShoot >= secondsToAttack * 1000) {
		int angle = atan2(mainPos.y - player->getPosition().y, player->getPosition().x - mainPos.x) * 180 / M_PI;
		if (angle < 0) angle += 360;
		em->createProjectile(glm::vec2(mainPos.x, mainPos.y), angle, projectileSpeed, 4, range, dmg);
		lastShoot = time;
	}
}

void Boss::shootLeft(float time) {
	if (time - leftLastShot >= secondsToAttackLeft * 1000) {
		glm::vec2 leftPos = glm::vec2(position.x + 1 * map->getTileSize(), position.y + 2.5 * map->getTileSize());
		int angle = atan2(leftPos.y - player->getPosition().y, player->getPosition().x -10 - leftPos.x) * 180 / M_PI;
		if (angle < 0) angle += 360;
		em->createProjectile(glm::vec2(leftPos.x, leftPos.y), angle, leftProjSpeed, 5, range, leftPartDMG);
		leftLastShot = time;
	}
}

void Boss::shootRight(float time) {
	if (time - rightLastShot >= secondsToAttackRight * 1000) {
		glm::vec2 rightPos = glm::vec2(position.x + 7 * map->getTileSize(), position.y + 2.5 * map->getTileSize());
		int angle = atan2(rightPos.y - player->getPosition().y, player->getPosition().x + 10 - rightPos.x) * 180 / M_PI;
		if (angle < 0) angle += 360;
		em->createProjectile(glm::vec2(rightPos.x, rightPos.y), angle, rightProjSpeed, 5, range, rightPartDMG);
		rightLastShot = time;
	}
}

void Boss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int pID, TileMap* tileMap, glm::vec2 pos)
{
	map = tileMap; 
	position = pos;

	range = 15;
	leftPartRange = rightPartRange = 15;

	hp = 30;
	rightPartHP = leftPartHP = 10;
	dmg = 2;
	rightPartDMG = leftPartDMG = 1;
	secondsToAttack = 3;
	secondsToAttackLeft = secondsToAttackRight = 2.5;
	projectileSpeed = 1;
	leftProjSpeed = rightProjSpeed = 1;

	dead = false;
	dyingTime = 300; //ms 
	stanceID = FULL;

	mainPos = glm::vec2(position.x + 3 * map->getTileSize() + 32, position.y + 3 * map->getTileSize());

	float spriteSheetX = 0.5;
	float spriteSheetY = 1.0 / 8.0;
	tileMapDispl = tileMapPos;
	spritesheet.loadFromFile("images/bossSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(8*64, 4*64), glm::vec2(0.5, spriteSheetY), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(12);

	sprite->setAnimationSpeed(FULL, 2);
	sprite->addKeyframe(FULL, glm::vec2(0.0 * spriteSheetX, 0.0 * spriteSheetY));

	sprite->setAnimationSpeed(FULL_EXPLODE, 2);
	sprite->addKeyframe(FULL_EXPLODE, glm::vec2(1 * spriteSheetX, 0.0 * spriteSheetY));

	sprite->setAnimationSpeed(LEFT_AND_BODY_EXPLODE, 2);
	sprite->addKeyframe(LEFT_AND_BODY_EXPLODE, glm::vec2(1 * spriteSheetX, 5.0 * spriteSheetY));

	sprite->setAnimationSpeed(RIGHT_AND_BODY_EXPLODE, 2);
	sprite->addKeyframe(RIGHT_AND_BODY_EXPLODE, glm::vec2(0 * spriteSheetX, 6.0 * spriteSheetY));

	sprite->setAnimationSpeed(BODY_EXPLODE, 2);
	sprite->addKeyframe(BODY_EXPLODE, glm::vec2(0 * spriteSheetX, 5.0 * spriteSheetY));

	sprite->setAnimationSpeed(LEFT_EXPLODE, 2);
	sprite->addKeyframe(LEFT_EXPLODE, glm::vec2(0 * spriteSheetX, 1 * spriteSheetY));

	sprite->setAnimationSpeed(WITHOUT_LEFT, 2);
	sprite->addKeyframe(WITHOUT_LEFT, glm::vec2(1 * spriteSheetX, 1 * spriteSheetY));

	sprite->setAnimationSpeed(WITHOUT_LEFT_EXPLODE_RIGHT, 2);
	sprite->addKeyframe(WITHOUT_LEFT_EXPLODE_RIGHT, glm::vec2(0 * spriteSheetX, 2 * spriteSheetY));

	sprite->setAnimationSpeed(ONLY_BODY, 2);
	sprite->addKeyframe(ONLY_BODY, glm::vec2(1 * spriteSheetX, 2 * spriteSheetY));

	sprite->setAnimationSpeed(RIGHT_EXPLODE, 2);
	sprite->addKeyframe(RIGHT_EXPLODE, glm::vec2(0 * spriteSheetX, 3 * spriteSheetY));

	sprite->setAnimationSpeed(WITHOUT_RIGHT, 2);
	sprite->addKeyframe(WITHOUT_RIGHT, glm::vec2(1 * spriteSheetX, 3 * spriteSheetY));

	sprite->setAnimationSpeed(WITHOUT_RIGHT_EXPLODE_LEFT, 2);
	sprite->addKeyframe(WITHOUT_RIGHT_EXPLODE_LEFT, glm::vec2(0 * spriteSheetX, 4 * spriteSheetY));

	sprite->changeAnimation(FULL);

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}


void Boss::update(int deltaTime){
	sprite->update(deltaTime);
	int time = glutGet(GLUT_ELAPSED_TIME);

	switch (stanceID) {
		case(FULL):
			if (hp <= 0 || Game::instance().getSpecialKey(GLUT_KEY_F1)) {
				sprite->changeAnimation(FULL_EXPLODE);
				stanceID = FULL_EXPLODE;
				dyingStartTime = time;
			}
			else if (leftPartHP <= 0) {
				sprite->changeAnimation(LEFT_EXPLODE);
				stanceID = LEFT_EXPLODE;
				dyingStartTime = time;
			}
			else if (rightPartHP <= 0) {
				sprite->changeAnimation(RIGHT_EXPLODE);
				stanceID = RIGHT_EXPLODE;
				dyingStartTime = time;
			}
			break;

		case(FULL_EXPLODE):
			if (time - dyingStartTime >= dyingTime) {
				dead = true;
			}
			break;

		case(LEFT_AND_BODY_EXPLODE):
			if (time - dyingStartTime >= dyingTime) {
				dead = true;
			}
			break;

		case(RIGHT_AND_BODY_EXPLODE):
			if (time - dyingStartTime >= dyingTime) {
				dead = true;
			}
			break;

		case(BODY_EXPLODE):
			if (time - dyingStartTime >= dyingTime) {
				dead = true;
			}
			break;

		case(LEFT_EXPLODE):
			if (time - dyingStartTime >= dyingTime) {
				sprite->changeAnimation(WITHOUT_LEFT);
				stanceID = WITHOUT_LEFT;
			}
			break;

		case(RIGHT_EXPLODE):
			if (time - dyingStartTime >= dyingTime) {
				sprite->changeAnimation(WITHOUT_RIGHT);
				stanceID = WITHOUT_RIGHT;
			}
			break;

		case(WITHOUT_LEFT):
			if (hp <= 0) {
				sprite->changeAnimation(RIGHT_AND_BODY_EXPLODE);
				stanceID = RIGHT_AND_BODY_EXPLODE;
				dyingStartTime = time;
			}
			else if (rightPartHP <= 0) {
				sprite->changeAnimation(WITHOUT_LEFT_EXPLODE_RIGHT);
				stanceID = WITHOUT_LEFT_EXPLODE_RIGHT;
				dyingStartTime = time;
			}
			break;

		case(WITHOUT_RIGHT):
			if (hp <= 0) {
				sprite->changeAnimation(LEFT_AND_BODY_EXPLODE);
				stanceID = LEFT_AND_BODY_EXPLODE;
				dyingStartTime = time;
			}
			else if (leftPartHP <= 0) {
				sprite->changeAnimation(WITHOUT_RIGHT_EXPLODE_LEFT);
				stanceID = WITHOUT_RIGHT_EXPLODE_LEFT;
				dyingStartTime = time;
			}
			break;

		case(WITHOUT_LEFT_EXPLODE_RIGHT):
			if (time - dyingStartTime >= dyingTime) {
				sprite->changeAnimation(ONLY_BODY);
				stanceID = ONLY_BODY;
			}
			break;

		case(WITHOUT_RIGHT_EXPLODE_LEFT):
			if (time - dyingStartTime >= dyingTime) {
				sprite->changeAnimation(ONLY_BODY);
				stanceID = ONLY_BODY;
			}
			break;

		case(ONLY_BODY):
			if (hp <= 0) {
				sprite->changeAnimation(BODY_EXPLODE);
				stanceID = BODY_EXPLODE;
				dyingStartTime = time;
			}
			break;
	}

	if (hp > 0) shootMain(time);
	if (leftPartHP > 0) shootLeft(time);
	if (rightPartHP > 0) shootRight(time);

}


void Boss::reduceLeftHp(float dmg) {
	leftPartHP -= dmg;
}

void Boss::reduceRightHp(float dmg) {
	rightPartHP -= dmg;
}

bool Boss::is_left_dead() {
	return leftPartHP <= 0;
}

bool Boss::is_right_dead() {
	return rightPartHP <= 0;
}



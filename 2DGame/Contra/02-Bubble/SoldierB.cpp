#include "SoldierB.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include<iostream>

enum SoldierBAnim {
	STAND_LEFT, EXPLODE
};

bool SoldierB::playerInRange() {
	int distY = (player->getPosition().y - position.y) / map->getTileSize();
	int distX = (player->getPosition().x - position.x) / map->getTileSize();
	if (distY == 0 && distX == 0) return true;
	if (distY == 0 && distX >= -range && distX <= 0) return true;
	return false;
}

void SoldierB::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int pID)
{
	range = 8;
	hp = 3;
	dmg = 3;
	secondsToAttack = 1.5;
	projectileSpeed = 5;
	dead = false;
	dying = false;
	dyingTime = 600; //ms 
	stanceID = pID;

	float spriteSheetX = 0.1;
	float spriteSheetY = 1.0 / 18.0;
	tileMapDispl = tileMapPos;
	spritesheet.loadFromFile("images/enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(55, 55), glm::vec2(0.11, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(STAND_LEFT, 2);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(5 * spriteSheetX +0.018, 14 * spriteSheetY + 0.01));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(6 * spriteSheetX +0.02, 14 * spriteSheetY + 0.01));

	sprite->setAnimationSpeed(EXPLODE, 3);
	sprite->addKeyframe(EXPLODE, glm::vec2(7.9 * spriteSheetX, 17 * spriteSheetY));
	sprite->addKeyframe(EXPLODE, glm::vec2(8.95 * spriteSheetX, 17 * spriteSheetY));

	sprite->changeAnimation(pID);

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}


void SoldierB::update(int deltaTime)
{
	sprite->update(deltaTime);
	int time = glutGet(GLUT_ELAPSED_TIME);

	if (Game::instance().getSpecialKey(GLUT_KEY_F1)) {	//die
		sprite->changeAnimation(EXPLODE);
		dying = true;
		dyingStartTime = time;
		return;
	}
	if (dying && time - dyingStartTime >= dyingTime) {
		dead = true;
		return;
	}

	else if(!dying) {
		if (playerInRange() && time - lastShoot >= secondsToAttack * 1000) {
			em->createProjectile(glm::vec2(position.x, position.y + 7), 180, projectileSpeed, 1, range);
			lastShoot = time;
		}
	}
}



#include "SoldierA.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include<iostream>

#define M_PI 3.14
#define tol 3.14/8

enum SoldierAAnim {
	STAND_LEFT, STAND_LEFT_DIAG_UP, STAND_LEFT_DAIG_DOWN, EXPLODE
}; 

bool SoldierA::playerInRange() {
	// Distance in Tiles
	int distY = (position.y - player->getPosition().y) / map->getTileSize();	//y girado para que los angulos salgan correctos
	int distX = (player->getPosition().x - position.x) / map->getTileSize();
	int dist = sqrt(distY * distY + distX * distX);
	if (distY == 0 && distX == 0) return true;
	switch (stanceID) {
		case (STAND_LEFT):
			if (distY == 0 && distX >= -range && distX <= 0) return true;
			break;
		case (STAND_LEFT_DIAG_UP):
			if (atan2(distY, distX) >= 3 * M_PI / 4 - tol && abs(atan2(distY, distX)) <= 3 * M_PI / 4 + tol)
				if (dist <= range && dist >= 0) return true;
			break;
		case (STAND_LEFT_DAIG_DOWN):
			if (atan2(distY, distX) >=  -3*M_PI / 4 - tol && atan2(distY, distX) <= -3*M_PI / 4 + tol)
				if (dist <= range && dist >= 0) return true;
			break;
	}
	return false;
}

void SoldierA::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int pID)
{
	range = 5;
	hp = 1;
	dmg = 1;
	secondsToAttack = 0.75;
	projectileSpeed = 4;
	dead = false;
	dying = false;
	dyingTime = 600; //ms 
	stanceID = pID;

	float spriteSheetX = 0.08;
	float spriteSheetY = 1/18.0;
	tileMapDispl = tileMapPos;
	spritesheet.loadFromFile("images/enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(55, 55), glm::vec2(0.065, 0.060), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 3);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0 * spriteSheetX+0.01, 0.055));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(1 * spriteSheetX+0.01, 0.055));
	
	sprite->setAnimationSpeed(STAND_LEFT_DIAG_UP, 3);
	sprite->addKeyframe(STAND_LEFT_DIAG_UP, glm::vec2(2*spriteSheetX, 0.055));
	sprite->addKeyframe(STAND_LEFT_DIAG_UP, glm::vec2(3*spriteSheetX-0.018, 0.055));
	
	sprite->setAnimationSpeed(STAND_LEFT_DAIG_DOWN, 3);
	sprite->addKeyframe(STAND_LEFT_DAIG_DOWN, glm::vec2(4*spriteSheetX-0.028, 0.055));

	sprite->setAnimationSpeed(EXPLODE, 4);
	sprite->addKeyframe(EXPLODE, glm::vec2(0 * spriteSheetX + 0.012, 17 * spriteSheetY));
	sprite->addKeyframe(EXPLODE, glm::vec2(1 * spriteSheetX + 0.012, 17 * spriteSheetY));
	sprite->addKeyframe(EXPLODE, glm::vec2(2 * spriteSheetX + 0.012, 17 * spriteSheetY));


	sprite->changeAnimation(pID);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}


void SoldierA::update(int deltaTime)
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

	else if (!dying) {
		int distY = (position.y - player->getPosition().y) / map->getTileSize();
		int distX = (player->getPosition().x - position.x) / map->getTileSize();
		int radAngle = atan2(distY, distX);

		 if (radAngle == int(M_PI)) {
			sprite->changeAnimation(STAND_LEFT);
			stanceID = STAND_LEFT;
		}
		else if (radAngle >= 3 * M_PI / 4 - tol && radAngle <= 3 * M_PI / 4 + tol) {
			sprite->changeAnimation(STAND_LEFT_DIAG_UP);
			stanceID = STAND_LEFT_DIAG_UP;
		}
		else if (radAngle >= -3 * M_PI / 4 - tol && radAngle <= -3 * M_PI / 4 + tol) {
			 sprite->changeAnimation(STAND_LEFT_DAIG_DOWN);
			 stanceID = STAND_LEFT_DAIG_DOWN;
		 }

		if (playerInRange()) {
			if (stanceID == STAND_LEFT) {
				if (time - lastShoot >= secondsToAttack * 1000) {
					em->createProjectile(glm::vec2(position.x, position.y + 15), 180, projectileSpeed, 1, range);
					lastShoot = time;
				}
			}
			else if (stanceID == STAND_LEFT_DIAG_UP) {
				if (time - lastShoot >= secondsToAttack * 1000) {
					em->createProjectile(glm::vec2(position.x + 15, position.y), 135, projectileSpeed, 1, range);
					lastShoot = time;
				}
			}
			else if (stanceID == STAND_LEFT_DAIG_DOWN) {
				if (time - lastShoot >= secondsToAttack * 1000) {
					em->createProjectile(glm::vec2(position.x + 15, position.y), -135, projectileSpeed, 1, range);
					lastShoot = time;
				}
			}
		}
	}
}



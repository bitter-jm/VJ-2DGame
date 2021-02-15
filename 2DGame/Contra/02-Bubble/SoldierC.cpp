#include "SoldierC.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include<iostream>

#define M_PI 3.14
#define tol 3.14/8

enum SoldierCAnim {
	UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT, LEFT, LEFTUP, EXPLODE
};

bool SoldierC::playerInRange() {
	// Distance in Tiles
	double distY = double((position.y - playerC->getPosition().y)) / (double)map->getTileSize();
	double distX = double((playerC->getPosition().x - position.x)) / (double)map->getTileSize();
	double dist = sqrt(distY * distY + distX * distX);
	if (dist < 7) return true;
	return false;
}

void SoldierC::setEntityManager(EntityManagerCenital* emc) {
	this->emc = emc;
}

void SoldierC::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	range = 6; // 6;
	hp = 1;
	dmg = 1;
	secondsToAttack = 1;
	projectileSpeed = 6;
	dead = false;
	dying = false;
	dyingTime = 600; //ms 

	float spriteSheetX = 0.08;
	float spriteSheetY = 1 / 18.0;
	tileMapDispl = tileMapPos;
	spritesheet.loadFromFile("images/enemyC.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(128,128), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(9);

	sprite->setAnimationSpeed(UP, 3);
	sprite->addKeyframe(UP, glm::vec2(0.50f, 0.00f)); // done

	sprite->setAnimationSpeed(UPRIGHT, 3);
	sprite->addKeyframe(UPRIGHT, glm::vec2(0.25f, 0.00f)); // done

	sprite->setAnimationSpeed(RIGHT, 3);
	sprite->addKeyframe(RIGHT, glm::vec2(0.00f, 0.00f)); // done

	sprite->setAnimationSpeed(RIGHTDOWN, 3);
	sprite->addKeyframe(RIGHTDOWN, glm::vec2(0.75f, 0.25f)); // done

	sprite->setAnimationSpeed(DOWN, 3);
	sprite->addKeyframe(DOWN, glm::vec2(0.50f, 0.25f)); // done

	sprite->setAnimationSpeed(DOWNLEFT, 3);
	sprite->addKeyframe(DOWNLEFT, glm::vec2(0.25f, 0.25f)); // done

	sprite->setAnimationSpeed(LEFT, 3);
	sprite->addKeyframe(LEFT, glm::vec2(0.00f, 0.25f)); // done

	sprite->setAnimationSpeed(LEFTUP, 3);
	sprite->addKeyframe(LEFTUP, glm::vec2(0.75f, 0.00f)); // done

	sprite->setAnimationSpeed(EXPLODE, 4);
	sprite->addKeyframe(EXPLODE, glm::vec2(0.00f, 0.50f));
	sprite->addKeyframe(EXPLODE, glm::vec2(0.25f, 0.50f));
	sprite->addKeyframe(EXPLODE, glm::vec2(0.50f, 0.50f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}


void SoldierC::update(int deltaTime)
{
	sprite->update(deltaTime);
	int time = glutGet(GLUT_ELAPSED_TIME);

	if ((hp <= 0 && !dying && !dead) || Game::instance().getSpecialKey(GLUT_KEY_F1)) {	//die
		SoundManager::getInstance()->playSound("sounds/explode.ogg", false);
		sprite->changeAnimation(EXPLODE);
		dying = true;
		dyingStartTime = time;
		return;
	}
	if (dying && time - dyingStartTime >= dyingTime) {
		dead = true;
		return;
	}

	else if (!dying && !dead) {

		angle = atan2(playerC->getPosition().y - position.y, playerC->getPosition().x - position.x) * 180 / M_PI;
		angle = -angle;
		if (angle < 0) angle = 360 + angle % 360;

		if (angle <= 22 || angle > 338) {
			sprite->changeAnimation(RIGHT);
		}
		else if (angle > 22 && angle <= 67) {
			sprite->changeAnimation(UPRIGHT);
		}
		else if (angle > 67 && angle <= 112) {
			sprite->changeAnimation(UP);
		}
		else if (angle > 112 && angle <= 157) {
			sprite->changeAnimation(LEFTUP);
		}
		else if (angle > 157 && angle <= 202) {
			sprite->changeAnimation(LEFT);
		}
		else if (angle > 202 && angle <= 247) {
			sprite->changeAnimation(DOWNLEFT);
		}
		else if (angle > 247 && angle <= 292) {
			sprite->changeAnimation(DOWN);
		}
		else if (angle > 292 && angle <= 338) {
			sprite->changeAnimation(RIGHTDOWN);
		}

		if (playerInRange()) {
			if (time - lastShoot >= secondsToAttack * 1000) {
				// TODO: modificar angulo y punto de inicio
				emc->createProjectile(glm::vec2(position.x +48, position.y +48), angle, projectileSpeed, 1, range);
				lastShoot = time;
			}
		}
	}
}


void SoldierC::setPlayer(PlayerCenital* p) {
	playerC = p;

}

void SoldierC::calculateAngle() {

}

#include "Turret.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include<iostream>

enum TurretAnim {
	STAND_LEFT, STAND_RIGHT, STAND_UP, STAND_DOWN, EXPLODE
};

bool Turret::playerInRange() {
	int distY = (player->getPosition().y - position.y) / map->getTileSize();
	int distX = (player->getPosition().x - position.x) / map->getTileSize();
	switch (stanceID) {
		case (STAND_LEFT):
			if (distY == 0 && distX >= -range && distX <= 0) return true;
			break;
		case (STAND_RIGHT):
			if (distY == 0 && distX <= range && distX <= 0) return true;
			break;
		case (STAND_UP):
			if (distX == 0 && distY >= -range && distY <= 0) return true;
			break;
		case (STAND_DOWN):
			if (distX == 0 && distY <= range && distY >= 0) return true;
			break;	
	}
	return false;
}

void Turret::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int pID)
{
	range = 5;
	hp = 5;
	dmg = 1;
	stanceID = pID;

	float spriteSheetX = 0.1;
	float spriteSheetY = 1.0 / 18.0;
	tileMapDispl = tileMapPos;
	spritesheet.loadFromFile("images/enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 48), glm::vec2(0.1, 0.05), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	if (pID == 0){ // left
		sprite->setAnimationSpeed(STAND_LEFT, 2);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0*spriteSheetX, 6 * spriteSheetY));
		sprite->changeAnimation(STAND_LEFT);
	}
	else if (pID == 1) {
		sprite->setAnimationSpeed(STAND_RIGHT, 2);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0 * spriteSheetX, 4 * spriteSheetY));
		sprite->changeAnimation(STAND_RIGHT);
	}
	else if (pID == 2) {
		sprite->setAnimationSpeed(STAND_UP, 2);
		sprite->addKeyframe(STAND_UP, glm::vec2(0.0 * spriteSheetX, 5 * spriteSheetY));
		sprite->changeAnimation(STAND_UP);
	}
	else if (pID == 3) {
		sprite->setAnimationSpeed(STAND_DOWN, 2);
		sprite->addKeyframe(STAND_DOWN, glm::vec2(0.0 * spriteSheetX, 7 * spriteSheetY));
		sprite->changeAnimation(STAND_DOWN);
	}

	sprite->setAnimationSpeed(EXPLODE, 3);
	sprite->addKeyframe(EXPLODE, glm::vec2(7.5 * spriteSheetX, 17 * spriteSheetY));
	sprite->addKeyframe(EXPLODE, glm::vec2(9 * spriteSheetX, 17 * spriteSheetY));

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}


void Turret::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (Game::instance().getSpecialKey(GLUT_KEY_F1)) {	//die
		sprite->changeAnimation(EXPLODE);
	}
	else {
		if (playerInRange()) {
			//shoot (in the turret direction)
		}
	}
}



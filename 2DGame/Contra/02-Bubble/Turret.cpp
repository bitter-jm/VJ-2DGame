#include "Turret.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include<iostream>

enum TurretAnim {
	LEFT, RIGHT, UP, DOWN, EXPLODE
};

bool Turret::playerInRange() {
	// Distance in Tiles
	int distY = (player->getPosition().y - position.y) / map->getTileSize();
	int distX = (player->getPosition().x - position.x) / map->getTileSize();
	if (distY == 0 && distX == 0) return true;
	switch (stanceID) {
		case (LEFT):
			if (distY == 0 && distX >= -range && distX <= 0) return true;
			break;
		case (RIGHT):
			if (distY == 0 && distX <= range && distX <= 0) return true;
			break;
		case (UP):
			if (distX == 0 && distY >= -range && distY <= 0) return true;
			break;
		case (DOWN):
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

	sprite->setAnimationSpeed(LEFT, 2);
	sprite->addKeyframe(LEFT, glm::vec2(0.0*spriteSheetX, 6 * spriteSheetY));

	sprite->setAnimationSpeed(RIGHT, 2);
	sprite->addKeyframe(RIGHT, glm::vec2(0.0 * spriteSheetX, 4 * spriteSheetY));

	sprite->setAnimationSpeed(UP, 2);
	sprite->addKeyframe(UP, glm::vec2(0.0 * spriteSheetX, 5 * spriteSheetY));

	sprite->setAnimationSpeed(DOWN, 2);
	sprite->addKeyframe(DOWN, glm::vec2(0.0 * spriteSheetX, 7 * spriteSheetY));
	

	sprite->setAnimationSpeed(EXPLODE, 3);
	sprite->addKeyframe(EXPLODE, glm::vec2(7.5 * spriteSheetX, 17 * spriteSheetY));
	sprite->addKeyframe(EXPLODE, glm::vec2(9 * spriteSheetX, 17 * spriteSheetY));

	sprite->changeAnimation(pID);

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



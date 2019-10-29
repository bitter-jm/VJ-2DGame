#include "Mina.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include<iostream>

#define SIZEMINA 32

enum MinaAnim {
	STAND, EXPLODING, INVISIBLE
};

void Mina::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	range = 0;
	hp = 1;
	dmg = 3;
	secondsToAttack = 0;
	projectileSpeed = 0;
	dead = false;
	dying = false; //Exploding
	dyingTime = 600; //ms 

	tileMapDispl = tileMapPos;
	spritesheet.loadFromFile("images/mina.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(STAND, 2);
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));
	
	sprite->setAnimationSpeed(EXPLODING, 8);
	sprite->addKeyframe(EXPLODING, glm::vec2(0.25f, 0.00f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.50f, 0.00f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.75f, 0.00f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.00f, 0.25f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.50f, 0.25f));

	sprite->setAnimationSpeed(INVISIBLE, 2);
	sprite->addKeyframe(INVISIBLE, glm::vec2(0.75f, 0.75f));

	sprite->changeAnimation(0);

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void Mina::update(int deltaTime)
{
	sprite->update(deltaTime);
	int time = glutGet(GLUT_ELAPSED_TIME);

	if (sprite->animation() == EXPLODING && timeExplosion + 800 < glutGet(GLUT_ELAPSED_TIME)) {
		dead = true;
		sprite->changeAnimation(INVISIBLE);
	}

	else if (!dying && !dead) {
		// Check collisions with playerC
			// kill playerC
			// Explode & die

		glm::vec2 posE = playerC->getPosition();
		posE.x += 16; // pos playerC
		posE.y += 48; // pos playerC
		int xSize = 64; // tamaño playerC
		int ySize = 64; // tamaño playerC
		if (position.x + SIZEMINA >= posE.x && position.x + SIZEMINA <= posE.x + xSize && position.y >= posE.y && position.y <= posE.y + ySize) { //RIGHT UP
			playerC->kill();
			setExploding();
		}
		if (position.x + SIZEMINA >= posE.x && position.x + SIZEMINA <= posE.x + xSize && position.y + SIZEMINA >= posE.y && position.y + SIZEMINA <= posE.y + ySize) { //RIGHT DOWN
			playerC->kill();
			setExploding();
		}
		if (position.x >= posE.x && position.x <= posE.x + xSize && position.y >= posE.y && position.y <= posE.y + ySize) { //LEFT UP
			playerC->kill();
			setExploding();
		}
		if (position.x >= posE.x && position.x <= posE.x + xSize && position.y + SIZEMINA >= posE.y && position.y + SIZEMINA <= posE.y + ySize) { //LEFT DOWN
			playerC->kill();
			setExploding();
		}

	}
}


void Mina::setExploding() {
	if (sprite->animation() != EXPLODING && sprite->animation() != INVISIBLE) {
		sprite->changeAnimation(EXPLODING);
		timeExplosion = glutGet(GLUT_ELAPSED_TIME);
		SoundManager::getInstance()->playSound("sounds/explode.ogg", false);
	}
}

void Mina::setPlayer(PlayerCenital* p) {
	playerC = p;

}
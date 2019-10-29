#include <cmath>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <servprov.h>
#include "Credits.h"
#include "Shader.h"
#include "Game.h" 

// Desplazamiento de pantalla 
#define SCREEN_X 0
#define SCREEN_Y 0

void Credits::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	SoundManager::getInstance()->playSound("sounds/mainCredits.ogg", false);

	buttonSound1 = false;
	buttonSound2 = false;

	spritesheet.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(768, 512), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 2);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));


	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

}

void Credits::render()
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
	sprite->render();
}


void Credits::update()
{
	if (Game::instance().getKey(13)) {
		Game::instance().returnToMenu();
	}

}

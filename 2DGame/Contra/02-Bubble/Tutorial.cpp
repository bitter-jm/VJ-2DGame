#include <cmath>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <servprov.h>
#include "Tutorial.h"
#include "Shader.h"
#include "Game.h"
 
// Desplazamiento de pantalla
#define SCREEN_X 0
#define SCREEN_Y 0

void Tutorial::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/tutorial.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(768, 512), glm::vec2(0.375, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(0, 2);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 2);
	sprite->addKeyframe(1, glm::vec2(0.375f, 0.f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

}

void Tutorial::render()
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
	sprite->render();
}


void Tutorial::update()
{
	int posMouseX = Game::instance().getPosMouseX();
	int posMouseY = Game::instance().getPosMouseY();
	int windowSizeX = glutGet(GLUT_WINDOW_WIDTH);
	int windowSizeY = glutGet(GLUT_WINDOW_HEIGHT);

	int absMX = (int)((double)posMouseX * ((double)768 / (double)windowSizeX));
	int absMY = (int)((double)posMouseY * ((double)512 / (double)windowSizeY));

	if (absMX > 24 && absMX < 180 && absMY > 450 && absMY < 502) {
		if (!buttonSound) {
			sprite->changeAnimation(1);
			SoundManager::getInstance()->playSound("sounds/button.ogg", false);
			buttonSound = true;
		}
	}
	else {
		buttonSound = false;
		sprite->changeAnimation(0);
	}

	if (Game::instance().isMousePressed()) {
		if (absMX > 24 && absMX < 180) {
			if (absMY > 450 && absMY < 502) {
				Game::instance().tutorialToMenu();
			}
		}
	}

}

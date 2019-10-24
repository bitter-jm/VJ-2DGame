#include <cmath>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <servprov.h>
#include "Menu.h"
#include "Shader.h"
#include "Game.h"

// Desplazamiento de pantalla
#define SCREEN_X 0
#define SCREEN_Y 0

void Menu::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(768, 512), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(0, 2);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 2);
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
	
	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));

}

void Menu::render()
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
	sprite->render();
}


void Menu::update()
{
	if (Game::instance().isMousePressed()) {
		int posMouseX = Game::instance().getPosMouseX();
		int posMouseY = Game::instance().getPosMouseY();
		int windowSizeX = glutGet(GLUT_WINDOW_WIDTH);
		int windowSizeY = glutGet(GLUT_WINDOW_HEIGHT);

		int absMX = (int)((double)posMouseX * ((double)768 / (double)windowSizeX));
		int absMY = (int)((double)posMouseY * ((double)512 / (double)windowSizeY));

		//cout << absMX << " . " << absMY << endl;

		if (absMX > 191 && absMX < 389) {
			if (absMY > 347 && absMY < 416) {
				if (absMY < 380) {
					Game::instance().changeLevel(1);
				}
				else {
					Game::instance().menuToTutorial();
				}
			}
		}
	}

}

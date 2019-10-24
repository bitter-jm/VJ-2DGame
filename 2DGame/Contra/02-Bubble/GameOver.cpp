#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "GameOver.h"
#include "Game.h"


void GameOver::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 pp)
{
	cout << "Empezando init GameOver" << endl;
	//spritesheet.loadFromFile("images/GameOverScreen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.loadFromFile("images/gameover.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cout << "Imagen Cargada" << endl;
	//sprite = Sprite::createSprite(glm::ivec2(768, 512), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite = Sprite::createSprite(glm::ivec2(768, 512), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
	cout << "Sprite creado" << endl;
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(0, 2);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, 2);
	sprite->addKeyframe(0, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(2, 2);
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));

	cout << "Animaciones cargadas" << endl;

	posPlayer = pp;

	sprite->changeAnimation(0);
	cout << "Animacion cambiada" << endl;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x - 768/2), float(tileMapDispl.y)));
	cout << "Posicion cambiada" << endl;

}

void GameOver::render()
{
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x - 768/2), float(tileMapDispl.y)));
	sprite->render();
}


void GameOver::update()
{
	if (Game::instance().isMousePressed()) {
		int posMouseX = Game::instance().getPosMouseX();
		int posMouseY = Game::instance().getPosMouseY();
		int windowSizeX = glutGet(GLUT_WINDOW_WIDTH);
		int windowSizeY = glutGet(GLUT_WINDOW_HEIGHT);
		
		int absMX = (int)((double)posMouseX * ((double)768 / (double)windowSizeX));
		int absMY = (int)((double)posMouseY * ((double)512 / (double)windowSizeY));
		//cout << "Mouse: (" << absoluteMouseX << ", " << absoluteMouseY << ") ScreenSize: (" << windowSizeX << ", " << windowSizeY << ")" << endl;

		if (absMX > 240 && absMX < 561) {
			if (absMY > 256 && absMY < 369) {
				if (absMY < 315) {
					cout << "Restart Level" << endl;
					timeAction = glutGet(GLUT_ELAPSED_TIME);
					action = 1;
				}
				else {
					cout << "Return Menu" << endl;
					timeAction = glutGet(GLUT_ELAPSED_TIME);
					action = 2;
					//Game::instance().returnToMenu();
				}
			}
		}
	}

	if (action > 0 && timeAction + 300 < glutGet(GLUT_ELAPSED_TIME)) {
		if (action == 1) Game::instance().restartLevel();
		else if (action == 2) Game::instance().returnToMenu();
	}

}
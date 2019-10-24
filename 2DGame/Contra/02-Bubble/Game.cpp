#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum State
{
	MENU, LEVEL1, LEVEL2, LEVEL3, CREDITS
};

void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	state = MENU;
	scene.init();
	menu.init();
}

bool Game::update(int deltaTime)
{
	if (state == MENU) menu.update(deltaTime);
	else if (state == LEVEL1) scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (state == MENU) menu.render();
	else if (state == LEVEL1) scene.render();
}

void Game::restartLevel()
{
	if (state == LEVEL1) scene.init();
}

void Game::returnToMenu()
{
	state = MENU;
	tutorialToMenu();
}

void Game::menuToTutorial()
{
	menu.toTutorial();
}

void Game::tutorialToMenu()
{
	menu.toMenu();
}

void Game::showCredits()
{
	state = CREDITS;
}

void Game::changeLevel(int lvl)
{
	if (lvl == 1) state = LEVEL1;
	else if (lvl == 2) state = LEVEL2;
	else if (lvl == 3) state = LEVEL3;
	restartLevel();
	
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	posMouseX = x;
	posMouseY = y;
}

void Game::mousePress(int button)
{
	mousePressed = true;
}

void Game::mouseRelease(int button)
{
	mousePressed = false;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}


int Game::getPosMouseX() const
{
	return posMouseX;
}

int Game::getPosMouseY() const
{
	return posMouseY;
}

bool Game::isMousePressed() const
{
	return mousePressed;
}


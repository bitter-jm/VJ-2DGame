#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "MenuScene.h"


#define SCREEN_WIDTH 512*1.5
#define SCREEN_HEIGHT 512


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();

	void restartLevel();
	void returnToMenu();
	void showCredits();
	void changeLevel(int lvl);
	void menuToTutorial();
	void tutorialToMenu();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	bool isMousePressed() const;
	int Game::getPosMouseX() const;
	int Game::getPosMouseY() const;

private:
	bool bPlay;                       // Continue to play game?
	MenuScene menu;
	Scene scene;                      // Scene level 1
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int posMouseX = 0;
	int posMouseY = 0;
	bool mousePressed = false;

	int state;

};


#endif // _GAME_INCLUDE



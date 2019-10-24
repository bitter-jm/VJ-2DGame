#ifndef _MENUSCENE_INCLUDE
#define _MENUSCENE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Menu.h"
#include "Tutorial.h"

// MenuScene contains all the entities of our game.
// It is responsible for updating and render them.


class MenuScene
{

public:
	MenuScene();
	~MenuScene();

	void init();
	void update(int deltaTime);
	void render();
	void toTutorial();
	void toMenu();

private:
	void initShaders();

private:

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Menu *menu;
	Tutorial *tutorial;
	bool inTutorial;

};


#endif // _MENUSCENE_INCLUDE


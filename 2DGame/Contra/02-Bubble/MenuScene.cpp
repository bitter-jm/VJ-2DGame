#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MenuScene.h"
#include "Game.h"
#include <servprov.h>

// Desplazamiento de pantalla
#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 8
#define INIT_PLAYER_Y_TILES 3

MenuScene::MenuScene()
{

}

MenuScene::~MenuScene()
{

}

void MenuScene::init()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	initShaders();

	inTutorial = false;

	menu = new Menu();
	menu->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	tutorial = new Tutorial();
	tutorial->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void MenuScene::update(int deltaTime)
{
	if (!inTutorial) {
		currentTime += deltaTime;
		menu->update();
	}
	else {
		tutorial->update();
	}
	
}

void MenuScene::render()
{
	glm::mat4 modelview;
	float playerX = 0;

	projection = glm::ortho(0.0f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if (!inTutorial) {
		menu->render();
	}
	else {
		tutorial->render();
	}

}

void MenuScene::toTutorial() {
	inTutorial = true;
}

void MenuScene::toMenu() {
	inTutorial = false;
}

void MenuScene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}


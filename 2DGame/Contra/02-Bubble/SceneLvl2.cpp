#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "SceneLvl2.h"
#include "Game.h"
#include <servprov.h>
#include "SoundManager.h"

// Desplazamiento de pantalla
#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 12
#define INIT_PLAYER_Y_TILES 13

#define LEVEL_COMPLETE_X 95
#define LEVEL_COMPLETE_Y 6

#define SPREADGUN_X 41*64
#define SPREADGUN_Y 3.25*64

SceneLvl2::SceneLvl2()
{
	map = NULL;
	player = NULL;
}

SceneLvl2::~SceneLvl2()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

void SceneLvl2::init()
{
	deadPlayer = false;

	initShaders();
	map = TileMap::createTileMap("levels/level2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map->setLevel(3);
	player = new PlayerCenital();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	cout << "Position Set to: " << INIT_PLAYER_X_TILES * map->getTileSize() << " - " << INIT_PLAYER_Y_TILES * map->getTileSize() << endl;

	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	//entityManager = new EntityManager();
	//entityManager->init(player, &texProgram);
}

void SceneLvl2::update(int deltaTime)
{
	currentTime += deltaTime;

	if (!levelComplete) player->update(deltaTime);
	//entityManager->update(deltaTime);
	int tSize = map->getTileSize();

	//level completed
	/*if (int(player->getPosition().x / map->getTileSize()) >= LEVEL_COMPLETE_X) {
		if (!levelComplete) {
			SoundManager::getInstance()->removeAllSound();
			SoundManager::getInstance()->playSound("sounds/level1Complete.ogg", false);
			levelComplete = true;
		}
	}*/

	if (deadPlayer) gameOver->update();
}

void SceneLvl2::render()
{
	glm::mat4 modelview;
	float playerX = player->getPosition().x;
	float playerY = player->getPosition().y;
	projection = glm::ortho(playerX - float(SCREEN_WIDTH - 1) / 2.0f - 64.f * 1, playerX + float(SCREEN_WIDTH - 1) / 2.0f + 64.f * 1, playerY + float(SCREEN_HEIGHT - 1) / 2.0f + 64.f*1, playerY - float(SCREEN_HEIGHT - 1) / 2.0f - 64.f * 1);
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();
	player->render();
	//entityManager->render();


	// Death screen
	if (player->isDead()) {
		if (!deadPlayer) {
			SoundManager::getInstance()->removeAllSound();
			SoundManager::getInstance()->playSound("sounds/gameOver.ogg", false);
			deadPlayer = true;
			deathTime = glutGet(GLUT_ELAPSED_TIME);
			gameOver = new GameOver();
			gameOver->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player->getPosition());
			cout << "Inicializado correctamente GameOver" << endl;
		}
		if (deathTime + 1000 < glutGet(GLUT_ELAPSED_TIME)) {
			gameOver->render();

		}
	}

		//level completed
	if (player->getPosition().y > 54*65) {
		if (!levelComplete) {
			SoundManager::getInstance()->removeAllSound();
			SoundManager::getInstance()->playSound("sounds/level1Complete.ogg", false);
			levelComplete = true;
		}
		else {
			Game::instance().changeLevel(3);
		}
	}

}

void SceneLvl2::initShaders()
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

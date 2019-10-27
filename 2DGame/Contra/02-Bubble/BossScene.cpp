#include "BossScene.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <servprov.h>


// Desplazamiento de pantalla
#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 0

#define LEVEL_COMPLETE_X 95
#define LEVEL_COMPLETE_Y 6

#define SPREADGUN_X 1*64
#define SPREADGUN_Y 5.25*64


BossScene::BossScene()
{
	map = NULL;
	player = NULL;
}

BossScene::~BossScene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}



void BossScene::init()
{

	spreadgunHidden = false;
	deadPlayer = false;

	initShaders();
	map = TileMap::createTileMap("levels/bossLevel.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map->setLevel(2);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	spreadgun = new SpreadGun();
	spreadgun->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(SPREADGUN_X, SPREADGUN_Y));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	entityManager = new EntityManager();
	entityManager->init(player, &texProgram);
}

void BossScene::update(int deltaTime)
{
	currentTime += deltaTime;

	if (!levelComplete) player->update(deltaTime);
	entityManager->update(deltaTime);
	int tSize = map->getTileSize();
	if (!spreadgunHidden && int((player->getPosition().x-SPREADGUN_X)/tSize) == 0 && int((player->getPosition().y - SPREADGUN_Y)/ tSize) == 0) {
		spreadgunHidden = true;
		player->upgradeSpreadGun();
	}
	else spreadgun->update(deltaTime);

	//level completed
	if (int(player->getPosition().x / map->getTileSize()) >= LEVEL_COMPLETE_X) {
		if (!levelComplete) {
			SoundManager::getInstance()->removeAllSound();
			SoundManager::getInstance()->playSound("sounds/level1Complete.ogg", false);
			levelComplete = true;
		}
	}

	if (deadPlayer) gameOver->update();
}

void BossScene::render()
{
	glm::mat4 modelview;
	float playerX = player->getPosition().x;
	// Limitar camara por izquierda
	if (playerX <= float(SCREEN_WIDTH - 1) / 2.0f)
		projection = glm::ortho(0.0f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	// Limitar por derecha
	else if (playerX >= map->getMapSize().x * map->getTileSize() - float(SCREEN_WIDTH - 1) / 2.0f)
		projection = glm::ortho(map->getMapSize().x * map->getTileSize() - float(SCREEN_WIDTH - 1),
			map->getMapSize().x * map->getTileSize(), float(SCREEN_HEIGHT - 1), 0.f);
	// Seguir al personaje
	else projection = glm::ortho(playerX - float(SCREEN_WIDTH - 1) / 2.0f, playerX + float(SCREEN_WIDTH - 1) / 2.0f, float(SCREEN_HEIGHT - 1), 0.f);
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();
	if (!spreadgunHidden) spreadgun->render();
	player->render();
	entityManager->render();


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
		else {
			//blackb->render(1);
		}
	}

}

void BossScene::initShaders()
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


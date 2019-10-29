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

#define PROB_HEART 0.25


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

void SceneLvl2::spawnMines() {
	vector<glm::ivec2> posMinas = { 
		glm::ivec2(22,17), glm::ivec2(23,17), glm::ivec2(23,18), glm::ivec2(30,25), glm::ivec2(31,25), glm::ivec2(32,25),
		glm::ivec2(30,26), glm::ivec2(30,27), glm::ivec2(32,26), glm::ivec2(32,27), glm::ivec2(31,26), glm::ivec2(31,27),
		glm::ivec2(40,16), glm::ivec2(40,17), glm::ivec2(40,18), glm::ivec2(42,16), glm::ivec2(43,16), glm::ivec2(44,16),
		glm::ivec2(47,30), glm::ivec2(48,30), glm::ivec2(49,30), glm::ivec2(41,32), glm::ivec2(41,33),
		glm::ivec2(16,35), glm::ivec2(16,36), glm::ivec2(16,37), glm::ivec2(17,37), glm::ivec2(18,37), glm::ivec2(15,27),
		glm::ivec2(15,28), glm::ivec2(15,29), glm::ivec2(10,22), glm::ivec2(10,21), glm::ivec2(10,20), glm::ivec2(11,20), 
		glm::ivec2(12,20), glm::ivec2(15,40), glm::ivec2(15,41), glm::ivec2(30,47), glm::ivec2(31,47), 
		glm::ivec2(32,47), glm::ivec2(40,40), glm::ivec2(41,40), glm::ivec2(42,40)
	};
	for (int i = 0; i < posMinas.size(); ++i) {
		Mina* s = new Mina();
		s->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		s->setPosition(glm::vec2(posMinas[i].x * map->getTileSize(), posMinas[i].y * map->getTileSize() + 12));
		s->setTileMap(map);
		s->setPlayer(player);
		minas.push_back(s);
	}
}

void SceneLvl2::spawnSoldierCs() {
	vector<glm::ivec2> posSoldierCs = {
		glm::ivec2(29,10), glm::ivec2(23,23), glm::ivec2(36,28), glm::ivec2(23,19), glm::ivec2(23,21), glm::ivec2(23,28),
		glm::ivec2(39,18), glm::ivec2(35,12), glm::ivec2(48,13), glm::ivec2(42,22), glm::ivec2(42,24), glm::ivec2(48,33),
		glm::ivec2(37,36), glm::ivec2(23,36), glm::ivec2(10,24), glm::ivec2(10,40), glm::ivec2(21,44), glm::ivec2(21,48),
		glm::ivec2(31,43), glm::ivec2(31,41), glm::ivec2(41,44), glm::ivec2(48,48)
	};
	for (int i = 0; i < posSoldierCs.size(); ++i) {
		SoldierC* s = new SoldierC();
		s->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		s->setPosition(glm::vec2(posSoldierCs[i].x * map->getTileSize(), posSoldierCs[i].y * map->getTileSize() + 12));
		s->setTileMap(map);
		s->setPlayer(player);
		s->setEntityManager(entityManager);
		soldierCs.push_back(s);
	}
}

void SceneLvl2::init()
{
	SoundManager::getInstance()->removeAllSound();
	SoundManager::getInstance()->playSound("sounds/level2.ogg", true, 0.5f); 

	deadPlayer = false;
	levelComplete = false;

	if (soldierCs.size() != 0) soldierCs.clear();
	if (minas.size() != 0) minas.clear();
	if (hearts.size() != 0) hearts.clear();

	initShaders();
	map = TileMap::createTileMap("levels/level2.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map->setLevel(3);
	player = new PlayerCenital();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);

	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	entityManager = new EntityManagerCenital();
	entityManager->init(player, &texProgram);
	entityManager->setMap(map);

	spawnMines();
	spawnSoldierCs();
}

void SceneLvl2::update(int deltaTime)
{
	currentTime += deltaTime;

	if (!levelComplete) player->update(deltaTime, texProgram);
	entityManager->update(deltaTime);
	int tSize = map->getTileSize();

	for (int i = 0; i < minas.size(); i++) {
		if (!minas[i]->is_dead()) {
			minas[i]->update(deltaTime);
		}
	}

	for (int i = 0; i < soldierCs.size(); i++) {
		if (!soldierCs[i]->is_dead()) {
			soldierCs[i]->update(deltaTime);
			if (entityManager->checkCollisionEnemy(glm::vec2(soldierCs[i]->getPosition().x + 32, soldierCs[i]->getPosition().y + 16), 64, 64)) {
				soldierCs[i]->reduceHP(1);
				if (soldierCs[i]->is_dead() || soldierCs[i]->is_dying()) {
					float r = float(rand() % 100) / 100;
					if (r <= PROB_HEART) {
						Heart* h = new Heart();
						h->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, glm::vec2(soldierCs[i]->getPosition().x + 32, soldierCs[i]->getPosition().y + 32));
						hearts.push_back(h);
					}
				}
			}
		}
	}

	for (int i = 0; i < hearts.size(); i++) {
		int distX = player->getPosition().x - hearts[i]->getPosition().x;
		int distY = player->getPosition().y - hearts[i]->getPosition().y;
		if (abs(distX) <= 64 && abs(distY) <= 64) {
			hearts.erase(hearts.begin() + i);
			SoundManager::getInstance()->playSound("sounds/health.ogg", false);
			player->addHP(1);
		}
	}

	if (deadPlayer) gameOver->update();

}

void SceneLvl2::render()
{
	glm::mat4 modelview;


	float playerX = player->getPosition().x;
	float playerY = player->getPosition().y;
	if (player->getDeathFinished()) {
		float iniX = player->getPosition().x - float(SCREEN_WIDTH - 1) / 2;
		float finalX = player->getPosition().x + float(SCREEN_WIDTH - 1) / 2;
		projection = glm::ortho(iniX, finalX, float(SCREEN_HEIGHT - 1), 0.f);
	}
	else {
		projection = glm::ortho(playerX+64 - float(SCREEN_WIDTH - 1) / 2.0f - 64.f * 1, playerX+64 + float(SCREEN_WIDTH - 1) / 2.0f + 64.f * 1, playerY+64 + float(SCREEN_HEIGHT - 1) / 2.0f + 64.f*1, playerY+64 - float(SCREEN_HEIGHT - 1) / 2.0f - 64.f * 1);
	}
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();

	for (int i = 0; i < minas.size(); i++) {
		if (!minas[i]->is_dead()) {
			minas[i]->render();
		}
	}

	for (int i = 0; i < soldierCs.size(); i++) {
		if (!soldierCs[i]->is_dead()) {
			soldierCs[i]->render();
		}
	}

	player->render();
	entityManager->render();


	// Death screen
	//cout << player->isDead() << endl;
	if (player->isDead()) {
		if (!deadPlayer) {
			SoundManager::getInstance()->removeAllSound();
			SoundManager::getInstance()->playSound("sounds/gameOver.ogg", false);
			deadPlayer = true;
			deathTime = glutGet(GLUT_ELAPSED_TIME);
			gameOver = new GameOver();
			gameOver->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player->getPosition());
		}
		if (deathTime + 1000 < glutGet(GLUT_ELAPSED_TIME)) {
			gameOver->render();

		}
	}

		//level completed
	if (player->getPosition().y > 53*64) {
		if (!levelComplete) {
			SoundManager::getInstance()->removeAllSound();
			SoundManager::getInstance()->playSound("sounds/level1Complete.ogg", false);
			levelComplete = true;
		}
		else {
			Game::instance().changeLevel(3);
		}
	}

	for (int i = 0; i < hearts.size(); i++) hearts[i]->render();
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

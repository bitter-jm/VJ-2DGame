#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "Game.h"
#include <servprov.h>

// Desplazamiento de pantalla
#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 3

#define SPREADGUN_X 2600


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::spawnTurrets() {
	enum Position { LEFT, RIGHT, UP, DOWN };
	vector<glm::ivec3> posTurrets = {glm::ivec3(14,3,LEFT), glm::ivec3(25,2,LEFT), glm::ivec3(35,3,LEFT), glm::ivec3(74,3,LEFT), glm::ivec3(84,5,UP), glm::ivec3(51,5,UP), glm::ivec3(41,5,UP)};
	for (int i = 0; i < posTurrets.size(); ++i) {
		// generar torreta
		Turret* t = new Turret();
		t->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posTurrets[i].z);
		t->setPosition(glm::vec2(posTurrets[i].x * map->getTileSize(), posTurrets[i].y * map->getTileSize()));
		t->setTileMap(map);
		t->setPlayer(player);
		t->setEntityManager(entityManager);
		turrets.push_back(t);
	}
}

void Scene::spawnSoldierAs() {
	enum Position { STAND_LEFT, STAND_LEFT_DIAG_UP, STAND_LEFT_DAIG_DOWN, EXPLODE };
	vector<glm::ivec3> posSoldierAs = { glm::ivec3(11,6,STAND_LEFT_DIAG_UP), glm::ivec3(21,0,STAND_LEFT_DAIG_DOWN), glm::ivec3(20,5,STAND_LEFT_DIAG_UP), glm::ivec3(44,3,STAND_LEFT), glm::ivec3(60,3,STAND_LEFT), glm::ivec3(67,1,STAND_LEFT_DAIG_DOWN), glm::ivec3(75,5,STAND_LEFT), glm::ivec3(81,1,STAND_LEFT), glm::ivec3(87,3,STAND_LEFT), glm::ivec3(93,6,STAND_LEFT) };
	// generar torretas
	for (int i = 0; i < posSoldierAs.size(); ++i) {
		SoldierA* s = new SoldierA();
		s->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, posSoldierAs[i].z);
		s->setPosition(glm::vec2(posSoldierAs[i].x * map->getTileSize(), posSoldierAs[i].y * map->getTileSize() + 12));
		s->setTileMap(map);
		s->setPlayer(player);
		s->setEntityManager(entityManager);
		soldierAs.push_back(s);
	}
} 

void Scene::spawnSoldierBs() {
	enum Position { STAND_LEFT, EXPLODE };
	vector<glm::ivec2> posSoldierBs = { glm::ivec2(13,1), glm::ivec2(20,3), glm::ivec2(34,2), glm::ivec2(52,1), glm::ivec2(78,0) };
	// generar torretas
	for (int i = 0; i < posSoldierBs.size(); ++i) {
		SoldierB* s = new SoldierB();
		s->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, STAND_LEFT);
		s->setPosition(glm::vec2(posSoldierBs[i].x * map->getTileSize(), posSoldierBs[i].y* map->getTileSize() + 12));
		s->setTileMap(map);
		s->setPlayer(player);
		s->setEntityManager(entityManager);
		soldierBs.push_back(s);
	}
}

void Scene::init()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	// For restart level correctly
	if (turrets.size() != 0) turrets.clear();
	if (soldierAs.size() != 0) soldierAs.clear();

	spreadgunHidden = false;
	deadPlayer = false;

	initShaders();
	map = TileMap::createTileMap("levels/level1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map->setLevel(1);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	spreadgun = new SpreadGun();
	spreadgun->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	entityManager = new EntityManager();
	entityManager->init(player, &texProgram);

	spawnTurrets();
	spawnSoldierAs();
	spawnSoldierBs();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	player->update(deltaTime);
	entityManager->update(deltaTime);
	if (!spreadgunHidden && player->getPosition().x > SPREADGUN_X) spreadgunHidden = true;
	else spreadgun->update(deltaTime);
	
	for (int i = 0; i < turrets.size(); i++) {
		if (!turrets[i]->is_dead()) { 
			turrets[i]->update(deltaTime); 
			if (entityManager->checkCollisionEnemy(glm::vec2(turrets[i]->getPosition().x, turrets[i]->getPosition().y+8), 48, 40)) {
				turrets[i]->reduceHP();
				cout << "A turret got hurted" << endl;
			}
		}
	}
	for (int i = 0; i < soldierAs.size(); i++) {
		if (!soldierAs[i]->is_dead()) { 
			soldierAs[i]->update(deltaTime); 
			if (entityManager->checkCollisionEnemy(glm::vec2(soldierAs[i]->getPosition().x+16, soldierAs[i]->getPosition().y+16), 32, 32)) {
				soldierAs[i]->reduceHP();
				cout << "An enemyA got hurted" << endl;
			}
		}
	}
	for (int i = 0; i < soldierBs.size(); i++) {
		if (!soldierBs[i]->is_dead()) { 
			soldierBs[i]->update(deltaTime); 
			if (entityManager->checkCollisionEnemy(soldierBs[i]->getPosition(), 64, 64)) {
				soldierBs[i]->reduceHP();
				cout << "An enemyB got hurted" << endl;
			}
		}
	}

	if (deadPlayer) gameOver->update();
}

void Scene::render()
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

	for (int i = 0; i < turrets.size(); i++) {
		if (!turrets[i]->is_dead()) turrets[i]->render();
	}
	for (int i = 0; i < soldierAs.size(); i++) {
		if (!soldierAs[i]->is_dead()) soldierAs[i]->render();
	}
	for (int i = 0; i < soldierBs.size(); i++) {
		if (!soldierBs[i]->is_dead()) soldierBs[i]->render();
	}

	player->render();
	entityManager->render();

	
	// Death screen
	if (player->isDead()) {
		if (!deadPlayer) {
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

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

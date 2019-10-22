#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"

// Desplazamiento de pantalla
#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 8
#define INIT_PLAYER_Y_TILES 3

#define WEAPON_X 2600


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
	Turret* t = new Turret();
	t->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	t->setPosition(glm::vec2(11 * map->getTileSize(), 3 * map->getTileSize()));
	t->setTileMap(map);
	turrets.push_back(t);
}

void Scene::init()
{
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
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	player->update(deltaTime);
	entityManager->update(deltaTime);
	if (!spreadgunHidden && player->getPosition().x > WEAPON_X) spreadgunHidden = true;
	else spreadgun->update(deltaTime);
	
	for (int i = 0; i < turrets.size(); i++) {
		turrets[i]->update(deltaTime);
	}
	
}

void Scene::render()
{
	glm::mat4 modelview;
	float playerX = player->getPosition().x;
	projection = glm::ortho(playerX - float(SCREEN_WIDTH - 1)/2.0f, playerX + float(SCREEN_WIDTH - 1)/2.0f + 64.f, float(SCREEN_HEIGHT - 1), 0.f);
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	if (!spreadgunHidden) spreadgun->render();
	//modelview = glm::scale(modelview, glm::vec3(4.f, 4.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	for (int i = 0; i < turrets.size(); i++) {
		turrets[i]->render();
	}
	player->render();
	entityManager->render();
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


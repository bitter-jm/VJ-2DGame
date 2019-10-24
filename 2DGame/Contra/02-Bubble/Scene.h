#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "EntityManager.h"
#include "GameOver.h"
#include "NPC.h"
#include "Turret.h"
#include "SoldierA.h"
#include "SpreadGun.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void spawnTurrets();
	void spawnSoldierAs();

private:
	TileMap *map;
	Player *player;
	SpreadGun *spreadgun;
	GameOver* gameOver;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	EntityManager *entityManager;
	vector<Turret*> turrets;
	vector<SoldierA*> soldierAs;
	bool spreadgunHidden;
	int deathTime;
	bool deadPlayer;

};


#endif // _SCENE_INCLUDE


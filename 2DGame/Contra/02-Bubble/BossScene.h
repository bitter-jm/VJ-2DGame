#pragma once

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "EntityManager.h"
#include "GameOver.h" 
#include "NPC.h"
#include "SpreadGun.h"
#include "SoundManager.h"
#include "Boss.h"

class BossScene
{
public:
	BossScene();
	~BossScene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap* map;
	Player* player;
	SpreadGun* spreadgun;
	GameOver* gameOver;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	EntityManager* entityManager;
	bool spreadgunHidden;
	int deathTime;
	bool deadPlayer, levelComplete;
	float completeTime, waitTime;
	Boss* boss;
};


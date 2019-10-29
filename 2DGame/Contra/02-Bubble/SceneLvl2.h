#ifndef _SCENELVL2_INCLUDE
#define _SCENELVL2_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "PlayerCenital.h"
#include "EntityManagerCenital.h"
#include "GameOver.h"
#include "NPC.h"
#include "Turret.h"
#include "SoldierA.h"
#include "SoldierB.h"
#include "SpreadGun.h"
#include "SoundManager.h"

// SceneLvl2 contains all the entities of our game.
// It is responsible for updating and render them.


class SceneLvl2
{

public:
	SceneLvl2();
	~SceneLvl2();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap* map;
	PlayerCenital* player;
	GameOver* gameOver;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	EntityManagerCenital* entityManager;
	int deathTime;
	bool deadPlayer, levelComplete;
};


#endif // _SCENELVL2_INCLUDE


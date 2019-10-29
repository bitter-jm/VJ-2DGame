#ifndef _SCENELVL2_INCLUDE
#define _SCENELVL2_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
//#include "TileMap.h"
#include "PlayerCenital.h" 
#include "EntityManagerCenital.h"
#include "GameOver.h"
#include "NPC.h"
#include "Mina.h"
#include "SoldierC.h"
#include "SoundManager.h"
#include "Heart.h"

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
	void spawnMines();
	void spawnSoldierCs();

private:
	TileMap* map;
	PlayerCenital* player;
	GameOver* gameOver;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	vector<Mina*> minas;
	vector<SoldierC*> soldierCs;
	EntityManagerCenital* entityManager;
	int deathTime;
	bool deadPlayer, levelComplete;
	vector<Heart*> hearts;
};


#endif // _SCENELVL2_INCLUDE


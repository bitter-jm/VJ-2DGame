#ifndef _PLAYERCENITAL_INCLUDE
#define _PLAYERCENITAL_INCLUDE


#include "Sprite.h" 
#include "TileMap.h"


// PlayerCenital is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class PlayerCenital
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::vec2 getPosition();
	void kill();
	bool isDead();

	// Projectile gets
	bool hasShootedProjectile();
	glm::ivec2 getProjectileCoords();
	int getProjectileAngle();
	int getProjectileVelocity();
	int getProjectileType();
	void upgradeSpreadGun();

private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayerCenital;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int posMouseX = 0;
	int posMouseY = 0;
	bool lookingRight = false;
	void changeBasicAction();
	void shoot(double angulo, int x, int y);

	int basicAction = 0;
	int angle;
	bool moving;
	bool shooting = false;
	int lastShot = 0;
	int currentGun = 1;
	bool dead = false;
	int deathTime;
	bool deathFinished = false;

	//Creating projectiles
	bool shootedProjectile = false;
	bool spreadGun = false;
	glm::ivec2 projectileCoords;
	int projectileAngle, projectileVelocity, projectileType;

};


#endif // _PLAYERCENITAL_INCLUDE


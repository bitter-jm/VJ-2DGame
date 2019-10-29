#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h" 
#include "Life.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	float getShotVelocity();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, ShaderProgram& shaderProgram);
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
	void upgradeGun(int gun);
	void reduceHP(float dmg);
	void addHP(float dmg);
	float getDMG();
	float getAttackSpeed();
	float getProjectileRange();

private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int posMouseX = 0;
	int posMouseY = 0;
	bool lookingRight = false;
	int basicAction = 1;
	void changeBasicAction(int basicAnimation, int deltaTime);
	bool shooting = false;
	int lastShot = 0;
	void shoot(double angulo, int x, int y);
	int currentGun = 1;
	bool dead = false;
	int deathTime;
	bool deathFinished = false;

	//Creating projectiles
	bool shootedProjectile = false;
	bool ableToMove;
	glm::ivec2 projectileCoords;
	int projectileAngle, projectileVelocity, projectileType;

	vector<Life*> lifes;
	float hp;


};


#endif // _PLAYER_INCLUDE
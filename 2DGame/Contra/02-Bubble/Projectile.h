#ifndef _Projectile_INCLUDE
#define _Projectile_INCLUDE

#include "Sprite.h"
#include "ShaderProgram.h"

class Projectile
{
	
public:
	void init(int ID, int x, int y, int a, int v, int t, float range, bool e, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	glm::vec2 getPosition();
	void collisioned();
	bool needToDelete();
	bool isEnemyProjectile();
	bool isExploding();
	int getDmg();
	void setDmg(float dmg);

private:
	Texture spritesheet;
	Sprite* sprite;

	glm::ivec2 posProjectile;
	int initialX, initialY;
	int angle;
	int velocity;
	int type;
	int collisionTime;
	int id;
	bool enemy;
	bool deleteProjectile = false;
	float range;
	int timesUpdated;
	float dmg = 1.f;
};


#endif 

#ifndef _Projectile_INCLUDE
#define _Projectile_INCLUDE

#include "Sprite.h"
#include "ShaderProgram.h"

class Projectile
{

public:
	void init(int id, int x, int y, int angle, int velocity, int type, bool enemy, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	glm::vec2 getPosition();
	void collisioned();
	bool needToDelete();

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
};


#endif 

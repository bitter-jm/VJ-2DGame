#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Projectile.h"

# define M_PI 3.14159265358979323846  /* pi */ 
#define EXPLODING_TIME 300
#define TILESIZE 64

enum ProjectileAnims
{
	FLYING, EXPLODING
};

void Projectile::init(int ID, int x, int y, int a, int v, int t, float range, bool e, ShaderProgram& shaderProgram)
{
	//cout << "Projectile created: " << x << "-" << y << " A:"<<a << endl;
	posProjectile.x = x;
	posProjectile.y = y;
	initialX = x;
	initialY = y;
	angle = a;
	velocity = v;
	type = t;
	enemy = e;
	timesUpdated = 0;
	id = ID;
	this->range = range;

	spritesheet.loadFromFile("images/proyectiles.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.1, 0.1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	if (!enemy) {
		sprite->setAnimationSpeed(FLYING, 8);
		sprite->addKeyframe(FLYING, glm::vec2(0.0f, 0.f));
		sprite->addKeyframe(FLYING, glm::vec2(0.1f, 0.f));
		sprite->addKeyframe(FLYING, glm::vec2(0.2f, 0.f));
		sprite->addKeyframe(FLYING, glm::vec2(0.3f, 0.f));
	} 
	else {
		if (type == 2) {
			sprite->setAnimationSpeed(FLYING, 8);
			sprite->addKeyframe(FLYING, glm::vec2(0.f, 0.4f));
			sprite->addKeyframe(FLYING, glm::vec2(0.1f, 0.4f));
		}
		else if (type == 4) {
			sprite->setAnimationSpeed(FLYING, 8);
			sprite->addKeyframe(FLYING, glm::vec2(0.f, 0.3f));
		}
		else if (type == 5) {
			sprite->setAnimationSpeed(FLYING, 8);
			sprite->addKeyframe(FLYING, glm::vec2(0.1f, 0.3f));
			sprite->addKeyframe(FLYING, glm::vec2(0.2f, 0.3f));
			sprite->addKeyframe(FLYING, glm::vec2(0.3f, 0.3f));
		}
		else {
			sprite->setAnimationSpeed(FLYING, 8);
			sprite->addKeyframe(FLYING, glm::vec2(0.0f, 0.2f));
			sprite->addKeyframe(FLYING, glm::vec2(0.1f, 0.2f));
			sprite->addKeyframe(FLYING, glm::vec2(0.2f, 0.2f));
			sprite->addKeyframe(FLYING, glm::vec2(0.3f, 0.2f));
		}
	}

	sprite->setAnimationSpeed(EXPLODING, 20);
	sprite->addKeyframe(EXPLODING, glm::vec2(0.0f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.1f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.2f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.3f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.4f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.5f, 0.1f));	

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posProjectile.x), float(posProjectile.y)));
}



void Projectile::update(int deltaTime)
{
	timesUpdated++;

	// Check max distance
	if (sqrt(((float)initialX - (float)posProjectile.x) * ((float)initialX - (float)posProjectile.x) + 
			((float)initialY - (float)posProjectile.y) * ((float)initialY - (float)posProjectile.y)) > range*TILESIZE) {
		//cout << "Projectile deleted (2)" << endl;
		deleteProjectile = true;
	}

	// If explotion time passed, delete projectile
	if (sprite->animation() == EXPLODING && collisionTime + EXPLODING_TIME < glutGet(GLUT_ELAPSED_TIME)) {
		//cout << "Projectile deleted (3)" << endl;
		deleteProjectile = true;
	}

	if (angle < 0) angle = 360 + angle % 360;

	// If not exploting, move
	if (sprite->animation() == FLYING) {
		int incSin = (int)((sin((double)2 * (double)M_PI * ((double)angle / (double)360)) * (double)velocity) * (double)timesUpdated); // Pequeno
		int incCos = (int)((cos((double)2 * (double)M_PI * ((double)angle / (double)360)) * (double)velocity) * (double)timesUpdated); // Grande
		if (angle >= 0 && angle < 90) {
			posProjectile.x = initialX + incCos;
			posProjectile.y = initialY - incSin;
		} 
		else if (angle >= 90 && angle < 180) {
			posProjectile.x = initialX + incCos;
			posProjectile.y = initialY - incSin;
		}
		else if (angle >= 180 && angle < 270) {
			posProjectile.x = initialX + incCos;
			posProjectile.y = initialY - incSin;
		}
		else if (angle >= 180 && angle <= 360) {
			posProjectile.x = initialX + incCos;
			posProjectile.y = initialY - incSin;
		}
	}

	sprite->setPosition(glm::vec2(float(posProjectile.x), float(posProjectile.y)));
	sprite->update(deltaTime);
}

void Projectile::render()
{
	sprite->render();
}

glm::vec2 Projectile::getPosition()
{
	return posProjectile;
}

void Projectile::collisioned()
{
	if (!isExploding()) {
		sprite->changeAnimation(EXPLODING);
		collisionTime = glutGet(GLUT_ELAPSED_TIME);
	}
}

bool Projectile::needToDelete() {
	return deleteProjectile;
}

bool Projectile::isEnemyProjectile() {
	return enemy;
}

bool Projectile::isExploding() {
	return (sprite->animation() == EXPLODING);
}

int Projectile::getDmg() {
	return dmg;
}

void Projectile::setDmg(float dmg) {
	this->dmg = dmg;
}
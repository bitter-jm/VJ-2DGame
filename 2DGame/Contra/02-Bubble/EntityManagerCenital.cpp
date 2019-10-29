#include <GL/glew.h>
#include <GL/glut.h>
#include "EntityManagerCenital.h"
#include <iostream>
#include <set>
#include "Projectile.h"
#include "Game.h"

using namespace std;

#define playerRange 7
#define PROJECTILESIZE 16
#define PLAYERHEIGHT 32
#define PLAYERWIDTH 48

//EntityManagerCenital::EntityManagerCenital()
//{
//	player = NULL;
//}

void EntityManagerCenital::init(PlayerCenital* p, ShaderProgram* SP)
{
	player = p;
	shaderProgram = SP;
}

void EntityManagerCenital::update(int deltaTime)
{
	//Find if player created new projectile
	if (player->hasShootedProjectile()) {
		int typeproj = player->getProjectileType();
		int angleproj = player->getProjectileAngle();
		glm::ivec2 coordsproj = player->getProjectileCoords();
		int velocityproj = player->getProjectileVelocity();
		Projectile p;
		projectiles[nextProjectileID] = p;
		projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, angleproj, velocityproj, typeproj, playerRange, false, *shaderProgram);
		nextProjectileID++;
	}

	checkCollisionPlayer();

	set<int> toErase;
	for (auto& x : projectiles) {
		x.second.update(deltaTime);
		if (x.second.needToDelete()) toErase.insert(x.first);
	}

	for (auto& x : toErase) {
		projectiles.erase(x);
	}

}

void EntityManagerCenital::render()
{
	for (auto& x : projectiles) {
		x.second.render();
	}
}

void EntityManagerCenital::createProjectile(glm::vec2 initPos, int angle, int vel, int type, int range) {
	Projectile p;
	projectiles[nextProjectileID] = p;
	projectiles[nextProjectileID].init(nextProjectileID, initPos.x, initPos.y, angle, vel, type, range, true, *shaderProgram);
	nextProjectileID++;
}

void EntityManagerCenital::destroyProjectile(int id) {

}

bool EntityManagerCenital::checkCollisionEnemy(glm::vec2 posE, int xSize, int ySize) {
	for (auto& p : projectiles) {
		if (!p.second.isEnemyProjectile() && !p.second.isExploding()) {

			int pX = p.second.getPosition().x;
			int pY = p.second.getPosition().y;

			if (pX + PROJECTILESIZE >= posE.x && pX + PROJECTILESIZE <= posE.x + xSize && pY >= posE.y && pY <= posE.y + ySize) { //RIGHT UP
				p.second.collisioned();
				return true;
			}
			if (pX + PROJECTILESIZE >= posE.x && pX + PROJECTILESIZE <= posE.x + xSize && pY + PROJECTILESIZE >= posE.y && pY + PROJECTILESIZE <= posE.y + ySize) { //RIGHT DOWN
				p.second.collisioned();
				return true;
			}
			if (pX >= posE.x && pX <= posE.x + xSize && pY >= posE.y && pY <= posE.y + ySize) { //LEFT UP
				p.second.collisioned();
				return true;
			}
			if (pX >= posE.x && pX <= posE.x + xSize && pY + PROJECTILESIZE >= posE.y && pY + PROJECTILESIZE <= posE.y + ySize) { //LEFT DOWN
				p.second.collisioned();
				return true;
			}
		}
	}

	return false;
}

void EntityManagerCenital::checkCollisionPlayer() {

	if (player->isDead()) return;

	for (auto& p : projectiles) {
		if (p.second.isEnemyProjectile() && !p.second.isExploding()) {

			int pX = p.second.getPosition().x;
			int pY = p.second.getPosition().y;
			int playerX = player->getPosition().x;
			int playerY = player->getPosition().y + 8;


			if (pX + PROJECTILESIZE >= playerX && pX + PROJECTILESIZE <= playerX + PLAYERWIDTH && pY >= playerY && pY <= playerY + PLAYERHEIGHT) { //RIGHT UP
				p.second.collisioned();
				player->kill();
			}
			if (pX + PROJECTILESIZE >= playerX && pX + PROJECTILESIZE <= playerX + PLAYERWIDTH && pY + PROJECTILESIZE >= playerY && pY + PROJECTILESIZE <= playerY + PLAYERHEIGHT) { //RIGHT DOWN
				p.second.collisioned();
				player->kill();
			}
			if (pX >= playerX && pX <= playerX + PLAYERWIDTH && pY >= playerY && pY <= playerY + PLAYERHEIGHT) { //LEFT UP
				p.second.collisioned();
				player->kill();
			}
			if (pX >= playerX && pX <= playerX + PLAYERWIDTH && pY + PROJECTILESIZE >= playerY && pY + PROJECTILESIZE <= playerY + PLAYERHEIGHT) { //LEFT DOWN
				p.second.collisioned();
				player->kill();
			}
		}
	}
}

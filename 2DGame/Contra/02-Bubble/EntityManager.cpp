#include <GL/glew.h>
#include <GL/glut.h>
#include "EntityManager.h"
#include <iostream>
#include <set>
#include "Projectile.h"
#include "Game.h" 

using namespace std;

#define PROJECTILESIZE 16
#define PLAYERHEIGHT 32
#define PLAYERWIDTH 48

//EntityManager::EntityManager()
//{
//	player = NULL;
//}

void EntityManager::init(Player *p, ShaderProgram *SP)
{
	player = p;
	shaderProgram = SP;
}

void EntityManager::update(int deltaTime)
{
	//Find if player created new projectile
	if (player->hasShootedProjectile()) {
		int typeproj = player->getProjectileType();
		int angleproj = player->getProjectileAngle();
		glm::ivec2 coordsproj = player->getProjectileCoords();
		int velocityproj = player->getProjectileVelocity();
		Projectile p;
		//p.init(nextProjectileID, coordsproj.x, coordsproj.y, angleproj, velocityproj, typeproj, playerRange, false, *shaderProgram);
		projectiles[nextProjectileID] = p;
		projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, angleproj, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
		projectiles[nextProjectileID].setDmg(player->getDMG());
		nextProjectileID++;

		if (Game::instance().getCurrentLevel() == 1 || Game::instance().getCurrentLevel() == 3) {
			if (typeproj == 2) {
				Projectile p2, p3;
				if (angleproj == 0) {
					projectiles[nextProjectileID] = p2;
					projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, 22, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID].setDmg(player->getDMG());
					projectiles[nextProjectileID+1] = p3;
					projectiles[nextProjectileID + 1].init(nextProjectileID+1, coordsproj.x, coordsproj.y, -22, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID + 1].setDmg(player->getDMG());
				}
				else if (angleproj == 45) {
					projectiles[nextProjectileID] = p2;
					projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, 67, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID].setDmg(player->getDMG());
					projectiles[nextProjectileID + 1] = p3;
					projectiles[nextProjectileID + 1].init(nextProjectileID + 1, coordsproj.x, coordsproj.y, 22, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID+1].setDmg(player->getDMG());
				}
				else if (angleproj == 90) {
					projectiles[nextProjectileID] = p2;
					projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, 112, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID].setDmg(player->getDMG());
					projectiles[nextProjectileID + 1] = p3;
					projectiles[nextProjectileID + 1].init(nextProjectileID + 1, coordsproj.x, coordsproj.y, 67, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID+1].setDmg(player->getDMG());
				}
				else if (angleproj == 135) {
					projectiles[nextProjectileID] = p2;
					projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, 112, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID].setDmg(player->getDMG());
					projectiles[nextProjectileID + 1] = p3;
					projectiles[nextProjectileID + 1].init(nextProjectileID + 1, coordsproj.x, coordsproj.y, 157, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID+1].setDmg(player->getDMG());
				}
				else if (angleproj == 180 || angleproj == -180) {
					projectiles[nextProjectileID] = p2;
					projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, 157, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID].setDmg(player->getDMG());
					projectiles[nextProjectileID + 1] = p3;
					projectiles[nextProjectileID + 1].init(nextProjectileID + 1, coordsproj.x, coordsproj.y, -157, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID+1].setDmg(player->getDMG());
				}
				else if (angleproj == -135 || angleproj == 225) {
					projectiles[nextProjectileID] = p2;
					projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, -157, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID].setDmg(player->getDMG());
					projectiles[nextProjectileID + 1] = p3;
					projectiles[nextProjectileID + 1].init(nextProjectileID + 1, coordsproj.x, coordsproj.y, -112, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID+1].setDmg(player->getDMG());
				}
				else if (angleproj == -45 || angleproj == 315) {
					projectiles[nextProjectileID] = p2;
					projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, -67, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID].setDmg(player->getDMG());
					projectiles[nextProjectileID + 1] = p3;
					projectiles[nextProjectileID + 1].init(nextProjectileID + 1, coordsproj.x, coordsproj.y, -22, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID+1].setDmg(player->getDMG());
				}
				else if (angleproj == 90) {
					projectiles[nextProjectileID] = p2;
					projectiles[nextProjectileID].init(nextProjectileID, coordsproj.x, coordsproj.y, 67, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID].setDmg(player->getDMG());
					projectiles[nextProjectileID + 1] = p3;
					projectiles[nextProjectileID + 1].init(nextProjectileID + 1, coordsproj.x, coordsproj.y, 112, velocityproj, typeproj, player->getProjectileRange(), false, *shaderProgram);
					projectiles[nextProjectileID+1].setDmg(player->getDMG());
				}
				nextProjectileID += 2;
			}
		}
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

void EntityManager::render()
{
	for (auto& x : projectiles) {
		x.second.render();
	}
}

void EntityManager::createProjectile(glm::vec2 initPos, int angle, int vel, int type, int range, float dmg) {
	Projectile p;
	projectiles[nextProjectileID] = p;
	projectiles[nextProjectileID].init(nextProjectileID, initPos.x, initPos.y, angle, vel, type, range, true, *shaderProgram);
	projectiles[nextProjectileID].setDmg(dmg);
	nextProjectileID++;
}



void EntityManager::destroyProjectile(int id) {

}

bool EntityManager::checkCollisionEnemy(glm::vec2 posE, int xSize, int ySize) {
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

void EntityManager::checkCollisionPlayer() {

	if (player->isDead()) return;

	for (auto& p : projectiles) {
		if (p.second.isEnemyProjectile() && !p.second.isExploding()) {

			float dmg = p.second.getDmg();
			int pX = p.second.getPosition().x;
			int pY = p.second.getPosition().y;
			int playerX = player->getPosition().x;
			int playerY = player->getPosition().y+8;

			if (pX + PROJECTILESIZE >= playerX && pX + PROJECTILESIZE <= playerX + PLAYERWIDTH && pY >= playerY && pY <= playerY + PLAYERHEIGHT) { //RIGHT UP
				p.second.collisioned();
				SoundManager::getInstance()->playSound("sounds/hurt.ogg", false, 0.5);
				player->reduceHP(dmg);
			}
			else if (pX + PROJECTILESIZE >= playerX && pX + PROJECTILESIZE <= playerX + PLAYERWIDTH && pY + PROJECTILESIZE >= playerY && pY + PROJECTILESIZE <= playerY + PLAYERHEIGHT) { //RIGHT DOWN
				p.second.collisioned();
				SoundManager::getInstance()->playSound("sounds/hurt.ogg", false, 0.5);
				player->reduceHP(dmg);
			}
			else if (pX >= playerX && pX <= playerX + PLAYERWIDTH && pY >= playerY && pY <= playerY + PLAYERHEIGHT) { //LEFT UP
				p.second.collisioned();
				SoundManager::getInstance()->playSound("sounds/hurt.ogg", false, 0.5);
				player->reduceHP(dmg);
			}
			else if (pX >= playerX && pX <= playerX + PLAYERWIDTH && pY + PROJECTILESIZE >= playerY && pY + PROJECTILESIZE <= playerY + PLAYERHEIGHT) { //LEFT DOWN
				p.second.collisioned();
				SoundManager::getInstance()->playSound("sounds/hurt.ogg", false, 0.5);
				player->reduceHP(dmg);
			}
		}
	}
}

#include <GL/glew.h>
#include <GL/glut.h>
#include "EntityManager.h"
#include <iostream>

using namespace std;

void EntityManager::init(Player *p)
{
	player = p;
}

void EntityManager::update(int deltaTime)
{
	//std::cout << player->getPosition().x << std::endl;
}

void EntityManager::render()
{

}

#ifndef _EM_INCLUDE
#define _EM_INCLUDE

#include "Player.h"

class EntityManager
{

public:
	EntityManager() {}


	static EntityManager& instance()
	{
		static EntityManager G;
		return G;
	}

	void init(Player *p); 
	void update(int deltaTime); 
	void render(); 

private:
	Player *player;

};

#endif

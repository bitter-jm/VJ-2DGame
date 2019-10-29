#include "Item.h"

void Item::render()
{
	sprite->render();
}

void Item::update(int deltaTime)
{
	sprite->update(deltaTime);

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y))); 
}

void Item::setHidden(bool b) {
	hidden = b;
}

bool Item::is_Hidden() {
	return hidden;
}

glm::vec2 Item::getPosition() {
	return pos;
}
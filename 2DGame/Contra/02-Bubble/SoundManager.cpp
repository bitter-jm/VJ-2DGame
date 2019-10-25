#include "SoundManager.h"

SoundManager* SoundManager::instance = 0;

SoundManager* SoundManager::getInstance()
{
	if (instance == 0)
	{
		instance = new SoundManager();
	}

	return instance;
}

void SoundManager::init() {
	engine = createIrrKlangDevice();
}

void SoundManager::playMenuSound() {
	engine->play2D("sounds/getout.ogg", true);
}

void SoundManager::removeSound(string source) {
	engine->removeSoundSource("sounds/getout.ogg");
}


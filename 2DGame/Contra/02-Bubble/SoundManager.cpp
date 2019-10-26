#include "SoundManager.h"
#include<iostream>

SoundManager* SoundManager::instance = 0;

SoundManager* SoundManager::getInstance()
{
	if (instance == 0)
	{
		instance = new SoundManager();
		instance->init();
	}
	return instance;
}

void SoundManager::init() {
	engine = createIrrKlangDevice();
}

void SoundManager::playMenuSound() {
	engine->play2D("sounds/mainMenu.ogg", true);
}


void SoundManager::playSound(string source, bool repeat) {
	engine->play2D(source.c_str(), repeat);
}

void SoundManager::removeAllSound() {
	engine->removeAllSoundSources();
}

void SoundManager::removeSound(string source) {
	engine->removeSoundSource(source.c_str());
}


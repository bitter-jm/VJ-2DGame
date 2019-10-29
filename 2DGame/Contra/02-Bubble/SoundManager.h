#pragma once


#include <string>
#include <stdio.h>
#include <irrKlang.h>

#if defined(WIN32)
#include <conio.h> 
#else
#include "../common/conio.h"
#endif

#include <stdio.h>
#include <irrKlang.h>
using namespace irrklang;
using namespace std;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


class SoundManager
{
	public:
		static SoundManager* getInstance();
		void playSound(string source, bool repeat);
		void playSound(string source, bool repeat, float volume);
		void removeAllSound();
		void removeSound(string source);
		void init();

	private:
		static SoundManager* instance;
		SoundManager() {};
		ISoundEngine* engine;


};


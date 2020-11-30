#include <SDL\SDL.h>
#include "MainGame.h"

#include <Windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

#include <iostream>

int main(int argc,char** argv) {

	PlaySound(TEXT("song.wav"), NULL, SND_FILENAME | SND_ASYNC);

	char start = 'a';

	cout << "Presione 's' para empezar: ";
	cin >> start;

	if(start == 's')
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		MainGame mainge;
		mainge.run();
		system("PAUSE");
	}
	
	return 0;
}
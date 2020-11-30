#include <SDL\SDL.h>
#include "MainGame.h"

#include <Windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")


int main(int argc,char** argv) {

	PlaySound(TEXT("song.wav"), NULL, SND_FILENAME | SND_ASYNC);
	SDL_Init(SDL_INIT_EVERYTHING);
	MainGame mainge;
	mainge.run();
	system("PAUSE");
	
	return 0;
}
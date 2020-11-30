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

	cout << "\033[1;31m**********************************************\033[0m\n" << endl;
	cout << "\033[1;31m****************DOOM ETERNAL******************\033[0m\n" << endl;
	cout << "\033[1;31m**********************************************\033[0m\n";

	cout << " " << endl;
	cout << "******Fundamentos de la Teoria de Juegos******" << endl;
	cout << " " << endl;
	cout << "-Geral Esteen Castillo Arredondo U201716913" << endl;
	cout << "-Rafael Andrés Andrade Rodríguez U201812443" << endl;
	cout << "-Javier Arturo Rozas Acurio U201711814" << endl;
	cout << " " << endl;

	cout << "\033[1;31m**********************************************\033[0m\n" << endl;
	cout << " " << endl;

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
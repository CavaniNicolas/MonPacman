#include <SANDAL2/SANDAL2.h>

#include "initplateau.h"

int main(){

	int black[] = {0,0,0,255};
	int blue[] = {0,0,255,255};


	initAllSANDAL2(IMG_INIT_JPG);
	createWindow(900,950,"Pacman",0,blue,0);

	init_plateau();

	while (!PollEvent(NULL)) {
		updateWindow();
		displayWindow();

		SDL_Delay(16);
	}

	closeAllWindow();
	closeAllSANDAL2();
	return 0;
}

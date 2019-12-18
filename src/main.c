#include <SANDAL2/SANDAL2.h>
#include <stdio.h>
#include <stdint.h>
#include "initplateau.h"

void key_behavior(Element * this, SDL_Keycode c);
void action(Element * this);
void click(Element * this,int);
Element * createPacman(int spawnX, int spawnY);


typedef enum{
	up,
	down,
	left,
	right
}dir;
dir direction=left;

int main(){
	Element * e;
	int spawnX = 50+11*800/TAILLE;
	int spawnY = 100+13*800/TAILLE;
	int darkblue[] = {0,3,69,255};


	initAllSANDAL2(IMG_INIT_JPG);
	createWindow(900,950,"Pacman",0,darkblue,0);

	init_plateau();

	e=createPacman(spawnX,spawnY);
	if(!e){
		puts("Pacman creation failed");
		closeAllWindow();
		closeAllSANDAL2();
		return -1;
	}

	/* adding key press/released behavior */
	setKeyPressedElement(e,key_behavior);
	setKeyReleasedElement(e,key_behavior);

	/* adding continuous behavior */
	setActionElement(e,action);

	/* --- adding an on click behavior --- */
	/* adding the clickable zone so that we can click on our element */
	addClickableElement(e, /* element */
		/*clickable zone which is a pointer of Clickable, here we use a rectangle clickable
		the coordinates we use to define a clickable in the object are :
		(0,0) for the top left corner
		(1,1) for the bottom right corner
		*/
	rectangleClickable(0.f,  /* x coordinate of the top left corner of the rectangle clickable zone */
						0.f,  /* y coordinate of the top left corner of the rectangle clickable zone */
						1.f,  /* width of the rectangle */
						1.f), /* height of the rectangle */
						0); /* telling wether or not this zone is forbidden (used to add unclickable holes in a clickable zone) */
	setOnClickElement(e,click);
	/* ----------------------------------- */


	/* PollEvent : function to catch events, return 1 when the user clicked on the cross to close the window */
	while(!PollEvent(NULL)){ 
	/* updating the window content, mandatory when you change things in your window while running */
	updateWindow();
	/* displaying the window */
	displayWindow();

	/* this delay is to have about 60fps */
	SDL_Delay(8);
	}

	closeAllWindow();
	closeAllSANDAL2();
	return 0;
}

Element * createPacman(int spawnX, int spawnY){
	Element * e;
	e=createImage(spawnX, /* x coordinate */
					spawnY, /* y coordinate */
					40, /* width */
					40, /* height */
					"bin/pacmanLeft.png", /* image to be loaded */
					0, /* display code */
					0); /* plan, the lower the nearer */
	return(e);
}

void key_behavior(Element * this, SDL_Keycode c){
	//printf("%d : %c\n",c,c);

	double x, y;
	double w, h;
	int w_w, w_h;

	getCoordElement(this, /* element */
					&x, /* where to store x coordinate, can be NULL */
					&y); /* where to store y coordinate, can be NULL */
			
	getDimensionElement(this, /* element */
			&w, /* where to store width, can be NULL */
			&h); /* where to store height, can be NULL */
			    
	getDimensionWindow(&w_w, /* where to store width, can be NULL */
						&w_h); /* where to store height, can be NULL */

	switch (c){
		case SDLK_UP:
			//moveElement(this,0,-1);
			direction=up;
			break;
		case SDLK_DOWN:
			//moveElement(this,0,1);
			direction=down;
			break;
		case SDLK_LEFT:
			//moveElement(this,-1,0);
			direction=left;
			break;
		case SDLK_RIGHT:
			//moveElement(this,1,0);
			direction=right;
			break;

	}
}

void action(Element * this){
	double x, y;
	double w, h;
	int w_w, w_h;

	int tableau_plateau_hitbox[TAILLEHITBOX][TAILLEHITBOX]={
	#include "../python/plateauHitbox.c"
	};


	getCoordElement(this, /* element */
					&x, /* where to store x coordinate, can be NULL */
					&y); /* where to store y coordinate, can be NULL */
			
	getDimensionElement(this, /* element */
						&w, /* where to store width, can be NULL */
						&h); /* where to store height, can be NULL */
			    
	getDimensionWindow(&w_w, /* where to store width, can be NULL */
						&w_h); /* where to store height, can be NULL */


	int posXtab = ((int)x-10)/(880/TAILLEHITBOX);
	int posYtab = ((int)y-60)/(880/TAILLEHITBOX);

	int ix=(int)x;
	int iy=(int)y;
	printf("x=%d y=%d\n",ix,iy );

	switch (direction){
		case up:
			setImageElement(this,"bin/pacmanUp.png");
			printf("Xtab=%d, Ytab=%d\n",posXtab,posYtab);
			printf("%d\n",tableau_plateau_hitbox[posYtab-1][posXtab]);
			if (tableau_plateau_hitbox[posYtab-1][posXtab]==0){
				moveElement(this, /* element to be moved */
							0, /* x offset to be added */
							-1); /* y offset to be added */
			}
			break;


		case down:
			setImageElement(this,"bin/pacmanDown.png");
			printf("Xtab=%d, Ytab=%d\n",posXtab,posYtab);
			printf("%d\n",tableau_plateau_hitbox[posYtab+1][posXtab]);
			if (tableau_plateau_hitbox[posYtab+1][posXtab]==0){
				moveElement(this,0,1);
			}
			break;


		case left:
			setImageElement(this,"bin/pacmanLeft.png");
			printf("Xtab=%d, Ytab=%d\n",posXtab,posYtab);
			printf("%d\n",tableau_plateau_hitbox[posYtab][posXtab-1]);
			if (tableau_plateau_hitbox[posYtab][posXtab-1]==0){
				moveElement(this,-1,0);
			}
			break;


		case right:
			setImageElement(this,"bin/pacmanRight.png");
			printf("Xtab=%d, Ytab=%d\n",posXtab,posYtab);
			printf("%d\n",tableau_plateau_hitbox[posYtab][posXtab+1]);
			if (tableau_plateau_hitbox[posYtab][posXtab+1]==0){
				moveElement(this,1,0);
			}
			break;
	}


	if(tableau_plateau_hitbox[posXtab][posYtab]==2){
		if (posXtab==0){
			replaceElement(this,810,y);
		}else{
			replaceElement(this,50,y);
		}
	}

}

void click(Element * this, int a){
	puts("Clicked !");
}
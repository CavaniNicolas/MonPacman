#include <SANDAL2/SANDAL2.h>
#include <stdio.h>
#include <stdint.h>
#include "initplateau.h"

void key_behavior(Element * this, SDL_Keycode c);
void action(Element * this);
void click(Element * this,int);
Element * createPacman(int spawnX, int spawnY);

int tableau_plateau_hitbox[TAILLEHITBOX][TAILLEHITBOX]={
#include "../python/plateauHitbox.c"
};
int coteCube = 880/TAILLEHITBOX;

typedef enum{
	up,
	down,
	left,
	right
}dir;
dir direction=left;



int main(){
	Element * e;
	int spawnX = 10+12*coteCube;
	int spawnY = 60+14*coteCube;
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
	SDL_Delay(14);
	}

	closeAllWindow();
	closeAllSANDAL2();
	return 0;
}

Element * createPacman(int spawnX, int spawnY){
	Element * e;
	e=createImage(spawnX, /* x coordinate */
					spawnY, /* y coordinate */
					coteCube, /* width */
					coteCube, /* height */
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

	angles coord_angles; //coord des angles internes du pacman

	coord_angles.hg.x = (x+1-10);
	coord_angles.hg.y = (y+1-60);

	coord_angles.bg.x = (x+1-10);
	coord_angles.bg.y = (y+coteCube-1-60);


	coord_angles.hd.x = (x+coteCube-1-10);
	coord_angles.hd.y = (y+1-60);

	coord_angles.bd.x = (x+coteCube-1-10);
	coord_angles.bd.y = (y+coteCube-1-60);


	int hitbox_X_hautgauche_left = (coord_angles.hg.x-2)/coteCube;
	int hitbox_Y_hautgauche_left = (coord_angles.hg.y)/coteCube;
	int hitbox_X_basgauche_left = (coord_angles.bg.x-2)/coteCube;
	int hitbox_Y_basgauche_left = (coord_angles.bg.y)/coteCube;

	int hitbox_X_hautdroite_right = (coord_angles.hd.x+2)/coteCube;
	int hitbox_Y_hautdroite_right = (coord_angles.hd.y)/coteCube;
	int hitbox_X_basdroite_right = (coord_angles.bd.x+2)/coteCube;
	int hitbox_Y_basdroite_right = (coord_angles.bd.y)/coteCube;

	int hitbox_X_basgauche_down = (coord_angles.bg.x)/coteCube;
	int hitbox_Y_basgauche_down = (coord_angles.bg.y+2)/coteCube;
	int hitbox_X_basdroite_down = (coord_angles.bd.x)/coteCube;
	int hitbox_Y_basdroite_down = (coord_angles.bd.y+2)/coteCube;

	int hitbox_X_hautgauche_up = (coord_angles.hg.x)/coteCube;
	int hitbox_Y_hautgauche_up = (coord_angles.hg.y-2)/coteCube;
	int hitbox_X_hautdroite_up = (coord_angles.hd.x)/coteCube;
	int hitbox_Y_hautdroite_up = (coord_angles.hd.y-2)/coteCube;


	switch (c){
		case SDLK_UP:
			if ((tableau_plateau_hitbox[hitbox_Y_hautgauche_up][hitbox_X_hautgauche_up]==0) && (tableau_plateau_hitbox[hitbox_Y_hautdroite_up][hitbox_X_hautdroite_up]==0)){
				direction=up;
			}
			break;
		case SDLK_DOWN:
			if ((tableau_plateau_hitbox[hitbox_Y_basgauche_down][hitbox_X_basgauche_down]==0) && (tableau_plateau_hitbox[hitbox_Y_basdroite_down][hitbox_X_basdroite_down]==0)){
				direction=down;
			}
			break;
		case SDLK_LEFT:
			if ((tableau_plateau_hitbox[hitbox_Y_hautgauche_left][hitbox_X_hautgauche_left]==0) && (tableau_plateau_hitbox[hitbox_Y_basgauche_left][hitbox_X_basgauche_left]==0)){
				direction=left;
			}
			break;
		case SDLK_RIGHT:
			if ((tableau_plateau_hitbox[hitbox_Y_hautdroite_right][hitbox_X_hautdroite_right]==0) && (tableau_plateau_hitbox[hitbox_Y_basdroite_right][hitbox_X_basdroite_right]==0)){
				direction=right;
			}
			break;

	}
}

void action(Element * this){
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


	// int ix=(int)x;
	// int iy=(int)y;
	//printf("x=%d y=%d\n",ix-10,iy-60 );

	angles coord_angles; //coord des angles internes du pacman

	coord_angles.hg.x = (x+1-10);
	coord_angles.hg.y = (y+1-60);
	//printf("hg.x=%d hg.y=%d\n",coord_angles.hg.x,coord_angles.hg.y);

	coord_angles.bg.x = (x+1-10);
	coord_angles.bg.y = (y+coteCube-1-60);
	//printf("bg.x=%d bg.y=%d\n",coord_angles.bg.x,coord_angles.bg.y);


	coord_angles.hd.x = (x+coteCube-1-10);
	coord_angles.hd.y = (y+1-60); ///////
	//printf("hd.x=%d hd.y=%d\n",coord_angles.hd.x,coord_angles.hd.y);

	coord_angles.bd.x = (x+coteCube-1-10);
	coord_angles.bd.y = (y+coteCube-1-60);
	//printf("bd.x=%d bd.y=%d\n",coord_angles.bd.x,coord_angles.bd.y);


	int hitbox_X_hautgauche_left = (coord_angles.hg.x-2)/coteCube;
	int hitbox_Y_hautgauche_left = (coord_angles.hg.y)/coteCube;
	int hitbox_X_basgauche_left = (coord_angles.bg.x-2)/coteCube;
	int hitbox_Y_basgauche_left = (coord_angles.bg.y)/coteCube;

	int hitbox_X_hautdroite_right = (coord_angles.hd.x+2)/coteCube;
	int hitbox_Y_hautdroite_right = (coord_angles.hd.y)/coteCube;
	int hitbox_X_basdroite_right = (coord_angles.bd.x+2)/coteCube;
	int hitbox_Y_basdroite_right = (coord_angles.bd.y)/coteCube;

	int hitbox_X_basgauche_down = (coord_angles.bg.x)/coteCube;
	int hitbox_Y_basgauche_down = (coord_angles.bg.y+2)/coteCube;
	int hitbox_X_basdroite_down = (coord_angles.bd.x)/coteCube;
	int hitbox_Y_basdroite_down = (coord_angles.bd.y+2)/coteCube;

	int hitbox_X_hautgauche_up = (coord_angles.hg.x)/coteCube;
	int hitbox_Y_hautgauche_up = (coord_angles.hg.y-2)/coteCube;
	int hitbox_X_hautdroite_up = (coord_angles.hd.x)/coteCube;
	int hitbox_Y_hautdroite_up = (coord_angles.hd.y-2)/coteCube;


	int deplacement=1;

	switch (direction){
		case up:
			setImageElement(this,"bin/pacmanUp.png");
			if ((tableau_plateau_hitbox[hitbox_Y_hautgauche_up][hitbox_X_hautgauche_up]==0) && (tableau_plateau_hitbox[hitbox_Y_hautdroite_up][hitbox_X_hautdroite_up]==0)){


				moveElement(this, /* element to be moved */
							0, /* x offset to be added */
							-deplacement); /* y offset to be added */
			}
			break;


		case down:
			setImageElement(this,"bin/pacmanDown.png");
			if ((tableau_plateau_hitbox[hitbox_Y_basgauche_down][hitbox_X_basgauche_down]==0) && (tableau_plateau_hitbox[hitbox_Y_basdroite_down][hitbox_X_basdroite_down]==0)){
				moveElement(this,0,deplacement);
			}
			break;


		case left:
			setImageElement(this,"bin/pacmanLeft.png");
			if ((tableau_plateau_hitbox[hitbox_Y_hautgauche_left][hitbox_X_hautgauche_left]==0) && (tableau_plateau_hitbox[hitbox_Y_basgauche_left][hitbox_X_basgauche_left]==0)){
				
					
				moveElement(this,-deplacement,0);
			}
			break;


		case right:
			setImageElement(this,"bin/pacmanRight.png");
			if ((tableau_plateau_hitbox[hitbox_Y_hautdroite_right][hitbox_X_hautdroite_right]==0) && (tableau_plateau_hitbox[hitbox_Y_basdroite_right][hitbox_X_basdroite_right]==0)){
				
					
				moveElement(this,deplacement,0);
			}
			break;
	}


	// if(tableau_plateau_hitbox[posXtab_hautgauche][posYtab_hautgauche]==2){
	// 	if (posXtab_hautgauche==0){
	// 		replaceElement(this,810,y);
	// 	}else{
	// 		replaceElement(this,50,y);
	// 	}
	// }

}

void click(Element * this, int a){
	puts("Clicked !");
}
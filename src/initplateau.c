#include <SANDAL2/SANDAL2.h>

#include "initplateau.h"
#define TAILLE 22
void init_plateau(){
	int red[]   = {255,0,0,255};
	int green[]  = {0,255,0,255};
	int blue[] = {0,0,255,255};
	int white[] = {255,255,255,255};
	int black[] = {0,0,0,255};

	//int TAILLE = 5;
	/*int tableau_plateau[TAILLE][TAILLE]={   {1,1,1,0,0},
											{0,1,1,0,0},
											{1,0,0,0,1},
											{0,1,1,0,1},
											{0,1,0,0,1}};*/

	int tableau_plateau[TAILLE][TAILLE]={
	#include "../python/plateautest.c"
	};



	int color[4];
	int i,j,k,x,y;
	for (i=0;i<TAILLE;i++){
		for (j=0;j<TAILLE;j++){
			x = 50 + j*800/TAILLE;
			y = 100 + i*800/TAILLE;
			switch (tableau_plateau[i][j]){
				case 0:

					for (k=0;k<4;k++){
						color[k]=green[k];
					}

					break;
				case 1:

					for (k=0;k<4;k++){
						color[k]=red[k];
					}

					break;
			}

			if(!createBlock(x, /* x coordinate */
							y, /* y coordinate */
							800/TAILLE+1, /* width */
							800/TAILLE+1, /* height */
							color, /* color */
							0, /* display code */
							0)) /* plan, the lower the nearer */
			puts("Failed to create the block");
		}
	}

	if(!createBlock(50, /* x coordinate */
					100, /* y coordinate */
					800, /* width */
					800, /* height */
					blue, /* color */
					0, /* display code */
					1)) /* plan, the lower the nearer */
	puts("Failed to create the block");
}
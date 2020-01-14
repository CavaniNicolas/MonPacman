#include <SANDAL2/SANDAL2.h>

#include "initplateau.h"

void init_plateau(){
	int pourpre[] = {100,0,0,255};
	int violet[] = {171,98,255,255};

	//int TAILLE = 5;
	/*int tableau_plateau[TAILLE][TAILLE]={   {1,1,1,0,0},
											{0,1,1,0,0},
											{1,0,0,0,1},
											{0,1,1,0,1},
											{0,1,0,0,1}};*/


	int color[4];
	int i,j,k,x,y;
	for (i=0;i<TAILLEHITBOX;i++){
		for (j=0;j<TAILLEHITBOX;j++){
			x = 10 + j*coteCube;
			y = 60 + i*coteCube;
			switch (tableau_plateau_hitbox[i][j]){
				case 0:

					for (k=0;k<4;k++){
						color[k]=pourpre[k];
					}

					break;
				case 1:

					for (k=0;k<4;k++){
						color[k]=violet[k];
					}

					break;
			}

			if(!createBlock(x, /* x coordinate */
							y, /* y coordinate */
							coteCube, /* width */
							coteCube, /* height */
							color, /* color */
							0, /* display code */
							1)) /* plan, the lower the nearer */
			puts("Failed to create the block");
		}
	}

	// if(!createBlock(50, /* x coordinate */
	// 				100, /* y coordinate */
	// 				800, /* width */
	// 				800, /* height */
	// 				darkblue, /* color */
	// 				0, /* display code */
	// 				2)) /* plan, the lower the nearer */
	// puts("Failed to create the block");
}
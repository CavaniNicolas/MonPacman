#include <SANDAL2/SANDAL2.h>

#include "initplateau.h"

void init_plateau(){
	int darkblue[] = {0,3,69,255};
	int pourpre[] = {100,0,0,255};
	int violet[] = {171,98,255,255};

	//int TAILLE = 5;
	/*int tableau_plateau[TAILLE][TAILLE]={   {1,1,1,0,0},
											{0,1,1,0,0},
											{1,0,0,0,1},
											{0,1,1,0,1},
											{0,1,0,0,1}};*/

	int tableau_plateau[TAILLE][TAILLE]={
	#include "../python/plateau.c"
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
							800/TAILLE+1, /* width */
							800/TAILLE+1, /* height */
							color, /* color */
							0, /* display code */
							1)) /* plan, the lower the nearer */
			puts("Failed to create the block");
		}
	}

	if(!createBlock(50, /* x coordinate */
					100, /* y coordinate */
					800, /* width */
					800, /* height */
					darkblue, /* color */
					0, /* display code */
					2)) /* plan, the lower the nearer */
	puts("Failed to create the block");
}
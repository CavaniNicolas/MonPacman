#ifndef initplateauH
#define initplateauH

#define TAILLEHITBOX 22

extern int tableau_plateau_hitbox[TAILLEHITBOX][TAILLEHITBOX];
extern int coteCube;
void init_plateau();

typedef struct coord{
	int x;
	int y;
}coord;

typedef struct angles{
	coord hg; // haut gauche
	coord hd; // haut droit
	coord bg; // bas gauche
	coord bd; // bas droit
}angles;

#endif
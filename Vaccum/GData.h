#ifndef __GAMEDATA_H
#define __GAMEDATA_H

struct score
{
	bool start;
	bool waveover;
	bool gameover;
	bool earthdistroyed;
	bool shipdistroyed;

	int wave;
	int nextmeteor;

	int smallmeteorsdestroyed;
	int largemeteorsdestroyed;
	int bulletsused;
	int misslesused;
	int bombsused;

	float largemeteorspeed;

};

//HUD=============================================================================================================

struct gameHUDITEMS
{
	int weaponindex1;
	int weaponindex2;
	int weaponindex3;

	int weaponvalue1;
	int weaponvalue2;
	int weaponvalue3;

	bool weaponsfree;
};
//SPACESHIP===========================================================================================================
struct gameSpaceShip
{
	int	     value;
	float     POSX;
	float     POSY;
	float     POSZ;
	bool       hit;
	bool      life;
	bool shotfired;
	bool readytofire;


	int      clip;

};
//WEAPONS=============================================================================================================
struct bullets
{
	bool  life;

	float POSX;
	float POSY;
	float POSZ;
	bool  readytofire;

};
//===============
struct missles
{
	bool  life;
	float POSX;
	float POSY;
	float POSZ;
};


//===================
struct AlienShips
{
	bool readytofire;
	bool positiontoshoot;
	bool         falling;
	bool            life;
	bool	         hit;
	bool       shotfired;
	bool     bulletloaded;
	float POSX;
	float POSY;
	float POSZ;
};

//===================
struct division
{
	int POSX;
	int POSY;
	bool leftbound;
	bool rightbound;
	int clip;
};
//EXTERNS========================
//SCORE
extern score          gScore;
//WEAPONS
extern bullets      gHeroBullets[20];
extern bullets      gAlienBullets[50];
//SPACESHIP
extern gameSpaceShip        gHM3;
//EMEMIES
extern division       gAlienDev;
extern AlienShips     gAlien[65];


#endif
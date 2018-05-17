#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "CGfxOpenGL.h"
#include "GData.h"


//EXTERNS=========================================================================
score          gScore;
//WEAPONS
bullets      gHeroBullets[20];
bullets      gAlienBullets[50];
//SPACESHIP
gameSpaceShip        gHM3;
//EMEMIES
division       gAlienDev;
AlienShips     gAlien[65];




//================================================================================
// disable implicit float-double casting
#pragma warning(disable:4305)
//================================================================================
CGfxOpenGL::CGfxOpenGL()
{
}
//================================================================================
CGfxOpenGL::~CGfxOpenGL()
{
}
//================================================================================
bool CGfxOpenGL::Init()
{
	srand(GetTickCount());
	//Alien Devision================
	gAlienDev.POSX = 0;
	gAlienDev.POSY = 0;
	gAlienDev.leftbound = true;
	gAlienDev.rightbound = false;
	gAlienDev.clip = 50;

	float posX = -2.0;
	float posY = 0.0;
	float posZ = 0.0;
	int temp1 = 0;
	int temp2 = 11;

	for (int x = 0; x <= 11; x++)
	{
		gAlien[x].life = false;
	}
	for (int x = 12; x < 65; x++)
	{
		gAlien[x].life = true;

	}


	//ALIEN SHIPS====================
	for (int x = 0; x < 65; x++)
	{
		gAlien[x].POSX = posX;
		gAlien[x].POSY = posY;
		gAlien[x].POSZ = 0.0;
		gAlien[x].hit = false;

		gAlien[x].bulletloaded = false;
		gAlien[x].shotfired = false;


		temp1 = x + 1;

		posX += .3;

		if (temp1 == temp2)
		{
			posY += .3;
			posX = -2.0;
			temp2 = temp1 + 11;

		}

	}

	//HM3=====================================
	gHM3.life = true;
	gHM3.readytofire = true;
	gHM3.hit = false;
	gHM3.POSX = 0.0;
	gHM3.POSY = -1.4;
	gHM3.POSZ = 0.0;
	gHM3.clip = 20;

	//BULLETS================================

	for (int x = 0; x < 19; x++)
	{
		gHeroBullets[x].life = false;
		gHeroBullets[x].POSX = gHM3.POSX + .125f;
		gHeroBullets[x].POSY = gHM3.POSY + .125f;

	}
	//Villain Bullets=========================
	for (int x = 0; x < 50; x++)
	{
		gAlienBullets[x].life = false;
		gAlienBullets[x].readytofire = false;
	}

	//========================================
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//========================================
	return true;
}
//================================================================================
bool CGfxOpenGL::Shutdown()
{
	return true;
}
//================================================================================
void CGfxOpenGL::SetupProjection(int width, int height)
{
	if (height == 0)					// don't want a divide by zero
	{
		height = 1;
	}

	//=============================================================================
	glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix
											//=============================================================================
											// calculate aspect ratio of window

	gluPerspective(52.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
	//=============================================================================
	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
											//=============================================================================
	glLoadIdentity();						// reset modelview matrix
											//=============================================================================
	m_windowWidth = width;
	m_windowHeight = height;
}
//================================================================================
void CGfxOpenGL::Prepare(float dt)
{
	static float alienslastmoved = 0.0f;
	static float timelastfired = 0.0f;
	static float timealienfired = 0.0f;
	static float timebulletlastmoved = 0.0f;
	static float timealienbulletlastmoved = 0.0f;
	//ALIENS MOVEMENT============================
	alienslastmoved += dt;

	if (alienslastmoved > 0.5)
	{
		for (int x = 0; x < 65; x++)
		{
			//========================================================
			if (gAlienDev.POSX < 10 && gAlienDev.rightbound == false)
			{
				gAlien[x].POSX += 0.1;
			}
			else
				if (gAlienDev.POSX > -10 && gAlienDev.leftbound == false)
				{
					gAlien[x].POSX -= 0.1;
				}
			//========================================================
			if (gAlienDev.POSX == 10)
			{
				gAlienDev.rightbound = true;
				gAlienDev.leftbound = false;
				gAlien[x].POSY -= .1;
			}
			//========================================================

			if (gAlienDev.POSX == -10)
			{
				gAlienDev.leftbound = true;
				gAlienDev.rightbound = false;
				gAlien[x].POSY -= .1;
			}
		}

		if (gAlienDev.leftbound == true && gAlienDev.rightbound == false)
		{
			gAlienDev.POSX++;
		}
		else
			if (gAlienDev.leftbound == false && gAlienDev.rightbound == true)
			{
				gAlienDev.POSX--;
			}

		alienslastmoved = 0.0f;

	}

	//ALIEN SHOOTING MECHANIC====================================================================================

	//=========================================================


	for (int x = 12; x <65; x++)
	{
		if (gAlien[x].life == true && gAlien[x - 11].life == false && gAlien[x].bulletloaded == false)
		{
			gAlien[x].positiontoshoot = true;
		}
	}

	if (gAlienDev.clip > 0)
	{

		for (int x = 12; x <65; x++)
		{
			if (gAlien[x].positiontoshoot == true)
			{
				gAlienBullets[gAlienDev.clip - 1].POSX = gAlien[x].POSX;
				gAlienBullets[gAlienDev.clip - 1].POSY = gAlien[x].POSY;

				gAlien[x].bulletloaded = true;
				gAlienDev.clip--;
			}
		}
	}

	timealienfired += dt;

	if (timealienfired < 0.10)
	{
		int x = gAlienDev.clip;
		gAlienBullets[x].readytofire = true;
		timealienfired = 0.0;



		if (gAlienBullets[x].readytofire == true)
		{
			gAlienBullets[x].life = true;
			gAlienBullets[x].readytofire = false;


		}
	}

	if (gAlienDev.clip = 0)
	{
		gAlienDev.clip = 50;

	}



	//ALIEN BULLET MOVED======================================================
	timealienbulletlastmoved += dt;
	if (timealienbulletlastmoved > 0.0095)
	{
		for (int x = 0; x < 50; x++)
		{
			if (gAlienBullets[x].life == true)
			{
				gAlienBullets[x].POSY -= 0.01f;

			}

			if (gAlienBullets[x].POSY < -7)
			{
				gAlienBullets[x].life = false;
			}
		}
		timealienbulletlastmoved = 0.0f;
	}







	//BULLETS MOVEMENT==============================
	timelastfired += dt;
	if (timelastfired > 0.5)
	{
		if (gHM3.shotfired == true)
		{
			if (gHM3.clip > -1)
			{
				gHeroBullets[gHM3.clip - 1].POSX = gHM3.POSX;
				gHeroBullets[gHM3.clip - 1].POSY = gHM3.POSY;
				gHeroBullets[gHM3.clip - 1].life = true;
			}
			gHM3.shotfired = false;
			gHM3.clip--;
		}

		timelastfired = 0.0;
	}

	//RELOAD
	if (gHM3.clip == 0)
	{
		gHM3.clip = 20;
	}

	//Shoot================================
	timebulletlastmoved += dt;
	if (timebulletlastmoved > 0.0009)
	{
		for (int x = 0; x < 20; x++)
		{
			if (gHeroBullets[x].life == true)
			{
				gHeroBullets[x].POSY += 0.09f;
			}
			if (gHeroBullets[x].POSY > 5)
			{
				gHeroBullets[x].life = false;
			}
			for (int alien = 12; alien <= 64; alien++)
			{
				if (gAlien[alien].life == true && gHeroBullets[x].life == true)
				{
					if (
						gHeroBullets[x].POSY > gAlien[alien].POSY       &&
						gHeroBullets[x].POSY < gAlien[alien].POSY + .2  &&
						gHeroBullets[x].POSX > gAlien[alien].POSX - .01 &&
						gHeroBullets[x].POSX < gAlien[alien].POSX + .21
						)
					{
						gHeroBullets[x].life = false;
						gAlien[alien].hit = true;

					}
				}
			}
		}
		timebulletlastmoved = 0.0f;
	}
	//ALIEN HIT DETECTION
	for (int i = 12; i <= 64; i++)
	{
		if (gAlien[i].hit == true)
		{
			gAlien[i].life = false;
			gAlien[i].hit = false;
		}
	}



}
//=============================================================================================================================
void CGfxOpenGL::DrawAlienShips()
{

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0f);
	glVertex3f(0.2, 0.0, 0.0f);
	glVertex3f(0.2, 0.2, 0.0f);
	glVertex3f(0.0, 0.2, 0.0f);
	glEnd();



}
//=============================================================================================================================
void CGfxOpenGL::DrawHeroShip()
{
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.2, 0.0f);
	glVertex3f(0.12, 0.0, 0.0f);
	glVertex3f(0.12, 0.12, 0.0f);
	glVertex3f(0.14, 0.115, 0.0f);
	glVertex3f(0.14, 0.0, 0.0f);
	glVertex3f(0.16, -0.11f, 0.0f);
	glVertex3f(0.17, -0.13f, 0.0f);
	glVertex3f(0.0, -0.19f, 0.0f);
	glVertex3f(-0.17, -0.13f, 0.0f);
	glVertex3f(-0.16, -0.11f, 0.0f);
	glVertex3f(-0.14, 0.0, 0.0f);
	glVertex3f(-0.14, 0.115, 0.0f);
	glVertex3f(-0.12, 0.12, 0.0f);
	glVertex3f(-0.12, 0.0f, 0.0f);



	glEnd();
}
//DRAW ITEMS//================================================================================================================
void CGfxOpenGL::DrawAlienBullets()
{

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0.0);
	glVertex3f(.04, -.03, 0.0);
	glVertex3f(.015, -.03, 0.0);
	glVertex3f(.015, -.09, 0.0);
	glVertex3f(-0.015, -.09, 0.0);
	glVertex3f(-0.015, -.03, 0.0);
	glVertex3f(-.04, -.03, 0.0);
	glEnd();
}

//======================================================================================================================
void CGfxOpenGL::PosAndMoveAlienDev(float xPos, float yPos, float zPos)
{

	glPushMatrix();
	//=============================
	glColor3f(0.0f, 4.0f, 0.0f);
	//=============================
	glTranslatef(xPos, yPos, zPos);
	//=============================	
	DrawAlienShips();
	//=============================
	glPopMatrix();

}
//=============================================================================================================================
void CGfxOpenGL::PosAndMoveHeroShip(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	//=============================
	glColor3f(0.0f, 4.0f, 0.0f);
	//=============================
	glTranslatef(xPos, yPos, zPos);
	//=============================
	DrawHeroShip();
	//=============================
	glPopMatrix();
}
//=============================================================================================================================
void CGfxOpenGL::PosAndMoveHeroBullets(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	//=============================
	glColor3f(0.0f, 4.0f, 0.0f);
	//=============================
	glTranslatef(xPos, yPos, zPos);
	//=============================
	DrawHeroBullets();
	//=============================
	glPopMatrix();
}
void CGfxOpenGL::PosAndMoveAlienBullets(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	//=============================
	glColor3f(0.0f, 4.0f, 0.0f);
	//=============================
	glTranslatef(xPos, yPos, zPos);
	//=============================
	DrawAlienBullets();
	//=============================
	glPopMatrix();
}
//=============================================================================================================================
void CGfxOpenGL::DrawHeroBullets()
{

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0.0);
	glVertex3f(.04, -.03, 0.0);
	glVertex3f(.015, -.03, 0.0);
	glVertex3f(.015, -.09, 0.0);
	glVertex3f(-0.015, -.09, 0.0);
	glVertex3f(-0.015, -.03, 0.0);
	glVertex3f(-.04, -.03, 0.0);



	glEnd();

}
//=======================================================================================================================
void CGfxOpenGL::Render(float dt)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	PosAndMoveHeroShip(gHM3.POSX, gHM3.POSY, -5);

	//ALIEN SHIP====================================================================
	for (int x = 0; x < 65; x++)
	{
		if (gAlien[x].life == true)
		{
			PosAndMoveAlienDev(gAlien[x].POSX, gAlien[x].POSY, -5);
		}
	}

	//HERO BULLETS==================================================================
	for (int x = 0; x < 19; x++)
	{
		if (gHeroBullets[x].life == true)
		{
			PosAndMoveHeroBullets(gHeroBullets[x].POSX, gHeroBullets[x].POSY, -5);
		}
	}
	//==============================================================================
	for (int x = 0; x < 50; x++)
	{
		if (gAlienBullets[x].life == true)
		{
			PosAndMoveAlienBullets(gAlienBullets[x].POSX, gAlienBullets[x].POSY, -5);
		}
	}

}
//=============================================================================================================================
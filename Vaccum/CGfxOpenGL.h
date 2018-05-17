#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

class CGfxOpenGL
{
private:
	int m_windowWidth;
	int m_windowHeight;

public:
	CGfxOpenGL();
	virtual ~CGfxOpenGL();

	bool Init();
	bool Shutdown();

	void SetupProjection(int width, int height);

	//GAME DRAW


	void DrawAlienDev();



	void DrawAlienShips();
	void DrawAlienBullets();

	void DrawHeroLives();
	void DrawHeroShip();
	void DrawHeroBullets();

	void PosAndMoveAlienDev(float xPos, float yPos, float zPos);
	void PosAndMoveHeroShip(float xPos, float yPos, float zPos);
	void PosAndMoveHeroBullets(float xPos, float yPos, float zPos);
	void PosAndMoveAlienBullets(float xPos, float yPos, float zPos);


	void Prepare(float dt = 0.0);
	void Render(float dt = 0.0);

	//MOVEMENT FUNCTIONS

	float AngleX;
	float AngleY;
	float AngleZ;

	float PosX;
	float PosY;
	float PosZ;

	float RandX;
	float RandY;
	float RandZ;

	bool ConstRotLeft;
	bool ConstRotRight;
	bool Toggle;

	int Ten;

	//ROTATIONS============== 
	void RotXplus() { AngleX++; }
	void RotXminus() { AngleX--; }


	void RotYplus() { AngleY++; }
	void RotYminus() { AngleY--; }

	void RotZplus() { AngleZ++; }
	void RotZminus() { AngleZ--; }


	//MOVEMENT===============

	void PosXplus() { PosX += .07f; }
	void PosXminus() { PosX -= .05f; }


	void PosYplus() { PosY += .07f; }
	void PosYminus() { PosY -= .05f; }

	void PosZplus() { PosZ += .07f; }
	void PosZminus() { PosZ -= .05f; }

};

#endif

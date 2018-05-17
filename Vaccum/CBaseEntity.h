#ifndef __BASE_ENTITY
#define __BASE_ENTITY

class Base_Entity
{
private:
	int ID;

	float posx;
	float posy;
	float posz;

	bool active;

	string name;
	string position;
	string active;



public:
	void setID();
	void getID();

	void set posx(z);
	void set posy(y);
	void set posz(z);

	float get posx() { return posx };
	float get posy() { return posy };
	float get posz() { return posz };

	void set activity(bool a);


}




#endif
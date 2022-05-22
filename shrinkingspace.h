#ifndef SHRINKINGSPACE_H
#define SHRINKINGSPACE_H

#include "gameobject.h"

class ShrinkingSpace : public GameObject
{
public:
	ShrinkingSpace();
	void update();
	void draw();


private:
	float m_ShrinkingSpeed = 10; // Shrinking speed per second
};

#endif // SHRINKINGSPACE_H
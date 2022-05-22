#ifndef GAMEPHYSICS_H
#define GAMEPHYSICS_H

#define PHYSICS_TIME 60.0f
#define GRAVITY_CONSTANT 0.0f
#define TERMINAL_VELOCITY 0.5f

#include "scene.h"
#include "gameobject.h"
#include "raylib.h"
#include "raymath.h"

class Scene;

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void initPhysics(Scene* scene);
	void simulatePhysics();
	void addObject(int sceneIndex);
	void removeObject(std::shared_ptr<GameObject> obj);

private:
	Scene* m_Scene;
	std::vector<std::shared_ptr<GameObject>> m_PhysicsObjects;
};


#endif // !GAMEPHYSICS_H

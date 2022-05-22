#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <raylib.h>
#include <vector>
#include <memory>

#include "gameobject.h"

class PhysicsSystem;

class Scene
{
public:
	Scene();
	Scene(std::string name);
	~Scene();

	void load();
	void unload();

	void update();
	void draw();
	void drawObjects();
	void drawObjects2d(Camera3D camera);

	std::string getSceneInfo();

	int addObject(std::shared_ptr<GameObject> g);
	std::shared_ptr<GameObject> getObject(int index);
	int getObjectCount();
	bool removeObject(std::shared_ptr<GameObject> g);
	bool removeObjectAtPosition(std::vector<std::shared_ptr<GameObject>>::iterator i);
	bool removeObjectAtPosition(int i);

	void setName(std::string newName);

	std::string name();

	bool loaded;

private:
	std::vector<std::shared_ptr<GameObject>> m_Objects;
	std::string m_Name;

	PhysicsSystem* m_PhysicsSystem;

	float m_PhysicsTimer;
	Camera3D m_Camera;
};

#endif // !SCENE_H

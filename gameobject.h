#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <raylib.h>

class GameObject
{
public:
	GameObject();
	~GameObject();
	void setModel(Model m);
	void setShader(Shader s);

	virtual void update();
	virtual void draw();
	virtual void draw2d(Camera3D camera);

	Vector3 getPosition();
	void setPosition(Vector3 newPos);

	// If this object should be deleted in the next update.
	bool active;

	// If this object should use gravity.
	bool useGravity;

	// Velocity of the object. 0 if it doesn't use gravity.
	Vector3 velocity;
	BoundingBox bounds;

protected:
	Vector3 m_Position;
	Vector3 m_Scale;
	Model m_Model;
	Shader m_Shader;

	Vector3 m_BoundsMinOffset;
	Vector3 m_BoundsMaxOffset;
private:

};

#endif // !GAMEOBJECT_H

#include "gameobject.h"
#include "raymath.h"
#include <string>

GameObject::GameObject()
{
	m_Model = Model();
	m_Shader = Shader();
	m_Position = Vector3{ 0 };
	m_Scale = Vector3{ 0 };
	active = true;
	useGravity = true;
	velocity = Vector3{ 0.0f, 0.0f, 0.0f };

	// Basic cube bounds
	bounds = GetMeshBoundingBox(GenMeshCube(1, 1, 1));
	m_BoundsMinOffset = Vector3Subtract(bounds.min, m_Position);
	m_BoundsMaxOffset = Vector3Subtract(bounds.max, m_Position);
}

GameObject::~GameObject()
{
}

void GameObject::setModel(Model m)
{
	m_Model = m;
	bounds = GetModelBoundingBox(m_Model);
}

void GameObject::setShader(Shader s)
{
	m_Shader = s;
}

void GameObject::update()
{
	if (IsKeyPressed(KEY_W))
	{
		m_Position = Vector3Add(m_Position, Vector3{ 0,1,0 });
	}

	m_Position = Vector3Add(m_Position, velocity);
}

void GameObject::draw()
{
	//	DrawModel(m_Model, m_Transform.translation, 1.0f, RAYWHITE);
	//	DrawMesh();
	//	SetShaderValue(m_Shader, 0, , SHADER_LOC_COLOR_DIFFUSE)

	

	DrawCube(m_Position, 1, 1, 1, RED);
	DrawBoundingBox(bounds, DARKGREEN);
}

std::string boolToString(bool value)
{
	return value ? "true" : "false";
}

void GameObject::draw2d(Camera3D camera)
{
	Vector2 screenpos = GetWorldToScreen(Vector3Add(m_Position, Vector3{ 0.0f,1.25f,0.0f }), camera);
	DrawText(boolToString(useGravity).c_str(), screenpos.x, screenpos.y, 24, BLACK);
}

Vector3 GameObject::getPosition()
{
	return m_Position;
}

void GameObject::setPosition(Vector3 newPos)
{
	m_Position = newPos;
	bounds.min = Vector3Add(m_Position, m_BoundsMinOffset);
	bounds.max = Vector3Add(m_Position, m_BoundsMaxOffset);
}

#include "shrinkingspace.h"
#include <raymath.h>

ShrinkingSpace::ShrinkingSpace()
{
	active = true;
	useGravity = false;
	m_Scale = Vector3{ 1.0f,0.25f,1.0f };
}

Vector3 Vector3Clamp(Vector3 v, float min, float max)
{
	auto result = Vector3{ Clamp(v.x,min,max), Clamp(v.y,min,max), Clamp(v.z,min,max) };
	return result;
}

void RotateAround(Vector3* pos, Vector3 point, Vector3 axis, float angle)
{
	Vector3 worldPos = *pos;
	Quaternion q = QuaternionFromAxisAngle(axis, angle * DEG2RAD);
	Vector3 dif = Vector3Subtract(worldPos, point);
	dif = Vector3RotateByQuaternion(dif, q);
	worldPos = Vector3Add(point, dif);
	*pos = worldPos;
}

void ShrinkingSpace::update()
{
	m_Scale = Vector3Clamp(
							Vector3Subtract(m_Scale, 
											Vector3{ m_ShrinkingSpeed, 0.0f, m_ShrinkingSpeed }), 
							0.1f, 2.0f);
}


void ShrinkingSpace::draw()
{
	DrawCube(m_Position, m_Scale.x, m_Scale.y, m_Scale.z, DARKBLUE);
}

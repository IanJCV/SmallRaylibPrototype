#ifndef GAMEUTILS_H
#define GAMEUTILS_H
#include <raylib.h>
#include <string>

Vector3 insideUnitSphere()
{
    Vector3 v;
    v.x = (float)GetRandomValue(-10, 10) / 10.0f;
    v.y = (float)GetRandomValue(-10, 10) / 10.0f;
    v.z = (float)GetRandomValue(-10, 10) / 10.0f;
    return v;
}

#endif // !GAMEUTILS_H

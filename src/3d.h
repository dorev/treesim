#pragma once
#include <mat4x4.hpp>

struct Vector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Position3D
{
    Vector3 position;
    Vector3 rotation;
};

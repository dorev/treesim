#pragma once

struct Position
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Quaternion
{
    float w = 0.0f;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct PosQuat
{
    Position position;
    Quaternion quaternion;
};

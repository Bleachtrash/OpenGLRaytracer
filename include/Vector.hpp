#pragma once

struct Vector2
{
    float x, y;
    Vector2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    Vector2() : Vector2(0, 0) {}

    Vector2 operator +(const Vector2 other)
    {
        return Vector2(this->x+other.x, this->y+other.y);
    }
};

struct Vector3
{
    float x, y, z;
    Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vector3() : Vector3(0, 0, 0) {}
};
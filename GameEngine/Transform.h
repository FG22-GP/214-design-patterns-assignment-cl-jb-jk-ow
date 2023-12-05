#pragma once

struct Vector2 {
public:
    int x;
    int y;
};

struct Transform {
public:
    Transform();
    Transform(Vector2 initialPosition);
    Transform(Vector2 initialPosition, Vector2 initialScale);

    Vector2 position;
    Vector2 scale;
};

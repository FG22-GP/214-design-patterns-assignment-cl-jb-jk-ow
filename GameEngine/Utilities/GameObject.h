#pragma once

struct Position {
public:
    int X;
    int Y;
};

struct Transform {
public:
    Position Position;
};

class GameObject {
public:
    Transform Transform;
};

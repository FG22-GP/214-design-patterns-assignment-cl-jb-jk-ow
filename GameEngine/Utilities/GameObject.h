#pragma once

struct Position {
public:
    int x;
    int y;
};

struct Transform {
public:
    Position position;
};

class GameObject {
public:
    Transform transform;
};

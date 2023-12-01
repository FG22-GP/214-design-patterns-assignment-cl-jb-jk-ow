#include "Intersection.h"

bool Intersection::IntersectionMouseRect(SDL_Rect* Rect, std::vector<int> MousePos) {
    int mouseX = MousePos[0];
    int mouseY = MousePos[1];

    return (mouseX >= Rect->x && mouseX <= (Rect->x + Rect->w) &&
                mouseY >= Rect->y && mouseY <= (Rect->y + Rect->h));
}

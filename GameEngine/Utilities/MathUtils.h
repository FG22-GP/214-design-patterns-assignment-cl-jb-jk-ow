#pragma once
#include <random>

class MathUtils {
public:
    static int GetRandomInt(int min, int max) {
        std::random_device random;
        std::mt19937 gen(random());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(gen);
    }

    static SDL_Color GetRandomColor() {
        Uint8 r = GetRandomInt(0, 255);
        Uint8 g = GetRandomInt(0, 255);
        Uint8 b = GetRandomInt(0, 255);

        SDL_Color randomColor = {r, g, b};
        return randomColor;
    }
};

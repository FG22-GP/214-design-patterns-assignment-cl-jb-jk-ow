#pragma once

#include <unordered_map>
#include <SDL_ttf.h>
#include <string>

class TextFactory {
public:
    TTF_Font* GetFont(const char* fontURL, int fontSize);

private:
    std::unordered_map<std::string, TTF_Font*> fontCache;
};

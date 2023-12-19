#include "TextFactory.h"

TTF_Font* TextFactory::GetFont(const char* fontURL, int fontSize) {
    
    std::string key = std::string(fontURL) + "_" + std::to_string(fontSize);

    auto it = fontCache.find(key);

    if(it != fontCache.end())
    {
        return it->second;
    }        

    TTF_Font* font = TTF_OpenFont(fontURL, fontSize);
    
    if (font != nullptr) {
        fontCache[key] = font;
    }

    return font;
}
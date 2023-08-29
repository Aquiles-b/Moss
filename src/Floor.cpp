#include "Floor.hpp"
using namespace moss;

Floor::Floor(const std::string& img)
    :Component{img, 1, (Vector2){0.0f, 0.0f}, 0}{
}

Floor::~Floor(){}

void Floor::update(struct Vector2& coord){
    DrawTextureV(this->getSprite(), coord, WHITE);
}

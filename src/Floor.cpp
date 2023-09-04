#include "../headers/Floor.hpp"
using namespace moss;

Floor::Floor(const std::string& img)
    :Component{img, 1, (Vector2){0.0f, 0.0f}, 0, 1, 1}{
}

Floor::~Floor(){}

void Floor::updateBefore(Vector2& coord, const Color& c){
    coord.x += this->getSprite()->getOffset().x;
    DrawTextureV(this->getImg(), coord, c);
}

void Floor::updateAfter(Vector2& coord, const Color& c){}

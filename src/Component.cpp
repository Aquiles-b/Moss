#include "Component.hpp"

using namespace moss;

unsigned int Component::nextId{0};

Component::Component(const std::string& img, const int& frames, const Vector2& posi, const int& speed)
    :sprite{new Animation{img, frames, speed}}, id{Component::nextId}, posi{posi}{
    Component::nextId++;
}

Component::~Component(){
    delete this->sprite;
}

void Component::update(struct Vector2& coord){
    sprite->linearAnimation(coord);
}

const unsigned int& Component::getId() const{
    return this->id;
}
 
const Texture2D& Component::getSprite() const{
    return this->sprite->getImg();
}

#include "../headers/Component.hpp"

using namespace moss;

int64_t Component::nextId{0};

Component::Component(const std::string& img, const int& frames, const Vector2& posi, const int& speed,
                     const int& width, const int& height)
    :sprite{new Animation{img, frames, speed}}, id{Component::nextId}, posi{posi},
        width{width}, height{height}{
    Component::nextId++;
}
Component::Component(const std::string& img, const int& frames, const Vector2& posi, const int& speed,
          const int& width, const int& height, const Vector2& offset)
    :sprite{new Animation{img, frames, speed, offset}}, id{Component::nextId}, posi{posi},
        width{width}, height{height}{
    Component::nextId++;
}

Component::~Component(){
    delete this->sprite;
}

void Component::update(Vector2& coord, const Color& c){
    sprite->linearAnimation(coord, c);
}  
bool Component::isInsideLimits(const int& l, const int& c, const int& size) const{
    if (l - (this->width-1) < 0 || c - (this->height-1) < 0){
        return false;
    }

    return true;
}

const int64_t& Component::getId() const{
    return this->id;
}
 
const Texture2D& Component::getImg() const{
    return this->sprite->getImg();
}

const int& Component::getWidth() const{
    return this->width;
}

const int& Component::getHeight() const{
    return this->height;
}

const moss::Animation *Component::getSprite() const{
    return this->sprite;
}

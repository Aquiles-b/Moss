#include "../headers/Component.hpp"

using namespace moss;

int64_t Component::nextId{0};

Component::Component(const std::string& img, const int& frames, const Vector2& posi, const int& speed, const int& width,
                const int& height)
    :spriteAf{new Animation{img, frames, speed}}, spriteBf{nullptr},
    id{Component::nextId}, posi{posi}, width{width}, height{height}{
    Component::nextId++;
}

Component::Component(const std::string& imgAf, const std::string& imgBf, const int& frames, 
            const Vector2& posi, const int& speed, const int& width, const int& height)
    :Component{imgAf, frames, posi, speed, width, height}{ 
    spriteBf = new Animation{imgBf, frames, speed};
}

Component::Component(const std::string& imgAf, const std::string& imgBf, const int& frames, const Vector2& posi, const int& speed,
          const int& width, const int& height, const Vector2& offset)
    :Component{imgAf, imgBf, frames, posi, speed, width, height}{ 
        this->spriteBf->setOffset(offset);
        this->spriteAf->setOffset(offset);
}

Component::~Component(){
    delete this->spriteAf;
    delete this->spriteBf;
}

void Component::updateAfter(Vector2& coord, const Color& c){
    spriteAf->linearAnimation(coord, c);
}  

void Component::updateBefore(Vector2& coord, const Color& c){
    spriteBf->linearAnimation(coord, c);
}  

const int64_t& Component::getId() const{
    return this->id;
}
 
const Texture2D& Component::getImg() const{
    return this->spriteAf->getImg();
}

const int& Component::getWidth() const{
    return this->width;
}

const int& Component::getHeight() const{
    return this->height;
}

const moss::Animation *Component::getSprite() const{
    return this->spriteAf;
}

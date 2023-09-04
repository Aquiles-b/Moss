#include "../headers/ComponentModel.hpp"

using namespace moss;

int64_t ComponentModel::nextId{0};

ComponentModel::ComponentModel(){}

ComponentModel::ComponentModel(const std::string& img, const int& frames, const int& speed, const int& width,
                const int& height, const bool& isTile)
    :spriteBf{new Animation{img, frames, speed}}, spriteAf{nullptr},
    id{ComponentModel::nextId}, width{width}, height{height}, isTile{isTile}{
    ComponentModel::nextId++;
}

ComponentModel::ComponentModel(const std::string& imgBf, const std::string& imgAf, const int& frames, 
            const int& speed, const int& width, const int& height, const bool& isTile)
    :ComponentModel{imgBf, frames, speed, width, height, isTile}{ 
    this->spriteAf = new Animation{imgAf, frames, speed};
}

ComponentModel::ComponentModel(const std::string& imgBf, const std::string& imgAf, const int& frames, const int& speed,
          const int& width, const int& height, const Vector2& offset, const bool& isTile)
    :ComponentModel{imgBf, imgAf, frames, speed, width, height, isTile}{ 
        this->spriteBf->setOffset(offset);
        this->spriteAf->setOffset(offset);
}

ComponentModel::~ComponentModel(){
    delete this->spriteAf;
    delete this->spriteBf;
}

void ComponentModel::updateAfter(Vector2& coord, const Color& c){
    if (!this->getIsTile())
        spriteAf->linearAnimation(coord, c);
}  

void ComponentModel::updateBefore(Vector2& coord, const Color& c){
    spriteBf->linearAnimation(coord, c);
}  

const int64_t& ComponentModel::getId() const{
    return this->id;
}

void ComponentModel::setId(const int64_t& id){
    this->id = id;
}

const int& ComponentModel::getWidth() const{
    return this->width;
}

void ComponentModel::setWidth(const int& width){
    this->width = width;
}

const int& ComponentModel::getHeight() const{
    return this->height;
}

void ComponentModel::setHeight(const int& height){
    this->height = height;
}

moss::Animation *ComponentModel::getSpriteBf() const{
    return this->spriteBf;
}

void ComponentModel::setSpriteBf(moss::Animation *spriteBf){
    this->spriteBf = spriteBf;
}

moss::Animation *ComponentModel::getSpriteAf() const{
    return this->spriteAf;
}

void ComponentModel::setSpriteAf(moss::Animation *spriteAf){
    this->spriteAf = spriteAf;
}

const bool ComponentModel::getIsTile() const{
    return this->isTile;
}

void ComponentModel::setIsTile(const bool& isTile){
    this->isTile = isTile;
}

#include "../headers/Robot.hpp"
moss::Robot::Robot(Texture2D *spr, const int& frames, const int& speedAnimation,
          const Vector2& offset, const int& frameHeight, const Vector2& posi, const float& speed,
          Vector2 *path, const int& tamPath)
    :sprite{new moss::Animation{spr, frames, speedAnimation, offset, frameHeight}}, posi{posi},
    speed{speed}, heightIndex{0}, path{new Vector2[128]}, tamPath{tamPath}, vertexIndex{0},
    hsp{1}, vsp{1}, reached{false}, color{WHITE}{
    for (int i = 0; i < tamPath; ++i){
        this->path[i].x = path[i].x;
        this->path[i].y = path[i].y;
    }
}

moss::Robot::~Robot(){
    delete this->sprite;
    delete[] this->path;
}

void moss::Robot::update(){
    chooseHeightIndex();
    this->sprite->linearAnimationHeight(this->posi, this->heightIndex, this->color);
    if (abs(this->posi.x - this->path[this->vertexIndex].x) >= 1.0f && 
            abs(this->posi.y - this->path[this->vertexIndex].y) >= 1.0f){
        this->posi.x += this->hsp * this->speed;
        this->posi.y += this->vsp * this->speed / 2.0f;
        return;
    } 
    if (this->vertexIndex == this->tamPath-1){
        this->reached = true;
        return;
    }
    ++this->vertexIndex;
    if (this->posi.x > this->path[this->vertexIndex].x)
        this->hsp = -1;
    else
        this->hsp = 1;
    if (this->posi.y > this->path[this->vertexIndex].y)
        this->vsp = -1;
    else
        this->vsp = 1;
}

void moss::Robot::chooseHeightIndex(){
    if (this->hsp < 0){
        if (this->vsp < 0)
            this->heightIndex = 2; 
        else if (this->vsp > 0)
            this-> heightIndex = 0;
    } else if (this->hsp > 0){
        if (this->vsp < 0)
            this->heightIndex = 3; 
        else if (this->vsp > 0)
            this-> heightIndex = 1;
    }
}

const bool& moss::Robot::getReached() const{
    return this->reached;
}

Vector2& moss::Robot::getPosi(){
    return this->posi;
}
 
const Color& moss::Robot::getColor() const{
    return this->color;
}

void moss::Robot::setColor(const Color& color){
    this->color = color;
}

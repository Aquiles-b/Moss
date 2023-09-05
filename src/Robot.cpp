#include "../headers/Robot.hpp"
moss::Robot::Robot(const std::string& spr, const int& frames, const int& speedAnimation,
          const Vector2& offset, const int& frameHeight, const Vector2& posi, const float& speed,
          Vector2 *path, const int& tamPath)
    :sprite{new moss::Animation{spr, frames, speedAnimation, offset, frameHeight}}, posi{posi},
    speed{speed}, heightIndex{0}, path{new Vector2[128]}, tamPath{tamPath}, vertexIndex{0},
    hsp{1}, vsp{1}, reached{false}{
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
    this->sprite->linearAnimationHeight(this->posi, this->heightIndex, WHITE);
    /* std::cerr << this->sprite->getImg().id << " (" << this->posi.x << ", " << this->posi.y << ")" << std::endl; */
    if (this->posi.x != this->path[this->vertexIndex].x && 
            this->posi.y != this->path[this->vertexIndex].y){
        this->posi.x += this->hsp * this->speed;
        this->posi.y += this->vsp * this->speed;
        return;
    } 
    if (this->vertexIndex == this->tamPath){
        this->reached = true;
        return;
    }
    std::cerr << this->vertexIndex << std::endl;
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

const bool& moss::Robot::getReached() const{
    return this->reached;
}

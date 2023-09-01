#include "../headers/Robot.hpp"
moss::Robot::Robot(const std::string& spr, const int& frames, const int& speed,
          const Vector2& offset, const int& frameHeight, const Vector2& posi): 
    sprite{new moss::Animation{spr, frames, speed, offset, frameHeight}}, posi{posi},
    speed{5}, heightIndex{0}{
}

moss::Robot::~Robot(){
    delete this->sprite;
}

void moss::Robot::update(){
    this->sprite->linearAnimationHeight(this->posi, this->heightIndex, WHITE);
    int hsp = (-IsKeyDown(KEY_LEFT) + IsKeyDown(KEY_RIGHT));
    int vsp = (-IsKeyDown(KEY_UP) + IsKeyDown(KEY_DOWN));
    this->posi.x += hsp * this->speed;
    this->posi.y += vsp * this->speed;

    if (hsp < 0)
        this->heightIndex = 0;
    else if (hsp > 0)
        this->heightIndex = 3;
    if (vsp < 0)
        this->heightIndex = 2;
    else if (vsp > 0)
        this->heightIndex = 1;
}

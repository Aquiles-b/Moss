#include "../headers/Animation.hpp"

using namespace moss;

Animation::Animation(const std::string& spr, const int& frames, const int& speed)
    : img{LoadTexture(spr.c_str())}, maxFrames{frames}, frameIndex{0},
        delay{0}, speed{speed}{
    this->frameWidth = this->img.width / frames;
    this->frameRec = {0.0f, 0.0f, static_cast<float>(this->frameWidth), static_cast<float>(this->img.height)};
}

Animation::~Animation(){
    UnloadTexture(this->img);
}

void Animation::linearAnimation(struct Vector2& coord){
    if (this->delay > this->speed){
        this->frameIndex++;
        this->frameIndex %= this->maxFrames;
        this->frameRec.x = this->frameWidth * this->frameIndex;
        this->delay = 0;
    }
    DrawTextureRec(this->img, this->frameRec, coord, WHITE);
    this->delay++;
}

const Texture2D& Animation::getImg() const{
    return this->img;
}

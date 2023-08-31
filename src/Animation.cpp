#include "../headers/Animation.hpp"

using namespace moss;

Animation::Animation(const std::string& spr, const int& frames, const int& speed)
    : img{LoadTexture(spr.c_str())}, maxFrames{frames}, frameIndex{0},
        delay{0}, speed{speed}{
    this->frameWidth = this->img.width / frames;
    this->frameRec = {0.0f, 0.0f, static_cast<float>(this->frameWidth), static_cast<float>(this->img.height)};
    this->offset.x = -this->img.height;
    this->offset.y = 0.0f;
}

Animation::Animation(const std::string& spr, const int& frames, const int& speed,
                    const Vector2& offset)
    :Animation{spr, frames, speed}{
        this->offset = offset;
}
Animation::~Animation(){
    UnloadTexture(this->img);
}

void Animation::linearAnimation(Vector2 coord, const Color& c){
    coord.x += this->offset.x;
    coord.y += this->offset.y;
    if (this->delay > this->speed){
        this->frameIndex++;
        this->frameIndex %= this->maxFrames;
        this->frameRec.x = this->frameWidth * this->frameIndex;
        this->delay = 0;
    }
    DrawTextureRec(this->img, this->frameRec, coord, c);
    this->delay++;
}

const Texture2D& Animation::getImg() const{
    return this->img;
}

const Vector2& Animation::getOffset() const{
    return this->offset;
}

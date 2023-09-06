#include "../headers/Animation.hpp"

using namespace moss;

Animation::Animation(const std::string& spr, const int& frames, const int& speed)
    : img{new Texture2D}, maxFrames{frames}, frameIndex{0},
        delay{0}, speed{speed}, direction{1}, imgShared{false}{
    *this->img = LoadTexture(spr.c_str());
    this->frameWidth = this->img->width / frames;
    this->frameRec = {0.0f, 0.0f, static_cast<float>(this->frameWidth), static_cast<float>(this->img->height)};
    this->offset.x = -this->img->height;
    this->offset.y = 0.0f;
    this->frameHeight = 0;
}

Animation::Animation(Texture2D *spr, const int& frames, const int& speed,
          const Vector2& offset, const int& frameHeight)
    : img{spr}, maxFrames{frames}, frameIndex{0}, delay{0}, speed{speed}, direction{1}, imgShared{true}{
    this->frameWidth = this->img->width / frames;
    this->frameRec = {0.0f, 0.0f, static_cast<float>(this->frameWidth), static_cast<float>(this->img->height)};
    this->offset = offset;
    this->frameHeight = frameHeight;
    this->frameRec.height = frameHeight;
}

Animation::Animation(const std::string& spr, const int& frames, const int& speed,
                    const Vector2& offset)
    :Animation{spr, frames, speed}{
        this->offset = offset;
}

Animation::Animation(const std::string& spr, const int& frames, const int& speed,
          const Vector2& offset, const int& frameHeight)
    :Animation{spr, frames, speed, offset}{
        this->frameHeight = frameHeight;
        this->frameRec.height = frameHeight;
}

Animation::~Animation(){
    if (!this->imgShared){
        UnloadTexture(*this->img);
        delete this->img;
    }
}

void Animation::linearAnimation(Vector2 coord, const Color& c){
    linearAnimationHeight(coord, 0, c);
}

void Animation::linearAnimationHeight(Vector2 coord, const int& heightIndex, const Color& c){
    coord.x += this->offset.x;
    coord.y += this->offset.y;
    this->frameRec.y = this->frameHeight * heightIndex;
    if (this->delay > this->speed){
        this->frameIndex++;
        this->frameIndex %= this->maxFrames;
        this->frameRec.x = this->frameWidth * this->frameIndex;
        this->delay = 0;
    }
    DrawTextureRec(*this->img, this->frameRec, coord, c);
    this->delay++;
}

void Animation::retractAnimation(Vector2 coord, const Color& c){
    coord.x += this->offset.x;
    coord.y += this->offset.y;
    if (this->delay > this->speed){
        this->frameIndex += this->direction;
        this->frameRec.x = this->frameWidth * this->frameIndex;
        this->delay = 0;
        if (this->frameIndex == this->maxFrames-1 || this->frameIndex == 0)
            this->direction = -this->direction;
    }
    DrawTextureRec(*this->img, this->frameRec, coord, c);
    this->delay++;
}

const Texture2D& Animation::getImg() const{
    return *this->img;
}

const Vector2& Animation::getOffset() const{
    return this->offset;
}
void Animation::setOffset(const Vector2& offset){
    this->offset = offset;
}

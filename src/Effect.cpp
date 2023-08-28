#include "Effect.hpp"

using namespace moss;

Effect::Effect(const std::string& efx, const int& frames, const Vector2& posi, const int& speed)
    : sprite{LoadTexture(efx.c_str())}, posi{posi}, maxFrames{frames}, frameIndex{0},
        delay{0}, speed{speed}{
    this->frameWidth = this->sprite.width / frames;
    this->frameRec = {0.0f, 0.0f, static_cast<float>(this->frameWidth), 
                        static_cast<float>(this->sprite.height)};
}

Effect::~Effect(){
    UnloadTexture(this->sprite);
}

void Effect::update(){
    if (this->delay > this->speed){
        this->frameIndex++;
        this->frameIndex %= this->maxFrames;
        this->frameRec.x = this->frameWidth * this->frameIndex;
        this->delay = 0;
    }
    DrawTextureRec(this->sprite, this->frameRec, this->posi, WHITE);
    this->delay++;
}

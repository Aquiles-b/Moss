#ifndef EFFECT_HPP
#define EFFECT_HPP
#include "../include/raylib.h"
#include <iostream>

namespace moss{
class Animation{
    public:
        Animation(const std::string& spr, const int& frames, const int& speed);
        virtual ~Animation();

        const Texture2D& getImg() const;

        void linearAnimation(struct Vector2& coord);
    private:
        Texture2D img;
        Rectangle frameRec;
        int frameWidth;
        int frameIndex;
        int maxFrames;
        int delay;
        int speed;
};
}
#endif

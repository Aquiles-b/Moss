#ifndef EFFECT_HPP
#define EFFECT_HPP
#include "../include/raylib.h"
#include <iostream>

namespace moss{
class Animation{
    public:
        Animation(const std::string& spr, const int& frames, const int& speed);
        Animation(const std::string& spr, const int& frames, const int& speed,
                  const Vector2& offset);
        virtual ~Animation();

        const Texture2D& getImg() const;
        const Vector2& getOffset() const;

        void linearAnimation(Vector2& coord);
    private:
        Texture2D img;
        Rectangle frameRec;
        int frameWidth;
        int frameIndex;
        int maxFrames;
        int delay;
        int speed;
        Vector2 offset;
};
}
#endif

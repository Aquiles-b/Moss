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
        Animation(const std::string& spr, const int& frames, const int& speed,
                  const Vector2& offset, const int& frameHeight);
        Animation(const Texture2D& spr, const int& frames, const int& speed,
                  const Vector2& offset, const int& frameHeight);
        virtual ~Animation();

        const Texture2D& getImg() const;
        const Vector2& getOffset() const;
        void setOffset(const Vector2& offset);

        void linearAnimation(Vector2 coord, const Color& c);
        void linearAnimationHeight(Vector2 coord, const int& heightIndex, const Color& c);
        void retractAnimation(Vector2 coord, const Color& c);
    private:
        Texture2D img;
        Rectangle frameRec;
        int frameWidth;
        int frameHeight;
        int frameIndex;
        int maxFrames;
        int delay;
        short direction;
        int speed;
        Vector2 offset;
};
}
#endif

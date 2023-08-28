#ifndef EFFECT_HPP
#define EFFECT_HPP
#include "../include/raylib.h"
#include <iostream>

namespace moss{
class Effect{
    public:
        Effect(const std::string& efx, const int& frames, const Vector2& posi, const int& speed);
        virtual ~Effect();

        void update();
    private:
        Texture2D sprite;
        Rectangle frameRec;
        int frameWidth;
        int frameIndex;
        int maxFrames;
        int delay;
        int speed;
        Vector2 posi;
};
}
#endif

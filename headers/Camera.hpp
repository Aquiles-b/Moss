#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "../include/raylib.h"
#include <iostream>

namespace moss{
class Camera{
    public:
        Camera(const float& width, const float& height, const short& speed, 
                const Vector2& target);
        virtual ~Camera();

        const Camera2D& getCam() const;
        const Vector2& getMouse() const;
        const Vector2& getMouseWorld() const;
        const short& getScrool() const;
    
        void update();
        void showMouseInfo(const bool& inScreen) const;
    private:
        Camera2D cam;
        short speed;
        Vector2 mouse;
        Vector2 mouseWorld;
        short scroll;

        void camColision();
};
}

#endif

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "../include/raylib.h"
#include <iostream>

namespace moss{
class Camera{
    public:
        Camera(const float& width, const float& height, const short& speed);
        virtual ~Camera();

        const Camera2D& getCam() const;
        const Vector2& getPosiMouse() const;
    
        void update();
    private:
        Camera2D cam;
        short speed;
        Vector2 posiMouse;
};
}

#endif

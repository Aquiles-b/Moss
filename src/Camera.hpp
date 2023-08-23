#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <raylib.h>
#include <iostream>

namespace moss{
class Camera{
    public:
        Camera(const float& width, const float& height, const short& speed);
        virtual ~Camera();

        Camera2D& getCam() const;
    
        void update();
    private:
        Camera2D *cam;
        short speed;
};
}

#endif

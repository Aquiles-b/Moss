#include "Camera.hpp"

moss::Camera::Camera(const float& width, const float& height, const short& speed,
        const Vector2& target)
    : speed{speed}, posiMouse{GetMousePosition()}{
    this->cam.offset = (Vector2){width / 2.0f, height / 2.0f};
    this->cam.target = target;
    this->cam.rotation = 0.0f;
    this->cam.zoom = 0.3f;
}

moss::Camera::~Camera(){
}

void moss::Camera::update(){
    this->posiMouse= GetMousePosition();
    if (IsKeyDown(KEY_S))
        this->cam.target.y += this->speed;
    if (IsKeyDown(KEY_W))
        this->cam.target.y -= this->speed;
    if (IsKeyDown(KEY_A))
        this->cam.target.x -= this->speed;
    if (IsKeyDown(KEY_D))
        this->cam.target.x += this->speed;
    short scrool = GetMouseWheelMove();
    if (scrool > 0){
        if (this->cam.zoom <= 1.0f)
            this->cam.zoom += 0.025f;
    } else if (scrool < 0){
        if (this->cam.zoom >= 0.12f)
            this->cam.zoom -= 0.025f;
    }
}

const Camera2D& moss::Camera::getCam() const{
    return this->cam;
}

const Vector2& moss::Camera::getPosiMouse() const{
    return this->posiMouse;
}

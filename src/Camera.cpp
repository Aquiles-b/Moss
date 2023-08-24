#include "Camera.hpp"

moss::Camera::Camera(const float& width,const float& height, const short& speed)
    : cam{new Camera2D{0}}, speed{speed}{
    this->cam->target = (Vector2){width / 2.0f, height / 2.0f};
    this->cam->offset = (Vector2){width / 2.0f, height / 2.0f};
    this->cam->rotation = 0.0f;
    this->cam->zoom = 0.3f;
}

moss::Camera::~Camera(){
    delete this->cam;
}

void moss::Camera::update(){
    if (IsKeyDown(KEY_S))
        this->cam->target.y += this->speed;
    if (IsKeyDown(KEY_W))
        this->cam->target.y -= this->speed;
    if (IsKeyDown(KEY_A))
        this->cam->target.x -= this->speed;
    if (IsKeyDown(KEY_D))
        this->cam->target.x += this->speed;
    switch((int)GetMouseWheelMove()){
        case 1:
            if (this->cam->zoom <= 1.0f)
                this->cam->zoom += 0.025f;
            break;
        case -1:
            if (this->cam->zoom >= 0.12f)
                this->cam->zoom -= 0.025f;
        default:
            break;
    }
}

Camera2D& moss::Camera::getCam() const{
    return *this->cam;
}

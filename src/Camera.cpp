#include "Camera.hpp"

moss::Camera::Camera(const float& width,const float& height)
    : cam{new Camera2D{0}}, speed{10}{
    this->cam->target = (Vector2){width / 2.0f, height / 2.0f};
    this->cam->offset = (Vector2){width / 2.0f, height / 2.0f};
    this->cam->rotation = 0.0f;
    this->cam->zoom = 1.0f;
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
}

Camera2D& moss::Camera::getCam() const{
    return *this->cam;
}

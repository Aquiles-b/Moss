#include "Camera.hpp"
#include <string>

moss::Camera::Camera(const float& width, const float& height, const short& speed,
        const Vector2& target)
    : speed{speed}, mouse{GetMousePosition()}, scrool{0}, 
    mouseWorld{GetScreenToWorld2D(this->mouse, this->cam)}{
    this->cam.offset = (Vector2){width / 2.0f, height / 2.0f};
    this->cam.target = target;
    this->cam.rotation = 0.0f;
    this->cam.zoom = 0.3f;
}

moss::Camera::~Camera(){
}

void moss::Camera::camColision(){
    if (this->cam.target.x < -3600.0f)
        this->cam.target.x = -3600.0f;
    if (this->cam.target.x > 3600.0f)
        this->cam.target.x = 3600.0f;
    if (this->cam.target.y < 650.0f)
        this->cam.target.y = 650.0f;
    if (this->cam.target.y > 4400.0f)
        this->cam.target.y = 4400.0f;
}

void moss::Camera::update(){
    this->cam.target.x += this->speed * (-IsKeyDown(KEY_A) + IsKeyDown(KEY_D));
    this->cam.target.y += this->speed * (-IsKeyDown(KEY_W) + IsKeyDown(KEY_S));
    camColision();

    this->mouse = GetMousePosition();
    this->mouseWorld = GetScreenToWorld2D(this->mouse, this->cam);
    this->scrool = GetMouseWheelMove();
    if (this->scrool > 0){
        if (this->cam.zoom <= 0.4f)
            this->cam.zoom += 0.025f;
    } else if (scrool < 0){
        if (this->cam.zoom >= 0.2f)
            this->cam.zoom -= 0.025f;
    }
}

void moss::Camera::showMouseInfo(const bool& inScreen) const{
    std::string posi = "World (" + std::to_string(this->mouseWorld.x);
    posi += ", " + std::to_string(this->mouseWorld.y) + ")\n\n";
    posi += "Screen (" + std::to_string(this->mouse.x);
    posi += ", " + std::to_string(this->mouse.y) + ")";

    if (inScreen)
        DrawText(posi.c_str(), 10, 30, 30, WHITE);
    else
        std::cout << posi << std::endl;
}


const Camera2D& moss::Camera::getCam() const{
    return this->cam;
}

const Vector2& moss::Camera::getMouse() const{
    return this->mouse;
}

const Vector2& moss::Camera::getMouseWorld() const{
    return this->mouseWorld; 
}

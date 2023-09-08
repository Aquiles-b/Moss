#include "../headers/Camera.hpp"

moss::Camera::Camera(const float& width, const float& height, const short& speed,
        const Vector2& target)
    : speed{speed}, mouse{GetMousePosition()}, scroll{0}{
    this->cam.offset = (Vector2){width / 2.0f, height / 2.0f};
    this->cam.target = target;
    this->cam.rotation = 0.0f;
    this->cam.zoom = 0.6f;
    this->mouseWorld = GetScreenToWorld2D(this->mouse, this->cam);
}

moss::Camera::~Camera(){
}

void moss::Camera::camColision(){
    if (this->cam.target.x < -1000.0f)
        this->cam.target.x = -1000.0f;
    if (this->cam.target.x > 1000.0f)
        this->cam.target.x = 1000.0f;
    if (this->cam.target.y < 0.0f)
        this->cam.target.y = 0.0f;
    if (this->cam.target.y > 1550.0f)
        this->cam.target.y = 1550.0f;
}

void moss::Camera::update(){
    this->cam.target.x += this->speed * (-IsKeyDown(KEY_A) + IsKeyDown(KEY_D));
    this->cam.target.y += this->speed * (-IsKeyDown(KEY_W) + IsKeyDown(KEY_S));
    camColision();

    this->mouse = GetMousePosition();
    this->mouseWorld = GetScreenToWorld2D(this->mouse, this->cam);
    this->scroll = GetMouseWheelMove();
    if (this->scroll > 0){
        if (this->cam.zoom <= 1.5f)
            this->cam.zoom += 0.05f;
    } else if (scroll < 0){
        if (this->cam.zoom >= 0.4f)
            this->cam.zoom -= 0.05f;
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

const short& moss::Camera::getScroll() const{
    return this->scroll;
}

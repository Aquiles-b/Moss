#include "include/raylib.h"
#include <string>
#include <iostream>
#include "src/Camera.hpp"
#include "src/Mapa.hpp"

void imprimePosi(const float& x, const float& y, const int& h){
    std::string posix = std::to_string(x);
    std::string posiy = std::to_string(y);
    posix = "x: " + posix + "\n\ny: " + posiy;
            DrawText(posix.c_str(), 10, h, 30, WHITE);
}

int main(void)
{
    const float width = 1280.0f;
    const float height = 720.0f;
    Vector2 posi{0};
    InitWindow(width, height, "Moss");
    SetTargetFPS(75);

    moss::Mapa *mapa{new moss::Mapa{10, 10, "img/map.png", "img/mapGrid.png"}};
    moss::Camera *cam{new moss::Camera{width, height, 40, (Vector2){0.0f, 1500.0f} }};

    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
                mapa->update();
            EndMode2D();
            DrawFPS(10, 10);
            posi = cam->getPosiMouse();
            imprimePosi(posi.x, posi.y, 30);
            posi = GetScreenToWorld2D(cam->getPosiMouse(), cam->getCam());
            imprimePosi(posi.x, posi.y, 120);
        EndDrawing();
        cam->update();
    }
    delete cam;
    delete mapa;
    CloseWindow();

    return 0;
}

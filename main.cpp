#include "include/raylib.h"
#include <string>
#include <iostream>
#include "src/Camera.hpp"
#include "src/Mapa.hpp"

void imprimePosiMouse(const moss::Camera& cam){
    std::string posix = std::to_string(cam.getPosiMouse().x);
    std::string posiy = std::to_string(cam.getPosiMouse().y);
    posix = "x: " + posix + "\n\ny: " + posiy;
            DrawText(posix.c_str(), 10, 30, 30, WHITE);
}

int main(void)
{
    const float width = 1280.0f;
    const float height = 720.0f;
    InitWindow(width, height, "Moss");
    SetTargetFPS(75);

    moss::Camera *cam{new moss::Camera{width, height, 40}};
    moss::Mapa *mapa{new moss::Mapa{10, 10, "img/map.png", "img/mapGrid.png"}};

    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
                mapa->update();
            EndMode2D();
            DrawFPS(10, 10);
            imprimePosiMouse(*cam);
        EndDrawing();
        cam->update();
    }
    delete cam;
    delete mapa;
    CloseWindow();

    return 0;
}

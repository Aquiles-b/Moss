#include "include/raylib.h"
#include <string>
#include "src/Camera.hpp"
#include "src/Mapa.hpp"

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
        EndDrawing();
        cam->update();
    }
    CloseWindow();

    return 0;
}

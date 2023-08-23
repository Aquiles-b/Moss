#include <raylib.h>
#include "src/Camera.hpp"
#include "src/Mapa.hpp"

int main(void)
{
    const float width = 1280.0f;
    const float height = 720.0f;
    InitWindow(width, height, "Moss");
    SetTargetFPS(60);

    moss::Camera *cam{new moss::Camera{width, height}};
    moss::Mapa *mapa{new moss::Mapa{10, 10}};
    mapa->imprimeMapa();

    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
            EndMode2D();
        EndDrawing();
        cam->update();
    }
    CloseWindow();

    return 0;
}

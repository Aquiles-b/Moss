#include <raylib.h>
#include <string>
#include "src/Camera.hpp"
#include "src/Mapa.hpp"

int main(void)
{
    const float width = 1280.0f;
    const float height = 720.0f;
    InitWindow(width, height, "Moss");
    SetTargetFPS(60);

    moss::Camera *cam{new moss::Camera{width, height, 45}};
    moss::Mapa *mapa{new moss::Mapa{10, 10, "img/mapa.png"}};

    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
                mapa->update();
            EndMode2D();
        DrawText(std::to_string(cam->getCam().zoom).c_str(),10, 10, 40, WHITE);
        EndDrawing();
        cam->update();
    }
    CloseWindow();

    return 0;
}

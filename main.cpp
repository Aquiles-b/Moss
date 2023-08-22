#include <raylib.h>

int main(void)
{
    InitWindow(1280, 720, "Moss");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("teeeeeeeeeeeste", 190, 200, 40, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

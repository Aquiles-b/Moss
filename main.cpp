#include "include/raylib.h"
#include <string>
#include <iostream>
#include "src/Camera.hpp"
#include "src/Map.hpp"

void imprimePosi(const float& x, const float& y, const int& h){
    std::string posix = std::to_string(x);
    std::string posiy = std::to_string(y);
    posix = "x: " + posix + "\n\ny: " + posiy;
            DrawText(posix.c_str(), 10, h, 30, WHITE);
}

int main(void){
    const float width = 1280.0f;
    const float height = 720.0f;
    Vector2 posiM{0}, posiMS{0};
    InitWindow(width, height, "Moss");
    SetTargetFPS(75);
    std::array<std::string, 6> texturesMap;
    texturesMap[moss::IdTexturesMap::MAPISO] = "img/mapIso.png";
    texturesMap[moss::IdTexturesMap::GRIDISO] = "img/gridIso.png";
    texturesMap[moss::IdTexturesMap::BUSISO] = "img/busIso.png";
    texturesMap[moss::IdTexturesMap::MAPTOP] = "img/mapTop.png";
    texturesMap[moss::IdTexturesMap::GRIDTOP] = "img/gridTop.png";
    texturesMap[moss::IdTexturesMap::BUSTOP] = "img/busTop.png";

    moss::Mapa *mapa{new moss::Mapa{texturesMap}};
    moss::Camera *cam{new moss::Camera{width, height, 40, (Vector2){0.0f, 1500.0f}}};

    while (!WindowShouldClose()){
        posiM = cam->getPosiMouse();
        posiMS = GetScreenToWorld2D(posiM, cam->getCam());

        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
                mapa->draw();
                mapa->update(posiMS);
            EndMode2D();
        EndDrawing();
        cam->update();
    }
    mapa->imprimeMapData();
    delete cam;
    delete mapa;
    CloseWindow();

    return 0;
}

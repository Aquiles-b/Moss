#include "include/raylib.h"
#include <string>
#include <iostream>
#include "src/Camera.hpp"
#include "src/Map.hpp"

int main(void){
    const float width = 1280.0f;
    const float height = 720.0f;
    Vector2 posiM{0}, posiMS{0};
    std::array<std::string, 4> texturesMap;
    texturesMap[moss::IdTexturesMap::MAPTOP] = "img/mapTop.png";
    texturesMap[moss::IdTexturesMap::GRIDTOP] = "img/gridTop.png";
    texturesMap[moss::IdTexturesMap::MAPISO] = "img/mapIso.png";
    texturesMap[moss::IdTexturesMap::GRIDISO] = "img/gridIso.png";
    std::vector<std::string> floors = {"img/busIso.png", "img/busTop.png"};

    InitWindow(width, height, "Moss");
    SetTargetFPS(75);

    moss::Mapa *mapa{new moss::Mapa{texturesMap, floors, 283.0f, 400.0f}};
    moss::Camera *cam{new moss::Camera{width, height, 50, (Vector2){0.0f, 1500.0f}}};

    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
                mapa->draw();
                mapa->update(cam->getMouseWorld(), 0);
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

#include "include/raylib.h"
#include <string>
#include <iostream>
#include "headers/Camera.hpp"
#include "headers/Component.hpp"
#include "headers/Floor.hpp"
#include "headers/Map.hpp"
#include "headers/IdTextureMap.hpp"

int main(void){
    const float width{1280.0f};
    const float height{720.0f};
    std::array<std::string, 4> texturesMap;
    texturesMap[static_cast<int>(IdTextureMap::MAPTOP)] = "img/mapTop.png";
    texturesMap[static_cast<int>(IdTextureMap::GRIDTOP)] = "img/gridTop.png";
    texturesMap[static_cast<int>(IdTextureMap::MAPISO)] = "img/mapIso.png";
    texturesMap[static_cast<int>(IdTextureMap::GRIDISO)] = "img/gridIso.png";

    InitWindow(width, height, "Moss");
    SetTargetFPS(75);

    std::vector<moss::Component*> components;
    moss::Floor *bus{new moss::Floor{"img/busIso.png"}};
    components.push_back(bus);
    moss::Component *base{new moss::Component{"img/spr_baseIso.png", 4, {-1414.0f, 0.0f}, 15}};
    moss::Map *mapa{new moss::Map{texturesMap, components, 83.3f, 118.0f}};
    moss::Camera *cam{new moss::Camera{width, height, 40, (Vector2){0.0f, 700.0f}}};

    Vector2 coordBase = {-1414.0f, 0.0f};
    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
                base->update(coordBase);
                mapa->draw();
                mapa->update(cam->getMouseWorld(), 0);
            EndMode2D();
        EndDrawing();
        cam->update();
    }
    mapa->imprimeMapData();
    delete cam;
    delete base;
    delete mapa;
    CloseWindow();

    return 0;
}

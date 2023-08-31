#include "headers/Animation.hpp"
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
    moss::Component *ram{new moss::Component{"img/ramIso.png", 1, {0.0f, 0.0f}, 1, 4, 2, {-235.0f, -161.0f}}};
    moss::Component *cpu{new moss::Component{"img/cpuIso.png", 1, {0.0f, 0.0f}, 1, 3, 3, {-200.0f, -205.0f}}};
    components.push_back(bus);
    components.push_back(ram);
    components.push_back(cpu);
    moss::Animation *base{new moss::Animation{"img/spr_baseIso.png", 4, 15, {0.0f, 0.0f}}};
    moss::Map *mapa{new moss::Map{texturesMap, components, 83.3f, 118.0f}};
    moss::Camera *cam{new moss::Camera{width, height, 40, (Vector2){0.0f, 700.0f}}};

    int comp{0};
    Vector2 coordBase{-1414.0f, 0.0f};
    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
                base->linearAnimation(coordBase, WHITE);
                mapa->draw();
                mapa->update(cam->getMouseWorld(), comp);
            EndMode2D();
        EndDrawing();
        cam->update();
        if (IsKeyPressed(KEY_ONE))
            comp = 0;
        if (IsKeyPressed(KEY_TWO))
            comp = 1;
        if (IsKeyPressed(KEY_THREE))
            comp = 2;
    }
    mapa->imprimeMapData();
    delete cam;
    delete base;
    delete mapa;
    CloseWindow();

    return 0;
}

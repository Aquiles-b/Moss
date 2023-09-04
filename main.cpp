#include "include/raylib.h"
#include <string>
#include <iostream>
#include "headers/Camera.hpp"
#include "headers/ComponentModel.hpp"
#include "headers/Map.hpp"
#include "headers/IdTextureMap.hpp"
#include "headers/Hud.hpp"
#include "headers/Animation.hpp"
#include "headers/Robot.hpp"

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

    std::vector<moss::ComponentModel*> components;
    moss::ComponentModel *bus{new moss::ComponentModel{"img/busIso.png", 1, 1, 1, 1, true}};
    moss::ComponentModel *ram{new moss::ComponentModel{"img/ramIsoBF.png", "img/ramIsoAF.png", 1, 1, 4, 2, {-235.0f, -161.0f}, false}};
    moss::ComponentModel *cpu{new moss::ComponentModel{"img/cpuIsoBF.png", "img/cpuIsoAF.png", 1, 1, 4, 4, {-200.0f, -205.0f}, false}};
    components.push_back(bus);
    components.push_back(ram);
    components.push_back(cpu);
    moss::Animation *base{new moss::Animation{"img/spr_baseIso.png", 4, 8, {0.0f, 0.0f}}};
    moss::Map *mapa{new moss::Map{texturesMap, components, 83.3f, 118.0f}};
    moss::Camera *cam{new moss::Camera{width, height, 40, {0.0f, 700.0f}}};
    moss::Hud *hud{new moss::Hud{"img/hudEditMode.png", "img/hammer.png"}};

    moss::Robot *r1{new moss::Robot("img/spr_robots.png", 3, 5, {0.0f, 0.0f}, 69, {0.0f, 0.0f})};

    Vector2 coordBase{-1414.0f, 0.0f};
    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
                base->retractAnimation(coordBase, WHITE);
                mapa->drawMapBefore();
                r1->update();
                mapa->drawMapAfter();
                mapa->update(cam->getMouseWorld(), hud->getSelected());
            EndMode2D();
            hud->draw(cam->getMouse(), mapa->getEditMode());
            hud->update(cam->getMouse(), mapa->getEditMode());
        EndDrawing();
        cam->update();
    }
    mapa->imprimeMapData();
    delete cam;
    delete base;
    delete mapa;
    delete hud;
    delete bus;
    delete ram;
    delete cpu;
    CloseWindow();

    return 0;
}

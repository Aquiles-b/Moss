#include "include/raylib.h"
#include <string>
#include <iostream>
#include "headers/Camera.hpp"
#include "headers/ComponentModel.hpp"
#include "headers/GameController.hpp"
#include "headers/Map.hpp"
#include "headers/RobotsController.hpp"
#include "headers/IdTextureMap.hpp"
#include "headers/Hud.hpp"
#include "headers/Animation.hpp"
#include "headers/Robot.hpp"
#include "headers/moss.hpp"
#include <memory>

int main(void){
    const float width{1280.0f};
    const float height{720.0f};
    InitWindow(width, height, "Moss");
    SetTargetFPS(75);

    std::unique_ptr<moss::Map> mapa = initMap();
    std::unique_ptr<moss::Camera> cam{new moss::Camera{width, height, 40, {0.0f, 700.0f}}};
    std::unique_ptr<moss::Hud> hud{new moss::Hud{"img/hudEditMode.png", "img/hammer.png"}};
    std::unique_ptr<moss::GameController> gc{new moss::GameController{mapa->getComponents()[0]->getId(), mapa->getHeightCellIso(), mapa->getSize()}};
    std::unique_ptr<moss::RobotsController> rc{new moss::RobotsController{"img/spr_robots.png", 10}};
    std::unique_ptr<moss::Animation> base{new moss::Animation{"img/spr_baseIso.png", 4, 8, {0.0f, 0.0f}}};
    Vector2 coordBase{-1414.0f, 0.0f};

    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(cam->getCam());
                base->retractAnimation(coordBase, WHITE);
                mapa->drawMapBefore(hud->getEditMode(), *gc);
                if (mapa->getChanged())
                    gc->updatePaths(mapa->getMapData(), mapa->getConstruCoords());
                rc->updateRobots(mapa->getConstruCoords(), *gc, mapa->getMapData());
                mapa->drawMapAfter(*gc);
                mapa->update(cam->getMouseWorld(), hud->getSelected(), hud->getEditMode(), *gc);
            EndMode2D();
            hud->draw(cam->getMouse());
            hud->update(cam->getMouse());
        EndDrawing();
        cam->update();
    }
    CloseWindow();

    return 0;
}

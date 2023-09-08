#ifndef ROBOTS_CONTROLLER_HPP
#define ROBOTS_CONTROLLER_HPP
#include "GameController.hpp"
#include "Robot.hpp"
#include "SimpleRobot.hpp"
#include "VirusRobot.hpp"
#include "../include/raylib.h"
#include "Construction.hpp"
#include "cellMatrix.hpp"
#include <vector>
namespace moss{
class RobotsController{
    public:
        RobotsController(const std::string& spr, const int& maxRobots);
        virtual ~RobotsController();

        void updateRobots(std::vector<struct cellMatrix> *constructions, const moss::GameController& gc,
                struct cellMatrix **mapData);
    private:
        std::vector<moss::Robot*> *robots;
        Texture2D *spr;
        int maxRobots;

        void generateRobots(std::vector<struct cellMatrix> *constructions);
        Robot *createRobot(struct paths& p);
};
}
#endif

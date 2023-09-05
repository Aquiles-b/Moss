#ifndef ROBOTS_CONTROLLER_HPP
#define ROBOTS_CONTROLLER_HPP
#include "Robot.hpp"
#include "../include/raylib.h"
#include "Construction.hpp"
#include "cellMatrix.hpp"
#include <vector>
namespace moss{
class RobotsController{
    public:
        RobotsController(const int& maxRobots);
        virtual ~RobotsController();

        void updateRobots(std::vector<struct cellMatrix> *constructions);
    private:
        std::vector<moss::Robot*> *robots;
        Texture2D spr;
        int maxRobots;
};
}
#endif

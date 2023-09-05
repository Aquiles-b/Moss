#include "../headers/RobotsController.hpp"

moss::RobotsController::RobotsController(const int& maxRobots): maxRobots{maxRobots},
    robots{new std::vector<moss::Robot*>}{

}

moss::RobotsController::~RobotsController(){
    delete this->robots;
}

void moss::RobotsController::updateRobots(std::vector<struct cellMatrix> *constructions){
    std::vector<struct cellMatrix>::iterator it = constructions->begin();
    struct paths *p;
    for ( ; it != constructions->end(); ++it){
        p = it->constInfo->getPaths();
        if(it->constInfo->getIsConnected()){
            while (it->constInfo->getRobots() != 0){
                this->robots->push_back(new moss::Robot{"img/spr_robots.png", 3, 5, {0.0f, 0.0f}, 69, p->coords[0], 0.5f,
                      p[0].coords, p[0].tam});
                it->constInfo->setRobots(it->constInfo->getRobots() - 1);
            }
        }
    }
    std::vector<moss::Robot*>::iterator itRobots = this->robots->begin();
    for ( ; itRobots != this->robots->end(); ++itRobots){
        /* if((*itRobots)->getReached()){ */
        /*     this->robots->erase(itRobots); */
        /*     delete (*itRobots); */
        /* } */
        (*itRobots)->update();
    }

}


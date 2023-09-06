#include "../headers/RobotsController.hpp"

moss::RobotsController::RobotsController(const std::string& spr, const int& maxRobots): maxRobots{maxRobots},
    robots{new std::vector<moss::Robot*>}, spr{new Texture2D}{
    *this->spr = LoadTexture(spr.c_str());
}

moss::RobotsController::~RobotsController(){
    delete this->robots;
    UnloadTexture(*this->spr);
    delete this->spr;
}

void moss::RobotsController::updateRobots(std::vector<struct cellMatrix> *constructions, 
        const moss::GameController& gc, struct cellMatrix **mapData){
    std::vector<struct cellMatrix>::iterator it = constructions->begin();
    struct paths *p;
    Vector2 posi;
    int l{0}, c{0}, auxOrigin{0};
    for ( ; it != constructions->end(); ++it){
        p = it->constInfo->getPaths();
        if(it->constInfo->getIsConnected()){
            while (GetRandomValue(1, 1000) > 970 && it->constInfo->getRobots() != 0){
                this->robots->push_back(new moss::Robot{this->spr, 3, 5, {-40.0f, -30.0f}, 69, p->coords[0], GetRandomValue(3, 7)*0.5f,
                      p[0].coords, p[0].tam});
                it->constInfo->setRobots(it->constInfo->getRobots() - 1);
            }
        }
    }
    std::vector<moss::Robot*>::iterator aux, itRobots = this->robots->begin();
    while (itRobots != this->robots->end()){
        (*itRobots)->update();
        posi = (*itRobots)->getPosi();
        gc.mapToMatrixCoord(posi.x, posi.y, l, c);
        /* if (mapData[l][c].value == -1){ */
        /*     itRobots = this->robots->erase(itRobots); */
        /* } */
        if((*itRobots)->getReached()){
            auxOrigin = mapData[l][c].cOrigin;
            l = mapData[l][c].lOrigin;
            c = auxOrigin;
            mapData[l][c].constInfo->increaseOneRobot();
            itRobots = this->robots->erase(itRobots);
        } else{
            itRobots++;
        }
    }

}


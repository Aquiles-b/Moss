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

void moss::RobotsController::generateRobots(std::vector<struct cellMatrix> *constructions){
    struct paths p;
    std::vector<struct cellMatrix>::iterator it = constructions->begin();
    for ( ; it != constructions->end(); ++it){
        if(it->constInfo->getIsConnected()){
            p = it->constInfo->getRandomPath();
            while (GetRandomValue(1, 1000) > 970 && it->constInfo->getRobots() != 0){
                this->robots->push_back(new moss::Robot{this->spr, 3, 5, {-40.0f, -50.0f}, 69, p.coords[0], GetRandomValue(3, 7)*0.5f,
                      p.coords, p.tam});
                it->constInfo->setRobots(it->constInfo->getRobots() - 1);
            }
        }
    }
}

void moss::RobotsController::updateRobots(std::vector<struct cellMatrix> *constructions, 
        const moss::GameController& gc, struct cellMatrix **mapData){
    Vector2 posi;
    int l{0}, c{0}, auxOrigin{0};
    this->generateRobots(constructions);

    std::vector<moss::Robot*>::iterator itRobots = this->robots->begin();
    while (itRobots != this->robots->end()){
        (*itRobots)->update();
        posi = (*itRobots)->getPosi();
        gc.mapToMatrixCoord(posi.x, posi.y, l, c);
        if (mapData[l][c].value == -1){
            itRobots = this->robots->erase(itRobots);
        } else if((*itRobots)->getReached()){
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


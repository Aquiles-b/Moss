#include "../headers/GameController.hpp"

moss::GameController::GameController(const int64_t& floorId, const int& heightCellIso, const int& size): floorId{floorId},
    numPaths{4}, paths{new struct paths[4]}, heightCellIso{heightCellIso}, footPrint{new short*[size]},
    size{size}{
    for (int i = 0; i < this->numPaths; ++i){
        this->paths[i].coords = new Vector2[128];
        this->paths[i].tam = 0;
    }
    for (int i = 0; i < size; ++i){
        this->footPrint[i] = new short[size];
        for (int j = 0; j < size; ++j)
            this->footPrint[i][j] = 0;
    }
}

moss::GameController::~GameController(){
    for (int i = 0; i < this->numPaths; ++i)
        delete[] this->paths[i].coords;
    delete[] this->paths;
    for (int i = 0; i < size; ++i)
        delete[] this->footPrint[i];
    delete[] this->footPrint;
}

void moss::GameController::updatePaths(struct cellMatrix **mtx, 
                            std::vector<struct cellMatrix> *construCoords){
    std::vector<struct cellMatrix>::iterator it = construCoords->begin();
    int pathIndex{0}, numCoord{0};
    int cDoor{0}, lDoor{0};
    short direction{-1};
    for ( ; it != construCoords->end(); ++it){
        clearFootPrint();
        clearPaths();
        lDoor = it->lOrigin - it->constInfo->getLDoor();
        cDoor = it->cOrigin - it->constInfo->getCDoor();
        this->footPrint[lDoor][cDoor] = 1;
        addCoordPath(lDoor, cDoor, pathIndex, numCoord);
        findPath(lDoor, cDoor, mtx, pathIndex, numCoord, direction);
        if (pathIndex > 0){
            it->constInfo->setPaths(this->paths, pathIndex);
            it->constInfo->setIsConnected(true);
        }
        else {
            it->constInfo->setIsConnected(false);
        }
        numCoord = pathIndex = 0;
    }
}

void moss::GameController::findPath(const int& l, const int& c, struct cellMatrix **mtx,
                                    int& pathIndex, int& numCoord, short direction){
    Vector2 coordIso{0};
    bool resul{false};
    if (isInsideLimit(l, c) && isAllowedWalk(l, c, mtx)){
        if (mtx[l][c].value == -3){
            addCoordPath(l, c, pathIndex, numCoord);
            this->paths[pathIndex].tam = numCoord;
            ++pathIndex;
            if (pathIndex < this->numPaths){
                for (int i = 0; i < numCoord; ++i){
                    this->paths[pathIndex].coords[i].x = this->paths[pathIndex-1].coords[i].x;
                    this->paths[pathIndex].coords[i].y = this->paths[pathIndex-1].coords[i].y;
                }
            }
            return;
        }
    }
    this->footPrint[l][c] = 1;
    if (isInsideLimit(l+1, c) && isAllowedWalk(l+1, c, mtx)){
        if (direction != 0){
            addCoordPath(l+1, c, pathIndex, numCoord);
            direction = 0;
        }
        findPath(l+1, c, mtx, pathIndex, numCoord, direction);
    }
    if (isInsideLimit(l, c+1) && isAllowedWalk(l, c+1, mtx)){
        if (direction != 1){
            addCoordPath(l, c+1, pathIndex, numCoord);
            direction = 1;
        }
        findPath(l, c+1, mtx, pathIndex, numCoord, direction);
    }
    if (isInsideLimit(l-1, c) && isAllowedWalk(l-1, c, mtx)){
        if (direction != 2){
            addCoordPath(l-1, c, pathIndex, numCoord);
            direction = 2;
        }
        findPath(l-1, c, mtx, pathIndex, numCoord, direction);
    }
    if (isInsideLimit(l, c-1) && isAllowedWalk(l, c-1, mtx)){
        if (direction != 3){
            addCoordPath(l, c-1, pathIndex, numCoord);
            direction = 3;
        }
        findPath(l, c-1, mtx, pathIndex, numCoord, direction);
    }
    --numCoord;
}

void moss::GameController::clearFootPrint(){
    for (int i = 0; i < this->size; ++i){
        for (int j = 0; j < this->size; ++j)
            this->footPrint[i][j] = 0;
    }
}

void moss::GameController::addCoordPath(const int& l, const int& c, const int& pathIndex, int& numCoord){
    Vector2 coordIso{0};
    matrixToMapCoord(l, c, coordIso);
    this->paths[pathIndex].coords[numCoord] = coordIso;
    ++numCoord;
}

void moss::GameController::matrixToMapCoord(const int& l, const int& c, Vector2& coordIso) const{
    coordIso.x = (c - l) * this->heightCellIso;
    coordIso.y = (c + l) * this->heightCellIso / 2.0f;
}

void moss::GameController::mapToMatrixCoord(const float& x, const float& y, int& l, int& c) const{
    l = -ceil((x * 0.5f - y) / this->heightCellIso);
    c = floor((x * 0.5f + y) / this->heightCellIso);
}

bool moss::GameController::isInsideLimit(const int& l, const int& c) const{
    if (l >= 0 && l < this->size && c >= 0 && c < this->size)
        return true;
    return false;
}

bool moss::GameController::isAllowedWalk(const int& l, const int& c, struct cellMatrix **mtx) const{
    if ((mtx[l][c].value == -3 || mtx[l][c].value == this->floorId) && this->footPrint[l][c] == 0)
        return true;
    return false;
}

void moss::GameController::clearPaths(){
    for (int i = 0; i < this->numPaths; ++i)
        this->paths[i].tam = 0;
}

const bool& moss::GameController::getIsChanged() const{
    return this->isChanged;
}

void moss::GameController::setIsChanged(const bool& isChanged){
    this->isChanged = isChanged;
}

#include "../headers/GameController.hpp"

moss::GameController::GameController(const int64_t& floorId, const int& heightCellIso, const int& size): floorId{floorId},
    numPaths{4}, paths{new struct paths[4]}, heightCellIso{heightCellIso}, footPrint{new short*[size]},
    size{size}{
    for (int i = 0; i < this->numPaths; ++i)
        this->paths[i].coords = new Vector2[128];
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
    for ( ; it != construCoords->end(); ++it){
        clearFootPrint();
        lDoor = it->lOrigin - it->constInfo->getLDoor();
        cDoor = it->cOrigin - it->constInfo->getCDoor();
        this->footPrint[lDoor][cDoor] = 1;
        addCoordPath(lDoor, cDoor, pathIndex, numCoord);
        if(findPath(lDoor, cDoor, mtx, pathIndex, numCoord)){
            it->constInfo->setPaths(this->paths, pathIndex);
            it->constInfo->setIsConnected(true);
        }
        else {
            it->constInfo->setIsConnected(false);
        }
        numCoord = pathIndex = 0;
    }
}

bool moss::GameController::findPath(const int& l, const int& c, struct cellMatrix **mtx,
                                    int& pathIndex, int& numCoord){
    Vector2 coordIso{0};
    bool resul{false};
    if (pathIndex == this->numPaths)
        return true;
    if (isInsideLimit(l, c) && isAllowedWalk(l, c, mtx)){
        if (mtx[l][c].value == -3){
            addCoordPath(l, c, pathIndex, numCoord);
            this->paths[pathIndex].tam = numCoord;
            ++pathIndex;
            return true;
        }
    }
    this->footPrint[l][c] = 1;
    if (isInsideLimit(l+1, c) && isAllowedWalk(l+1, c, mtx)){
        addCoordPath(l+1, c, pathIndex, numCoord);
        resul = findPath(l+1, c, mtx, pathIndex, numCoord);
    }
    if (isInsideLimit(l, c+1) && isAllowedWalk(l, c+1, mtx)){
        addCoordPath(l, c+1, pathIndex, numCoord);
        resul = findPath(l, c+1, mtx, pathIndex, numCoord);
    }
    if (isInsideLimit(l-1, c) && isAllowedWalk(l-1, c, mtx)){
        addCoordPath(l-1, c, pathIndex, numCoord);
        resul = findPath(l-1, c, mtx, pathIndex, numCoord);
    }
    if (isInsideLimit(l, c-1) && isAllowedWalk(l, c-1, mtx)){
        addCoordPath(l, c-1, pathIndex, numCoord);
        resul = findPath(l, c-1, mtx, pathIndex, numCoord);
    }
    --numCoord;
    return resul;
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

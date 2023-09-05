#include "../headers/Map.hpp"

using namespace moss;

moss::Map::Map(const std::array<std::string, 4>& textures, const std::vector<ComponentModel*>& components,
                const float& widthCellTop, const float& widthCellIso)
    :construCoords{new std::vector<struct cellMatrix>}{
    for (short i = 0; i < textures.size(); ++i)
        this->textures[i] = LoadTexture(textures[i].c_str());
    this->components = components;

    this->size = floor(this->textures[static_cast<int>(IdTextureMap::MAPTOP)].width / widthCellTop);
    this->heightCellIso = ceil(widthCellIso / 2.0f);
    coordMap.x = -this->textures[static_cast<int>(IdTextureMap::MAPISO)].width / 2.0f;
    coordMap.y = 0.0f;

    this->mapData = new struct cellMatrix*[this->size];
    for (int i = 0; i < this->size; ++i){
        this->mapData[i] = new struct cellMatrix[this->size];
        for (int j = 0; j < this->size; ++j){
            this->mapData[i][j].value = -1;
            this->mapData[i][j].lOrigin = -1;
            this->mapData[i][j].cOrigin = -1;
            this->mapData[i][j].constInfo = nullptr;
        }
    }
}

moss::Map::~Map(){
    for (int i = 0; i < this->textures.size(); ++i)
        UnloadTexture(this->textures[i]);
    for (int i = 0; i < this->size; ++i){
        for (int j = 0; j < this->size; ++j){
            if (this->mapData[i][j].constInfo != nullptr)
                delete this->mapData[i][j].constInfo;
        }
        delete[] this->mapData[i];
    }
    delete[] this->mapData;
    delete this->construCoords;
}
 
void moss::Map::imprimeMapData() const{
    for (int i = 0; i < this->size; ++i){
        for (int j = 0; j < this->size; ++j)
            std::cout << this->mapData[i][j].value << "  ";
        std::cout << std::endl;
    }
}

void moss::Map::drawMapBefore(const bool& editMode, const moss::GameController& gc) const{
    Vector2 coordIso{0};
    struct cellMatrix aux{0};
    this->construCoords->clear();
    DrawTexture(this->textures[static_cast<int>(IdTextureMap::MAPISO)], this->coordMap.x, this->coordMap.y, WHITE);
    if (editMode)
        DrawTexture(this->textures[static_cast<int>(IdTextureMap::GRIDISO)], this->coordMap.x, this->coordMap.y, WHITE);
    for (unsigned short i = 0; i < this->size; ++i){
        for (unsigned short j = 0; j < this->size; ++j){
            if (this->mapData[i][j].value > -1){
                gc.matrixToMapCoord(i, j, coordIso);
                aux = this->mapData[i][j];
                if (this->components[aux.value]->getIsTile()){
                    this->components[aux.value]->updateBefore(coordIso, WHITE);
                } else {
                    this->construCoords->push_back(aux);
                    if (aux.constInfo->getIsConnected())
                        aux.constInfo->setColor(WHITE);
                    else
                        aux.constInfo->setColor(GRAY);
                    this->components[aux.value]->updateBefore(coordIso, aux.constInfo->getColor());
                }
            }
        }
    }
}
void moss::Map::drawMapAfter(const moss::GameController& gc) const{
    Vector2 coordIso{0};
    std::vector<struct cellMatrix>::iterator it = this->construCoords->begin();
    for ( ; it != this->construCoords->end(); ++it){
        gc.matrixToMapCoord(it->lOrigin, it->cOrigin, coordIso);
        this->components[it->value]->updateAfter(coordIso, it->constInfo->getColor());
    }
}

void moss::Map::fillColisionMatrix(const int& l, const int& c, const int& widthComp, 
        const int& heightComp, const int& numFill, const int& lOrigin, const int& cOrigin){
    for (int i = 0; i < widthComp; ++i){
        for (int j = 0; j < heightComp; ++j){
                this->mapData[l-i][c-j].value = numFill;
                this->mapData[l-i][c-j].lOrigin = lOrigin;
                this->mapData[l-i][c-j].cOrigin = cOrigin;
        }
    }
}

bool moss::Map::tryDrawInMatrix(ComponentModel* component, const int& l, const int& c, Vector2& coordIso){
    int widthComp{component->getWidth()};
    int heightComp{component->getHeight()};
    int lDoor{component->getLDoor()}, cDoor{component->getCDoor()};
    if(!isComponentInsideLimits(l, c, widthComp, heightComp) || colision(l, c, widthComp, heightComp))
        return false;
    component->updateBefore(coordIso, WHITE);
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        this->setChanged(true);
        fillColisionMatrix(l, c, widthComp, heightComp, -2, l, c);
        this->mapData[l][c].value = component->getId();
        if (!component->getIsTile()){
            this->mapData[l][c].constInfo = new Construction(lDoor, cDoor);
            this->mapData[l-lDoor][c-cDoor].value = -3;
        }
    }
    return true;
}

bool moss::Map::isComponentInsideLimits(const int& l, const int& c, const int& width, const int& height) const{
    if (l - (width-1) < 0 || c - (height-1) < 0){
        return false;
    }
    return true;
}

bool moss::Map::colision(const int& l, const int& c, const int& width, const int& height) const{
    int aux{-1};
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
           aux = this->mapData[l-i][c-j].value;
            if (aux > -1)
                return true;
            else if (aux == -2)
                return true;
        }
    }
    return false;
}

void moss::Map::destructionMode(int l, int c, const moss::GameController& gc){
    Vector2 coordIso{0};
    struct cellMatrix compIndex{this->mapData[l][c]};
    int widthComp{0}, heightComp{0};
    if (compIndex.value == -1)
        return;
    if (compIndex.value <= -2){
        l = compIndex.lOrigin;
        c = compIndex.cOrigin;
        compIndex = this->mapData[l][c];
    }
    gc.matrixToMapCoord(l, c, coordIso);
    widthComp = this->components[compIndex.value]->getWidth();
    heightComp = this->components[compIndex.value]->getHeight();
    this->components[compIndex.value]->updateBefore(coordIso, RED);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        this->setChanged(true);
        if (compIndex.constInfo != nullptr){
            delete compIndex.constInfo;
            compIndex.constInfo = nullptr;
        }
        fillColisionMatrix(l, c, widthComp, heightComp, -1, -1, -1);
    }
}

void moss::Map::update(const Vector2& mouse, const int& comp, const bool& editMode, 
        const moss::GameController& gc){
    this->setChanged(false);
    Vector2 coordIso{0};
    int l{0}, c{0};
    gc.mapToMatrixCoord(mouse.x, mouse.y, l, c);
    gc.matrixToMapCoord(l, c, coordIso);
    if (editMode) {
        if (l >=0 && l < this->size && c >= 0 && c < this->size){
            if (comp == -1)
                destructionMode(l, c, gc);
            else if (!tryDrawInMatrix(this->components[comp], l, c, coordIso))
                this->components[comp]->updateBefore(coordIso, RED);
        }
    }
}

const int& moss::Map::getHeightCellIso() const{
    return this->heightCellIso;
}

const int& moss::Map::getSize() const{
    return this->size;
}

struct cellMatrix **Map::getMapData(){
    return this->mapData;
}

std::vector<struct cellMatrix> *moss::Map::getConstruCoords(){
    return this->construCoords;
}

const bool& moss::Map::getChanged() const{
    return this->changed;
}

void moss::Map::setChanged(const bool& changed){
    this->changed = changed;
}

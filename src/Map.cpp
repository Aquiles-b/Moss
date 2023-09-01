#include "../headers/Map.hpp"
#include "../headers/IdTextureMap.hpp"


moss::Map::Map(const std::array<std::string, 4>& textures, const std::vector<Component*>& components,
                const float& widthCellTop, const float& widthCellIso)
    :editMode{false}{
    for (short i = 0; i < textures.size(); ++i)
        this->textures[i] = LoadTexture(textures[i].c_str());
    this->components = components;

    this->size = floor(this->textures[static_cast<int>(IdTextureMap::MAPTOP)].width / widthCellTop);
    this->heightCellIso = widthCellIso / 2.0f;
    coordMap.x = -this->textures[static_cast<int>(IdTextureMap::MAPISO)].width / 2.0f;
    coordMap.y = 0.0f;

    this->mapData = new struct cellMatrix*[this->size];
    for (int i = 0; i < this->size; ++i){
        this->mapData[i] = new struct cellMatrix[this->size];
        for (int j = 0; j < this->size; ++j){
            this->mapData[i][j].value = -1;
            this->mapData[i][j].lOrigin = -1;
            this->mapData[i][j].cOrigin = -1;
        }
    }
}

moss::Map::~Map(){
    for (int i = 0; i < this->textures.size(); ++i)
        UnloadTexture(this->textures[i]);
    for (int i = 0; i < this->size; ++i)
        delete[] this->mapData[i];
    delete[] this->mapData;
}
 
void moss::Map::imprimeMapData() const{
    for (int i = 0; i < this->size; ++i){
        for (int j = 0; j < this->size; ++j)
            std::cout << this->mapData[i][j].value << "  ";
        std::cout << std::endl;
    }
}

void moss::Map::matrixToMapCoord(const int& l, const int& c, Vector2& coordIso) const{
    coordIso.x = (c - l) * this->heightCellIso;
    coordIso.y = (c + l) * this->heightCellIso / 2.0f;
}

void moss::Map::mapToMatrixCoord(const float& x, const float& y, int& l, int& c) const{
    l = -ceil((x * 0.5f - y) / this->heightCellIso);
    c = floor((x * 0.5f + y) / this->heightCellIso);
}

void moss::Map::draw() const{
    Vector2 coordIso{0};
    DrawTexture(this->textures[static_cast<int>(IdTextureMap::MAPISO)], this->coordMap.x, this->coordMap.y, WHITE);
    if (this->editMode)
        DrawTexture(this->textures[static_cast<int>(IdTextureMap::GRIDISO)], this->coordMap.x, this->coordMap.y, WHITE);
    for (unsigned short i = 0; i < this->size; ++i){
        for (unsigned short j = 0; j < this->size; ++j){
            if (this->mapData[i][j].value > -1){
                matrixToMapCoord(i, j, coordIso);
                this->components[this->mapData[i][j].value]->update(coordIso, WHITE);
            }
        }
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

bool moss::Map::tryDrawInMatrix(Component* component, const int& l, const int& c, Vector2& coordIso){
    int widthComp{0}, heightComp{0};
    widthComp = component->getWidth();
    heightComp = component->getHeight();
    if(!isComponentInsideLimits(l, c, widthComp, heightComp) || colision(l, c, widthComp, heightComp))
        return false;
    component->update(coordIso, WHITE);
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        fillColisionMatrix(l, c, widthComp, heightComp, -2, l, c);
        this->mapData[l][c].value = component->getId();
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

void moss::Map::destructionMode(int l, int c){
    Vector2 coordIso{0};
    struct cellMatrix compIndex{this->mapData[l][c]};
    int widthComp{0}, heightComp{0};
    if (compIndex.value == -1)
        return;
    if (compIndex.value == -2){
        l = compIndex.lOrigin;
        c = compIndex.cOrigin;
        compIndex = this->mapData[l][c];
    }
    matrixToMapCoord(l, c, coordIso);
    widthComp = this->components[compIndex.value]->getWidth();
    heightComp = this->components[compIndex.value]->getHeight();
    this->components[compIndex.value]->update(coordIso, RED);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        fillColisionMatrix(l, c, widthComp, heightComp, -1, -1, -1);
}

void moss::Map::update(const Vector2& mouse, const int& comp){
    Vector2 coordIso{0};
    int l{0}, c{0};
    mapToMatrixCoord(mouse.x, mouse.y, l, c);
    matrixToMapCoord(l, c, coordIso);

    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode) {
        if (l >=0 && l < this->size && c >= 0 && c < this->size){
            if (comp == -1)
                destructionMode(l, c);
            else if (!tryDrawInMatrix(this->components[comp], l, c, coordIso))
                this->components[comp]->update(coordIso, RED);
        }
    }
}

const bool moss::Map::getEditMode() const{
    return this->editMode;
}

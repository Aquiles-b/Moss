#include "Map.hpp"

using namespace moss;

Mapa::Mapa(const std::array<std::string, 4>& textures, const std::vector<std::string>& floors,
                const float& widthCellTop, const float& widthCellIso)
    :editMode{false}{
    for (short i = 0; i < textures.size(); ++i)
        this->textures[i] = LoadTexture(textures[i].c_str());
    for (int i = 0; i < floors.size(); ++i)
        this->floors.push_back(LoadTexture(floors[i].c_str()));

    this->size = floor(this->textures[IdTexturesMap::MAPTOP].width / widthCellTop);
    this->heightCellIso = widthCellIso / 2.0f;
    coordMap.x = -this->textures[IdTexturesMap::MAPISO].width / 2.0f;
    coordMap.y = 0.0f;

    this->mapData = new int*[this->size];
    for (int i = 0; i < this->size; ++i){
        this->mapData[i] = new int[this->size];
        for (int j = 0; j < this->size; ++j)
            this->mapData[i][j] = -1;
    }
}

Mapa::~Mapa(){
    for (int i = 0; i < this->textures.size(); ++i)
        UnloadTexture(this->textures[i]);
    for (int i = 0; i < this->floors.size(); ++i)
        UnloadTexture(this->floors[i]);
}
 
int **Mapa::getMapData() const{
    return this->mapData;
}

void Mapa::imprimeMapData() const{
    for (int i = 0; i < this->size; ++i){
        for (int j = 0; j < this->size; ++j)
            std::cout << this->mapData[i][j] << "  ";
        std::cout << std::endl;
    }
}

void Mapa::matrixToMapCoord(const short& l, const short& c, Vector2& coordIso) const{
    coordIso.x = (c - l) * this->heightCellIso;
    coordIso.y = (c + l) * this->heightCellIso / 2.0f;
}

void Mapa::mapToMatrixCoord(const float& x, const float& y, struct matrixCoord& coordIso) const{
    coordIso.l = floor(abs((x * 0.5f - y) / this->heightCellIso));
    coordIso.c = floor((x * 0.5f + y) / this->heightCellIso);
}

void Mapa::draw() const{
    Vector2 coordIso{0};
    DrawTexture(this->textures[IdTexturesMap::MAPISO], this->coordMap.x, this->coordMap.y, WHITE);
    if (this->editMode)
        DrawTexture(this->textures[IdTexturesMap::GRIDISO], this->coordMap.x, this->coordMap.y, WHITE);
    for (unsigned short i = 0; i < this->size; ++i){
        for (unsigned short j = 0; j < this->size; ++j){
            if (this->mapData[i][j] != -1){
                matrixToMapCoord(i, j, coordIso);
                coordIso.x -= this->heightCellIso;
                DrawTexture(this->floors[this->mapData[i][j]], coordIso.x, coordIso.y, WHITE);
            }
        }
    }
}

void Mapa::update(const Vector2& mouse, const int& floor){
    Vector2 coordIso{0};
    struct matrixCoord coordMtx{0};
    mapToMatrixCoord(mouse.x, mouse.y, coordMtx);

    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode) {
        if (coordMtx.l < this->size && coordMtx.c >= 0 && coordMtx.c < this->size){
            matrixToMapCoord(coordMtx.l, coordMtx.c, coordIso);
            coordIso.x -= this->heightCellIso;
            DrawTexture(this->floors[floor], coordIso.x, coordIso.y, WHITE);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && this->mapData[coordMtx.l][coordMtx.c] == -1)
                this->mapData[coordMtx.l][coordMtx.c] = floor;
        }
    }
}

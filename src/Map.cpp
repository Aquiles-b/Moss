#include "Map.hpp"

using namespace moss;

Mapa::Mapa(const std::array<std::string, 4>& textures, const float& widthCellTop,
                const float& widthCellIso)
    :editMode{false}{
        for (short i = 0; i < this->textures.size(); ++i)
            this->textures[i] = LoadTexture(textures[i].c_str());

        this->size = floor(this->textures[IdTexturesMap::MAPTOP].width / widthCellTop);
        this->mapData = new short*[this->size];
        this->heightCellIso = widthCellIso / 2.0f;
        coordMap.x = -this->textures[IdTexturesMap::MAPISO].width / 2.0f;
        coordMap.y = 0.0f;
    for (int i = 0; i < this->size; ++i)
        mapData[i] = new short[this->size]{0};
}

Mapa::~Mapa(){
    for (short i = 0; i < this->textures.size(); ++i)
        UnloadTexture(this->textures[i]);
    for (unsigned short i = 0; i < this->size; ++i)
        delete[] this->mapData[i];
    delete[] this->mapData;
}
 
short **Mapa::getMapData() const{
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
            if (this->mapData[i][j] == IdTexturesMap::CELLISO) {
                matrixToMapCoord(i, j, coordIso);
                coordIso.x -= this->heightCellIso;
                DrawTexture(this->textures[IdTexturesMap::CELLISO], coordIso.x, coordIso.y, WHITE);
            }
        }
    }
}

void Mapa::update(const Vector2& mouse){
    Vector2 coordIso{0};
    struct matrixCoord coordMatrix{0};
    mapToMatrixCoord(mouse.x, mouse.y, coordMatrix);

    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode) {
        if (coordMatrix.l < this->size && coordMatrix.c >= 0 && coordMatrix.c < this->size){
            matrixToMapCoord(coordMatrix.l, coordMatrix.c, coordIso);
            coordIso.x -= this->heightCellIso;
            DrawTexture(this->textures[IdTexturesMap::CELLISO], coordIso.x, coordIso.y, WHITE);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    this->mapData[coordMatrix.l][coordMatrix.c] = IdTexturesMap::CELLISO;
        }
    }
}

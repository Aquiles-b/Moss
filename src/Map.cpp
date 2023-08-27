#include "Map.hpp"

using namespace moss;

Mapa::Mapa(const std::array<std::string, 6>& textures)
    :editMode{false}{
        for (short i = 0; i < this->textures.size(); ++i)
            this->textures[i] = LoadTexture(textures[i].c_str());

        unsigned short size = floor(this->textures[IdTexturesMap::MAPTOP].width / this->textures[IdTexturesMap::BUSTOP].width);
        this->mapData = new short*[size];
        this->tamCelulaIso = this->textures[IdTexturesMap::BUSISO].height;
        this->size = size;
        coordMap.x = -this->textures[IdTexturesMap::MAPISO].width / 2.0f;
        coordMap.y = 0.0f;
    for (int i = 0; i < size; ++i)
        mapData[i] = new short[size]{0};
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

void Mapa::converteMatrizMapa(const short& l, const short& c, Vector2& coordIso) const{
    coordIso.x = (c - l - 1) * this->tamCelulaIso;
    coordIso.y = (l + c) * this->tamCelulaIso / 2.0f;
}

void Mapa::draw() const{
    float x{0}, y{0};
    Vector2 coordIso{0};
    DrawTexture(this->textures[IdTexturesMap::MAPISO], this->coordMap.x, this->coordMap.y, WHITE);
    if (this->editMode)
        DrawTexture(this->textures[IdTexturesMap::GRIDISO], this->coordMap.x, this->coordMap.y, WHITE);
    for (unsigned short i = 0; i < this->size; ++i){
        for (unsigned short j = 0; j < this->size; ++j){
            if (this->mapData[i][j] == IdTexturesMap::BUSISO) {
                converteMatrizMapa(i, j, coordIso);
                DrawTexture(this->textures[IdTexturesMap::BUSISO], coordIso.x, coordIso.y, WHITE);
            }
        }
    }
}

void Mapa::update(const Vector2& mouse){
    short l = floor(abs((mouse.x * 0.5f - mouse.y) / this->tamCelulaIso));
    short c = floor((mouse.x * 0.5f + mouse.y) / this->tamCelulaIso);
    Vector2 coordIso{0};

    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode) {
        if (l < this->size && c >= 0 && c < this->size){
            converteMatrizMapa(l, c, coordIso);
            DrawTexture(this->textures[IdTexturesMap::BUSISO], coordIso.x, coordIso.y, WHITE);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    this->mapData[l][c] = IdTexturesMap::BUSISO;
        }
    }
}

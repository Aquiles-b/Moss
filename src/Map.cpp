#include "Map.hpp"
#include "Component.hpp"

using namespace moss;

Mapa::Mapa(const std::array<std::string, 4>& textures, const std::vector<Component*>& components,
                const float& widthCellTop, const float& widthCellIso)
    :editMode{false}{
    for (short i = 0; i < textures.size(); ++i)
        this->textures[i] = LoadTexture(textures[i].c_str());
    this->components = components;

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

void Mapa::matrixToMapCoord(const int& l, const int& c, Vector2& coordIso) const{
    coordIso.x = (c - l) * this->heightCellIso;
    coordIso.y = (c + l) * this->heightCellIso / 2.0f;
}

void Mapa::mapToMatrixCoord(const float& x, const float& y, int& l, int& c) const{
    l = floor(abs((x * 0.5f - y) / this->heightCellIso));
    c = floor((x * 0.5f + y) / this->heightCellIso);
}

void Mapa::draw() const{
    Vector2 coordIso{0};
    DrawTexture(this->textures[IdTexturesMap::MAPISO], this->coordMap.x, this->coordMap.y, WHITE);
    if (this->editMode)
        DrawTexture(this->textures[IdTexturesMap::GRIDISO], this->coordMap.x, this->coordMap.y, WHITE);
    for (unsigned short i = 0; i < this->size; ++i){
        for (unsigned short j = 0; j < this->size; ++j){
            if (this->mapData[i][j] > -1){
                matrixToMapCoord(i, j, coordIso);
                coordIso.x -= this->heightCellIso;
                this->components[this->mapData[i][j]]->update(coordIso);
            }
        }
    }
}

void Mapa::update(const Vector2& mouse, const int& comp){
    Vector2 coordIso{0};
    int l{0}, c{0};
    mapToMatrixCoord(mouse.x, mouse.y, l, c);

    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode) {
        if (l < this->size && c >= 0 && c < this->size){
            matrixToMapCoord(l, c, coordIso);
            coordIso.x -= this->heightCellIso;
            this->components[comp]->update(coordIso);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && this->mapData[l][c] == -1)
                this->mapData[l][c] = this->components[comp]->getId();
        }
    }
}

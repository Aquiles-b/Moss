#include "Mapa.hpp"

moss::Mapa::Mapa(const unsigned short& size, const std::string& map, 
        const std::string& mapGrid, const std::string& bus)
    :mapData{new short*[size]}, size{size}, editMode{false}{
        this->map = LoadTexture(map.c_str());
        this->mapGrid = LoadTexture(mapGrid.c_str());
        this->bus = LoadTexture(bus.c_str());
        coordMap.x = -this->map.width / 2.0f;
        coordMap.y = 0.0f;
    for (int i = 0; i < size; ++i)
        mapData[i] = new short[size]{0};
}

moss::Mapa::~Mapa(){
    UnloadTexture(this->map);
    UnloadTexture(this->mapGrid);
    for (int i = 0; i < this->size; ++i)
        delete[] this->mapData[i];
    delete[] this->mapData;
}
 
short **moss::Mapa::getMapData() const{
    return this->mapData;
}

void moss::Mapa::imprimeMapData() const{
    for (int i = 0; i < this->size; ++i){
        for (int j = 0; j < this->size; ++j)
            std::cout << this->mapData[i][j] << "  ";
        std::cout << std::endl;
    }
}

void moss::Mapa::update(const Vector2& mouse){
    float isoX = (mouse.x * 0.5f - mouse.y) / this->bus.height;
    float isoY = (mouse.x * 0.5f + mouse.y) / this->bus.height;
    short l = floor(abs(isoX));
    short c = floor(isoY);
    float x{0}, y{0};

    DrawTexture(this->map, this->coordMap.x, this->coordMap.y, WHITE);
    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode) {
        DrawTexture(this->mapGrid, this->coordMap.x, this->coordMap.y, WHITE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            if (isoX < this->size && isoY >=0 && isoY < this->size)
                this->mapData[l][c] = 1;
        }
        if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)){
            x = (c - (l + 1)) * this->bus.height;
            y = (l + c) * this->bus.height / 2.0f;
            /* DrawTexture(this->bus, x, y, WHITE); */
        }
    }
    for (short i = 0; i < this->size; ++i){
        for (short j = 0; j < this->size; ++j){
            if (this->mapData[i][j] == 1) {
                x = (j - (i + 1)) * this->bus.height;
                y = (i + j) * this->bus.height / 2.0f;
                DrawTexture(this->bus, x, y, WHITE);
            }
        }
    }
}

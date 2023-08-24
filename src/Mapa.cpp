#include "Mapa.hpp"

moss::Mapa::Mapa(const unsigned short& size, const std::string& map, 
        const std::string& mapGrid, const std::string& bus)
    :mapData{new short*[size]}, size{size}, editMode{false}{
        this->map = LoadTexture(map.c_str());
        this->mapGrid = LoadTexture(mapGrid.c_str());
        this->bus = LoadTexture(bus.c_str());
        coordMap.x = -3192.0f;
        coordMap.y = -20.0f;
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
    int isoX = abs(floor((mouse.x * 0.5f - mouse.y) / 122.0f) + 1);
    int isoY = floor( (mouse.x * 0.5f + mouse.y) / 122.0f);
    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode) {
        DrawTexture(this->mapGrid, this->coordMap.x, this->coordMap.y, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (isoX <= 24 && isoY >=0 && isoY <= 24)
                this->mapData[isoX][isoY] = 1;
        }
        if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
            DrawTexture(this->bus, mouse.x - this->bus.width / 2.0f, mouse.y - this->bus.height / 2.0f, WHITE);
    }
    else {
        DrawTexture(this->map, this->coordMap.x, this->coordMap.y, WHITE);
    }
    for (short i = 0; i < this->size; ++i){
        for (short j = 0; j < this->size; ++j){
            if (this->mapData[i][j] == 1)
                continue;
        }
    }
}

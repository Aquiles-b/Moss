#include "Mapa.hpp"

moss::Mapa::Mapa(const unsigned int& lines, const unsigned int& columns,
        const std::string& map, const std::string& mapGrid)
    :mapData{new short*[lines]}, lines{lines}, columns{columns}, editMode{false}{
        this->map = LoadTexture(map.c_str());
        this->mapGrid = LoadTexture(mapGrid.c_str());
        /* coordMap.x = GetScreenWidth() / 2.0f - this->mapGrid.width / 2.0f; */
        /* coordMap.y = GetScreenHeight() / 2.0f - this->mapGrid.height / 2.0f; */
        coordMap.x = -3186.0f;
        coordMap.y = -13.12f;
    for (int i = 0; i < lines; ++i)
        mapData[i] = new short[columns]{0};
}

moss::Mapa::~Mapa(){
    UnloadTexture(this->map);
    UnloadTexture(this->mapGrid);
    for (int i = 0; i < this->lines; ++i)
        delete[] this->mapData[i];
    delete[] this->mapData;
}
 
short **moss::Mapa::getMapData() const{
    return this->mapData;
}

void moss::Mapa::imprimeMapData() const{
    for (int i = 0; i < this->lines; ++i){
        for (int j = 0; j < this->columns; ++j)
            std::cout << this->mapData[i][j] << "  ";
        std::cout << std::endl;
    }
}

void moss::Mapa::update(){
    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode)
        DrawTexture(this->mapGrid, this->coordMap.x, this->coordMap.y, WHITE);
    else
        DrawTexture(this->map, this->coordMap.x, this->coordMap.y, WHITE);
}

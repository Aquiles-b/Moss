#include "Mapa.hpp"

moss::Mapa::Mapa(const std::string& mapIso, const std::string& gridIso,
                const std::string& busIso, const std::string& mapTop,
                const std::string& gridTop, const std::string& busTop,
                const std::string& ef1)
    :editMode{false}{
        this->mapIso = LoadTexture(mapIso.c_str());
        this->gridIso = LoadTexture(gridIso.c_str());
        this->busIso = LoadTexture(busIso.c_str());
        this->mapTop = LoadTexture(mapTop.c_str());
        this->gridTop = LoadTexture(gridTop.c_str());
        this->busTop = LoadTexture(busTop.c_str());
        this->ef1 = LoadTexture(ef1.c_str());

        unsigned short size = floor(this->mapTop.width / this->busTop.width);
        this->mapData = new short*[size];
        this->size = size;
        coordMap.x = -this->mapIso.width / 2.0f;
        coordMap.y = 0.0f;
    for (int i = 0; i < size; ++i)
        mapData[i] = new short[size]{0};
}

moss::Mapa::~Mapa(){
    UnloadTexture(this->mapIso);
    UnloadTexture(this->gridIso);
    UnloadTexture(this->busIso);
    UnloadTexture(this->mapTop);
    UnloadTexture(this->gridTop);
    UnloadTexture(this->busTop);
    UnloadTexture(this->ef1);
    for (unsigned short i = 0; i < this->size; ++i)
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

void moss::Mapa::converteMatrizMapa(const short& l, const short& c, Vector2& coordIso) const{
    coordIso.x = (c - l - 1) * this->busIso.height;
    coordIso.y = (l + c) * this->busIso.height / 2.0f;
}

void moss::Mapa::draw() const{
    float x{0}, y{0};
    Vector2 coordIso{0};
    DrawTexture(this->mapIso, this->coordMap.x, this->coordMap.y, WHITE);
    if (this->editMode)
        DrawTexture(this->gridIso, this->coordMap.x, this->coordMap.y, WHITE);
    for (unsigned short i = 0; i < this->size; ++i){
        for (unsigned short j = 0; j < this->size; ++j){
            if (this->mapData[i][j] == 1) {
                converteMatrizMapa(i, j, coordIso);
                DrawTexture(this->busIso, coordIso.x, coordIso.y, WHITE);
            }
        }
    }
}

void moss::Mapa::update(const Vector2& mouse){
    short l = floor(abs((mouse.x * 0.5f - mouse.y) / this->busIso.height));
    short c = floor((mouse.x * 0.5f + mouse.y) / this->busIso.height);
    Vector2 coordIso{0};

    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode) {
        if (l < this->size && c >= 0 && c < this->size){
            converteMatrizMapa(l, c, coordIso);
            DrawTexture(this->busIso, coordIso.x, coordIso.y, WHITE);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    this->mapData[l][c] = 1;
        }
    }
}

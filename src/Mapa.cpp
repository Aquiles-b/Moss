#include "Mapa.hpp"
#include <raylib.h>

moss::Mapa::Mapa()
    :mapa{new short*[100]}, lines{100}, columns{100}{
    for (int i = 0; i < this->lines; ++i)
        mapa[i] = new short[this->columns]{0};
}
moss::Mapa::Mapa(const unsigned int& lines, const unsigned int& columns,
        const std::string& texture)
    :mapa{new short*[lines]}, lines{lines}, columns{columns}{
        this->texture = new Texture2D;
        *this->texture = LoadTexture(texture.c_str());
    for (int i = 0; i < lines; ++i)
        mapa[i] = new short[columns]{0};
    }
moss::Mapa::~Mapa(){
    for (int i = 0; i < this->lines; ++i)
        delete[] this->mapa[i];
    delete[] this->mapa;
    delete texture;
}
 
short **moss::Mapa::getMapa() const{
    return this->mapa;
}

void moss::Mapa::imprimeMapa() const{
    for (int i = 0; i < this->lines; ++i){
        for (int j = 0; j < this->columns; ++j)
            std::cout << this->mapa[i][j] << "  ";
        std::cout << std::endl;
    }
}

void moss::Mapa::update(){
    DrawTexture(*this->texture, GetScreenWidth() / 2 - this->texture->width / 2, 
            GetScreenHeight() / 2 - this->texture->height / 2, WHITE);
}

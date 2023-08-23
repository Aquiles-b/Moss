#include "Mapa.hpp"

moss::Mapa::Mapa()
    :mapa{new short*[100]}, lines{100}, columns{100}{
    for (int i = 0; i < this->lines; ++i)
        mapa[i] = new short[this->columns]{0};
}
moss::Mapa::Mapa(const unsigned int& lines, const unsigned int& columns)
    :mapa{new short*[lines]}, lines{lines}, columns{columns}{
    for (int i = 0; i < lines; ++i)
        mapa[i] = new short[columns]{0};
    }
moss::Mapa::~Mapa(){
    for (int i = 0; i < this->lines; ++i)
        delete[] this->mapa[i];
    delete[] this->mapa;
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

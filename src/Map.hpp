#ifndef MAPA_HPP
#define MAPA_HPP
#include <array>
#include <iostream>
#include "../include/raylib.h"
#include "../include/raymath.h"

namespace moss{
enum IdTexturesMap{
    MAPTOP,
    GRIDTOP,
    BUSTOP,
    MAPISO,
    GRIDISO,
    BUSISO
};

struct matrixCoord{
    int l;
    int c;
};

class Mapa{
    public:
        Mapa();
        Mapa(const std::array<std::string, 6>& textures);
        virtual ~Mapa();

       short **getMapData() const;

        void imprimeMapData() const;
        void update(const Vector2& mouse);
        void draw() const;
        void matrixToMapCoord(const short& l, const short& c, Vector2& coordIso) const;
        void mapToMatrixCoord(const float& x, const float& y, struct matrixCoord& coordMatrix) const;
        
    private:
        std::array<Texture2D, 6> textures;
        unsigned short tamCelulaIso;
        Vector2 coordMap;
        bool editMode;
        unsigned short size;
        short **mapData;
};
}
#endif

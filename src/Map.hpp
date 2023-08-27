#ifndef MAPA_HPP
#define MAPA_HPP
#include <iostream>
#include <array>
#include <vector>
#include "../include/raylib.h"
#include "../include/raymath.h"

namespace moss{
enum IdTexturesMap{
    MAPTOP,
    GRIDTOP,
    MAPISO,
    GRIDISO,
};

struct matrixCoord{
    int l;
    int c;
};

class Mapa{
    public:
        Mapa();
        Mapa(const std::array<std::string, 4>& textures, const std::vector<std::string>& floors,
                const float& widthCellTop, const float& widthCellIso);
        virtual ~Mapa();

       int **getMapData() const;

        void imprimeMapData() const;
        void update(const Vector2& mouse, const int& floor);
        void draw() const;
        void matrixToMapCoord(const short& l, const short& c, Vector2& coordIso) const;
        void mapToMatrixCoord(const float& x, const float& y, struct matrixCoord& coordMatrix) const;
    private:
        std::array<Texture2D, 4> textures;
        std::vector<Texture2D> floors;
        unsigned short heightCellIso;
        Vector2 coordMap;
        bool editMode;
        unsigned short size;
        int **mapData;
};
}
#endif

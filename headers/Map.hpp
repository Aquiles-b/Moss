#ifndef MAPA_HPP
#define MAPA_HPP
#include <iostream>
#include <array>
#include <vector>
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "Component.hpp"

namespace moss{
class Map{
    public:
        Map();
        Map(const std::array<std::string, 4>& textures, const std::vector<Component*>& components,
                const float& widthCellTop, const float& widthCellIso);
        virtual ~Map();

       int **getMapData() const;

        void imprimeMapData() const;
        void update(const Vector2& mouse, const int& floor);
        void draw() const;
        void matrixToMapCoord(const int& l, const int& c, Vector2& coordIso) const;
        void mapToMatrixCoord(const float& x, const float& y, int& l, int& c) const;
        bool colision(const int& l, const int& c, const int& width, const int& height) const;
        bool isComponentInsideLimits(const int& l, const int& c, const int& width, const int& height) const;
    private:
        std::array<Texture2D, 4> textures;
        std::vector<Component*> components;
        unsigned short heightCellIso;
        Vector2 coordMap;
        bool editMode;
        unsigned short size;
        int **mapData;

        bool tryDrawInMatrix(Component* component, const int& l, const int& c, Vector2& coordIso);
        void destructionMode(const int& l, const int& c, Vector2& coordIso);
        void fillColisionMatrix(const int& l, const int& c, const int& widthComp, 
                            const int& heightComp, const int& numFill);
};
}
#endif

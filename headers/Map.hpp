#ifndef MAPA_HPP
#define MAPA_HPP
#include <iostream>
#include <array>
#include <vector>
#include "../headers/IdTextureMap.hpp"
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "ComponentModel.hpp"
#include "Construction.hpp"

namespace moss{
struct cellMatrix{
    int value;
    int lOrigin;
    int cOrigin;
    moss::Construction *constInfo;
};
class Map{
    public:
        Map();
        Map(const std::array<std::string, 4>& textures, const std::vector<ComponentModel*>& components,
                const float& widthCellTop, const float& widthCellIso);
        virtual ~Map();

        const bool& getEditMode() const;
        const int& getSize() const;
        struct cellMatrix **getMapData();
        std::vector<struct cellMatrix> *getConstruCoords();
        const int& getHeightCellIso() const;

        void imprimeMapData() const;
        void update(const Vector2& mouse, const int& comp, const bool& editMode);
        void drawMapBefore(const bool& editMode) const;
        void drawMapAfter() const;
        void matrixToMapCoord(const int& l, const int& c, Vector2& coordIso) const;
        void mapToMatrixCoord(const float& x, const float& y, int& l, int& c) const;
        bool colision(const int& l, const int& c, const int& width, const int& height) const;
        bool isComponentInsideLimits(const int& l, const int& c, const int& width, const int& height) const;
    private:
        std::array<Texture2D, 4> textures;
        std::vector<ComponentModel*> components;
        std::vector<struct cellMatrix> *construCoords;
        int heightCellIso;
        Vector2 coordMap;
        int size;
        struct cellMatrix **mapData;

        bool tryDrawInMatrix(ComponentModel* component, const int& l, const int& c, Vector2& coordIso);
        void destructionMode(int l, int c);
        void fillColisionMatrix(const int& l, const int& c, const int& widthComp, const int& heightComp,
                                const int& numFill, const int& lOrigin, const int& cOrigin);
};
}
#endif

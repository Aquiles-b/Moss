#ifndef MAPA_HPP
#define MAPA_HPP
#include <iostream>
#include <array>
#include <vector>
#include "../headers/IdTextureMap.hpp"
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "ComponentModel.hpp"
#include "GameController.hpp"
#include "cellMatrix.hpp"

namespace moss{
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
        const bool& getChanged() const;
        void setChanged(const bool& changed);

        void imprimeMapData() const;
        void update(const Vector2& mouse, const int& comp, const bool& editMode,
                const moss::GameController& gc);
        void drawMapBefore(const bool& editMode, const moss::GameController& gc) const;
        void drawMapAfter(const moss::GameController& gc) const;
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
        bool changed;

        bool tryDrawInMatrix(ComponentModel* component, const int& l, const int& c, Vector2& coordIso);
        void destructionMode(int l, int c, const moss::GameController& gc);
        void fillColisionMatrix(const int& l, const int& c, const int& widthComp, const int& heightComp,
                                const int& numFill, const int& lOrigin, const int& cOrigin);
};
}
#endif

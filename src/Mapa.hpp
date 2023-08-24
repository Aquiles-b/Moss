#include <iostream>
#include "../include/raylib.h"
#ifndef MAPA_HPP
#define MAPA_HPP
namespace moss{
class Mapa{
    public:
        Mapa();
        Mapa(const unsigned int& lines, const unsigned int& columns,
                const std::string& map, const std::string& mapGrid);
        virtual ~Mapa();

       short **getMapData() const;

        void imprimeMapData() const;
        void update();
        
    private:
        Texture2D map;
        Texture2D mapGrid;
        Vector2 coordMap;
        bool editMode;
        const unsigned lines;
        const unsigned columns;
        short **mapData;
};
}
#endif

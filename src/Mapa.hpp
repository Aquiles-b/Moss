#include <iostream>
#include "../include/raylib.h"
#include "../include/raymath.h"
#ifndef MAPA_HPP
#define MAPA_HPP
namespace moss{
class Mapa{
    public:
        Mapa();
        Mapa(const unsigned short& size, const std::string& map, 
                const std::string& mapGrid, const std::string& bus);
        virtual ~Mapa();

       short **getMapData() const;

        void imprimeMapData() const;
        void update(const Vector2& mouse);
        
    private:
        Texture2D map;
        Texture2D mapGrid;
        Texture2D bus;
        Vector2 coordMap;
        bool editMode;
        const unsigned short size;
        short **mapData;
};
}
#endif

#include <iostream>
#include "../include/raylib.h"
#include "../include/raymath.h"
#ifndef MAPA_HPP
#define MAPA_HPP
namespace moss{
class Mapa{
    public:
        Mapa();
        Mapa(const std::string& mapIso, const std::string& gridIso,
                const std::string& busIso, const std::string& mapTop,
                const std::string& gridTop, const std::string& busTop,
                const std::string& ef1);
        virtual ~Mapa();

       short **getMapData() const;

        void imprimeMapData() const;
        void update(const Vector2& mouse);
        void draw() const;
        void converteMatrizMapa(const short& l, const short& c, Vector2& coordIso) const;
        
    private:
        Texture2D mapIso;
        Texture2D gridIso;
        Texture2D busIso;
        Texture2D mapTop;
        Texture2D gridTop;
        Texture2D busTop;
        Texture2D ef1;
        Vector2 coordMap;
        bool editMode;
        unsigned short size;
        short **mapData;
};
}
#endif

#include <iostream>
#include <raylib.h>
#ifndef MAPA_HPP
#define MAPA_HPP
namespace moss{
class Mapa{
    public:
        Mapa();
        Mapa(const unsigned int& lines, const unsigned int& columns,
                const std::string& texture);
        virtual ~Mapa();

        short **getMapa() const;

        void imprimeMapa() const;
        void update();
        
    private:
        Texture2D *texture;
        const unsigned lines;
        const unsigned columns;
        short **mapa;
};
}
#endif

#include "../headers/moss.hpp"

std::unique_ptr<moss::Map> initMap(){
    std::array<std::string, 4> texturesMap;
    texturesMap[static_cast<int>(IdTextureMap::MAPTOP)] = "img/mapTop.png";
    texturesMap[static_cast<int>(IdTextureMap::GRIDTOP)] = "img/gridTop.png";
    texturesMap[static_cast<int>(IdTextureMap::MAPISO)] = "img/mapIso.png";
    texturesMap[static_cast<int>(IdTextureMap::GRIDISO)] = "img/gridIso.png";
    std::vector<moss::ComponentModel*> components;
    moss::ComponentModel *bus{new moss::ComponentModel{"img/busIso.png", 1, 1, 1, 1, true}};
    moss::ComponentModel *ram{new moss::ComponentModel{"img/ramIsoBF.png", "img/ramIsoAF.png", 1, 1, 4, 2, {-235.0f, -161.0f}, false, 2, 0}};
    moss::ComponentModel *cpu{new moss::ComponentModel{"img/cpuIsoBF.png", "img/cpuIsoAF.png", 1, 1, 3, 3, {-200.0f, -205.0f}, false, 0, 2}};
    components.push_back(bus);
    components.push_back(ram);
    components.push_back(cpu);
    std::unique_ptr<moss::Map> mapa{new moss::Map{texturesMap, components, 83.3f, 118.0f}};

    return mapa;
}

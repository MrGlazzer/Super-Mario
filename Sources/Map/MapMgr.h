/*
*/

#ifndef MapMgr_h_
#define MapMgr_h_

#include <string>
#include "SFML/Graphics.hpp"

using SpriteByID = std::map<int, sf::Sprite>;

struct Layer
{
    Layer() = default;

    std::vector<sf::Sprite> Objects;
};


class MapMgr
{
protected:
    MapMgr();
    ~MapMgr();

public:
    static MapMgr* Instance();

    std::vector<Layer> CreateMap(std::string pathToXMLMap, std::string pathToXMLTiles, std::string pathToImmageTiles);

private:
    SpriteByID PrepareTiles(std::string pathToXMLTiles, std::string pathToImmageTiles);
};

#define sMapMgr MapMgr::Instance()
#endif // !MapMgr_h_

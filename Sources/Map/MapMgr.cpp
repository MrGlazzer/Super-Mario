/*
*/

#include "MapMgr.h"
#include "Sources/Utils/TinyXML/tinyxml2.h"
#include <map>
#include <iostream>


MapMgr::MapMgr()
{
}

MapMgr::~MapMgr()
{
}

MapMgr* MapMgr::Instance()
{
    static MapMgr instance;
    return &instance;
}

std::vector<Layer> MapMgr::CreateMap(std::string pathToXMLMap, std::string pathToXMLTiles, std::string pathToImmageTiles)
{
    auto spriteById = PrepareTiles(pathToXMLTiles, pathToImmageTiles);
    if (spriteById.empty())
        return std::vector<Layer>();

    tinyxml2::XMLDocument xml;
    xml.LoadFile(pathToXMLMap.c_str());

    auto el_map = xml.FirstChildElement("map");
    if (!el_map)
        return std::vector<Layer>();

    auto width = atoi(el_map->Attribute("width"));
    auto height = atoi(el_map->Attribute("height"));
    auto tileWidth = atoi(el_map->Attribute("tilewidth"));
    auto tileHeight = atoi(el_map->Attribute("tileheight"));

    auto el_tileset = el_map->FirstChildElement("tileset");
    if (!el_tileset)
        return std::vector<Layer>();

    std::vector<Layer> layers;
    auto el_layer = el_map->FirstChildElement("layer");

    while (el_layer)
    {
        auto el_data = el_layer->FirstChildElement("data");
        if (!el_data)
            return std::vector<Layer>();

        Layer layer;
        std::string temp;
        auto data = std::string(el_data->GetText());
        
        int x = 0, y = 0;
        for (auto el : data)
        {
            if (el != ',')
            {
                temp.push_back(el);
                continue;
            }

            auto id = atoi(temp.c_str());
            temp.clear();

            if (id > 0)
            {
                auto sprite = spriteById[id - 1];
                sprite.setPosition(x * tileWidth, y * tileHeight);
                layer.Objects.push_back(sprite);
            }

            ++x;
            if (x >= width)
            {
                x = 0;
                ++y;

                if (y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);
        el_layer = el_layer->NextSiblingElement("layer");
    }

    return layers;
}

SpriteByID MapMgr::PrepareTiles(std::string pathToXMLTiles, std::string pathToImmageTiles)
{
    tinyxml2::XMLDocument xml;
    xml.LoadFile(pathToXMLTiles.c_str());

    auto el_tileset = xml.FirstChildElement("tileset");
    if (!el_tileset)
        return SpriteByID();

    auto tileWidth = atoi(el_tileset->Attribute("tilewidth"));
    auto tileHeight = atoi(el_tileset->Attribute("tileheight"));
    auto margin = atoi(el_tileset->Attribute("margin"));
    auto tileCount = atoi(el_tileset->Attribute("tilecount"));
    auto columns = atoi(el_tileset->Attribute("columns"));

    sf::Texture texture;
    if (!texture.loadFromFile(pathToImmageTiles.c_str()))
        return SpriteByID();

    auto x = 0, y = 0;
    auto curTileCount = 0;
    SpriteByID spriteById;

    while (curTileCount < tileCount)
    {
        for (auto i = 0; i < columns; ++i)
        {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(x, y, tileWidth, tileHeight));
            spriteById[curTileCount] = sprite;

            x += tileWidth + margin;
            ++curTileCount;
        }

        x = 0;
        y += tileHeight + margin;
    }

    return spriteById;
}

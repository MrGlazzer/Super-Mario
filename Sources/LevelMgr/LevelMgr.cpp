/*
* Glazzer
*/

#include "LevelMgr.h"
#include "Sources/Map/Map.h"
#include "Sources/Utils/TinyXML/tinyxml2.h"


LevelMgr::LevelMgr() {}

LevelMgr::~LevelMgr() {}

LevelMgr* LevelMgr::Instance()
{
    static LevelMgr instance;
    return &instance;
}

Map* LevelMgr::CreateLevelMap(sf::Uint16 level)
{
    auto ParseXML = [&](std::string path, Map* map, bool isMap, bool tileOnMapXML = false)-> bool
    {
        tinyxml2::XMLDocument xml;
        xml.LoadFile(path.c_str());

        if (isMap)
        {
            auto el_map = xml.FirstChildElement("map");
            if (!el_map)
                return false;

            map->Initialization(atoi(el_map->Attribute("width")), atoi(el_map->Attribute("height")), atoi(el_map->Attribute("tilewidth")), atoi(el_map->Attribute("tileheight")));

            auto el_layer = el_map->FirstChildElement("layer");
            while (el_layer)
            {
                auto el_data = el_layer->FirstChildElement("data");
                if (!el_data)
                    continue;

                std::string temp;
                auto data = std::string(el_data->GetText());

                Position position;
                for (const auto& itr : data)
                {
                    if (itr != ',')
                    {
                        temp.push_back(itr);
                        continue;
                    }

                    auto tileId = atoi(temp.c_str());
                    temp.clear();

                    if (tileId > 0)
                    {
                        TileInfo tile;
                        tile.ID = tileId;
                        tile.PositionOnMap = Position(position.X * (float)map->GetTileWidth(), position.Y * (float)map->GetTileHeight());
                        map->AddTile(tile);
                    }

                    position.X += 1.f;
                    if (position.X >= (float)map->GetWidth())
                    {
                        position.X = 0.f;
                        position.Y += 1.f;

                        if (position.Y >= (float)map->GetHeight())
                            position.Y = 0.f;
                    }
                }

                el_layer = el_layer->NextSiblingElement("layer");
            }

            auto el_object = el_map->FirstChildElement("objectgroup");
            while (el_object)
            {
                auto el_data = el_object->FirstChildElement("object");
                while (el_data)
                {
                    ObjectInfo object;
                    if (auto name = el_data->Attribute("name"))
                        object.Type = GetObjectType(name);

                    object.PositionOnMap.X = (float)atoi(el_data->Attribute("x"));
                    object.PositionOnMap.Y = (float)atoi(el_data->Attribute("y")) - (float)CELL_SIZE;
                    object.Width = atoi(el_data->Attribute("width"));
                    object.Height = atoi(el_data->Attribute("height"));

                    if (auto el_gid = el_data->Attribute("gid"))
                    {
                        TileInfo tile;
                        tile.ID = atoi(el_gid);
                        tile.PositionOnMap = object.PositionOnMap;
                        map->AddTile(tile);
                    }

                    map->AddObjectInfo(object);
                    el_data = el_data->NextSiblingElement("object");
                }

                el_object = el_object->NextSiblingElement("objectgroup");
            }
        }
        else
        {
            tinyxml2::XMLElement* el_tileset = nullptr;
            if (tileOnMapXML)
            {
                auto el_map = xml.FirstChildElement("map");
                if (!el_map)
                    return false;

                el_tileset = el_map->FirstChildElement("tileset");
            }
            else
            {
                el_tileset = xml.FirstChildElement("tileset");
            }

            if (!el_tileset)
                return false;

            auto tileWidth = atoi(el_tileset->Attribute("tilewidth"));
            auto tileHeight = atoi(el_tileset->Attribute("tileheight"));
            auto spacing = atoi(el_tileset->Attribute("spacing"));
            auto margin = atoi(el_tileset->Attribute("margin"));
            auto tileCount = atoi(el_tileset->Attribute("tilecount"));
            auto columns = atoi(el_tileset->Attribute("columns"));

            Position position;
            auto curTileCount = 0;

            while (curTileCount < tileCount)
            {
                for (auto i = 0; i < columns; ++i)
                {
                    for (auto& tile : map->GetTiles())
                    {
                        if ((tile.ID - 1) == curTileCount)
                            tile.TextureRect = position;
                    }

                    position.X += tileWidth + spacing;
                    ++curTileCount;
                }

                position.X = 0;
                position.Y += tileHeight + spacing;
            }
        }

        return true;
    };

    std::string path = "E:/Learning/SFML/Super-Mario/Assets/Levels/" + std::to_string(level) + "/";
    std::string pathToXMLMap = path + "Map.tmx";
    std::string pathToXMLTiles = path + "Tiles.tsx";

    auto map = new Map();
    ParseXML(pathToXMLMap, map, true);
    if (!ParseXML(pathToXMLMap, map, false, true))
        ParseXML(pathToXMLTiles, map, false, false);

    map->CreateObjects();
    return map;
}

ObjectType LevelMgr::GetObjectType(const std::string& name)
{
    if (name == "collision_floor")
    {
        return ObjectType::OBJECT_COLLISION_ROOM;
    }
    else if (name == "mario")
    {
        return ObjectType::OBJECT_MARIO;
    }

    return ObjectType();
}

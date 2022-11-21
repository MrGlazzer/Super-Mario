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

Map* LevelMgr::LoadMap(sf::Uint8 level)
{
    auto ParseXML = [&](std::string path, Map* map, bool isParseMapXML, bool isParseTilesXML)-> bool
    {
        tinyxml2::XMLDocument xml;
        xml.LoadFile(path.c_str());

        if (isParseMapXML && !isParseTilesXML)
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

                sf::Vector2<float> position;
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
                        auto tile = new Tile();
                        tile->ID = tileId;
                        tile->Position = sf::Vector2<float>(position.x * (float)map->GetTileWidth(), position.y * (float)map->GetTileHeight());
                        map->AddTile(tile);
                    }

                    position.x += 1.f;
                    if (position.x >= (float)map->GetWidth())
                    {
                        position.x = 0.f;
                        position.y += 1.f;

                        if (position.y >= (float)map->GetHeight())
                            position.y = 0.f;
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
                    auto object = new GridObject();
                    if (auto name = el_data->Attribute("name"))
                        object->Type = GetObjectType(name);

                    object->Position = sf::Vector2<float>((float)atoi(el_data->Attribute("x")), (float)atoi(el_data->Attribute("y")));
                    object->Width = atoi(el_data->Attribute("width"));
                    object->Height = atoi(el_data->Attribute("height"));

                    if (auto el_gid = el_data->Attribute("gid"))
                    {
                        object->Position.y -= (float)CELL_SIZE;

                        auto tile = new Tile();
                        tile->ID = atoi(el_gid);
                        tile->Position = object->Position;
                        map->AddTile(tile);
                    }

                    map->AddGridObject(object, sf::Vector2<int>((int)(object->Position.x / (float)CELL_SIZE), (int)(object->Position.y / (float)CELL_SIZE)));
                    el_data = el_data->NextSiblingElement("object");
                }

                el_object = el_object->NextSiblingElement("objectgroup");
            }
        }
        else
        {
            tinyxml2::XMLElement* el_tileset = nullptr;
            if (isParseTilesXML)
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

            sf::Vector2<int> position;
            auto curTileCount = 0;

            while (curTileCount < tileCount)
            {
                for (auto i = 0; i < columns; ++i)
                {
                    for (auto tile : map->GetTiles())
                    {
                        if ((tile->ID - 1) == curTileCount)
                            tile->TextureRect = position;
                    }

                    position.x += tileWidth + spacing;
                    ++curTileCount;
                }

                position.x = 0;
                position.y += tileHeight + spacing;
            }
        }

        return true;
    };

    std::string path = "E:/Learning/SFML/Super-Mario/Assets/Levels/" + std::to_string(level) + "/";
    std::string pathToXMLMap = path + "Map.tmx";
    std::string pathToXMLTiles = path + "Tiles.tsx";

    auto map = new Map();
    ParseXML(pathToXMLMap, map, true, false);
    if (!ParseXML(pathToXMLMap, map, true, true))
        ParseXML(pathToXMLTiles, map, false, true);

    map->CreateUnits();
    return map;
}

/*
* необходимо доработать, чтобы можно было понимать, какие блоки можно ломать, какие спавнят бафы, какие ломаются и т.п.
*/
ObjectType LevelMgr::GetObjectType(const std::string& name)
{
    ObjectType type = ObjectType::None;
    if (name == "object_floor")
    {
        return ObjectType::Collision;
    }
    else if (name == "object_mario")
    {
        return ObjectType::Mario;
    }
    else if (name == "object_generating_money_block")
    {
        return ObjectType::Block;
    }
    else if (name == "object_destructible_block")
    {
        return ObjectType::Block;
    }
    else if (name == "object_pipe_default")
    {
        return ObjectType::Pipe;
    }
    else if (name == "object_pipe_default_teleport")
    {
        return ObjectType::Pipe;
    }

    return type;
}

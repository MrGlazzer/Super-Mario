/*
* Glazzer
*/

#include "Map.h"
#include "Sources/Objects/Mario/Mario.h"


Map::Map() : _Width(0), _Height(0), _TileWidth(0), _TileHeight(0), _CameraOffsetX(0.f)
{
    _Texture.loadFromFile("E:/Learning/SFML/Super-Mario/Assets/Textures/Map/Map.png");
}

Map::~Map() {}

void Map::Initialization(sf::Uint32 width, sf::Uint32 height, sf::Uint32 tileWidth, sf::Uint32 tileHeight)
{
    _Width = width;
    _Height = height;
    _TileWidth = tileWidth;
    _TileHeight = tileHeight;
}

void Map::CreateObjects()
{
    for (const auto& object : _ObjectInfos)
    {
        if (object.Type == ObjectType::OBJECT_MARIO)
        {
            auto mario = new Mario();
            mario->Create(ObjectType::OBJECT_MARIO, this, object.PositionOnMap);
            _Objects.push_back(mario);
        }
    }
}

std::vector<ObjectInfo> Map::GetObject(ObjectType type)
{
    std::vector<ObjectInfo> result;
    for (const auto& object : _ObjectInfos)
    {
        if (object.Type == type)
            result.push_back(object);
    }

    return result;
}

void Map::Draw(sf::RenderTarget* target, float diff)
{
    if (!target)
        return;

    for (const auto& tile : _Tiles)
    {
        sf::Sprite sprite;
        sprite.setTexture(_Texture);
        sprite.setTextureRect(sf::IntRect((int)tile.TextureRect.X, (int)tile.TextureRect.Y, _TileWidth, _TileHeight));
        sprite.setPosition(tile.PositionOnMap.X, tile.PositionOnMap.Y);
        target->draw(sprite);
    }

    for (auto object : _Objects)
        object->Draw(target, diff);
}

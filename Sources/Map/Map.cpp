#include "Map.h"
#include "Sources/Units/Mario/Mario.h"


Map::Map() : _Width(0), _Height(0), _TileWidth(0), _TileHeight(0), _CameraOffsetX(0.f), _GridObjects(nullptr)
{
    _Texture.loadFromFile("E:/Learning/SFML/Super-Mario/Assets/Textures/Map/Map.png");
}

Map::~Map()
{
    while (!_Tiles.empty())
    {
        delete _Tiles.back();
        _Tiles.pop_back();
    }

    for (auto x = 0u; x < _Width; ++x)
        delete _GridObjects[x];
    delete _GridObjects;

    while (!_Units.empty())
    {
        delete _Units.back();
        _Units.pop_back();
    }   
}

void Map::Initialization(sf::Uint32 width, sf::Uint32 height, sf::Uint32 tileWidth, sf::Uint32 tileHeight)
{
    _Width = width;
    _Height = height;
    _TileWidth = tileWidth;
    _TileHeight = tileHeight;

    _GridObjects = new GridObject**[width];
    for (auto x = 0u; x < width; ++x)
    {
        _GridObjects[x] = new GridObject*[height];

        for (auto y = 0u; y < height; ++y)
            _GridObjects[x][y] = nullptr;
    }
}

void Map::AddGridObject(GridObject* object, sf::Vector2<int> position)
{
    if (!object || position.x > (int)_Width || position.y > (int)_Height)
        return;

    _GridObjects[position.x][position.y] = object;
}

void Map::CreateUnits()
{
    for (auto x = 0u; x < _Width; ++x)
    {
        for (auto y = 0u; y < _Height; ++y)
        {
            auto gridObject = _GridObjects[x][y];
            if (!gridObject || gridObject->Type != ObjectType::Mario)
                continue;

            auto mario = new Mario();
            mario->Create(this, ObjectType::Mario, gridObject->Position);
            _Units.push_back(mario);
        }
    }
}

void Map::Draw(sf::RenderTarget* target, float diff)
{
    if (!target)
        return;

    for (auto tile : _Tiles)
    {
        sf::Sprite sprite;
        sprite.setTexture(_Texture);
        sprite.setTextureRect(sf::IntRect(tile->TextureRect.x, tile->TextureRect.y, _TileWidth, _TileHeight));
        sprite.setPosition(tile->Position);
        target->draw(sprite);
    }

    for (auto unit : _Units)
        unit->Draw(target, diff);
}

#ifndef Map_h_
#define Map_h_

#include "Sources/Utils/Globals.h"

class Unit;


struct Tile
{
    Tile() = default;

    sf::Uint32 ID = 0;
    sf::Vector2<int> TextureRect;
    sf::Vector2<float> Position;
};

struct GridObject
{
    GridObject() = default;

    sf::Uint32 Width = 0;
    sf::Uint32 Height = 0;
    ObjectType Type = ObjectType::None;
    sf::Vector2<float> Position;
};

class Map
{
public:
    Map();
    ~Map();

    void Initialization(sf::Uint32 width, sf::Uint32 height, sf::Uint32 tileWidth, sf::Uint32 tileHeight);

    sf::Uint32 GetWidth() { return _Width; }
    sf::Uint32 GetHeight() { return _Height; }
    sf::Uint32 GetTileWidth() { return _TileWidth; }
    sf::Uint32 GetTileHeight() { return _TileHeight; }

    void SetCameraOffsetX(float offsetX) { _CameraOffsetX = offsetX; }
    float GetCameraOffsetX() const { return _CameraOffsetX; }

    void AddTile(Tile* tile) { _Tiles.push_back(tile); }
    std::vector<Tile*> GetTiles() { return _Tiles; }

    void AddGridObject(GridObject* object, sf::Vector2<int> position);
    GridObject* GetGridObject(int x, int y) { return _GridObjects[x][y]; }

    void CreateUnits();
    std::vector<Unit*> GetUnits() { return _Units; }

    void Draw(sf::RenderTarget* target, float diff);

private:
    sf::Uint32 _Width;
    sf::Uint32 _Height;
    sf::Uint32 _TileWidth;
    sf::Uint32 _TileHeight;
    float _CameraOffsetX;
    sf::Texture _Texture;
    std::vector<Tile*> _Tiles;
    GridObject*** _GridObjects;
    std::vector<Unit*> _Units;
};

#endif // !Map_h_

/*
* Glazzer
*/

#ifndef Map_h_
#define Map_h_

#include "Sources/Utils/Global.hpp"

class Object;
class Mario;


struct TileInfo
{
    TileInfo() = default;

    sf::Uint32 ID = 0;
    Position TextureRect;
    Position PositionOnMap;
    sf::Sprite Sprite;
};

struct ObjectInfo
{
    ObjectInfo() = default;

    Position PositionOnMap;
    sf::Uint32 Width = 0;
    sf::Uint32 Height = 0;
    ObjectType Type;
};

class Map
{
public:
    Map();
    ~Map();

    void Initialization(sf::Uint32 width, sf::Uint32 height, sf::Uint32 tileWidth, sf::Uint32 tileHeight);
    void AddTile(const TileInfo& tile) { _Tiles.push_back(tile); }
    void AddObjectInfo(const ObjectInfo& object) { _ObjectInfos.push_back(object); }

    sf::Uint32 GetWidth() { return _Width; }
    sf::Uint32 GetHeight() { return _Height; }
    sf::Uint32 GetTileWidth() { return _TileWidth; }
    sf::Uint32 GetTileHeight() { return _TileHeight; }
    std::vector<TileInfo>& GetTiles() { return _Tiles; }

    void CreateObjects();
    std::vector<ObjectInfo> GetObject(ObjectType type);
    std::vector<ObjectInfo> GetObject() { return _ObjectInfos; }

    void SetCameraOffsetX(float value) { _CameraOffsetX = value; }
    float GetCameraOffsetX() const { return _CameraOffsetX; }

    void Draw(sf::RenderTarget* target, float diff);

private:
    sf::Uint32 _Width;
    sf::Uint32 _Height;
    sf::Uint32 _TileWidth;
    sf::Uint32 _TileHeight;
    float _CameraOffsetX;
    std::vector<TileInfo> _Tiles;
    std::vector<ObjectInfo> _ObjectInfos;
    std::vector<Object*> _Objects;
    sf::Texture _Texture;
};

#endif // !Map_h_

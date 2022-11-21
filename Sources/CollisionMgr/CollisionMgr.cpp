#include "CollisionMgr.h"
#include "Sources/Map/Map.h"


CollisionMgr::CollisionMgr() {}

CollisionMgr::~CollisionMgr() {}

CollisionMgr* CollisionMgr::Instance()
{
    static CollisionMgr instance;
    return &instance;
}

bool CollisionMgr::IsCollision(Map* map, const sf::Vector2<float>& source, std::set<ObjectType> types, sf::Uint32& collisionMask)
{
	if (!map)
		return false;

	auto cell_x = source.x / (float)CELL_SIZE;
	auto cell_y = source.y / (float)CELL_SIZE;

	for (sf::Uint8 i = 0; i < 4; ++i)
	{
		sf::Uint16 x = 0, y = 0;

		switch (i)
		{
			case 0: //Top left cell
			{
				x = (sf::Uint16)floor(cell_x);
				y = (sf::Uint16)floor(cell_y);
				break;
			}
			case 1: //Top right cell
			{
				x = (sf::Uint16)ceil(cell_x);
				y = (sf::Uint16)floor(cell_y);
				break;
			}
			case 2: //Bottom left cell
			{
				x = (sf::Uint16)floor(cell_x);
				y = (sf::Uint16)ceil(cell_y);
				break;
			}
			case 3: //Bottom right cell
			{
				x = (sf::Uint16)ceil(cell_x);
				y = (sf::Uint16)ceil(cell_y);
				break;
			}
		}

		if (x < 0 || y < 0 || x > map->GetWidth() || y > map->GetHeight())
			continue;

		for (const auto& type : types)
		{
			auto object = map->GetGridObject(x, y);
			if (!object || object->Type != type)
				continue;

			collisionMask |= 1 << (sf::Uint32)object->Type;
		}
	}

	return collisionMask;
}

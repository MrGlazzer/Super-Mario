#ifndef CollisionMgr_h_
#define CollisionMgr_h_

#include "Sources/Utils/Globals.h"
#include <set>

class Map;


class CollisionMgr
{
protected:
    CollisionMgr();
    ~CollisionMgr();

public:
    static CollisionMgr* Instance();

    [[nodiscard]] bool IsCollision(Map* map, const sf::Vector2<float>& source, std::set<ObjectType> types, sf::Uint32& collisionMask);
};

#define sCollisionMgr CollisionMgr::Instance()
#endif // !CollisionMgr_h_

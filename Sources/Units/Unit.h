#ifndef Unit_h_
#define Unit_h_

#include "Sources/Utils/Globals.h"
#include "Sources/Handlers/AnimationHandler/AnimationHandler.h"
#include "Sources/CollisionMgr/CollisionMgr.h"

class Map;
class Mario;


class Unit
{
public:
    Unit();
    ~Unit();

    void Create(Map* map, ObjectType type, sf::Vector2<float> position);

    ObjectType GetObjectType() { return _Type; }

    [[nodiscard]] bool IsMario() const { return _Type == ObjectType::Mario; }

    Mario* ToMario() { if (IsMario()) return reinterpret_cast<Mario*>(this); return nullptr; }

    void SetPosition(sf::Vector2<float> position) { _Position = position; }
    void SetPositionX(float x) { _Position.x = x; }
    void SetPositionY(float y) { _Position.y = y; }

    sf::Vector2<float> GetPosition() { return _Position; }
    float GetPositionX() { return _Position.x; }
    float GetPositionY() { return _Position.y; }

    AnimationHandler* GetAnimationHandler() { return _AnimationHandler; }

    Map* GetMap() { return _Map; }

    void Draw(sf::RenderTarget* target, float diff);
    virtual void Update(float diff) {}

private:
    ObjectType _Type;
    sf::Vector2<float> _Position;
    AnimationHandler* _AnimationHandler;
    Map* _Map;
};

#endif // !Unit_h_

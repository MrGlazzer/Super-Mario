/*
* Glazzer
*/

#ifndef Object_h_
#define Object_h_

#include "Sources/Utils/Global.hpp"
#include "Sources/Handlers/AnimationHandler/AnimationHandler.h"
#include "Sources/Map/Map.h"


class Object
{
public:
    Object();
    virtual ~Object();

    void Create(ObjectType type, Map* map, const Position& position);

    [[nodiscard]] bool IsMario() const { return _Type == ObjectType::OBJECT_MARIO; }

    Mario* ToMario() { if (IsMario()) return reinterpret_cast<Mario*>(this); return nullptr; }

    void SetPosition(const Position& position) { _Position = position; }
    Position GetPosition() { return _Position; }
    float GetPositionX() { return _Position.X; }
    float GetPositionY() { return _Position.Y; }

    void SetFalling(float delta = 0.f);
    [[nodiscard]] bool IsFalling() const { return _IsFalling; }

    void SetJumped() { _IsJumped = true; }
    [[nodiscard]] bool IsJumped() const { return _IsJumped; }

    void SetIgnoreCollision(bool value) { _IgonereCollision = value; }

    void SetHorizontalImpulse(float delta) { _HorizontalImpulse = delta; }
    float GetHorizontalImpulse() { return _HorizontalImpulse; }

    AnimationHandler& GetAnimationHandler() { return _AnimationHandler; }

    Map* GetMap() { return _Map; }

    bool IsCollision();

    void Draw(sf::RenderTarget* target, float diff);
    virtual void Update(float diff) {}

private:
    ObjectType _Type;
    Position _Position;
    float _FallingImpulse;
    bool _IsFalling;
    bool _IsJumped;
    bool _IgonereCollision;
    float _HorizontalImpulse;
    AnimationHandler _AnimationHandler;
    Map* _Map;
};

#endif // !Object_h_

/*
* Glazzer
*/

#include "Object.h"


Object::Object() : _Type(ObjectType::OBJECT_NONE), _Map(nullptr), _FallingImpulse(0.f), _IsFalling(false), _IsJumped(false), _IgonereCollision(false), _HorizontalImpulse(0.f) {}

Object::~Object() {}

void Object::Create(ObjectType type, Map* map, const Position& position)
{
    if (type == ObjectType::OBJECT_NONE)
        return;

    _Type = type;
    _Map = map;

    sf::Texture texture;
    if (IsMario())
    {
        SetPosition(position);

        texture.loadFromFile("E:/Learning/SFML/Super-Mario/Assets/Textures/Mario/DefaultMario.png");
        _AnimationHandler.AddAnimation(texture, AnimationType::ANIMATION_IDLE, Position(0.f, 0.f), Position(16.f, 0.f), 16, 16, 0.f, false);
        _AnimationHandler.AddAnimation(texture, AnimationType::ANIMATION_WALK, Position(16.f, 0.f), Position(64.f, 0.f), 16, 16, 10.f, true);
        _AnimationHandler.AddAnimation(texture, AnimationType::ANIMATION_JUMP, Position(64.f, 0.f), Position(80.f, 0.f), 16, 16, 0.f, true);
        _AnimationHandler.AddAnimation(texture, AnimationType::ANIMATION_BRAKE, Position(80.f, 0.f), Position(96.f, 0.f), 16, 16, 0.f, true);
        _AnimationHandler.AddAnimation(texture, AnimationType::ANIMATION_DEATH, Position(96.f, 0.f), Position(112.f, 0.f), 16, 16, 10.f, false);
        _AnimationHandler.Idle();
    }
}

void Object::SetFalling(float delta)
{
    _IsFalling = true;
    _FallingImpulse += delta;
}

bool Object::IsCollision()
{
    auto map = GetMap();
    if (!map)
        return false;

    auto objects = map->GetObject(ObjectType::OBJECT_COLLISION_ROOM);
    for (const auto& object : objects)
    {


        if (object.PositionOnMap.Y <= GetPositionY() + CELL_SIZE)
            return true;
    }

    return false;
}

void Object::Draw(sf::RenderTarget* target, float diff)
{
    if (!target)
        return;

    Update(diff);
    if (IsCollision() && !_IgonereCollision)
    {
        _IsFalling = false;
        _IsJumped = false;
        _FallingImpulse = 0.f;
    }
    else
    {
        _IsFalling = true;
        _FallingImpulse += GRAVITY * diff;
    }

    if (_HorizontalImpulse != 0.f && !_IsFalling)
    {
        if (_HorizontalImpulse > 0.f)
        {
            _HorizontalImpulse -= MARIO_ACCELERATION * diff;
            if (_HorizontalImpulse <= 0.f)
                _HorizontalImpulse = 0.f;
        }
        else if (_HorizontalImpulse < 0.f)
        {
            _HorizontalImpulse += MARIO_ACCELERATION * diff;
            if (_HorizontalImpulse >= 0.f)
                _HorizontalImpulse = 0.f;
        }
    }

    _Position.Y += _FallingImpulse;
    _Position.X += _HorizontalImpulse;

    if (auto map = GetMap())
    {
        _Position.X = clamp(_Position.X, 0.f, std::min(_Position.X, (map->GetWidth() - 1) * (float)CELL_SIZE));
        //<
    }

    _AnimationHandler.Update(target, diff, _Position);
}

#include "Unit.h"
#include "Sources/Map/Map.h"


Unit::Unit() : _Type(ObjectType::None), _AnimationHandler(nullptr), _Map(nullptr)
{
    _AnimationHandler = new AnimationHandler();
}

Unit::~Unit()
{
    delete _AnimationHandler;
    _AnimationHandler = nullptr;
}

void Unit::Create(Map* map, ObjectType type, sf::Vector2<float> position)
{
    if (!map || type == ObjectType::None)
        return;

    _Map = map;
    _Type = type;
    SetPosition(position);

    sf::Texture texture;
    if (IsMario())
    {
        texture.loadFromFile("E:/Learning/SFML/Super-Mario/Assets/Textures/Mario/DefaultMario.png");
        _AnimationHandler->AddAnimation(texture, AnimationType::Idle, sf::Vector2<int>(0, 0), sf::Vector2<int>(16, 0), 16, 16, 0.f, false);
        _AnimationHandler->AddAnimation(texture, AnimationType::Walk, sf::Vector2<int>(16, 0), sf::Vector2<int>(64, 0), 16, 16, 10.f, true);
        _AnimationHandler->AddAnimation(texture, AnimationType::Jump, sf::Vector2<int>(64, 0), sf::Vector2<int>(80, 0), 16, 16, 0.f, true);
        _AnimationHandler->AddAnimation(texture, AnimationType::Sliding, sf::Vector2<int>(80, 0), sf::Vector2<int>(96, 0), 16, 16, 0.f, true);
        _AnimationHandler->AddAnimation(texture, AnimationType::Death, sf::Vector2<int>(96, 0), sf::Vector2<int>(112, 0), 16, 16, 10.f, false);
        _AnimationHandler->Idle();
    }
}

void Unit::Draw(sf::RenderTarget* target, float diff)
{
    if (!target)
        return;

    Update(diff);
    _AnimationHandler->Update(target, diff, _Position);
}

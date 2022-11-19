/*
*/

#include "Mario.h"


Mario::Mario()
{
}

Mario::~Mario()
{
}

void Mario::CreateAnimations(AnimationHandler& handler)
{
    sf::Texture texture;
    texture.loadFromFile("E:/Learning/SFML/Super-Mario/Resources/Images/Mario/MarioIdle.png");
    handler.PushAnimation(AnimationType::ANIMATION_IDLE, Animation(texture, sf::IntRect(0, 0, 16, 16), 0.f, false));

    texture.loadFromFile("E:/Learning/SFML/Super-Mario/Resources/Images/Mario/MarioWalk.png");
    handler.PushAnimation(AnimationType::ANIMATION_WALK, Animation(texture, sf::IntRect(0, 0, 16, 16), 10.f, true));

    texture.loadFromFile("E:/Learning/SFML/Super-Mario/Resources/Images/Mario/MarioJump.png");
    handler.PushAnimation(AnimationType::ANIMATION_JUMP, Animation(texture, sf::IntRect(0, 0, 16, 16), 0.f, false));

    texture.loadFromFile("E:/Learning/SFML/Super-Mario/Resources/Images/Mario/MarioDeath.png");
    handler.PushAnimation(AnimationType::ANIMATION_DEATH, Animation(texture, sf::IntRect(0, 0, 16, 16), 0.f, false));

    texture.loadFromFile("E:/Learning/SFML/Super-Mario/Resources/Images/Mario/MarioBrake.png");
    handler.PushAnimation(AnimationType::ANIMATION_BRAKE, Animation(texture, sf::IntRect(0, 0, 16, 16), 0.f, true));

    handler.Idle();
}

void Mario::TryMove(float diff)
{
    auto dir = 0.f;
    auto isMoved = false;

    auto IsLeft = []()-> bool
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    };

    auto IsRight = []()-> bool
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    };

    if (IsLeft() || IsRight())
    {
        isMoved = !(IsLeft() && IsRight());
        if (isMoved)
            dir = IsRight() ? 1.f : -1.f;
    }

    /*auto isJumped = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
    }*/

    if (isMoved)
    {
        SetPosition(Position(GetPositionX() + diff * 48.f * dir, GetPositionY(), GetPositionZ()));
        GetAnimationHandler().Walk(dir < 0.f);
    }
    else
    {
        GetAnimationHandler().Idle();
    }
}

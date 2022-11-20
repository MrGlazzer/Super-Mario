/*
* Glazzer
*/

#include "Mario.h"


Mario::Mario() {}

Mario::~Mario() {}

void Mario::Update(float diff)
{
    auto IsLeft = []()-> bool
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    };

    auto IsRight = []()-> bool
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    };

    auto IsUp = []()-> bool
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    };

    auto dir = 0.f;
    auto isMoved = false;

    if (IsLeft() || IsRight())
    {
        isMoved = !(IsLeft() && IsRight());
        if (isMoved)
            dir = IsRight() ? 1.f : -1.f;
    }

    SetIgnoreCollision(false);
    if (IsUp() && !IsFalling() && !IsJumped())
    {
        isMoved = true;

        SetJumped();
        SetFalling(-0.09f);
        SetIgnoreCollision(true);
        GetAnimationHandler().Jump(GetHorizontalImpulse() <= 0.f);
    }

    if (!IsFalling() && !IsJumped())
    {
        if (isMoved)
        {
            SetHorizontalImpulse(dir > 0.f ? 0.03f : -0.03f);
            GetAnimationHandler().Walk(dir < 0.f);
        }
        else
        {
            GetAnimationHandler().Idle();
        }
    }
}

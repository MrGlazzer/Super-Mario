/*
*/

#include "Mario.h"


Mario::Mario()
{
}

Mario::~Mario()
{
}

void Mario::CreateAnimations(const sf::Texture& trxture, AnimationHandler& handler)
{
    handler.PushAnimation(AnimationType::ANIMATION_WALK, Animation(trxture, sf::IntRect(0, 0, 153, 138), 10.f));
}

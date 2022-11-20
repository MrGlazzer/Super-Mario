/*
* Glazzer
*/

#include "AnimationHandler.h"


void Animation::Draw(sf::RenderTarget* target, float diff, Position position, bool isFlipped)
{
    if (!target)
        return;

    CurrentFrame += Speed * diff;
    CurrentFrame = CurrentFrame > FrameCount ? 0.f : CurrentFrame;

    Sprite.setTexture(Texture);
    Sprite.setTextureRect(Frames[isFlipped][(sf::Int16)CurrentFrame]);
    Sprite.setPosition(round(position.X), round(position.Y));
    target->draw(Sprite);
}


AnimationHandler::AnimationHandler() {}

AnimationHandler::~AnimationHandler() {}

void AnimationHandler::AddAnimation(const sf::Texture& texture, AnimationType type, Position begin, Position end, int width, int height, float speed, bool isNeedFlip)
{
    Animation animation;
    animation.Texture = texture;
    animation.Speed = speed;

    while (begin.X < end.X)
    {
        animation.Frames[0].push_back(sf::IntRect((int)begin.X, (int)begin.Y, width, height));
        if (isNeedFlip)
            animation.Frames[1].push_back(sf::IntRect((int)begin.X + width, (int)begin.Y, -width, height));

        animation.FrameCount += 1.f;
        begin.X += (float)width;
    }

    Animations[type] = animation;
}

void AnimationHandler::Update(sf::RenderTarget* target, float diff, Position position)
{
    if (CurrentAnimation == AnimationType::ANIMATION_NONE || Animations.find(CurrentAnimation) == Animations.end())
        return;

    switch (CurrentAnimation)
    {
        case AnimationType::ANIMATION_IDLE:
        case AnimationType::ANIMATION_DEATH:
        {
            IsFlipped = false;
            break;
        }
    }

    Animations[CurrentAnimation].Draw(target, diff, position, IsFlipped);
}

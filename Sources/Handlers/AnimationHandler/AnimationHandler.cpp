#include "AnimationHandler.h"


void Animation::Draw(sf::RenderTarget* target, float diff, sf::Vector2<float> position, bool isFlipped)
{
    if (!target)
        return;

    CurrentFrame += Speed * diff;
    CurrentFrame = CurrentFrame > FrameCount ? 0.f : CurrentFrame;

    Sprite.setTexture(Texture);
    Sprite.setTextureRect(Frames[isFlipped][(sf::Int16)CurrentFrame]);
    Sprite.setPosition(position);
    target->draw(Sprite);
}


AnimationHandler::AnimationHandler() : CurrentAnimation(AnimationType::None), IsFlipped(false) {}

AnimationHandler::~AnimationHandler()
{
    for (const auto& itr : Animations)
        delete itr.second;
    Animations.clear();
}

void AnimationHandler::AddAnimation(const sf::Texture& texture, AnimationType type, sf::Vector2<int> begin, sf::Vector2<int> end, int width, int height, float speed, bool isNeedFlip)
{
    auto animation = new Animation();
    animation->Texture = texture;
    animation->Speed = speed;

    while (begin.x < end.x)
    {
        animation->Frames[0].push_back(sf::IntRect(begin.x, begin.y, width, height));
        if (isNeedFlip)
            animation->Frames[1].push_back(sf::IntRect(begin.x + width, begin.y, -width, height));

        animation->FrameCount += 1.f;
        begin.x += width;
    }

    Animations[type] = animation;
}

void AnimationHandler::Update(sf::RenderTarget* target, float diff, sf::Vector2<float> position)
{
    if (CurrentAnimation == AnimationType::None || Animations.find(CurrentAnimation) == Animations.end())
        return;

    switch (CurrentAnimation)
    {
        case AnimationType::Idle:
        case AnimationType::Death:
        {
            IsFlipped = false;
            break;
        }
    }

    Animations[CurrentAnimation]->Draw(target, diff, position, IsFlipped);
}

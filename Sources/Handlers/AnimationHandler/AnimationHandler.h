/*
* Glazzer
*/

#ifndef AnimationHandler_h_
#define AnimationHandler_h_

#include "Sources/Utils/Global.hpp"


enum class AnimationType
{
    ANIMATION_NONE                      = 0,
    ANIMATION_IDLE,
    ANIMATION_WALK,
    ANIMATION_RUN,
    ANIMATION_JUMP,
    ANIMATION_DEATH,
    ANIMATION_BRAKE
};

struct Animation
{
    Animation() = default;

    void Draw(sf::RenderTarget* target, float diff, Position position, bool isFlipped);

    sf::Texture Texture;
    sf::Sprite Sprite;
    float FrameCount = 0.f;
    float Speed = 0.f;
    std::vector<sf::IntRect> Frames[2];

private:
    float CurrentFrame = 0.f;
};

class AnimationHandler
{
public:
    AnimationHandler();
    ~AnimationHandler();

    void AddAnimation(const sf::Texture& texture, AnimationType type, Position begin, Position end, int width, int height, float speed, bool isNeedFlip);

    void Update(sf::RenderTarget* target, float diff, Position position);

    void Stop()
    {
        CurrentAnimation = AnimationType::ANIMATION_NONE;
    }

    void Idle()
    {
        CurrentAnimation = AnimationType::ANIMATION_IDLE;
    }

    void Walk(bool isFlipped)
    {
        IsFlipped = isFlipped;
        CurrentAnimation = AnimationType::ANIMATION_WALK;
    }

    void Run(bool isFlipped)
    {
        IsFlipped = isFlipped;
        CurrentAnimation = AnimationType::ANIMATION_RUN;
    }

    void Jump(bool isFlipped)
    {
        IsFlipped = isFlipped;
        CurrentAnimation = AnimationType::ANIMATION_JUMP;
    }

private:
    AnimationType CurrentAnimation = AnimationType::ANIMATION_NONE;
    std::map<AnimationType, Animation> Animations;
    bool IsFlipped = false;
};

#endif // !AnimationHandler_h_

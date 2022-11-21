#ifndef AnimationHandler_h_
#define AnimationHandler_h_

#include "Sources/Utils/Globals.h"


enum class AnimationType
{
    None,
    Idle,
    Walk,
    Run,
    Jump,
    Death,
    Sliding
};

struct Animation
{
    Animation() = default;

    void Draw(sf::RenderTarget* target, float diff, sf::Vector2<float> position, bool isFlipped);

    sf::Texture Texture;
    sf::Sprite Sprite;
    float FrameCount = 0.f;
    float Speed = 0.f;
    std::vector<sf::IntRect> Frames[2];

private:
    float CurrentFrame = 0.f;
};

struct AnimationHandler
{
public:
    AnimationHandler();
    ~AnimationHandler();

    void AddAnimation(const sf::Texture& texture, AnimationType type, sf::Vector2<int> begin, sf::Vector2<int> end, int width, int height, float speed, bool isNeedFlip);

    void Update(sf::RenderTarget* target, float diff, sf::Vector2<float> position);

    void Idle()
    {
        CurrentAnimation = AnimationType::Idle;
    }

    void Walk(bool isFlipped)
    {
        IsFlipped = isFlipped;
        CurrentAnimation = AnimationType::Walk;
    }

    void Run(bool isFlipped)
    {
        IsFlipped = isFlipped;
        CurrentAnimation = AnimationType::Run;
    }

    void Jump(bool isFlipped)
    {
        IsFlipped = isFlipped;
        CurrentAnimation = AnimationType::Jump;
    }

    void Sliding(bool isFlipped)
    {
        IsFlipped = isFlipped;
        CurrentAnimation = AnimationType::Sliding;
    }

private:
    AnimationType CurrentAnimation;
    std::map<AnimationType, Animation*> Animations;
    bool IsFlipped;
};

#endif // !AnimationHandler_h_

/*
*/

#ifndef Object_h_
#define Object_h_

#include "SFML/Graphics.hpp"


enum class ObjectType
{
    OBJECT_NONE                         = 0,
    OBJECT_MARIO,
};

enum class AnimationType
{
    ANIMATION_NONE                      = 0,
    ANIMATION_IDLE,
    ANIMATION_WALK,
    ANIMATION_RUN
};

struct Animation
{
public:
    Animation() = default;

    Animation(const sf::Texture& texture, sf::IntRect rect, float speed)
    {
        Texture = texture;
        FrameWidth = rect.width;
        FrameHeight = rect.height;
        TotalFrameCount = texture.getSize().x / FrameWidth;
        AnimationSpeed = speed;

        for (auto i = 0; i < TotalFrameCount; ++i)
            Frames.push_back(sf::IntRect(rect.left + i * FrameWidth, rect.top, FrameWidth, FrameHeight));
    }

    void Draw(sf::RenderTarget* target, float diff, float x, float y)
    {
        if (!target)
            return;

        CurrentFrame += AnimationSpeed * diff;
        CurrentFrame = CurrentFrame > (float)TotalFrameCount ? 0.f : CurrentFrame;

        Sprite.setTexture(Texture);
        Sprite.setTextureRect(Frames[(sf::Int16)CurrentFrame]);
        Sprite.setPosition(x, y);
        target->draw(Sprite);
    }

private:
    sf::Texture Texture;
    sf::Sprite Sprite;
    int FrameWidth = 0;
    int FrameHeight = 0;
    int TotalFrameCount = 0;
    float CurrentFrame = 0;
    float AnimationSpeed = 0.f;
    std::vector<sf::IntRect> Frames;
};

struct AnimationHandler
{
public:
    AnimationHandler() = default;

    void PushAnimation(AnimationType type, Animation animation) { Animations[type] = animation; }

    void Update(sf::RenderTarget* target, float diff, float x, float y)
    {
        if (CurrentAnimation == AnimationType::ANIMATION_NONE || Animations.find(CurrentAnimation) == Animations.end())
            return;

        Animations[CurrentAnimation].Draw(target, diff, x, y);
    }

    void Stop() { CurrentAnimation = AnimationType::ANIMATION_NONE; }
    void Idle() { CurrentAnimation = AnimationType::ANIMATION_IDLE; }
    void Walk() { CurrentAnimation = AnimationType::ANIMATION_WALK; }
    void Run() { CurrentAnimation = AnimationType::ANIMATION_RUN; }

private:
    AnimationType CurrentAnimation = AnimationType::ANIMATION_NONE;
    std::map<AnimationType, Animation> Animations;
};

class Object
{
public:
    Object();
    virtual ~Object();

    [[nodiscard]] bool Create(std::string path, ObjectType type);
    virtual void CreateAnimations(const sf::Texture& trxture, AnimationHandler& handler) {}

    [[nodiscard]] bool IsMario() const { return _ObjectType == ObjectType::OBJECT_MARIO; }

    void Draw(sf::RenderTarget* target, float diff);

private:
    sf::Sprite _Sprite;
    sf::Texture _Texture;
    ObjectType _ObjectType;
    AnimationHandler _AnimationHandler;
};

#endif // !Object_h_

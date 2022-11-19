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
    ANIMATION_RUN,
    ANIMATION_JUMP,
    ANIMATION_DEATH,
    ANIMATION_BRAKE,
};

struct Animation
{
public:
    Animation() = default;

    Animation(const sf::Texture& texture, sf::IntRect rect, float speed, bool isNeedFlip)
    {
        Texture = texture;
        FrameWidth = rect.width;
        FrameHeight = rect.height;
        TotalFrameCount = texture.getSize().x / FrameWidth;
        AnimationSpeed = speed;

        for (auto i = 0; i < TotalFrameCount; ++i)
        {
            Frames[0].push_back(sf::IntRect(rect.left + i * FrameWidth, rect.top, FrameWidth, FrameHeight));

            if (isNeedFlip)
                Frames[1].push_back(sf::IntRect(rect.left + i * FrameWidth + FrameWidth, rect.top, -FrameWidth, FrameHeight));
        }
    }

    void Draw(sf::RenderTarget* target, float diff, float x, float y, bool isFlipped)
    {
        if (!target)
            return;

        CurrentFrame += AnimationSpeed * diff;
        CurrentFrame = CurrentFrame > (float)TotalFrameCount ? 0.f : CurrentFrame;

        Sprite.setTexture(Texture);
        Sprite.setTextureRect(Frames[isFlipped][(sf::Int16)CurrentFrame]);
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
    std::vector<sf::IntRect> Frames[2];
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

        switch (CurrentAnimation)
        {
            case AnimationType::ANIMATION_IDLE:
            case AnimationType::ANIMATION_JUMP:
            case AnimationType::ANIMATION_DEATH:
            {
                IsFlipped = false;
                break;
            }
        }

        Animations[CurrentAnimation].Draw(target, diff, x, y, IsFlipped);
    }

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

private:
    AnimationType CurrentAnimation = AnimationType::ANIMATION_NONE;
    std::map<AnimationType, Animation> Animations;
    bool IsFlipped = false;
};

struct Position
{
    Position() = default;

    Position(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
};

class Object
{
public:
    Object();
    virtual ~Object();

    [[nodiscard]] bool Create(std::string path, ObjectType type);
    virtual void CreateAnimations(AnimationHandler& handler) {}

    [[nodiscard]] bool IsMario() const { return _ObjectType == ObjectType::OBJECT_MARIO; }

    void Draw(sf::RenderTarget* target, float diff);

    Position GetPosition() { return _Position; }
    float GetPositionX() { return _Position.x; }
    float GetPositionY() { return _Position.y; }
    float GetPositionZ() { return _Position.z; }
    void SetPosition(Position position) { _Position = position; }

    AnimationHandler& GetAnimationHandler() { return _AnimationHandler; }

    virtual void TryMove(float diff) {}

private:
    sf::Sprite _Sprite;
    sf::Texture _Texture;
    ObjectType _ObjectType;
    AnimationHandler _AnimationHandler;
    Position _Position;
};

#endif // !Object_h_

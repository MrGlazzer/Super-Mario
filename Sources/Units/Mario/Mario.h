#ifndef Mario_h_
#define Mario_h_

#include "Sources/Units/Unit.h"


class Mario : public Unit
{
public:
    Mario();
    ~Mario();

    bool IsLeft() const
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    }

    bool IsRight() const
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    }

    bool IsUp() const
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    }

    bool IsDown() const
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    }

    void Update(float diff) override;

private:
    /* Move */
    sf::Vector2<float> _Velocity;
    bool _IsFalling;
    float _JumpTimer;
};

#endif // !Mario_h_

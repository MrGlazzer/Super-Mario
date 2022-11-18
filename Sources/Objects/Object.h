/*
*/

#ifndef Object_h_
#define Object_h_

#include "SFML/Graphics.hpp"

class Mario;


enum class ObjectType
{
    OBJECT_NONE                         = 0,
    OBJECT_MARIO,
};

class Object
{
public:
    Object();
    virtual ~Object();

    [[nodiscard]] bool Create(std::string path, ObjectType type);

    [[nodiscard]] bool IsMario() const { return _ObjectType == ObjectType::OBJECT_MARIO; }

    void Draw(sf::RenderTarget* target);

private:
    sf::Sprite _Sprite;
    sf::Texture _Texture;
    ObjectType _ObjectType;
};

#endif // !Object_h_

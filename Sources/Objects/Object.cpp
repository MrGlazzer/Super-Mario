/*
*/

#include "Object.h"


Object::Object() : _ObjectType(ObjectType::OBJECT_NONE)
{
}

Object::~Object()
{
}

bool Object::Create(std::string path, ObjectType type)
{
    if (path.empty())
        return false;

    _ObjectType = type;
    switch (_ObjectType)
    {
        case ObjectType::OBJECT_MARIO:
        {
            if (!_Texture.loadFromFile(path, sf::IntRect()))
                return false;

            _Sprite.setTexture(_Texture);
            return true;
        }
    }

    return false;
}

void Object::Draw(sf::RenderTarget* target)
{
    target->draw(_Sprite);
}

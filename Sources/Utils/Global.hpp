/*
* Glazzer
*/

#ifndef Global_h_
#define Global_h_

#include "SFML/Graphics.hpp"
#include <iostream>


/**/
constexpr auto SCREEN_WIDTH = 225;
constexpr auto SCREEN_HEIGHT = 225;
constexpr auto CELL_SIZE = 15;

/**/
constexpr auto GRAVITY = 0.3f;

/**/
constexpr auto MARIO_ACCELERATION = 0.15f;


enum class ObjectType
{
    OBJECT_NONE                         = 0,
    OBJECT_MARIO,
    OBJECT_COLLISION_ROOM
};


struct Position
{
    Position() = default;

    Position(float x, float y)
    {
        X = x;
        Y = y;
    }

    float X = 0.f;
    float Y = 0.f;
};

inline float clamp(float val, float low, float hi)
{
    if (val <= low)
    {
        return low;
    }
    else if (val >= hi)
    {
        return hi;
    }
    else
    {
        return val;
    }
}

#endif // !Global_h_

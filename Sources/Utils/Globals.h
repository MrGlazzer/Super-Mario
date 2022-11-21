#ifndef Global_h_
#define Global_h_

#include "SFML/Graphics.hpp"
#include <iostream>


/* Engine */
constexpr auto SCREEN_WIDTH = 225;
constexpr auto SCREEN_HEIGHT = 225;

/* Grid */
constexpr auto CELL_SIZE = 15;

/* Physics */
constexpr auto GRAVITY = 0.4f;

/* Mario */
constexpr auto MARIO_ACCELERATION = 0.1f;
constexpr auto MARIO_WALK_SPEED = 0.03f;
constexpr auto MARIO_JUMP_SPEED = -0.08f;


enum class ObjectType
{
    None                                = 0,
    Mario,
    Enemie,
    Collision,
    Block,
    Pipe
};


inline float Clamp(float val, float low, float hi)
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

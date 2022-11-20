/*
* Glazzer
*/

#ifndef Global_h_
#define Global_h_

#include "SFML/Graphics.hpp"

/**/
constexpr auto SCREEN_WIDTH = 225;
constexpr auto SCREEN_HEIGHT = 225;
constexpr auto CELL_SIZE = 16;

/**/
constexpr auto GRAVITY = 0.3f;

/**/
constexpr auto MARIO_ACCELERATION = 0.2f;


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

#endif // !Global_h_

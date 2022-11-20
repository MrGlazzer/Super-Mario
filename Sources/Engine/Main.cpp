/*
* Glazzer
*/

#include "Engine.h"
#include <chrono>


int main()
{
    auto engine = new Engine();
    if (!engine)
    {
        delete engine;
        engine = nullptr;
        return 0;
    }

    sf::Clock clock;
    while (engine->IsRunable())
        engine->Update(clock.restart().asSeconds());

    delete engine;
    engine = nullptr;
    return 0;
}

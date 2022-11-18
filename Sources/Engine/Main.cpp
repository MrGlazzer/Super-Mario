/*
*/

#include "Engine.h"


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
    {
        auto diff = clock.getElapsedTime();
        clock.restart();

        engine->Update(diff.asMilliseconds());
    }

    delete engine;
    engine = nullptr;
    return 0;
}

/*
* Glazzer
*/

#include "Engine.h"
#include "Sources/Map/Map.h"
#include "Sources/LevelMgr/LevelMgr.h"


Engine::Engine()
{
    _Window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Super Mario!");
    _Map = sLevelMgr->CreateLevelMap(0);
}

Engine::~Engine()
{
    delete _Window;
    _Window = nullptr;
}

void Engine::Update(float diff)
{
    HandleEvents();
    Render(diff);
}

void Engine::HandleEvents()
{
    sf::Event event;
    while (_Window->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            case sf::Event::KeyPressed:
            {
                if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                    _Window->close();
                break;
            }
        }
    }
}

void Engine::Render(float diff)
{
    _Window->clear();
    if (_Map)
        _Map->Draw(_Window, diff);
    _Window->display();
}

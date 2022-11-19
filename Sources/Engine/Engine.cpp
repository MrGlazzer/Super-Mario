/*
*/

#include "Engine.h"
#include "Sources/Objects/Mario/Mario.h"


Engine::Engine() : _Window(nullptr)
{
    _Window = new sf::RenderWindow(sf::VideoMode(320, 240), "Super Mario!");

    auto mario = new Mario();
    if (!mario->Create("E:/Learning/SFML/Super-Mario/Resources/Images/Mario/MarioIdle.png", ObjectType::OBJECT_MARIO))
    {
        delete mario;
        exit(0);
        return;
    }

    _Objects.push_back(mario);
}

Engine::~Engine()
{
    delete _Window;
    _Window = nullptr;

    while (!_Objects.empty())
    {
        delete _Objects.back();
        _Objects.pop_back();
    }
}

void Engine::Update(float diff)
{
    HandleEvents();
    Render(diff);
}

void Engine::HandleEvents()
{
    sf::Event e;
    while (_Window->pollEvent(e))
    {
        switch (e.type)
        {
            case sf::Event::Closed:
            case sf::Event::KeyPressed:
            {
                if (e.type == sf::Event::Closed || e.key.code && e.key.code == sf::Keyboard::Escape)
                    _Window->close();
                break;
            }
        }
    }
}

void Engine::Render(float diff)
{
    _Window->clear();
    for (const auto& object : _Objects)
        object->Draw(_Window, diff);
    _Window->display();
}

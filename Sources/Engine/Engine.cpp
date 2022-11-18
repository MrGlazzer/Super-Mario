/*
*/

#include "Engine.h"
#include "Sources/Objects/Mario/Mario.h"
#include <iostream>


Engine::Engine() : _Window(nullptr), _Mario(nullptr)
{
    _Window = new sf::RenderWindow(sf::VideoMode(1024, 720), "Super Mario!", (sf::Style::Titlebar | sf::Style::Close));

    _Mario = new Mario();
    if (!_Mario->Create("E:/Learning/SFML/Super-Mario/Resources/Images/wolf.jpg", ObjectType::OBJECT_MARIO))
    {
        delete _Mario;
        _Mario = nullptr;
    }
}

Engine::~Engine()
{
    if (_Window)
        delete _Window;
    _Window = nullptr;

    if (_Mario)
        delete _Mario;
    _Mario = nullptr;
}

void Engine::Update(sf::Int32 diff)
{
    HandleEvents();
    Render();
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

void Engine::Render()
{
    _Window->clear();
    if (_Mario)
        _Mario->Draw(_Window);
    _Window->display();
}

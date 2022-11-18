/*
*/

#ifndef Engine_h_
#define Engine_h_

#include "SFML/Graphics.hpp"

class Mario;


class Engine
{
public:
    Engine();
    ~Engine();

    [[nodiscard]] bool IsRunable() const { return _Window && _Window->isOpen(); }

    void Update(sf::Int32 diff);

private:
    void HandleEvents();
    void Render();

    sf::RenderWindow* _Window;
    Mario* _Mario;
};

#endif // !Engine_h_

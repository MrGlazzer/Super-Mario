/*
*/

#ifndef Engine_h_
#define Engine_h_

#include "SFML/Graphics.hpp"

class Object;


class Engine
{
public:
    Engine();
    ~Engine();

    [[nodiscard]] bool IsRunable() const { return _Window && _Window->isOpen(); }

    void Update(float diff);

private:
    void HandleEvents();
    void Render(float diff);

    sf::RenderWindow* _Window;
    std::vector<Object*> _Objects;
};

#endif // !Engine_h_

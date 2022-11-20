/*
* Glazzer
*/

#ifndef Engine_h_
#define Engine_h_

#include "Sources/Utils/Global.hpp"

class Map;


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
    Map* _Map;
};

#endif // !Engine_h_

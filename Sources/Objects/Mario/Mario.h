/*
*/

#ifndef Mario_h_
#define Mario_h_

#include "Sources/Objects/Object.h"


class Mario : public Object
{
public:
    explicit Mario();
    ~Mario();

    void CreateAnimations(const sf::Texture& trxture, AnimationHandler& handler) override;

private:
    //<
};

#endif // !Mario_h_

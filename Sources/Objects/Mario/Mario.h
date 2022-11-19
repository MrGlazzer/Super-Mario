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

    void CreateAnimations(AnimationHandler& handler) override;

    void TryMove(float diff) override;

private:
    //<
};

#endif // !Mario_h_

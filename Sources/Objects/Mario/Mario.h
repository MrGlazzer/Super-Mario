/*
* Glazzer
*/

#ifndef Mario_h_
#define Mario_h_

#include "Sources/Objects/Object.h"


class Mario : public Object
{
public:
    explicit Mario();
    ~Mario();

    void Update(float diff) override;

private:
    //<
};

#endif // !Mario_h_

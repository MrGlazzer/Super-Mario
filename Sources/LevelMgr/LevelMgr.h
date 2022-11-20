/*
* Glazzer
*/

#ifndef LevelMgr_h_
#define LevelMgr_h_

#include "Sources/Utils/Global.hpp"

class Map;


class LevelMgr
{
protected:
    LevelMgr();
    ~LevelMgr();

public:
    static LevelMgr* Instance();

    Map* CreateLevelMap(sf::Uint16 level);
};

#define sLevelMgr LevelMgr::Instance()
#endif // !LevelMgr_h_

#ifndef LevelMgr_h_
#define LevelMgr_h_

#include "Sources/Utils/Globals.h"

class Map;


class LevelMgr
{
protected:
    LevelMgr();
    ~LevelMgr();

public:
    static LevelMgr* Instance();

    Map* LoadMap(sf::Uint8 level);

private:
    ObjectType GetObjectType(const std::string& name);
};

#define sLevelMgr LevelMgr::Instance()
#endif // !LevelMgr_h_

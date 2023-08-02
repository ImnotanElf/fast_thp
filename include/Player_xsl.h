#ifndef __PLAYER_XSL_H__
#define __PLAYER_XSL_H__

#include <iostream>

#include "Card.h"

class Player_xsl {
public:
    int id;
    const char* name;
    std::vector<Card> holecards;
    bool is_on_table;
    Player_xsl() {}
    Player_xsl( int id, const char* name, Card aa, Card bb ) : holecards( 2 ) {
        this->id = id;
        this->name = name;
        holecards[ 0 ] = aa;
        holecards[ 1 ] = bb;    
    }
};

#endif
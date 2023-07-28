#ifndef __FIVECARDS_H__
#define __FIVECARDS_H__

#include "Card.h"

class Fivecards {
public:
    Card fivecards[ 5 ];
    int level;
    uint64_t cards_5;
    Fivecards();
    Fivecards( Card c1, Card c2, Card c3, Card c4, Card c5 );
    Fivecards min_five();
    bool is_royalflush();
    bool is_straightflush();
    bool is_fourofakind();
    bool is_fullhouse();
    bool is_flush();
    bool is_straight();
    bool is_threeofakind();
    bool is_twopairs();
    bool is_onepair();
    bool is_highcard();
    bool operator<( const Fivecards& b ) const;
    bool operator==( const Fivecards& b ) const;
    int get_level();
    uint64_t get_cards_5();
    friend std::ostream& operator<<( std::ostream& os, const Fivecards& b );
};

#endif
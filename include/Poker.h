#ifndef __POKER_H__
#define __POKER_H__

#include "Card.h"
#include <vector>
#include <array>

class Poker {
public:
    std::vector< Card > cards;
    std::vector< std::pair< Card, bool > > is_in_poker_pair;
    int num_in_poker;
    Card sA;
    Card s2;
    Card s3;
    Card s4;
    Card s5;
    Card s6;
    Card s7;
    Card s8;
    Card s9;
    Card sT;
    Card sJ;
    Card sQ;
    Card sK;

    Card hA;
    Card h2;
    Card h3;
    Card h4;
    Card h5;
    Card h6;
    Card h7;
    Card h8;
    Card h9;
    Card hT;
    Card hJ;
    Card hQ;
    Card hK;
    
    Card cA;
    Card c2;
    Card c3;
    Card c4;
    Card c5;
    Card c6;
    Card c7;
    Card c8;
    Card c9;
    Card cT;
    Card cJ;
    Card cQ;
    Card cK;

    Card dA;
    Card d2;
    Card d3;
    Card d4;
    Card d5;
    Card d6;
    Card d7;
    Card d8;
    Card d9;
    Card dT;
    Card dJ;
    Card dQ;
    Card dK;
    Poker();
    Poker( bool is_test );
    Poker( int num_of_cards );
    bool deal_card( int card_order );
    bool deal_card( Card card );
    bool back_card( int card_order );
    bool back_card( Card card );
    void shuffle(); 
};

#endif
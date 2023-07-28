#ifndef __CARD_H__
#define __CARD_H__

#include <iostream>

enum Card_suits {
    heart = 'h',
    club = 'c',
    diamond = 'd',
    spade = 's'
};

class Card {
public:
    int id;
    int card_number;
    Card_suits card_suit;
    Card() {
        this->id = -1;
        this->card_number = 2;
        this->card_suit = spade; 
    }
    Card( int num, Card_suits cs, int id ) {
        this->card_number = num;
        this->card_suit = cs;
        this->id = id;
    }
    bool operator<( const Card& b ) const {
        return this->card_number < b.card_number;
    }
    bool operator==( const Card& b ) const {
        return this->card_number == b.card_number;
    }
    friend std::ostream& operator<<( std::ostream& os, const Card& b ) {
        if ( b.card_number == 14 )
            os << 'A' << ( char ) b.card_suit;
        else if ( b.card_number == 13 )
            os << 'K' << ( char ) b.card_suit;
        else if ( b.card_number == 12 )
            os << 'Q' << ( char ) b.card_suit;
        else if ( b.card_number == 11 )
            os << 'J' << ( char ) b.card_suit;
        else if ( b.card_number == 10 )
            os << 'T' << ( char ) b.card_suit;
        else
            os << b.card_number << ( char ) b.card_suit;
        return os;
    }
};

#endif
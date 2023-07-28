#include "Poker.h"

bool Poker::deal_card( int card_order ) {
    if ( Poker::is_in_poker_pair[ card_order ].second == false ) {
        return false;
    }
    Poker::is_in_poker_pair[ card_order ].second = false;
    for ( int i = 0; i < cards.size(); ++i ) {
        if ( cards[i].id == card_order ) {
            cards.erase( cards.begin() + i );
            Poker::num_in_poker -= 1;
            break;
        }
    }
    return true;
}

bool Poker::deal_card( Card card ) {
    // printf( "" );
    if ( Poker::is_in_poker_pair[ card.id ].second == false ) {
        return false;
    }
    Poker::is_in_poker_pair[ card.id ].second = false;
    for ( int i = 0; i < cards.size(); ++i ) {
        if ( cards[i].card_number == card.card_number && cards[ i ].card_suit == card.card_suit ) {
            cards.erase( cards.begin() + i );
            Poker::num_in_poker -= 1;
            break;
        }
    }
    return true;
}

bool Poker::back_card( int card_order ) {
    return Poker::back_card( Poker::is_in_poker_pair[ card_order ].first );
}

bool Poker::back_card( Card card ) {
    if ( Poker::is_in_poker_pair[ card.id ].second == true ) {
        return false;
    }
    cards.push_back( card );
    Poker::num_in_poker += 1;
    Poker::is_in_poker_pair[ card.id ].second = true;
    return true;
}

Poker::Poker() : cards( 52 ), is_in_poker_pair( 52 ) {
    this->num_in_poker = 52;

    int count_id = 0;
    
    this->s2 = Card( 2, spade, count_id++ );
    this->h2 = Card( 2, heart, count_id++ );
    this->c2 = Card( 2, club, count_id++ );
    this->d2 = Card( 2, diamond, count_id++ );

    this->s3 = Card( 3, spade, count_id++ );
    this->h3 = Card( 3, heart, count_id++ );
    this->c3 = Card( 3, club, count_id++ );
    this->d3 = Card( 3, diamond, count_id++ );

    this->s4 = Card( 4, spade, count_id++ );
    this->h4 = Card( 4, heart, count_id++ );
    this->c4 = Card( 4, club, count_id++ );
    this->d4 = Card( 4, diamond, count_id++ );

    this->s5 = Card( 5, spade, count_id++ );
    this->h5 = Card( 5, heart, count_id++ );
    this->c5 = Card( 5, club, count_id++ );
    this->d5 = Card( 5, diamond, count_id++ );

    this->s6 = Card( 6, spade, count_id++ );
    this->h6 = Card( 6, heart, count_id++ );
    this->c6 = Card( 6, club, count_id++ );
    this->d6 = Card( 6, diamond, count_id++ );

    this->s7 = Card( 7, spade, count_id++ );
    this->h7 = Card( 7, heart, count_id++ );
    this->c7 = Card( 7, club, count_id++ );
    this->d7 = Card( 7, diamond, count_id++ );

    this->s8 = Card( 8, spade, count_id++ );
    this->h8 = Card( 8, heart, count_id++ );
    this->c8 = Card( 8, club, count_id++ );
    this->d8 = Card( 8, diamond, count_id++ );

    this->s9 = Card( 9, spade, count_id++ );
    this->h9 = Card( 9, heart, count_id++ );
    this->c9 = Card( 9, club, count_id++ );
    this->d9 = Card( 9, diamond, count_id++ );

    this->sT = Card( 10, spade, count_id++ );
    this->hT = Card( 10, heart, count_id++ );
    this->cT = Card( 10, club, count_id++ );
    this->dT = Card( 10, diamond, count_id++ );

    this->sJ = Card( 11, spade, count_id++ );
    this->hJ = Card( 11, heart, count_id++ );
    this->cJ = Card( 11, club, count_id++ );
    this->dJ = Card( 11, diamond, count_id++ );

    this->sQ = Card( 12, spade, count_id++ );
    this->hQ = Card( 12, heart, count_id++ );
    this->cQ = Card( 12, club, count_id++ );
    this->dQ = Card( 12, diamond, count_id++ );

    this->sK = Card( 13, spade, count_id++ );
    this->hK = Card( 13, heart, count_id++ );
    this->cK = Card( 13, club, count_id++ );
    this->dK = Card( 13, diamond, count_id++ );

    this->sA = Card( 14, spade, count_id++ );
    this->hA = Card( 14, heart, count_id++ );
    this->cA = Card( 14, club, count_id++ );
    this->dA = Card( 14, diamond, count_id++ );



    cards[ 0 ] = s2;
    cards[ 1 ] = h2;
    cards[ 2 ] = c2;
    cards[ 3 ] = d2;

    cards[ 4 ] = s3;
    cards[ 5 ] = h3;
    cards[ 6 ] = c3;
    cards[ 7 ] = d3;

    cards[ 8 ] = s4;
    cards[ 9 ] = h4;
    cards[ 10 ] = c4;
    cards[ 11 ] = d4;

    cards[ 12 ] = s5;
    cards[ 13 ] = h5;
    cards[ 14 ] = c5;
    cards[ 15 ] = d5;

    cards[ 16 ] = s6;
    cards[ 17 ] = h6;
    cards[ 18 ] = c6;
    cards[ 19 ] = d6;

    cards[ 20 ] = s7;
    cards[ 21 ] = h7;
    cards[ 22 ] = c7;
    cards[ 23 ] = d7;

    cards[ 24 ] = s8;
    cards[ 25 ] = h8;
    cards[ 26 ] = c8;
    cards[ 27 ] = d8;

    cards[ 28 ] = s9;
    cards[ 29 ] = h9;
    cards[ 30 ] = c9;
    cards[ 31 ] = d9;

    cards[ 32 ] = sT;
    cards[ 33 ] = hT;
    cards[ 34 ] = cT;
    cards[ 35 ] = dT;

    cards[ 36 ] = sJ;
    cards[ 37 ] = hJ;
    cards[ 38 ] = cJ;
    cards[ 39 ] = dJ;

    cards[ 40 ] = sQ;
    cards[ 41 ] = hQ;
    cards[ 42 ] = cQ;
    cards[ 43 ] = dQ;

    cards[ 44 ] = sK;
    cards[ 45 ] = hK;
    cards[ 46 ] = cK;
    cards[ 47 ] = dK;

    cards[ 48 ] = sA;
    cards[ 49 ] = hA;
    cards[ 50 ] = cA;
    cards[ 51 ] = dA;


    is_in_poker_pair[ 0 ] = std::pair< Card, bool >( s2, true );
    is_in_poker_pair[ 1 ] = std::pair< Card, bool >( h2, true );
    is_in_poker_pair[ 2 ] = std::pair< Card, bool >( c2, true );
    is_in_poker_pair[ 3 ] = std::pair< Card, bool >( d2, true );

    is_in_poker_pair[ 4 ] = std::pair< Card, bool >( s3, true );
    is_in_poker_pair[ 5 ] = std::pair< Card, bool >( h3, true );
    is_in_poker_pair[ 6 ] = std::pair< Card, bool >( c3, true );
    is_in_poker_pair[ 7 ] = std::pair< Card, bool >( d3, true );

    is_in_poker_pair[ 8 ] = std::pair< Card, bool >( s4, true );
    is_in_poker_pair[ 9 ] = std::pair< Card, bool >( h4, true );
    is_in_poker_pair[ 10 ] = std::pair< Card, bool >( c4, true );
    is_in_poker_pair[ 11 ] = std::pair< Card, bool >( d4, true );

    is_in_poker_pair[ 12 ] = std::pair< Card, bool >( s5, true );
    is_in_poker_pair[ 13 ] = std::pair< Card, bool >( h5, true );
    is_in_poker_pair[ 14 ] = std::pair< Card, bool >( c5, true );
    is_in_poker_pair[ 15 ] = std::pair< Card, bool >( d5, true );

    is_in_poker_pair[ 16 ] = std::pair< Card, bool >( s6, true );
    is_in_poker_pair[ 17 ] = std::pair< Card, bool >( h6, true );
    is_in_poker_pair[ 18 ] = std::pair< Card, bool >( c6, true );
    is_in_poker_pair[ 19 ] = std::pair< Card, bool >( d6, true );

    is_in_poker_pair[ 20 ] = std::pair< Card, bool >( s7, true );
    is_in_poker_pair[ 21 ] = std::pair< Card, bool >( h7, true );
    is_in_poker_pair[ 22 ] = std::pair< Card, bool >( c7, true );
    is_in_poker_pair[ 23 ] = std::pair< Card, bool >( d7, true );

    is_in_poker_pair[ 24 ] = std::pair< Card, bool >( s8, true );
    is_in_poker_pair[ 25 ] = std::pair< Card, bool >( h8, true );
    is_in_poker_pair[ 26 ] = std::pair< Card, bool >( c8, true );
    is_in_poker_pair[ 27 ] = std::pair< Card, bool >( d8, true );

    is_in_poker_pair[ 28 ] = std::pair< Card, bool >( s9, true );
    is_in_poker_pair[ 29 ] = std::pair< Card, bool >( h9, true );
    is_in_poker_pair[ 30 ] = std::pair< Card, bool >( c9, true );
    is_in_poker_pair[ 31 ] = std::pair< Card, bool >( d9, true );

    is_in_poker_pair[ 32 ] = std::pair< Card, bool >( sT, true );
    is_in_poker_pair[ 33 ] = std::pair< Card, bool >( hT, true );
    is_in_poker_pair[ 34 ] = std::pair< Card, bool >( cT, true );
    is_in_poker_pair[ 35 ] = std::pair< Card, bool >( dT, true );

    is_in_poker_pair[ 36 ] = std::pair< Card, bool >( sJ, true );
    is_in_poker_pair[ 37 ] = std::pair< Card, bool >( hJ, true );
    is_in_poker_pair[ 38 ] = std::pair< Card, bool >( cJ, true );
    is_in_poker_pair[ 39 ] = std::pair< Card, bool >( dJ, true );

    is_in_poker_pair[ 40 ] = std::pair< Card, bool >( sQ, true );
    is_in_poker_pair[ 41 ] = std::pair< Card, bool >( hQ, true );
    is_in_poker_pair[ 42 ] = std::pair< Card, bool >( cQ, true );
    is_in_poker_pair[ 43 ] = std::pair< Card, bool >( dQ, true );

    is_in_poker_pair[ 44 ] = std::pair< Card, bool >( sK, true );
    is_in_poker_pair[ 45 ] = std::pair< Card, bool >( hK, true );
    is_in_poker_pair[ 46 ] = std::pair< Card, bool >( cK, true );
    is_in_poker_pair[ 47 ] = std::pair< Card, bool >( dK, true );

    is_in_poker_pair[ 48 ] = std::pair< Card, bool >( sA, true );
    is_in_poker_pair[ 49 ] = std::pair< Card, bool >( hA, true );
    is_in_poker_pair[ 50 ] = std::pair< Card, bool >( cA, true );
    is_in_poker_pair[ 51 ] = std::pair< Card, bool >( dA, true );
}

Poker::Poker( bool is_test ) : cards( 20 ), is_in_poker_pair( 20 ) {
    this->num_in_poker = 20;
    int count_id = 0;

    this->sT = Card( 10, spade, count_id++ );
    this->sJ = Card( 11, spade, count_id++ );
    this->sQ = Card( 12, spade, count_id++ );
    this->sK = Card( 13, spade, count_id++ );
    this->sA = Card( 14, spade, count_id++ );
    this->cT = Card( 10, club, count_id++ );
    this->cJ = Card( 11, club, count_id++ );
    this->cQ = Card( 12, club, count_id++ );
    this->cK = Card( 13, club, count_id++ );
    this->cA = Card( 14, club, count_id++ );
    this->hT = Card( 10, heart, count_id++ );
    this->hJ = Card( 11, heart, count_id++ );
    this->hQ = Card( 12, heart, count_id++ );
    this->hK = Card( 13, heart, count_id++ );
    this->hA = Card( 14, heart, count_id++ );
    this->dT = Card( 10, diamond, count_id++ );
    this->dJ = Card( 11, diamond, count_id++ );
    this->dQ = Card( 12, diamond, count_id++ );
    this->dK = Card( 13, diamond, count_id++ );
    this->dA = Card( 14, diamond, count_id++ );

    cards[ 0 ] = sT;
    cards[ 1 ] = sJ;
    cards[ 2 ] = sQ;
    cards[ 3 ] = sK;
    cards[ 4 ] = sA;
    cards[ 5 ] = cT;
    cards[ 6 ] = cJ;
    cards[ 7 ] = cQ;
    cards[ 8 ] = cK;
    cards[ 9 ] = cA;
    cards[ 10 ] = hT;
    cards[ 11 ] = hJ;
    cards[ 12 ] = hQ;
    cards[ 13 ] = hK;
    cards[ 14 ] = hA;
    cards[ 15 ] = dT;
    cards[ 16 ] = dJ;
    cards[ 17 ] = dQ;
    cards[ 18 ] = dK;
    cards[ 19 ] = dA;

    is_in_poker_pair[ 0 ] = std::pair< Card, bool >( sT, true );
    is_in_poker_pair[ 1 ] = std::pair< Card, bool >( sJ, true );
    is_in_poker_pair[ 2] = std::pair< Card, bool >( sQ, true );
    is_in_poker_pair[ 3 ] = std::pair< Card, bool >( sK, true );
    is_in_poker_pair[ 4 ] = std::pair< Card, bool >( sA, true );
    is_in_poker_pair[ 5 ] = std::pair< Card, bool >( cT, true );
    is_in_poker_pair[ 6 ] = std::pair< Card, bool >( cJ, true );
    is_in_poker_pair[ 7 ] = std::pair< Card, bool >( cQ, true );
    is_in_poker_pair[ 8 ] = std::pair< Card, bool >( cK, true );
    is_in_poker_pair[ 9 ] = std::pair< Card, bool >( cA, true );
    is_in_poker_pair[ 10 ] = std::pair< Card, bool >( hT, true );
    is_in_poker_pair[ 11 ] = std::pair< Card, bool >( hJ, true );
    is_in_poker_pair[ 12 ] = std::pair< Card, bool >( hQ, true );
    is_in_poker_pair[ 13 ] = std::pair< Card, bool >( hK, true );
    is_in_poker_pair[ 14 ] = std::pair< Card, bool >( hA, true );
    is_in_poker_pair[ 15 ] = std::pair< Card, bool >( dT, true );
    is_in_poker_pair[ 16 ] = std::pair< Card, bool >( dJ, true );
    is_in_poker_pair[ 17 ] = std::pair< Card, bool >( dQ, true );
    is_in_poker_pair[ 18 ] = std::pair< Card, bool >( dK, true );
    is_in_poker_pair[ 19 ] = std::pair< Card, bool >( dA, true );
}

Poker::Poker( int num_of_cards ) : cards( 12 ), is_in_poker_pair( 12 ) {
    this->num_in_poker = 12;
    int count_id = 0;

    this->sT = Card( 10, spade, count_id++ );
    this->hT = Card( 10, heart, count_id++ );
    this->cT = Card( 10, club, count_id++ );
    this->dT = Card( 10, diamond, count_id++ );
    this->sJ = Card( 11, spade, count_id++ );
    this->hJ = Card( 11, heart, count_id++ );
    this->cJ = Card( 11, club, count_id++ );
    this->dJ = Card( 11, diamond, count_id++ );
    this->sQ = Card( 12, spade, count_id++ );
    this->hQ = Card( 12, heart, count_id++ );
    this->cQ = Card( 12, club, count_id++ );
    this->dQ = Card( 12, diamond, count_id++ );

    cards[ 0 ] = sT;
    cards[ 1 ] = hT;
    cards[ 2 ] = cT;
    cards[ 3 ] = dT;
    cards[ 4 ] = sJ;
    cards[ 5 ] = hJ;
    cards[ 6 ] = cJ;
    cards[ 7 ] = dJ;
    cards[ 8 ] = sQ;
    cards[ 9 ] = hQ;
    cards[ 10 ] = cQ;
    cards[ 11 ] = dQ;

    is_in_poker_pair[ 0 ] = std::pair< Card, bool >( sT, true );
    is_in_poker_pair[ 1 ] = std::pair< Card, bool >( hT, true );
    is_in_poker_pair[ 2 ] = std::pair< Card, bool >( cT, true );
    is_in_poker_pair[ 3 ] = std::pair< Card, bool >( dT, true );
    is_in_poker_pair[ 4 ] = std::pair< Card, bool >( sJ, true );
    is_in_poker_pair[ 5 ] = std::pair< Card, bool >( hJ, true );
    is_in_poker_pair[ 6 ] = std::pair< Card, bool >( cJ, true );
    is_in_poker_pair[ 7 ] = std::pair< Card, bool >( dJ, true );
    is_in_poker_pair[ 8 ] = std::pair< Card, bool >( sQ, true );
    is_in_poker_pair[ 9 ] = std::pair< Card, bool >( hQ, true );
    is_in_poker_pair[ 10 ] = std::pair< Card, bool >( cQ, true );
    is_in_poker_pair[ 11 ] = std::pair< Card, bool >( dQ, true );
}
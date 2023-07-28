#include "Fivecards.h"
#include <map>
#include <algorithm>
#include <cassert>


std::ostream& operator<<( std::ostream& os, const Fivecards& b ) {
    os << b.fivecards[ 0 ] << ' ';
    os << b.fivecards[ 1 ] << ' ';
    os << b.fivecards[ 2 ] << ' ';
    os << b.fivecards[ 3 ] << ' ';
    os << b.fivecards[ 4 ];
    return os;
}

Fivecards Fivecards::min_five() {
    Card c1( 2, spade, -1 );
    Card c2( 3, club, -2 );
    Card c3( 4, diamond, -3 );
    Card c4( 5, heart, -4 );
    Card c5( 7, spade, -5 );
    Fivecards::fivecards[ 0 ] = c1;
    Fivecards::fivecards[ 0 ] = c2;
    Fivecards::fivecards[ 0 ] = c3;
    Fivecards::fivecards[ 0 ] = c4;
    Fivecards::fivecards[ 0 ] = c5;
    Fivecards::level = 0;
    return *this;
}

int Fivecards::get_level() {
    if ( this->is_royalflush() )
        Fivecards::level = 9;
    else if ( this->is_straightflush() )
        Fivecards::level = 8;
    else if ( this->is_fourofakind() )
        Fivecards::level = 7;
    else if ( this->is_fullhouse() )
        Fivecards::level = 6;
    else if ( this->is_flush() )
        Fivecards::level = 5;
    else if ( this->is_straight() )
        Fivecards::level = 4;
    else if ( this->is_threeofakind() )
        Fivecards::level = 3;
    else if ( this->is_twopairs() )
        Fivecards::level = 2;
    else if ( this->is_onepair() )
        Fivecards::level = 1;
    else
        Fivecards::level = 0;
    return Fivecards::level;
}

Fivecards::Fivecards() {
    Card c1( -1, spade, -1 );
    Card c2( -2, club, -2 );
    Card c3( -4, diamond, -3 );
    Card c4( -5, heart, -4 );
    Card c5( -8, spade, -5 );
    this->fivecards[ 0 ] = c1;
    this->fivecards[ 1 ] = c2;
    this->fivecards[ 2 ] = c3;
    this->fivecards[ 3 ] = c4;
    this->fivecards[ 4 ] = c5;
    this->level = 0;
}

Fivecards::Fivecards( Card c1, Card c2, Card c3, Card c4, Card c5 ) {
    this->fivecards[ 0 ] = c1;
    this->fivecards[ 1 ] = c2;
    this->fivecards[ 2 ] = c3;
    this->fivecards[ 3 ] = c4;
    this->fivecards[ 4 ] = c5;
    std::sort( Fivecards::fivecards, Fivecards::fivecards + 5 );
    this->level = this->get_level();
}

bool Fivecards::operator<( const Fivecards& b ) const {
    if ( this->level == b.level ) {
        if ( *this == b ) {
            return false;
        }
        if ( this->level == 9 ) {
            return false;
        } else if ( this->level == 0 || this->level == 5 ) {
            for ( int i = 0; i < 5; ++i ) {
                if ( this->fivecards[ 4 - i ].card_number > b.fivecards[ 4 - i ].card_number ) {
                    return false;
                } else if ( this->fivecards[ 4 - i ].card_number < b.fivecards[ 4 - i ].card_number ) {
                    return true;
                }
            }
            return false;
        } else if ( this->level == 4 || this->level == 8 ) {
            if ( this->fivecards[ 4 ].card_number == 14 && this->fivecards[ 3 ].card_number == 5 ) {
                if ( b.fivecards[ 4 ].card_number == 14 && b.fivecards[ 3 ].card_number == 5 ) {
                    return false;
                } else {
                    return true;
                }
            } else {
                if ( b.fivecards[ 4 ].card_number == 14 && b.fivecards[ 3 ].card_number == 5 ) {
                    return false;
                } else {
                    return this->fivecards[ 0 ].card_number < b.fivecards[ 0 ].card_number;
                }
            }
        } else if ( this->level == 1 ) {
            int a;
            int c;
            for ( int i = 1; i < 5; ++ i ) {
                if ( this->fivecards[ i ].card_number == this->fivecards[ i - 1 ].card_number ) {
                    a = this->fivecards[ i ].card_number;
                }
                if ( b.fivecards[ i ].card_number == b.fivecards[ i - 1 ].card_number ) {
                    c = b.fivecards[ i ].card_number;
                }
            }
            if ( a == c ) {
                for ( int i = 0; i < 5; ++i ) {
                    if ( this->fivecards[ 4 - i ].card_number > b.fivecards[ 4 - i ].card_number ) {
                        return false;
                    } else if ( this->fivecards[ 4 - i ].card_number < b.fivecards[ 4 - i ].card_number ) {
                        return true;
                    }
                }
                return false;
            }
            return a < c;
        } else if ( this->level == 2 ) {
            int a1 = -1, a2 = -1, b1 = -1, b2 = -1;
            for ( int i = 3; i >= 0; i -- ) {
                if ( this->fivecards[ i ].card_number == this->fivecards[ i + 1 ].card_number ) {
                    if ( a1 != -1 ) {
                        a2 = this->fivecards[ i ].card_number;
                    }
                    if ( a2 == -1 ) {
                        a1 = this->fivecards[ i ].card_number;
                    }
                }
                if ( b.fivecards[ i ].card_number == b.fivecards[ i + 1 ].card_number ) {
                    if ( b1 != -1 ) {
                        b2 = b.fivecards[ i ].card_number;
                    }
                    if ( b2 == -1 ) {
                        b1 = b.fivecards[ i ].card_number;
                    }
                }
            }
            if ( a1 == b1 ) {
                if ( a2 == b2 ) {
                    for ( int i = 0; i < 5; ++i ) {
                        if ( this->fivecards[ 4 - i ].card_number > b.fivecards[ 4 - i ].card_number ) {
                            return false;
                        } else if ( this->fivecards[ 4 - i ].card_number < b.fivecards[ 4 - i ].card_number ) {
                            return true;
                        }
                    }
                    return false;
                }
                return a2 < b2;
            }
            return a1 < b1;
        } else if ( this->level == 3 ) {
            if ( this->fivecards[ 2 ].card_number == b.fivecards[ 2 ].card_number ) {
                for ( int i = 0; i < 5; ++i ) {
                    if ( this->fivecards[ 4 - i ].card_number > b.fivecards[ 4 - i ].card_number ) {
                        return false;
                    } else if ( this->fivecards[ 4 - i ].card_number < b.fivecards[ 4 - i ].card_number ) {
                        return true;
                    }
                }
                return false;
            }
            return this->fivecards[ 2 ].card_number < b.fivecards[ 2 ].card_number;
        } else if ( this->level == 6 ) {
            if ( this->fivecards[ 2 ].card_number == b.fivecards[ 2 ].card_number ) {
                if ( this->fivecards[ 4 ].card_number == b.fivecards[ 4 ].card_number ) {
                    return this->fivecards[ 0 ].card_number < b.fivecards[ 0 ].card_number;
                }
                return this->fivecards[ 4 ].card_number < b.fivecards[ 4 ].card_number;
            }
            return this->fivecards[ 2 ].card_number < b.fivecards[ 2 ].card_number;
        } else if ( this->level == 7 ) {
            if ( this->fivecards[ 2 ].card_number == b.fivecards[ 2 ].card_number ) {
                if ( this->fivecards[ 4 ].card_number == b.fivecards[ 4 ].card_number ) {
                    return this->fivecards[ 0 ].card_number < b.fivecards[ 0 ].card_number;
                }
                return this->fivecards[ 4 ].card_number < b.fivecards[ 4 ].card_number;
            }
            return this->fivecards[ 2 ].card_number < b.fivecards[ 2 ].card_number;
        } 
    }
    return this->level < b.level;
}

bool Fivecards::operator==( const Fivecards& b ) const {
    if ( this->level == b.level ) {
        for ( int i = 0; i < 5; ++i ) {
            if ( this->fivecards[ 4 - i ].card_number != b.fivecards[ 4 - i ].card_number ) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Fivecards::is_royalflush() {
    if ( Fivecards::is_straightflush() && this->fivecards[ 4 ].card_number == 14 && this->fivecards[ 3 ].card_number == 13 ) {
        return true;
    }
    return false;
}

bool Fivecards::is_straightflush() {
    if ( Fivecards::is_flush() && Fivecards::is_straight() ) {
        return true;
    }
    return false;
}

bool Fivecards::is_fourofakind() {
    // Card* cards = Fivecards::fourofakind;
    // auto hasher = []( const Card& b ) -> std::size_t { return std::hash< int >()( b.card_number ); };
    std::map< int, int > temp_map;
    for ( int i = 0; i < 5; ++i ) {
        Card cur_card = Fivecards::fivecards[ i ];
        if ( temp_map.find( cur_card.card_number ) == temp_map.end() ) {
            temp_map.emplace( cur_card.card_number, 1 );
        } else {
            temp_map[ cur_card.card_number ] ++;
        }
    }
    auto it = temp_map.begin();
    if ( temp_map.size() == 2 && ( it->second == 1 || it->second == 4 ) ) {
        return true;
    }
    return false;
}

bool Fivecards::is_fullhouse() {
    // Card* cards = Fivecards::fullhouse;
    // auto hasher = []( const Card& b ) -> std::size_t { return std::hash< int >()( b.card_number ); };
    std::map< int, int > temp_map;
    for ( int i = 0; i < 5; ++i ) {
        Card cur_card = Fivecards::fivecards[i];
        if ( temp_map.find( cur_card.card_number ) == temp_map.end() ) {
            temp_map.emplace( cur_card.card_number, 1 );
        } else {
            temp_map[ cur_card.card_number ] ++;
        }
    }
    auto it = temp_map.begin();
    if ( temp_map.size() == 2 && ( it->second == 2 || it->second == 3 ) ) {
        return true;
    }
    return false;
}

bool Fivecards::is_flush() {
    for ( int i = 1; i < 5; ++i ) {
        Card cur_card = Fivecards::fivecards[ i ];
        if ( cur_card.card_suit != Fivecards::fivecards[ i - 1 ].card_suit ) {
            return false;
            break;
        }
    }
    return true;
}

bool Fivecards::is_straight() {
    // std::sort( this->fivecards, this->fivecards + 5 );
    assert( this->fivecards[ 0 ].card_number <= this->fivecards[ 1 ].card_number && this->fivecards[ 1 ].card_number <= this->fivecards[ 2 ].card_number && this->fivecards[ 2 ].card_number <= this->fivecards[ 3 ].card_number && this->fivecards[ 3 ].card_number <= this->fivecards[ 4 ].card_number );
    if ( this->fivecards[0].card_number == 2
        && this->fivecards[1].card_number == 3
        && this->fivecards[2].card_number == 4
        && this->fivecards[3].card_number == 5
        && this->fivecards[4].card_number == 14
    ) {
        return true;
    }
    for ( int i = 1; i < 5; ++i ) {
        if ( this->fivecards[ i ].card_number != 1 + this->fivecards[ i - 1 ].card_number ) {
            return false;
        }
    }
    return true;
}

bool Fivecards::is_threeofakind() {
    // Card* cards = Fivecards::threeofakind;
    // auto hasher = []( const Card& b ) -> std::size_t { return std::hash< int >()( b.card_number ); };
    std::map< int, int > temp_map;
    for ( int i = 0; i < 5; ++i ) {
        Card cur_card = Fivecards::fivecards[i];
        if ( temp_map.find( cur_card.card_number ) == temp_map.end() ) {
            temp_map.emplace( cur_card.card_number, 1 );
        } else {
            temp_map[ cur_card.card_number ] ++;
        }
    }
    if ( temp_map.size() != 3 )
        return false;
    auto it = temp_map.begin();
    int aa = it->second;
    ++it;
    int bb = it->second;
    if ( temp_map.size() == 3 && ( aa == 1 || aa == 3 ) && ( bb == 3 || bb == 1 ) ) {
        return true;
    }
    return false;
}

bool Fivecards::is_twopairs() {
    std::map< int, int > temp_map;
    for ( int i = 0; i < 5; ++i ) {
        Card cur_card = Fivecards::fivecards[i];
        if ( temp_map.find( cur_card.card_number ) == temp_map.end() ) {
            temp_map.emplace( cur_card.card_number, 1 );
        } else {
            temp_map[ cur_card.card_number ] ++;
        }
    }
    if ( temp_map.size() != 3 )
        return false;
    auto it = temp_map.begin();
    int aa = it->second;
    ++it;
    int bb = it->second;
    if ( temp_map.size() == 3 && ( aa == 2 || bb == 2 ) ) {
        return true;
    }
    return false;
}

bool Fivecards::is_onepair() {
    std::map< int, int > temp_map;
    for ( int i = 0; i < 5; ++i ) {
        Card cur_card = Fivecards::fivecards[i];
        if ( temp_map.find( cur_card.card_number ) == temp_map.end() ) {
            temp_map.emplace( cur_card.card_number, 1 );
        } else {
            temp_map[ cur_card.card_number ] ++;
        }
    }
    return temp_map.size() == 4;
}

bool Fivecards::is_highcard() {
    std::map< int, int > temp_map;
    for ( int i = 0; i < 5; ++i ) {
        Card cur_card = Fivecards::fivecards[i];
        if ( temp_map.find( cur_card.card_number ) == temp_map.end() ) {
            temp_map.emplace( cur_card.card_number, 1 );
        } else {
            temp_map[ cur_card.card_number ] ++;
        }
    }
    return temp_map.size() == 5;
}

uint64_t Fivecards::get_cards_5() {
    this->cards_5 = 0ULL;
    for ( int i = 0; i < 5; ++ i ) {
        int card_id = this->fivecards[ i ].id;
        uint64_t tmp = 1ULL;
        tmp <<= card_id;
        cards_5 |= tmp;
    }
    return this->cards_5;
}
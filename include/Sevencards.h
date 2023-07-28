#ifndef __SEVENCARDS_H__
#define __SEVENCARDS_H__

#include "Card.h"
#include "Fivecards.h"
#include "methods.h"
#include <vector>
#include <cstring>
#include <bitset>
#include <fstream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <random>

#include "SevenEval.h"

#define DEBUG 0

class Sevencards {
public:
    std::vector<Card> sevencards;
    Fivecards max_fivecards;
    uint64_t cards_7;
    Sevencards( Card aa, Card bb, Card cc, Card dd, Card ee, Card ff, Card gg ) : sevencards( 7 ) {
        sevencards[ 0 ] = aa;
        sevencards[ 1 ] = bb;
        sevencards[ 2 ] = cc;
        sevencards[ 3 ] = dd;
        sevencards[ 4 ] = ee;
        sevencards[ 5 ] = ff;
        sevencards[ 6 ] = gg;
        this->max_fivecards = max_five_in_seven( this->sevencards );
    }
    bool operator<( const Sevencards& b ) const;
    bool operator==( const Sevencards& b ) const;
    uint64_t get_cards_7();
};

bool Sevencards::operator<( const Sevencards& b ) const {
    return this->max_fivecards < b.max_fivecards;
}

bool Sevencards::operator==( const Sevencards& b ) const {
    return this->max_fivecards == b.max_fivecards;
}

uint64_t Sevencards::get_cards_7() {
    this->cards_7 = 0ULL;
    for ( int i = 0; i < 7; ++ i ) {
        int card_id = this->sevencards[ i ].id;
        uint64_t tmp = 1ULL;
        tmp <<= card_id;
        cards_7 |= tmp;
    }
    return this->cards_7;
}

Sevencards get_sevencards( int index[], const std::vector< Card >& value ) {
    std::vector< Card > temp;
    for ( int i = 0; i < value.size(); i++ ) {
        // std::cout << index[ i ];
        if ( index[ i ] )
            temp.emplace_back( value[ i ] );
    }
    // std::cout << std::endl;
    Sevencards sc( temp[ 0 ], temp[ 1 ], temp[ 2 ], temp[ 3 ], temp[ 4 ], temp[ 5 ], temp[ 6 ] );
    return sc;
}

double winrate(  const std::vector< Card >& value, const std::vector< Card >& ap, const std::vector< Card >& bp )  //核心算法函数
{
    int m = 5;
    int n = value.size();
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6;
    for ( i = 0; i < m; i++ ) {
        index[ i ] = 1;
    }
    Fivecards temp = get_fivecards( index, value );
    Sevencards a_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], ap[ 0 ], ap[ 1 ] );
    Sevencards b_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], bp[ 0 ], bp[ 1 ] );
    if ( a_s.max_fivecards == b_s.max_fivecards ) {
        count_equal += 1;
        if ( a_s.max_fivecards.level == level ) {
            count_level += 1;
            // std::cout << "a_s.max_five:" << a_s.max_fivecards << std::endl;
        }
    }
    if ( b_s.max_fivecards < a_s.max_fivecards )
        count_bigger += 1;
    if ( a_s.max_fivecards < b_s.max_fivecards )
        count_smaller += 1;
    num += 1;
    printf( "num: %d\n", num );
    while ( !judge( n, m, index ) ) { //只要没使1全部移到右边，就继续循环
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( index[ i ] == 1 && index[ i + 1 ] == 0 ) {
                index[ i ] = 0;
                index[ i + 1 ] = 1;
                //将01组合左边的1全部放在数组最左边
                int count = 0;
                for( j = 0; j < i; j++ ) {
                    if ( index[ j ] ) {
                        index[ j ] = 0;
                        index[ count++ ] = 1;
                    }
                }
                Fivecards temp = get_fivecards( index, value );
                Sevencards a_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], ap[ 0 ], ap[ 1 ] );
                Sevencards b_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], bp[ 0 ], bp[ 1 ] );
                if ( a_s.max_fivecards == b_s.max_fivecards ) {
                    count_equal += 1;
                    if ( a_s.max_fivecards.level == level ) {
                        count_level += 1;
                        // std::cout << "a_s.max_five:" << a_s.max_fivecards << std::endl;
                    }
                }
                if ( b_s.max_fivecards < a_s.max_fivecards )
                    count_bigger += 1;
                if ( a_s.max_fivecards < b_s.max_fivecards ) {
                    count_smaller += 1;
                    // std::cout << "a_s.maxfive" << a_s.max_fivecards << std::endl;
                    // std::cout << "b_s.maxfive" << b_s.max_fivecards << std::endl;
                }
                num += 1;
                printf( "num: %d\n", num );
                break;
            }
        }
    }
    std::cout << "共有" << num << "种" << std::endl;
    std::cout << "大于" << count_bigger << "种" << std::endl;
    std::cout << "小于" << count_smaller << "种" << std::endl;
    std::cout << "相等" << count_equal << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
    return ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
}



double wr_bits(  const std::vector< Card >& value, const std::vector< Card >& ap, const std::vector< Card >& bp )  //核心算法函数
{
    int m = 5;
    int n = value.size();
    // int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    std::bitset< 52 > in;
    // memset( index, 0, sizeof( index ) );
    int i, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6, count_omit = 0;
    for ( i = 0; i < m; i++ ) {
        in[ i ] = 1;
    }
    Fivecards temp = get_fivecards( in, value );
    Sevencards a_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], ap[ 0 ], ap[ 1 ] );
    Sevencards b_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], bp[ 0 ], bp[ 1 ] );
    if ( a_s.max_fivecards == b_s.max_fivecards ) {
        count_equal += 1;
        if ( a_s.max_fivecards.level == level ) {
            count_level += 1;
            // std::cout << "a_s.max_five:" << a_s.max_fivecards << std::endl;
        }
    } else if ( b_s.max_fivecards < a_s.max_fivecards )
        count_bigger += 1;
    else if ( a_s.max_fivecards < b_s.max_fivecards )
        count_smaller += 1;
    else {
        count_omit += 1;
        std::cout << temp << std::endl;
    }
    num += 1;
    // printf( "num: %d\n", num );
    while ( !judge( n, m, in ) ) { //只要没使1全部移到右边，就继续循环
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( in[ i ] && !in[ i + 1 ] ) {
                in[ i ] = 0;
                in[ i + 1 ] = 1;
                //将01组合左边的1全部放在数组最左边
                int count = 0;
                for( j = 0; j < i; j++ ) {
                    if ( in[ j ] ) {
                        in[ j ] = 0;
                        in[ count++ ] = 1;
                    }
                }
                Fivecards temp = get_fivecards( in, value );
                Sevencards a_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], ap[ 0 ], ap[ 1 ] );
                Sevencards b_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], bp[ 0 ], bp[ 1 ] );
                if ( a_s.max_fivecards == b_s.max_fivecards ) {
                    count_equal += 1;
                    if ( a_s.max_fivecards.level == level ) {
                        count_level += 1;
                        // std::cout << "a_s.max_five:" << a_s.max_fivecards << std::endl;
                    }
                } else if ( b_s.max_fivecards < a_s.max_fivecards )
                    count_bigger += 1;
                else if ( a_s.max_fivecards < b_s.max_fivecards ) {
                    count_smaller += 1;
                    // std::cout << "a_s.maxfive" << a_s.max_fivecards << std::endl;
                    // std::cout << "b_s.maxfive" << b_s.max_fivecards << std::endl;
                } else {
                    count_omit += 1;
                    std::cout << "omit: " << temp << std::endl;
                }
                num += 1;
                // printf( "num: %d\n", num );
                break;
            }
        }
    }
    std::cout << "共有: " << num << "种" << std::endl;
    std::cout << "大于: " << count_bigger << "种" << std::endl;
    std::cout << "小于: " << count_smaller << "种" << std::endl;
    std::cout << "相等: " << count_equal << "种" << std::endl;
    std::cout << "omit: " << count_omit << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
    return ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
}

struct thread_data {
   int *res;
   int *start;
   int *end;
   std::vector< Card > value;
   std::vector< Card > ap;
   std::vector< Card > bp;
};

void *wr_pthreads( void *thread_arg )  //核心算法函数
// void * wr_threads( int res[], int start[], int end[], const std::vector< Card >& value, const std::vector< Card >& ap, const std::vector< Card >& bp )  //核心算法函数
{
    struct thread_data *t_data;
    t_data = ( struct thread_data * ) thread_arg;
    int *res = t_data->res;
    int *start = t_data->start;
    int *end = t_data->end;
    std::vector< Card > value = t_data->value;
    std::vector< Card > ap = t_data->ap;
    std::vector< Card > bp = t_data->bp;
    int n = value.size();
    int i, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6;
    while ( !judge( n, start, end ) ) { //只要没使1全部移到右边，就继续循环
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( start[ i ] == 1 && start[ i + 1 ] == 0 ) {
                start[ i ] = 0;
                start[ i + 1 ] = 1;
                //将01组合左边的1全部放在数组最左边
                int count = 0;
                for( j = 0; j < i; j++ ) {
                    if ( start[ j ] ) {
                        start[ j ] = 0;
                        start[ count++ ] = 1;
                    }
                }
                Fivecards temp = get_fivecards( start, value );
                Sevencards a_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], ap[ 0 ], ap[ 1 ] );
                Sevencards b_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], bp[ 0 ], bp[ 1 ] );
                if ( a_s.max_fivecards == b_s.max_fivecards ) {
                    count_equal += 1;
                    if ( a_s.max_fivecards.level == level ) {
                        count_level += 1;
                        // std::cout << "a_s.max_five:" << a_s.max_fivecards << std::endl;
                    }
                }
                if ( b_s.max_fivecards < a_s.max_fivecards )
                    count_bigger += 1;
                if ( a_s.max_fivecards < b_s.max_fivecards ) {
                    count_smaller += 1;
                    // std::cout << "a_s.maxfive" << a_s.max_fivecards << std::endl;
                    // std::cout << "b_s.maxfive" << b_s.max_fivecards << std::endl;
                }
                num += 1;
                // printf( "num: %d\n", num );
                break;
            }
        }
    }
    // assert( num == count_bigger + count_smaller + count_equal );
    res[ 0 ] = count_bigger;
    res[ 1 ] = count_smaller;
    res[ 2 ] = count_equal;
    std::cout << "共有" << num << "种" << std::endl;
    std::cout << "大于" << count_bigger << "种" << std::endl;
    std::cout << "小于" << count_smaller << "种" << std::endl;
    std::cout << "相等" << count_equal << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
    // double wr = ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
    return 0;
}

void wr_threads( const std::vector< Card >& value, int start[], int end[], int res[], const std::vector< Card >& ap, const std::vector< Card >& bp )  //核心算法函数
// void * wr_threads( int res[], int start[], int end[], const std::vector< Card >& value, const std::vector< Card >& ap, const std::vector< Card >& bp )  //核心算法函数
{
    int n = value.size();
    int i, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6;
    while ( !judge( n, start, end ) ) { //只要没使1全部移到右边，就继续循环
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( start[ i ] == 1 && start[ i + 1 ] == 0 ) {
                start[ i ] = 0;
                start[ i + 1 ] = 1;
                //将01组合左边的1全部放在数组最左边
                int count = 0;
                for( j = 0; j < i; j++ ) {
                    if ( start[ j ] ) {
                        start[ j ] = 0;
                        start[ count++ ] = 1;
                    }
                }
                Fivecards temp = get_fivecards( start, value );
                Sevencards a_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], ap[ 0 ], ap[ 1 ] );
                Sevencards b_s( temp.fivecards[ 0 ], temp.fivecards[ 1 ], temp.fivecards[ 2 ], temp.fivecards[ 3 ], temp.fivecards[ 4 ], bp[ 0 ], bp[ 1 ] );
                if ( a_s.max_fivecards == b_s.max_fivecards ) {
                    count_equal += 1;
                    if ( a_s.max_fivecards.level == level ) {
                        count_level += 1;
                        // std::cout << "a_s.max_five:" << a_s.max_fivecards << std::endl;
                    }
                }
                if ( b_s.max_fivecards < a_s.max_fivecards )
                    count_bigger += 1;
                if ( a_s.max_fivecards < b_s.max_fivecards ) {
                    count_smaller += 1;
                    // std::cout << "a_s.maxfive" << a_s.max_fivecards << std::endl;
                    // std::cout << "b_s.maxfive" << b_s.max_fivecards << std::endl;
                }
                num += 1;
                // printf( "num: %d\n", num );
                break;
            }
        }
    }
    // assert( num == count_bigger + count_smaller + count_equal );
    res[ 0 ] = count_bigger;
    res[ 1 ] = count_smaller;
    res[ 2 ] = count_equal;
    std::cout << "共有" << num << "种" << std::endl;
    std::cout << "大于" << count_bigger << "种" << std::endl;
    std::cout << "小于" << count_smaller << "种" << std::endl;
    std::cout << "相等" << count_equal << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
    // double wr = ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
}

uint64_t get_5_bits( int index[] ) {
    uint64_t ret = 0ULL;
    for ( int i = 0; i < 52; ++ i ) {
        if ( index[ i ] == 1 ) {
            uint64_t tmp = 1ULL << i;
            ret |= tmp;
        }
    }
    return ret;
}

void set_index_by_cards( uint64_t cards, int m, int index[], int n ) {
    // memset( index, 0, n * sizeof( int ) );
    for ( int j = 0; j < n; ++ j ) assert( !index[ j ] );
    int i = 0;
    int count = 0;
    while ( cards && i < 52 && count < m ) {
        index[ i ] = ( int ) ( cards & 1ULL );
        if ( index[ i ] )
            count ++;
        i ++;
        cards >>= 1;
    }
}

void get_values_rightmost( int values[], int values_rightmost[], int n ) {
    // memset( values_rightmost, 0, sizeof( values_rightmost ) );
    for ( int j = 0; j < n; ++ j ) {
        assert( !values_rightmost[ j ] );
    }
    int i = 0;
    int k = 51;
    while ( i < 5 && k >= 0 ) {
        if ( values[ k ] == 1 ) {
            values_rightmost[ k ] = 1;
            i ++;
        }
        k --;
    }
}

void get_2_rightmost( int values[], int values_rightmost[], int n ) {
    // memset( values_rightmost, 0, sizeof( values_rightmost ) );
    for ( int j = 0; j < n; ++ j ) {
        assert( !values_rightmost[ j ] );
    }
    int i = 0;
    int k = 51;
    while ( i < 2 && k >= 0 ) {
        if ( values[ k ] == 1 ) {
            values_rightmost[ k ] = 1;
            i ++;
        }
        k --;
    }
}

void get_1_rightmost( int values[], int values_rightmost[], int n ) {
    // memset( values_rightmost, 0, sizeof( values_rightmost ) );
    for ( int j = 0; j < n; ++ j ) {
        assert( !values_rightmost[ j ] );
    }
    int i = 0;
    int k = 51;
    while ( i < 1 && k >= 0 ) {
        if ( values[ k ] == 1 ) {
            values_rightmost[ k ] = 1;
            i ++;
        }
        k --;
    }
}

void get_7_values_rightmost( int values[], int values_rightmost[], int n ) {
    // memset( values_rightmost, 0, sizeof( values_rightmost ) );
    for ( int j = 0; j < n; ++ j ) {
        assert( !values_rightmost[ j ] );
    }
    int i = 0;
    int k = 51;
    while ( i < 7 && k >= 0 ) {
        if ( values[ k ] == 1 ) {
            values_rightmost[ k ] = 1;
            i ++;
        }
        k --;
    }
}

bool judge_bits( int index[], int values_rightmost[] )
{
    int i;
    for ( i = 51; i >= 0; i -- ) {
        if ( index[ i ] != values_rightmost[ i ] )  
            return false;
    }
    return true;
}

// Fivecards max_five_in_seven( const std::vector< Card >& value )  //核心算法函数
uint64_t max_fc_in_sc( uint64_t sc, std::unordered_map< uint64_t, int >& mp ) {
    // int m = 5;
    // assert( popcnt( sc ) == 7 );
    int n = 52;
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int values[ 52 ];
    memset( values, 0, sizeof( values ) );
    set_index_by_cards( sc, 7, values, 52 );
    // std::cout << "358: " << popcnt( get_5_bits( values ) ) << std::endl;
    // assert( popcnt( get_5_bits( values ) ) == 7 );
    
    int num = 0;
    int i = 0;
    int j;
    int k = 0;
    while ( i < 5 && k < 51 ) {
        if ( values[ k ] == 1 ) {
            index[ k ] = 1;
            i ++;
        }
        k ++;
    }
    num += 1;
    uint64_t res = get_5_bits( index );
    // assert( popcnt( res ) == 5 );

    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        int values_rightmost[ 52 ];
        memset( values_rightmost, 0, sizeof( values_rightmost ) );
        get_values_rightmost( values, values_rightmost, 52 );
        // assert( popcnt( get_5_bits( values_rightmost ) ) == 5 );
        if ( judge_bits( index, values_rightmost ) )
            is_over = true;
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            //找到10，变成01
            if ( index[ i ] == 1 ) {
                int next = i + 1;
                while ( !values[ next ] && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                if ( index[ next ] == 0 ) {
                    index[ i ] = 0;
                    index[ next ] = 1;
                    //将01组合左边的1全部放在数组最左边
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        if ( index[ j ] ) {
                            index[ j ] = 0;
                            while ( !values[ count ] ) {
                                count ++;
                            }
                            index[ count++ ] = 1;
                        }
                    }
                    // std::cout << "res: " << res << " " << res.level << std::endl;
                    // std::cout << "get: " << get_fivecards( index, value ) << " " << get_fivecards( index, value ).level << std::endl;
                    // std::cout << ccc ++ << std::endl;
                    if ( mp[ res ] < mp[ get_5_bits( index ) ] ) {
                        res = get_5_bits( index );
                    }
                    num += 1;
                    break;
                }
            }
        }
    }
    // std::sort( res.fivecards, res.fivecards + 5 );
    // std::cout << "num: " << num << std::endl;
    // assert( num == 21 );
    return res;
}

double wr_fast( uint64_t hc_a, uint64_t hc_b, std::unordered_map< uint64_t, int >& mp ) 
{
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 ) ^ hc_a ^ hc_b;
    // assert( popcnt( left_cards ) == 48 );
    int lc[ 52 ];
    memset( lc, 0, sizeof( lc ) );
    set_index_by_cards( left_cards, 48, lc, 52 );
    // assert( popcnt( get_5_bits( lc ) ) == 48 );
    int m = 5;
    int n = 52;
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i = 0, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6, count_omit = 0;
    int k = 0;
    while ( i < 5 && k < 51 ) {
        if ( lc[ k ] == 1 ) {
            index[ k ] = 1;
            i ++;
        }
        k ++;
    }
    uint64_t fc_tmp = get_5_bits( index );
    uint64_t sc_a = fc_tmp | hc_a;
    uint64_t sc_b = fc_tmp | hc_b;
    // assert( popcnt( sc_a ) == 7 );
    // assert( popcnt( sc_b ) == 7 );

    if ( max_fc_in_sc( sc_a, mp ) == max_fc_in_sc( sc_b, mp ) ) {
        count_equal += 1;
    } else if ( mp[ max_fc_in_sc( sc_b, mp ) ] < mp[ max_fc_in_sc( sc_a, mp ) ] )
        count_bigger += 1;
    else if ( mp[ max_fc_in_sc( sc_a, mp ) ] == mp[ max_fc_in_sc( sc_b, mp ) ] ) 
        count_equal += 1;
    num += 1;
    // printf( "num: %d\n", num );
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        // assert( popcnt( get_5_bits( index ) ) == 5 );
        int debug = 0;
        if ( num >= 194581 ) {
            debug ++;
        }
        int lc_rightmost[ 52 ];
        memset( lc_rightmost, 0, sizeof( lc_rightmost ) );
        get_values_rightmost( lc, lc_rightmost, 52 );
        // assert( popcnt( get_5_bits( lc_rightmost ) ) == 5 );
        if ( judge_bits( index, lc_rightmost ) )
            is_over = true;
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( index[ i ] == 1 ) {
                int next = i + 1;
                while ( !lc[ next ] && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                if ( index[ next ] == 0 ) {
                    index[ i ] = 0;
                    index[ next ] = 1;
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        if ( index[ j ] ) {
                            index[ j ] = 0;
                            while ( !lc[ count ] ) {
                                count ++;
                            }
                            index[ count++ ] = 1;
                        }
                    }
                    uint64_t fc_tmp = get_5_bits( index );
                    uint64_t sc_a = fc_tmp | hc_a;
                    uint64_t sc_b = fc_tmp | hc_b;

                    if ( max_fc_in_sc( sc_a, mp ) == max_fc_in_sc( sc_b, mp ) ) {
                        count_equal += 1;
                    } else if ( mp[ max_fc_in_sc( sc_b, mp ) ] < mp[ max_fc_in_sc( sc_a, mp ) ] )
                        count_bigger += 1;
                    else if ( mp[ max_fc_in_sc( sc_a, mp ) ] == mp[ max_fc_in_sc( sc_b, mp ) ] )
                        count_equal += 1;
                    num += 1;
                    break;
                }
            }
        }
    }
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
    std::cout << "大于: " << count_bigger << "种" << std::endl;
    std::cout << "小于: " << count_smaller << "种" << std::endl;
    std::cout << "相等: " << count_equal << "种" << std::endl;
    std::cout << "omit: " << count_omit << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
    return ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
}

double wr_total_bits( uint64_t hc_a, uint64_t hc_b, std::unordered_map< uint64_t, int >& mp ) 
{
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 ) ^ hc_a ^ hc_b;
    // assert( popcnt( left_cards ) == 48 );
    uint64_t ind = left_cards;
    for ( int jj = 0; jj < 5; ++ jj ) {
        ind = ind & ( ind - 1 );
    }
    ind = ind ^ left_cards;
    // assert( popcnt( ind ) == 5 );

    int i = 0, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6;
    uint64_t sc_a = ind | hc_a;
    uint64_t sc_b = ind | hc_b;
    // assert( popcnt( sc_a ) == 7 );
    // assert( popcnt( sc_b ) == 7 );
    if ( ( max_fc_in_sc( sc_a, mp ) ^ max_fc_in_sc( sc_b, mp ) ) == 0ULL ) {
        count_equal += 1;
    }
    if ( mp[ max_fc_in_sc( sc_b, mp ) ] < mp[ max_fc_in_sc( sc_a, mp ) ] )
        count_bigger += 1;
    num += 1;
    // while ( !judge( n, m, index ) ) { //只要没使1全部移到右边，就继续循环
    // while ( judge_bits( index, lc ) ) { //只要没使1全部移到右边，就继续循环
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        // assert( popcnt( ind ) == 5 );
        uint64_t lc_leftmost = left_cards;
        while ( popcnt( lc_leftmost ) > 5 ) {
            lc_leftmost = lc_leftmost & ( lc_leftmost - 1 );
        }
        // assert( popcnt( lc_leftmost ) == 5 );
        if ( ind == lc_leftmost )
            is_over = true;
        for( i = 0; i < 51; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( ( ( ind >> i ) & 1ULL ) == 1 ) {
                int next = i + 1;
                // while ( !lc[ next ] && next < 52 ) {
                while ( !( ( left_cards >> next ) & 1ULL ) && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                // if ( index[ next ] == 0 ) {
                if ( ( ( ind >> next ) & 1ULL ) == 0 ) {
                    // if ( debug ) std::cout << "3: " << debug << std::endl;
                    uint64_t tmp_i = 1ULL << i;
                    uint64_t tmp_next = 1ULL << next;
                    ind = ind ^ tmp_i ^ tmp_next;
                    //将01组合左边的1全部放在数组最左边
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        // if ( index[ j ] ) {
                        if ( ( ( ind >> j ) & 1ULL ) ) {
                            uint64_t tmp_j = 1ULL << j;
                            ind = ind ^ tmp_j;
                            // index[ j ] = 0;
                            // while ( !lc[ count ] ) {
                            while ( !( ( left_cards >> count ) & 1ULL ) ) {
                                count ++;
                            }
                            uint64_t tmp_count = 1ULL << count;
                            ind = ind ^ tmp_count;
                            count ++;
                            // index[ count++ ] = 1;
                        }
                    }
                    uint64_t sc_a = ind | hc_a;
                    uint64_t sc_b = ind | hc_b;
                    assert( popcnt( sc_a ) == 7 );
                    assert( popcnt( sc_b ) == 7 );

                    if ( ( max_fc_in_sc( sc_a, mp ) ^ max_fc_in_sc( sc_b, mp ) ) == 0ULL ) {
                        count_equal += 1;
                    }
                    if ( mp[ max_fc_in_sc( sc_b, mp ) ] < mp[ max_fc_in_sc( sc_a, mp ) ] )
                        count_bigger += 1;
                    num += 1;
                    // printf( "num: %d\n", num );
                    break;
                }
            }
        }
    }
    std::cout << "共有" << num << "种" << std::endl;
    std::cout << "大于" << count_bigger << "种" << std::endl;
    std::cout << "小于" << count_smaller << "种" << std::endl;
    std::cout << "相等" << count_equal << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
    return ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
}

double wr_total_bits_v1( uint64_t hc_a, uint64_t hc_b, std::unordered_map< uint64_t, int >& mp ) 
{
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 ) ^ hc_a ^ hc_b;
    // assert( popcnt( left_cards ) == 48 );
    uint64_t ind = left_cards;
    for ( int jj = 0; jj < 5; ++ jj ) {
        ind = ind & ( ind - 1 );
    }
    ind = ind ^ left_cards;
    // assert( popcnt( ind ) == 5 );

    int j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6;
    uint64_t sc_a = ind | hc_a;
    uint64_t sc_b = ind | hc_b;
    // assert( popcnt( sc_a ) == 7 );
    // assert( popcnt( sc_b ) == 7 );
    /*
    if ( ( max_fc_in_sc( sc_a, mp ) ^ max_fc_in_sc( sc_b, mp ) ) == 0ULL ) {
        count_equal += 1;
    }
    if ( mp[ max_fc_in_sc( sc_b, mp ) ] < mp[ max_fc_in_sc( sc_a, mp ) ] )
        count_bigger += 1;
    */
    num += 1;
    printf( "num: %d\n", num );
    // while ( !judge( n, m, index ) ) { //只要没使1全部移到右边，就继续循环
    // while ( judge_bits( index, lc ) ) { //只要没使1全部移到右边，就继续循环
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        assert( popcnt( ind ) == 5 );
        uint64_t lc_leftmost = left_cards;
        while ( popcnt( lc_leftmost ) > 5 ) {
            lc_leftmost = lc_leftmost & ( lc_leftmost - 1 );
        }
        assert( popcnt( lc_leftmost ) == 5 );
        if ( ind == lc_leftmost )
            is_over = true;
        for( int i = 0; i < 51; i++ ) {
            if ( ( ( ind >> i ) & 1ULL ) == 1 ) {
                int next = i + 1;
                // while ( !lc[ next ] && next < 52 ) {
                while ( !( ( left_cards >> next ) & 1ULL ) && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                // if ( index[ next ] == 0 ) {
                if ( ( ( ind >> next ) & 1ULL ) == 0 ) {
                    // is_10_found = true;
                    // if ( debug ) std::cout << "3: " << debug << std::endl;
                    uint64_t tmp_i = 1ULL << i;
                    uint64_t tmp_next = 1ULL << next;
                    ind = ind ^ tmp_i ^ tmp_next;
                    //将01组合左边的1全部放在数组最左边
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        // if ( index[ j ] ) {
                        if ( ( ( ind >> j ) & 1ULL ) ) {
                            uint64_t tmp_j = 1ULL << j;
                            ind = ind ^ tmp_j;
                            // index[ j ] = 0;
                            // while ( !lc[ count ] ) {
                            while ( !( ( left_cards >> count ) & 1ULL ) ) {
                                count ++;
                            }
                            uint64_t tmp_count = 1ULL << count;
                            ind = ind ^ tmp_count;
                            count ++;
                            // index[ count++ ] = 1;
                        }
                    }
                    uint64_t sc_a = ind | hc_a;
                    uint64_t sc_b = ind | hc_b;
                    // assert( popcnt( sc_a ) == 7 );
                    // assert( popcnt( sc_b ) == 7 );
                    /*
                    if ( ( max_fc_in_sc( sc_a, mp ) ^ max_fc_in_sc( sc_b, mp ) ) == 0ULL ) {
                        count_equal += 1;
                    }
                    if ( mp[ max_fc_in_sc( sc_b, mp ) ] < mp[ max_fc_in_sc( sc_a, mp ) ] )
                        count_bigger += 1;
                    */
                    num += 1;
                    printf( "num: %d\n", num );
                    break;
                }
            }
        }
    }
    std::cout << "共有" << num << "种" << std::endl;
    std::cout << "大于" << count_bigger << "种" << std::endl;
    std::cout << "小于" << count_smaller << "种" << std::endl;
    std::cout << "相等" << count_equal << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
    return ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
}

void generate_all_7( const Poker& p, std::vector< Sevencards >& ret )  //核心算法函数
{
    const std::vector< Card >& value = p.cards;
    int m = 7;
    int n = value.size();
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i, j, num = 0;
    for ( i = 0; i < m; i++ ) {
        index[ i ] = 1;
    }
    Sevencards temp = get_sevencards( index, value );
    // ret.emplace_back( temp );
    num += 1;
    // printf( "%d\n", num );
    while ( !judge( n, m, index ) ) { //只要没使1全部移到右边，就继续循环
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            //找到10，变成01
            if ( index[ i ] == 1 && index[ i + 1 ] == 0 ) {
                index[ i ] = 0;
                index[ i + 1 ] = 1;
                //将01组合左边的1全部放在数组最左边
                int count = 0;
                for( j = 0; j < i; j++ ) {
                    if ( index[ j ] ) {
                        index[ j ] = 0;
                        index[ count++ ] = 1;
                    }
                }
                Sevencards temp = get_sevencards( index, value );
                // ret.emplace_back( temp );
                num += 1;
                // printf( "%d\n", num );
                break;
            }
        }
    }
    std::cout << "共有" << num << "种" << std::endl;
}
uint32_t hash_num[ 13 ] = { 0U, 1U, 5U, 22U, 98U, 453U, 2031U, 8698U, 22854U, 83661U, 262349U, 636345U, 1479181U };
uint32_t hash_n( uint64_t sc ) {
    assert( popcnt( sc ) == 7 );
    uint32_t hash_value = 0U;
    uint64_t copy_sc = sc;
    while ( copy_sc ) {
        int one_pos = xsl_bsf( copy_sc );
        hash_value += hash_num[ one_pos / 4 ];
        copy_sc = copy_sc & ( copy_sc - 1 );
    }
    return hash_value;
}

uint32_t hash_suit[ 4 ] = { 0U, 1U, 8U, 57U };
uint32_t hash_s( uint64_t sc ) {
    assert( popcnt( sc ) == 7 );
    uint32_t hash_su = 0U;
    while ( sc ) {
        int one_pos = xsl_bsf( sc );
        switch ( one_pos % 4 ) {
        case 0:
            hash_su += 0;
            break;
        case 1:
            hash_su += 1;
            break;
        case 2:
            hash_su += 8;
            break;
        case 3:
            hash_su += 57;
            break;
        default:
            std::cout << "Error!!!" << std::endl;
            exit( -2 );
        }
        sc = sc & ( sc - 1 );
    }
    return hash_su;
}

std::unordered_set< uint32_t > flush_set {  0U, 
                                            1U, 8U, 57U, 
                                            9U, 58U, 65U, 
                                            2U, 16U, 114U, 
                                            7U, 
                                            6U, 14U, 63U, 
                                            13U, 62U, 70U, 
                                            5U, 21U, 119,
                                            56U, 
                                            48U, 49U, 105U, 
                                            41U, 97U, 98U, 
                                            40U, 42U, 154U,
                                            399U, 
                                            342U, 343U, 350U, 
                                            286U, 293U, 294U,
                                            285U, 287U, 301U };

bool is_fc_flush_in_sc( uint64_t sc ) {
    uint32_t hash_su = hash_s( sc );
    switch ( flush_set.count( hash_su ) ) {
    case 1 :
        return true;
    case 0:
        return false;
    default:
        exit( -3 );
    }
}

void generate_fast( std::unordered_map< uint64_t, int >& mp, std::unordered_map< uint64_t, uint32_t >& mp_7 ) {
    uint64_t left_cards = ( 1ULL << 52 ) - 1;
    assert( popcnt( left_cards ) == 52 );
    int lc[ 52 ];
    memset( lc, 0, sizeof( lc ) );
    set_index_by_cards( left_cards, 52, lc, 52 );
    assert( popcnt( get_5_bits( lc ) ) == 52 );
    int m = 7;
    int n = 52;
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i = 0, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6, count_omit = 0;
    int k = 0;
    while ( i < 7 && k < 51 ) {
        if ( lc[ k ] == 1 ) {
            index[ k ] = 1;
            i ++;
        }
        k ++;
    }
    uint64_t sc_tmp = get_5_bits( index );
    assert( popcnt( sc_tmp ) == 7 );
    int rank = mp[ max_fc_in_sc( sc_tmp, mp ) ];
    uint32_t urank = ( uint32_t ) rank;
    uint64_t key = 0ULL;
    if ( is_fc_flush_in_sc( sc_tmp ) ) {
        key = ( 1ULL << 63 ) | sc_tmp;
    } else {
        key = ( uint64_t ) hash_n( sc_tmp );
    }

    if ( mp_7.find( key ) == mp_7.end() ) {
        mp_7[ key ] = urank;
    }
    num += 1;
    // printf( "num: %d\n", num );
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        assert( popcnt( get_5_bits( index ) ) == 7 );
        int lc_rightmost[ 52 ];
        memset( lc_rightmost, 0, sizeof( lc_rightmost ) );
        get_7_values_rightmost( lc, lc_rightmost, 52 );
        assert( popcnt( get_5_bits( lc_rightmost ) ) == 7 );
        if ( judge_bits( index, lc_rightmost ) )
            is_over = true;
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( index[ i ] == 1 ) {
                int next = i + 1;
                while ( !lc[ next ] && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                if ( index[ next ] == 0 ) {
                    index[ i ] = 0;
                    index[ next ] = 1;
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        if ( index[ j ] ) {
                            index[ j ] = 0;
                            while ( !lc[ count ] ) {
                                count ++;
                            }
                            index[ count++ ] = 1;
                        }
                    }
                    uint64_t sc_tmp = get_5_bits( index );
                    assert( popcnt( sc_tmp ) == 7 );

                    int rank = mp[ max_fc_in_sc( sc_tmp, mp ) ];
                    uint32_t urank = ( uint32_t ) rank;
                    uint64_t key = 0ULL;
                    if ( is_fc_flush_in_sc( sc_tmp ) ) {
                        key = ( 1ULL << 63 ) | sc_tmp;;
                    } else {
                        key = ( uint64_t ) hash_n( sc_tmp );
                    }

                    if ( mp_7.find( key ) == mp_7.end() ) {
                        mp_7[ key ] = urank;
                    }
                    num += 1;
                    if ( num % 1000000 == 0 )
                        printf( "num: %d\n", num );
                    break;
                }
            }
        }
    }
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
}

double wr_final( uint64_t hc_a, uint64_t hc_b, std::unordered_map< uint64_t, int >& mp, std::unordered_map< uint64_t, uint32_t >& mp_7 )
{
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 ) ^ hc_a ^ hc_b;
    assert( popcnt( left_cards ) == 48 );
    int lc[ 52 ];
    memset( lc, 0, sizeof( lc ) );
    set_index_by_cards( left_cards, 48, lc, 52 );
    assert( popcnt( get_5_bits( lc ) ) == 48 );
    int m = 5;
    int n = 52;
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i = 0, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6, count_omit = 0;
    int k = 0;
    while ( i < 5 && k < 51 ) {
        if ( lc[ k ] == 1 ) {
            index[ k ] = 1;
            i ++;
        }
        k ++;
    }
    
    uint64_t fc_tmp = get_5_bits( index );
    uint64_t sc_a = fc_tmp | hc_a;
    uint64_t sc_b = fc_tmp | hc_b;
    assert( popcnt( sc_a ) == 7 );
    assert( popcnt( sc_b ) == 7 );

    uint64_t key_a = 0ULL;
    uint64_t key_b = 0ULL;
    if ( is_fc_flush_in_sc( sc_a ) ) {
        key_a = ( 1ULL << 63 ) | sc_a;
    } else {
        key_a = ( uint64_t ) hash_n( sc_a );
    }
    if ( is_fc_flush_in_sc( sc_b ) ) {
        key_b = ( 1ULL << 63 ) | sc_b;
    } else {
        key_b = ( uint64_t ) hash_n( sc_b );
    }
    
    if ( mp_7[ key_a ] == mp_7[ key_b ] ) {
        count_equal += 1;
    } else if ( mp_7[ key_a ] > mp_7[ key_b ] )
        count_bigger += 1;
    else if ( mp_7[ key_a ] < mp_7[ key_b ] )
        count_smaller += 1;
    else {
        count_omit ++;
    }
    
    num += 1;
    // printf( "num: %d\n", num );
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        assert( popcnt( get_5_bits( index ) ) == 5 );
        int debug = 0;
        if ( num >= 194581 ) {
            debug ++;
        }
        int lc_rightmost[ 52 ];
        memset( lc_rightmost, 0, sizeof( lc_rightmost ) );
        get_values_rightmost( lc, lc_rightmost, 52 );
        assert( popcnt( get_5_bits( lc_rightmost ) ) == 5 );
        if ( judge_bits( index, lc_rightmost ) )
            is_over = true;
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( index[ i ] == 1 ) {
                int next = i + 1;
                while ( !lc[ next ] && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                if ( index[ next ] == 0 ) {
                    index[ i ] = 0;
                    index[ next ] = 1;
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        if ( index[ j ] ) {
                            index[ j ] = 0;
                            while ( !lc[ count ] ) {
                                count ++;
                            }
                            index[ count++ ] = 1;
                        }
                    }
                    
                    uint64_t fc_tmp = get_5_bits( index );
                    uint64_t sc_a = fc_tmp | hc_a;
                    uint64_t sc_b = fc_tmp | hc_b;
                    assert( popcnt( sc_a ) == 7 );
                    assert( popcnt( sc_b ) == 7 );

                    uint64_t key_a = 0ULL;
                    uint64_t key_b = 0ULL;
                    if ( is_fc_flush_in_sc( sc_a ) ) {
                        key_a = ( 1ULL << 63 ) | sc_a;
                    } else {
                        key_a = ( uint64_t ) hash_n( sc_a );
                    }
                    if ( is_fc_flush_in_sc( sc_b ) ) {
                        key_b = ( 1ULL << 63 ) | sc_b;
                    } else {
                        key_b = ( uint64_t ) hash_n( sc_b );
                    }
                    
                    if ( mp_7[ key_a ] == mp_7[ key_b ] ) {
                        count_equal += 1;
                    } else if ( mp_7[ key_a ] > mp_7[ key_b ] )
                        count_bigger += 1;
                    else if ( mp_7[ key_a ] < mp_7[ key_b ] )
                        count_smaller += 1;
                    else {
                        count_omit ++;
                    }
                    
                    num += 1;
                    // printf( "num: %d\n", num );
                    break;
                }
            }
        }
    }
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
    std::cout << "大于: " << count_bigger << "种" << std::endl;
    std::cout << "小于: " << count_smaller << "种" << std::endl;
    std::cout << "相等: " << count_equal << "种" << std::endl;
    std::cout << "omit: " << count_omit << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
    return ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
}

uint64_t random_fc( uint64_t hc_a, uint64_t hc_b ) {
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 ) ^ hc_a ^ hc_b;
    assert( popcnt( left_cards ) == 48 );
    uint64_t ret = 0ULL;
    while ( popcnt( ret ) < 5 ) {
        int r = rand() % 52;
        uint64_t tmp = 1ULL << r;
        if ( tmp & left_cards ) {
            ret = ret | tmp;
        }
    }
    return ret;
}

double wr_montecado( uint64_t hc_a, uint64_t hc_b, std::unordered_map< uint64_t, int >& mp ) 
{
    srand( ( unsigned int ) ( time( NULL ) ) );
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 ) ^ hc_a ^ hc_b;
    assert( popcnt( left_cards ) == 48 );
    int lc[ 52 ];
    memset( lc, 0, sizeof( lc ) );
    set_index_by_cards( left_cards, 48, lc, 52 );
    assert( popcnt( get_5_bits( lc ) ) == 48 );
    int m = 5;
    int n = 52;
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i = 0, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6, count_omit = 0;
    int k = 0;
    for ( int ii = 0; ii < 10000; ++ ii ) {
        uint64_t fc_tmp = random_fc( hc_a, hc_b );
        uint64_t sc_a = fc_tmp | hc_a;
        uint64_t sc_b = fc_tmp | hc_b;
        assert( popcnt( sc_a ) == 7 );
        assert( popcnt( sc_b ) == 7 );

        if ( max_fc_in_sc( sc_a, mp ) == max_fc_in_sc( sc_b, mp ) ) {
            count_equal += 1;
        } else if ( mp[ max_fc_in_sc( sc_b, mp ) ] < mp[ max_fc_in_sc( sc_a, mp ) ] )
            count_bigger += 1;
        else if ( mp[ max_fc_in_sc( sc_a, mp ) ] < mp[ max_fc_in_sc( sc_b, mp ) ] )
            count_smaller += 1;
        else {
            count_omit ++;
            count_equal += 1;
        }
        num += 1;
    }
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
    std::cout << "大于: " << count_bigger << "种" << std::endl;
    std::cout << "小于: " << count_smaller << "种" << std::endl;
    std::cout << "相等: " << count_equal << "种" << std::endl;
    std::cout << "omit: " << count_omit << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
    return ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
}

uint16_t get_rank( uint64_t sc ) {
    assert( popcnt( sc ) == 7 );
    int cards[ 7 ];
    memset( cards, 0, sizeof( cards ) );
    for ( int i = 0; i < 7; ++ i ) {
        cards[ i ] = xsl_bsf( sc );
        sc = sc & ( sc - 1 );
    }
    return SevenEval::GetRank( cards[ 0 ], cards[ 1 ], cards[ 2 ], cards[ 3 ], cards[ 4 ], cards[ 5 ], cards[ 6 ] ); 
}

double wr_SK( uint64_t hc_a, uint64_t hc_b ) 
{
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 ) ^ hc_a ^ hc_b;
    assert( popcnt( left_cards ) == 48 );
    int lc[ 52 ];
    memset( lc, 0, sizeof( lc ) );
    set_index_by_cards( left_cards, 48, lc, 52 );
    assert( popcnt( get_5_bits( lc ) ) == 48 );
    int m = 5;
    int n = 52;
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i = 0, j, num = 0, count_bigger = 0, count_equal = 0, count_smaller = 0, count_level = 0, level = 6, count_omit = 0;
    int k = 0;
    while ( i < 5 && k < 51 ) {
        if ( lc[ k ] == 1 ) {
            index[ k ] = 1;
            i ++;
        }
        k ++;
    }
    uint64_t fc_tmp = get_5_bits( index );
    uint64_t sc_a = fc_tmp | hc_a;
    uint64_t sc_b = fc_tmp | hc_b;
    assert( popcnt( sc_a ) == 7 );
    assert( popcnt( sc_b ) == 7 );

    // std::cout << "a: " << std::hex << sc_a << "<->" << std::dec << get_rank( sc_a ) << std::endl;
    // std::cout << "b: " << std::hex << sc_b << "<->" << std::dec << get_rank( sc_b ) << std::endl;

    if ( get_rank( sc_a ) == get_rank( sc_b ) ) {
        count_equal += 1;
    } else if ( get_rank( sc_a ) > get_rank( sc_b )  )
        count_bigger += 1;
    else if ( get_rank( sc_a ) < get_rank( sc_b )  )
        count_smaller += 1;
    else {
        count_omit ++;
        // std::cout << std::hex << fc_tmp << std::endl;
    }
    num += 1;
    // printf( "num: %d\n", num );
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        assert( popcnt( get_5_bits( index ) ) == 5 );
        int debug = 0;
        if ( num >= 194581 ) {
            debug ++;
        }
        int lc_rightmost[ 52 ];
        memset( lc_rightmost, 0, sizeof( lc_rightmost ) );
        get_values_rightmost( lc, lc_rightmost, 52 );
        assert( popcnt( get_5_bits( lc_rightmost ) ) == 5 );
        if ( judge_bits( index, lc_rightmost ) )
            is_over = true;
        for( i = 0; i < n - 1; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( index[ i ] == 1 ) {
                int next = i + 1;
                while ( !lc[ next ] && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                if ( index[ next ] == 0 ) {
                    index[ i ] = 0;
                    index[ next ] = 1;
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        if ( index[ j ] ) {
                            index[ j ] = 0;
                            while ( !lc[ count ] ) {
                                count ++;
                            }
                            index[ count++ ] = 1;
                        }
                    }
                    uint64_t fc_tmp = get_5_bits( index );
                    uint64_t sc_a = fc_tmp | hc_a;
                    uint64_t sc_b = fc_tmp | hc_b;

                    if ( get_rank( sc_a ) == get_rank( sc_b ) ) {
                        count_equal += 1;
                    } else if ( get_rank( sc_a ) > get_rank( sc_b )  )
                        count_bigger += 1;
                    else if ( get_rank( sc_a ) < get_rank( sc_b )  )
                        count_smaller += 1;
                    else {
                        count_omit ++;
                        // std::cout << std::hex << fc_tmp << std::endl;
                    }
                    num += 1;
                    // std::cout << "a: " << std::hex << sc_a << "<->" << std::dec << get_rank( sc_a ) << std::endl;
                    // std::cout << "b: " << std::hex << sc_b << "<->" << std::dec << get_rank( sc_b ) << std::endl;
                    // printf( "num: %d\n", num );
                    break;
                }
            }
        }
    }
#if DEBUG
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
    std::cout << "大于: " << count_bigger << "种" << std::endl;
    std::cout << "小于: " << count_smaller << "种" << std::endl;
    std::cout << "相等: " << count_equal << "种" << std::endl;
#endif
    assert( num == count_bigger + count_equal + count_smaller );
    return ( count_bigger + ( double ) count_equal / 2 ) / ( double ) num;
}

std::vector< double > wr_preflop( const std::vector< uint64_t >& hcs ) {
    int num_players = hcs.size();
    assert( 1 < num_players && num_players < 24 );
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 );
    uint64_t overlap_flag = 0ULL;
    for ( int i = 0; i < num_players; ++ i ) {
        assert( popcnt( hcs[ i ] ) == 2 );
        overlap_flag = overlap_flag | hcs[ i ];
        left_cards = left_cards ^ hcs[ i ];
    }
    assert( popcnt( overlap_flag ) == 2 * num_players );
    assert( popcnt( left_cards ) == 52 - num_players * 2 );
    assert( xsl_bsr( left_cards ) < 52 ); 

    int lc[ 52 ];
    memset( lc, 0, sizeof( lc ) );
    set_index_by_cards( left_cards, 52 - num_players * 2, lc, 52 );
    assert( popcnt( get_5_bits( lc ) ) == 52 - num_players * 2 );

    int index[ 52 ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i = 0, j, num = 0;
    int k = 0;
    double count_bigest[ num_players ];
    memset( count_bigest, 0, sizeof( count_bigest ) );
    while ( i < 5 && k < 51 ) {
        if ( lc[ k ] == 1 ) {
            index[ k ] = 1;
            i ++;
        }
        k ++;
    }
    uint64_t fc_tmp = get_5_bits( index );
    
    uint64_t scs[ num_players ];
    memset( scs, 0, sizeof( scs ) );
    std::vector< std::pair< int, uint16_t > > v_tmp;
    for ( int p = 0; p < num_players; ++ p ) {
        scs[ p ] = fc_tmp | hcs[ p ];
        assert( popcnt( scs[ p ] ) == 7 );
        uint16_t rank_p = get_rank( scs[ p ] );
        v_tmp.emplace_back( p, rank_p );
    }
    sort( v_tmp.begin(), v_tmp.end(), [] ( const std::pair< int, uint16_t >& vx, const std::pair< int, uint16_t >& vy ) { return vx.second > vy.second; } );
    assert( v_tmp[ 0 ].second >= v_tmp[ 1 ].second );

    int num_equal = 1;
    for ( int p = 1; p < num_players; ++ p ) {
        if ( v_tmp[ p ].second == v_tmp[ p - 1 ].second ) {
            num_equal += 1;
        } else {
            break;
        }
    }
    for ( int p = 0; p < num_equal; ++ p ) {
        count_bigest[ v_tmp[ p ].first ] += 1.0 / num_equal;
    }
    

    num += 1;
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        assert( popcnt( get_5_bits( index ) ) == 5 );
        int debug = 0;
        if ( num >= 194581 ) {
            debug ++;
        }
        int lc_rightmost[ 52 ];
        memset( lc_rightmost, 0, sizeof( lc_rightmost ) );
        get_values_rightmost( lc, lc_rightmost, 52 );
        assert( popcnt( get_5_bits( lc_rightmost ) ) == 5 );
        if ( judge_bits( index, lc_rightmost ) )
            is_over = true;
        for( i = 0; i < 51; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( index[ i ] == 1 ) {
                int next = i + 1;
                while ( !lc[ next ] && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                if ( index[ next ] == 0 ) {
                    index[ i ] = 0;
                    index[ next ] = 1;
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        if ( index[ j ] ) {
                            index[ j ] = 0;
                            while ( !lc[ count ] ) {
                                count ++;
                            }
                            index[ count++ ] = 1;
                        }
                    }
                    uint64_t fc_tmp = get_5_bits( index );
                    assert( popcnt( fc_tmp ) == 5 );

                    uint64_t scs[ num_players ];
                    memset( scs, 0, sizeof( scs ) );
                    std::vector< std::pair< int, uint16_t > > v_tmp;
                    for ( int p = 0; p < num_players; ++ p ) {
                        scs[ p ] = fc_tmp | hcs[ p ];
                        uint16_t rank_p = get_rank( scs[ p ] );
                        v_tmp.emplace_back( p, rank_p );
                    }
                    sort( v_tmp.begin(), v_tmp.end(), [] ( const std::pair< int, uint16_t >& vx, const std::pair< int, uint16_t >& vy ) { return vx.second > vy.second; } );

                    int num_equal = 1;
                    for ( int p = 1; p < num_players; ++ p ) {
                        if ( v_tmp[ p ].second == v_tmp[ p - 1 ].second ) {
                            num_equal += 1;
                        } else {
                            break;
                        }
                    }
                    for ( int p = 0; p < num_equal; ++ p ) {
                        count_bigest[ v_tmp[ p ].first ] += 1.0 / num_equal;
                    }
                    num += 1;
                    break;
                }
            }
        }
    }
#if DEBUG
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
#endif
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
    std::vector< double > ret( count_bigest, count_bigest + num_players );
    int sum_test = 0;
    for ( auto& x : ret ) {
        sum_test += x;
        x = x / num;
    }
    // assert( abs( sum_test - num ) < 0.0001 );
    return ret;
}

std::vector< double > wr_flop( const std::vector< uint64_t >& hcs, uint64_t flop_c ) {
    int num_players = hcs.size();
    assert( 1 < num_players && num_players < 24 );
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 );
    uint64_t overlap_flag = 0ULL;
    for ( int i = 0; i < num_players; ++ i ) {
        assert( popcnt( hcs[ i ] ) == 2 );
        overlap_flag = overlap_flag | hcs[ i ];
        left_cards = left_cards ^ hcs[ i ];
    }
    left_cards = left_cards ^ flop_c;
    overlap_flag = overlap_flag | flop_c;

    assert( popcnt( overlap_flag ) == 2 * num_players + 3 );
    assert( popcnt( left_cards ) == 52 - num_players * 2 - 3 );
    assert( xsl_bsr( left_cards ) < 52 );

    

    int lc[ 52 ];
    memset( lc, 0, sizeof( lc ) );
    set_index_by_cards( left_cards, 52 - num_players * 2 - 3, lc, 52 );
    assert( popcnt( get_5_bits( lc ) ) == 52 - num_players * 2 - 3 );

    int index[ 52 ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i = 0, j, num = 0;
    int k = 0;
    double count_bigest[ num_players ];
    memset( count_bigest, 0, sizeof( count_bigest ) );
    while ( i < 2 && k < 51 ) {
        if ( lc[ k ] == 1 ) {
            index[ k ] = 1;
            i ++;
        }
        k ++;
    }
    uint64_t tc_tmp = get_5_bits( index );
    
    uint64_t scs[ num_players ];
    memset( scs, 0, sizeof( scs ) );
    std::vector< std::pair< int, uint16_t > > v_tmp;
    for ( int p = 0; p < num_players; ++ p ) {
        scs[ p ] = tc_tmp | hcs[ p ] | flop_c;
        assert( popcnt( scs[ p ] ) == 7 );
        uint16_t rank_p = get_rank( scs[ p ] );
        v_tmp.emplace_back( p, rank_p );
    }
    sort( v_tmp.begin(), v_tmp.end(), [] ( const std::pair< int, uint16_t >& vx, const std::pair< int, uint16_t >& vy ) { return vx.second > vy.second; } );
    assert( v_tmp[ 0 ].second >= v_tmp[ 1 ].second );

    int num_equal = 1;
    for ( int p = 1; p < num_players; ++ p ) {
        if ( v_tmp[ p ].second == v_tmp[ p - 1 ].second ) {
            num_equal += 1;
        } else {
            break;
        }
    }
    for ( int p = 0; p < num_equal; ++ p ) {
        count_bigest[ v_tmp[ p ].first ] += 1.0 / num_equal;
    }
    

    num += 1;
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        assert( popcnt( get_5_bits( index ) ) == 2 );
        int lc_rightmost[ 52 ];
        memset( lc_rightmost, 0, sizeof( lc_rightmost ) );
        get_2_rightmost( lc, lc_rightmost, 52 );
        assert( popcnt( get_5_bits( lc_rightmost ) ) == 2 );
        if ( judge_bits( index, lc_rightmost ) )
            is_over = true;
        for( i = 0; i < 51; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( index[ i ] == 1 ) {
                int next = i + 1;
                while ( !lc[ next ] && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                if ( index[ next ] == 0 ) {
                    index[ i ] = 0;
                    index[ next ] = 1;
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        if ( index[ j ] ) {
                            index[ j ] = 0;
                            while ( !lc[ count ] ) {
                                count ++;
                            }
                            index[ count++ ] = 1;
                        }
                    }
                    uint64_t tc_tmp = get_5_bits( index );
                    assert( popcnt( tc_tmp ) == 2 );

                    uint64_t scs[ num_players ];
                    memset( scs, 0, sizeof( scs ) );
                    std::vector< std::pair< int, uint16_t > > v_tmp;
                    for ( int p = 0; p < num_players; ++ p ) {
                        scs[ p ] = tc_tmp | hcs[ p ] | flop_c;
                        uint16_t rank_p = get_rank( scs[ p ] );
                        v_tmp.emplace_back( p, rank_p );
                    }
                    sort( v_tmp.begin(), v_tmp.end(), [] ( const std::pair< int, uint16_t >& vx, const std::pair< int, uint16_t >& vy ) { return vx.second > vy.second; } );

                    int num_equal = 1;
                    for ( int p = 1; p < num_players; ++ p ) {
                        if ( v_tmp[ p ].second == v_tmp[ p - 1 ].second ) {
                            num_equal += 1;
                        } else {
                            break;
                        }
                    }
                    for ( int p = 0; p < num_equal; ++ p ) {
                        count_bigest[ v_tmp[ p ].first ] += 1.0 / num_equal;
                    }
                    num += 1;
                    break;
                }
            }
        }
    }
#if DEBUG
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
#endif
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
    std::vector< double > ret( count_bigest, count_bigest + num_players );
    int sum_test = 0;
    for ( auto& x : ret ) {
        sum_test += x;
        x = x / num;
    }
    // assert( abs( sum_test - num ) < 0.0001 );
    return ret;
}

std::vector< double > wr_turn( const std::vector< uint64_t >& hcs, uint64_t flop_c, uint64_t turn_c ) {
    int num_players = hcs.size();
    assert( 1 < num_players && num_players < 24 );
    uint64_t left_cards = ( ( 1ULL << 52 ) - 1 );
    uint64_t overlap_flag = 0ULL;
    for ( int i = 0; i < num_players; ++ i ) {
        assert( popcnt( hcs[ i ] ) == 2 );
        overlap_flag = overlap_flag | hcs[ i ];
        left_cards = left_cards ^ hcs[ i ];
    }
    left_cards = left_cards ^ flop_c ^ turn_c;
    overlap_flag = overlap_flag | flop_c | turn_c;

    assert( popcnt( overlap_flag ) == 2 * num_players + 3 + 1 );
    assert( popcnt( left_cards ) == 52 - num_players * 2 - 3 - 1 );
    assert( xsl_bsr( left_cards ) < 52 );

    

    int lc[ 52 ];
    memset( lc, 0, sizeof( lc ) );
    set_index_by_cards( left_cards, 52 - num_players * 2 - 3 - 1, lc, 52 );
    assert( popcnt( get_5_bits( lc ) ) == 52 - num_players * 2 - 3 - 1 );

    int index[ 52 ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i = 0, j, num = 0;
    int k = 0;
    double count_bigest[ num_players ];
    memset( count_bigest, 0, sizeof( count_bigest ) );
    while ( i < 1 && k < 51 ) {
        if ( lc[ k ] == 1 ) {
            index[ k ] = 1;
            i ++;
        }
        k ++;
    }
    uint64_t oc_tmp = get_5_bits( index );
    assert( popcnt( oc_tmp ) == 1 );
    
    uint64_t scs[ num_players ];
    memset( scs, 0, sizeof( scs ) );
    std::vector< std::pair< int, uint16_t > > v_tmp;
    for ( int p = 0; p < num_players; ++ p ) {
        scs[ p ] = oc_tmp | hcs[ p ] | flop_c | turn_c;
        assert( popcnt( scs[ p ] ) == 7 );
        uint16_t rank_p = get_rank( scs[ p ] );
        v_tmp.emplace_back( p, rank_p );
    }
    sort( v_tmp.begin(), v_tmp.end(), [] ( const std::pair< int, uint16_t >& vx, const std::pair< int, uint16_t >& vy ) { return vx.second > vy.second; } );
    assert( v_tmp[ 0 ].second >= v_tmp[ 1 ].second );

    int num_equal = 1;
    for ( int p = 1; p < num_players; ++ p ) {
        if ( v_tmp[ p ].second == v_tmp[ p - 1 ].second ) {
            num_equal += 1;
        } else {
            break;
        }
    }
    for ( int p = 0; p < num_equal; ++ p ) {
        count_bigest[ v_tmp[ p ].first ] += 1.0 / num_equal;
    }
    

    num += 1;
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        assert( popcnt( get_5_bits( index ) ) == 1 );
        int lc_rightmost[ 52 ];
        memset( lc_rightmost, 0, sizeof( lc_rightmost ) );
        get_1_rightmost( lc, lc_rightmost, 52 );
        assert( popcnt( get_5_bits( lc_rightmost ) ) == 1 );
        if ( judge_bits( index, lc_rightmost ) )
            is_over = true;
        for( i = 0; i < 51; i++ ) {  //注意是n-1,因为i=n-1时，i+1是不存在的
            if ( index[ i ] == 1 ) {
                int next = i + 1;
                while ( !lc[ next ] && next < 52 ) {
                    next ++;
                }
                if ( next > 51 ) {
                    break;
                }
                if ( index[ next ] == 0 ) {
                    index[ i ] = 0;
                    index[ next ] = 1;
                    int count = 0;
                    for( j = 0; j < i; j++ ) {
                        if ( index[ j ] ) {
                            index[ j ] = 0;
                            while ( !lc[ count ] ) {
                                count ++;
                            }
                            index[ count++ ] = 1;
                        }
                    }
                    uint64_t oc_tmp = get_5_bits( index );
                    assert( popcnt( oc_tmp ) == 1 );

                    uint64_t scs[ num_players ];
                    memset( scs, 0, sizeof( scs ) );
                    std::vector< std::pair< int, uint16_t > > v_tmp;
                    for ( int p = 0; p < num_players; ++ p ) {
                        scs[ p ] = oc_tmp | hcs[ p ] | flop_c | turn_c;
                        uint16_t rank_p = get_rank( scs[ p ] );
                        v_tmp.emplace_back( p, rank_p );
                    }
                    sort( v_tmp.begin(), v_tmp.end(), [] ( const std::pair< int, uint16_t >& vx, const std::pair< int, uint16_t >& vy ) { return vx.second > vy.second; } );

                    int num_equal = 1;
                    for ( int p = 1; p < num_players; ++ p ) {
                        if ( v_tmp[ p ].second == v_tmp[ p - 1 ].second ) {
                            num_equal += 1;
                        } else {
                            break;
                        }
                    }
                    for ( int p = 0; p < num_equal; ++ p ) {
                        count_bigest[ v_tmp[ p ].first ] += 1.0 / num_equal;
                    }
                    num += 1;
                    break;
                }
            }
        }
    }
#if DEBUG
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
#endif
    std::cout << std::dec << "共有: " << num << "种" << std::endl;
    std::vector< double > ret( count_bigest, count_bigest + num_players );
    int sum_test = 0;
    for ( auto& x : ret ) {
        sum_test += x;
        x = x / num;
    }
    // assert( abs( sum_test - num ) < 0.0001 );
    return ret;
}


double wr_hc_preflop( uint64_t my_hc, int num_players ) {
    int test_rounds = 10;
    double my_wr = 0.0;
    for ( int j = 0; j < test_rounds; ++ j ) {
        std::vector< uint64_t > hcs;
        hcs.push_back( my_hc );
        uint64_t poker = ( 1ULL << 52 ) - 1;
        poker = poker ^ my_hc;
        for ( int i = 0; i < num_players - 1; ++ i ) {
            std::random_device rd;
            std::default_random_engine eng( rd() );
            std::uniform_int_distribution< int > distr( 0, 51 );

            uint64_t hc = 0ULL;
            while ( popcnt( hc ) != 2 ) {
                int rand_a = distr( eng );
                uint64_t card = 1ULL << rand_a;
                if ( ( card & poker ) == card ) {
                    hc = hc ^ card;
                    poker = poker ^ card;
                }
            }
            assert( popcnt( hc ) == 2 );
            assert( ( hc & poker ) == 0ULL );
            hcs.push_back( hc );
        }
        auto wrs = wr_preflop( hcs );
        my_wr += wrs[ 0 ];
    }
    my_wr /= test_rounds;
    return my_wr;
}
#endif
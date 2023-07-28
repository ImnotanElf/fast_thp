#ifndef __METHODS_H__
#define __METHODS_H__

#include "Card.h"
#include "Fivecards.h"
#include "Poker.h"
#include <vector>
#include <cstring>
#include <algorithm>
#include <bitset>

Fivecards get_fivecards( int index[], const std::vector< Card >& value ) {
    std::vector< Card > temp;
    for ( int i = 0; i < value.size(); i++ ) {
        // std::cout << index[ i ];
        if ( index[ i ] )
            temp.emplace_back( value[ i ] );
    }
    // std::cout << std::endl;
    Fivecards fc( temp[ 0 ], temp[ 1 ], temp[ 2 ], temp[ 3 ], temp[ 4 ] );
    return fc;
}

Fivecards get_fivecards( std::bitset< 52 > in, const std::vector< Card >& value ) {
    std::vector< Card > temp;
    for ( int i = 0; i < value.size(); i++ ) {
        // std::cout << index[ i ];
        if ( in[ i ] )
            temp.emplace_back( value[ i ] );
    }
    // std::cout << std::endl;
    Fivecards fc( temp[ 0 ], temp[ 1 ], temp[ 2 ], temp[ 3 ], temp[ 4 ] );
    return fc;
}

bool judge( int n, int m, std::bitset< 52 > in )
{
    int i;
    for ( i = n - 1; i >= n-m; i-- ) {
        if ( !in[ i ] )  
            return false;
    }
    return true;
}

bool judge( int n, int m, int index[] )
{
    int i;
    for ( i = n - 1; i >= n-m; i-- ) {
        if ( !index[ i ] )  
            return false;
    }
    return true;
}

bool judge( int n, int start[], int end[] ) {
    for ( int i = n - 1; i >= 0; i -- ) {
        if ( start[ i ] != end[ i ] )  
            return false;
    }
    return true;
}

void change( int m, const std::vector< Card >& value, const Fivecards& fc )  //核心算法函数
{
    int n = value.size();
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i, j, num = 0, count_bigger = 0, count_equal = 0;
    for ( i = 0; i < m; i++ ) {
        index[ i ] = 1;
    }
    num += 1;
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
                if ( fc == get_fivecards( index, value ) ) {
                    count_equal += 1;
                }
                if ( fc < get_fivecards( index, value ) ) {
                    count_bigger += 1;
                }
                num += 1;
                break;
            }
        }
    }
    std::cout << "共有" << num << "种" << std::endl;
    std::cout << "大于" << count_bigger << "种" << std::endl;
    std::cout << "相等" << count_equal << "种" << std::endl;
}

Fivecards max_five_in_seven( const std::vector< Card >& value )  //核心算法函数
{
    Fivecards res;
    int m = 5;
    int n = value.size();
    int num = 0;
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i, j;
    for ( i = 0; i < m; i++ ) {
        index[ i ] = 1;
    }
    num += 1;
    // std::cout << "res: " << res << " " << res.level << std::endl;
    // std::cout << "get: " << get_fivecards( index, value ) << " " << get_fivecards( index, value ).level << std::endl;
    // std::cout << ccc ++ << std::endl;
    if ( res < get_fivecards( index, value ) ) {
        res = get_fivecards( index, value );
    }
    // auto debug = get_fivecards( index, value );
    // std::cout << debug << std::endl;
    bool is_over = false;
    while ( !is_over ) { //只要没使1全部移到右边，就继续循环
        if ( judge( n, m, index ) )
            is_over = true;
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
                num += 1;
                // std::cout << "res: " << res << " " << res.level << std::endl;
                // std::cout << "get: " << get_fivecards( index, value ) << " " << get_fivecards( index, value ).level << std::endl;
                // std::cout << ccc ++ << std::endl;
                if ( res < get_fivecards( index, value ) ) {
                    res = get_fivecards( index, value );
                }
                // auto debug = get_fivecards( index, value );
                // std::cout << debug << std::endl;
                break;
            }
        }
    }
    // std::sort( res.fivecards, res.fivecards + 5 );
    // std::cout << "num: " << num << std::endl;
    assert( num == 21 );
    return res;
}

int combination( int n, int m ) {
    int res = n;
    for ( int i = 2; i <= m; ++i ) {
        res *= ( n + 1 - i );
        res /= i;
    }
    return res;
}

void change_( int m, int n )  //核心算法函数
{
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i, j, num = 0;
    for ( i = 0; i < m; i++ ) {
        index[ i ] = 1;
    }
    num += 1;
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
                num += 1;
                break;
            }
        }
    }
    std::cout << "共有" << num << "种" << std::endl;
}

void choose_5_from_value( const std::vector< Card >& value, int level )  //核心算法函数
{
    int m = 5;
    int n = value.size();
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i, j, num = 0, count_level = 0;
    for ( i = 0; i < m; i++ ) {
        index[ i ] = 1;
    }
    Fivecards temp = get_fivecards( index, value );
    if ( temp.level == level ) {
        count_level += 1;
    }
    num += 1;
    printf( "%d\n", num );
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
                Fivecards temp = get_fivecards( index, value );
                if ( temp.level == level ) {
                    count_level += 1;
                }
                num += 1;
                printf( "%d\n", num );
                break;
            }
        }
    }
    std::cout << "共有" << num << "种" << std::endl;
    std::cout << "count_" << level << ": " << count_level << "种" << std::endl;
}

void generate_all_5( const Poker& p, std::vector< Fivecards >& ret )  //核心算法函数
{
    const std::vector< Card >& value = p.cards;
    int m = 5;
    int n = value.size();
    int index[ n ]; // index务必初始化为0，不然无法知道m个数之后里面是真还是假
    memset( index, 0, sizeof( index ) );
    int i, j, num = 0;
    for ( i = 0; i < m; i++ ) {
        index[ i ] = 1;
    }
    Fivecards temp = get_fivecards( index, value );
    ret.emplace_back( temp );
    num += 1;
    printf( "%d\n", num );
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
                Fivecards temp = get_fivecards( index, value );
                ret.emplace_back( temp );
                num += 1;
                printf( "%d\n", num );
                break;
            }
        }
    }
    std::cout << "共有" << num << "种" << std::endl;
}


int assembly_popcnt( uint32_t n ) {
#ifdef _MSC_VER  // Intel style assembly
    __asm popcnt eax,n;
#elif __GNUC__  // AT&T style assembly
    __asm__("popcnt %0,%%eax"::"r"(n));
#else
#error "other POPCNT implementations go here"
#endif
}

int popcnt( uint64_t n)
{
#ifdef _MSC_VER  // Intel style assembly
    __asm popcntq rax,n;
#elif __GNUC__  // AT&T style assembly
    __asm__("popcntq %0,%%rax"::"r"(n));
#else
#error "other POPCNT implementations go here"
#endif
}

int assembly_bsf( uint32_t n )
{
#ifdef _MSC_VER  // Intel style assembly
    __asm bsf eax,n;
#elif __GNUC__  // AT&T style assembly
    __asm__( "bsf %0,%%eax"::"r"(n) );
#else
#error "other BSF implementations go here"
#endif
}

int xsl_bsf( uint64_t n ) {
    if ( ( uint32_t ) n ) {
        return assembly_bsf( ( uint32_t ) n );
    } else {
        if ( ( uint32_t ) ( n >> 32 ) ) {
            return 32 + assembly_bsf( ( uint32_t ) ( n >> 32 ) );
        } else {
            return -1;
        }
    }
}


int assembly_bsr( uint32_t n )
{
#ifdef _MSC_VER  // Intel style assembly
    __asm bsr eax,n;
#elif __GNUC__  // AT&T style assembly
    __asm__( "bsr %0,%%eax"::"r"(n) );
#else
#error "other BSR implementations go here"
#endif
}

int xsl_bsr( uint64_t n ) {
    if ( ( uint32_t ) ( n >> 32 ) ) {
        return 32 + assembly_bsr( ( uint32_t ) ( n >> 32 ) );
    } else {
        if ( ( uint32_t ) n ) {
            return assembly_bsr( ( uint32_t ) n );
        } else {
            return -1;
        }
    }
}

#endif
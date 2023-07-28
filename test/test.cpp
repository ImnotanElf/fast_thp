#include <cstdio>
#include <cstdlib>
#include <functional>
#include <chrono>
#include <cassert>
#include <map>
#include <pthread.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>


#include "Card.h"
#include "Fivecards.h"
#include "Poker.h"
#include "methods.h"
#include "Sevencards.h"
#include "for-human.h"

#include "SevenEval.h"

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


class Gaming {
public:
    std::vector<Card> flopcards;
    Card turncard;
    Card rivercard;
    Gaming () : flopcards( 3 ) {}
    void run() {
        Poker p;
        Player_xsl pa( 1, "xsl", p.c2, p.s2 );
        Player_xsl pb( 2, "yw", p.cA, p.sA );
        p.deal_card( p.c2 );
        p.deal_card( p.s2 );
        p.deal_card( p.cA );
        p.deal_card( p.sA );
        double wr = winrate( p.cards, pa.holecards, pb.holecards );
        printf( "xsl's winrate = %f\n", wr );
    }
};

void test_change_() {
    change_( 5, 48 );
}

void test_max_fc() {
    Poker p;

    p.deal_card( p.c2 );
    p.deal_card( p.s2 );
    p.deal_card( p.h2 );
    p.deal_card( p.d2 );
    p.deal_card( p.hA );
    p.deal_card( p.c2 );
    p.deal_card( p.s2 );
    p.deal_card( p.h2 );
    p.deal_card( p.d2 );
    p.deal_card( p.hA );
    Fivecards fc_1( p.c2, p.s2, p.h2, p.d2, p.hA );
    Fivecards fc_2( p.c2, p.s2, p.h2, p.d2, p.hA );

    Sevencards sc_01( p.c2, p.s2, p.h3, p.h4, p.h5, p.h6, p.h7 );
    Sevencards sc_02( p.cA, p.sA, p.h3, p.h4, p.h5, p.h6, p.h7 );

    std::cout << sc_01.max_fivecards << std::endl;
    std::cout << sc_02.max_fivecards << std::endl;

    if ( fc_1 == fc_2 ) {
        std::cout << "equal" << std::endl;
    }
}

void test_wr() {
    Poker p( true );

    Player_xsl pa( 1, "xsl", p.cT, p.sT );
    Player_xsl pb( 2, "yw", p.cQ, p.sQ );
    // printf( "length of p.cards: %d\n", p.cards.size() );
    p.deal_card( p.cT );
    // printf( "length of p.cards: %d\n", p.cards.size() );
    p.deal_card( p.sT );
    // printf( "length of p.cards: %d\n", p.cards.size() );
    p.deal_card( p.cQ );
    // printf( "length of p.cards: %d\n", p.cards.size() );
    p.deal_card( p.sQ );
    printf( "length of p.cards: %lu\n", p.cards.size() );
    printf( "cards: " );
    for ( int i = 0; i < p.cards.size(); ++ i ) {
        std::cout << p.cards[ i ] << " ";
    }
    std::cout << std::endl;
    double wr = winrate( p.cards, pa.holecards, pb.holecards );
    printf( "xsl's winrate = %f\n", wr );
}
void test_operator_s() {
    Poker p;
    Fivecards fc_1( p.sT, p.hT, p.cT, p.dT, p.dJ );
    Fivecards fc_2( p.dT, p.hT, p.sQ, p.cQ, p.dJ );
    if ( fc_1 < fc_2 ) {
        printf( "1 < 2\n" );
    }
    if ( fc_2 < fc_1 ) {
        printf( "2 < 1\n" );
    }
}

void choose_level_from_value( int level = 9 ) {
    Poker p;
    choose_5_from_value( p.cards, level );
}

void wr_2( const char *c_1 = "c2", const char *c_2 = "s2", const char *c_3 = "cA", const char *c_4 = "sA" ) {
    assert( strlen( c_1 ) == 2 && strlen( c_2 ) == 2 &&  strlen( c_3 ) == 2 &&  strlen( c_4 ) == 2 );
    assert( c_1[ 0 ] == 's' || c_1[ 0 ] == 'c' || c_1[ 0 ] == 'h' || c_1[ 0 ] == 'd' );
    assert( c_2[ 0 ] == 's' || c_2[ 0 ] == 'c' || c_2[ 0 ] == 'h' || c_2[ 0 ] == 'd' );
    assert( c_3[ 0 ] == 's' || c_3[ 0 ] == 'c' || c_3[ 0 ] == 'h' || c_3[ 0 ] == 'd' );
    assert( c_4[ 0 ] == 's' || c_4[ 0 ] == 'c' || c_4[ 0 ] == 'h' || c_4[ 0 ] == 'd' );
    assert( ( c_1[ 1 ] <= ( '9' ) && ( '1' ) < c_1[ 1 ] ) || c_1[ 1 ] == 'A' || c_1[ 1 ] == 'K' || c_1[ 1 ] == 'Q' || c_1[ 1 ] == 'J' || c_1[ 1 ] == 'T' );
    assert( ( c_2[ 1 ] <= ( '9' ) && ( '1' ) < c_2[ 1 ] ) || c_2[ 1 ] == 'A' || c_2[ 1 ] == 'K' || c_2[ 1 ] == 'Q' || c_2[ 1 ] == 'J' || c_2[ 1 ] == 'T' );
    assert( ( c_3[ 1 ] <= ( '9' ) && ( '1' ) < c_3[ 1 ] ) || c_3[ 1 ] == 'A' || c_3[ 1 ] == 'K' || c_3[ 1 ] == 'Q' || c_3[ 1 ] == 'J' || c_3[ 1 ] == 'T' );
    assert( ( c_4[ 1 ] <= ( '9' ) && ( '1' ) < c_4[ 1 ] ) || c_4[ 1 ] == 'A' || c_4[ 1 ] == 'K' || c_4[ 1 ] == 'Q' || c_4[ 1 ] == 'J' || c_4[ 1 ] == 'T' );
    
    Poker p;

    auto ptr_cmp = [] ( const char *s1, const char *s2 ) { return strcmp( s1, s2 ) < 0; };
    std::map< const char *, Card, decltype( ptr_cmp ) > stoCard( ptr_cmp );
    stoCard[ "s2" ] = p.s2;
    stoCard[ "s3" ] = p.s3;
    stoCard[ "s4" ] = p.s4;
    stoCard[ "s5" ] = p.s5;
    stoCard[ "s6" ] = p.s6;
    stoCard[ "s7" ] = p.s7;
    stoCard[ "s8" ] = p.s8;
    stoCard[ "s9" ] = p.s9;
    stoCard[ "sT" ] = p.sT;
    stoCard[ "sJ" ] = p.sJ;
    stoCard[ "sQ" ] = p.sQ;
    stoCard[ "sK" ] = p.sK;
    stoCard[ "sA" ] = p.sA;

    stoCard[ "h2" ] = p.h2;
    stoCard[ "h3" ] = p.h3;
    stoCard[ "h4" ] = p.h4;
    stoCard[ "h5" ] = p.h5;
    stoCard[ "h6" ] = p.h6;
    stoCard[ "h7" ] = p.h7;
    stoCard[ "h8" ] = p.h8;
    stoCard[ "h9" ] = p.h9;
    stoCard[ "hT" ] = p.hT;
    stoCard[ "hJ" ] = p.hJ;
    stoCard[ "hQ" ] = p.hQ;
    stoCard[ "hK" ] = p.hK;
    stoCard[ "hA" ] = p.hA;

    stoCard[ "c2" ] = p.c2;
    stoCard[ "c3" ] = p.c3;
    stoCard[ "c4" ] = p.c4;
    stoCard[ "c5" ] = p.c5;
    stoCard[ "c6" ] = p.c6;
    stoCard[ "c7" ] = p.c7;
    stoCard[ "c8" ] = p.c8;
    stoCard[ "c9" ] = p.c9;
    stoCard[ "cT" ] = p.cT;
    stoCard[ "cJ" ] = p.cJ;
    stoCard[ "cQ" ] = p.cQ;
    stoCard[ "cK" ] = p.cK;
    stoCard[ "cA" ] = p.cA;

    stoCard[ "d2" ] = p.d2;
    stoCard[ "d3" ] = p.d3;
    stoCard[ "d4" ] = p.d4;
    stoCard[ "d5" ] = p.d5;
    stoCard[ "d6" ] = p.d6;
    stoCard[ "d7" ] = p.d7;
    stoCard[ "d8" ] = p.d8;
    stoCard[ "d9" ] = p.d9;
    stoCard[ "dT" ] = p.dT;
    stoCard[ "dJ" ] = p.dJ;
    stoCard[ "dQ" ] = p.dQ;
    stoCard[ "dK" ] = p.dK;
    stoCard[ "dA" ] = p.dA;

    Player_xsl pa( 1, "xsl", stoCard[ c_1 ], stoCard[ c_2 ] );
    Player_xsl pb( 2, "yw",  stoCard[ c_3 ], stoCard[ c_4 ] );
    p.deal_card( stoCard[ c_1 ] );
    p.deal_card( stoCard[ c_2 ] );
    p.deal_card( stoCard[ c_3 ] );
    p.deal_card( stoCard[ c_4 ] );
    // std::cout << stoCard[ c_1 ] ;
    // double wr = winrate( p.cards, pa.holecards, pb.holecards );
    std::cout << "Running..." << std::endl;
    double wr = 0; // wr_bits( p.cards, pa.holecards, pb.holecards );
    std::cout << c_1 << " + " << c_2 << " vs " << c_3 << " + " << c_4 << " winrate : " << wr << std::endl;
}

void test_thread() {
    const int num_threads = 32;

    Poker p[ num_threads ];

    Player_xsl player_xsl[ num_threads ][ 2 ];

    for ( int i = 0; i < 2; ++ i ) {
        player_xsl[ i ][ 0 ].id = 1;
        player_xsl[ i ][ 0 ].name = "xsl";
        player_xsl[ i ][ 0 ].holecards = { p[ i ].sA, p[ i ].cA };
        player_xsl[ i ][ 1 ].id = 2;
        player_xsl[ i ][ 1 ].name = "yw";
        player_xsl[ i ][ 1 ].holecards = { p[ i ].s2, p[ i ].c2 };
        p[ i ].deal_card( p[ i ].sA );
        p[ i ].deal_card( p[ i ].cA );
        p[ i ].deal_card( p[ i ].s2 );
        p[ i ].deal_card( p[ i ].c2 );
    }

    int start[ num_threads ][ 52 ];
    int end[ num_threads ][ 52 ];
    int res[ num_threads ][ 3 ];
    memset( res, 0, sizeof( res ) );
    memset( start, 0, sizeof( start ) );
    memset( end, 0, sizeof( end ) );

    start[ 0 ][ 0 ]  = 1; start[ 0 ][ 1 ]  = 1; start[ 0 ][ 2 ]  = 1; start[ 0 ][ 3 ]  = 1; start[ 0 ][ 4 ]  = 1;
    end[ 0 ][ 20 ]   = 1; end[ 0 ][ 21 ]   = 1; end[ 0 ][ 22 ]   = 1; end[ 0 ][ 23 ]   = 1; end[ 0 ][ 24 ]   = 1;
    start[ 1 ][ 20 ] = 1; start[ 1 ][ 21 ] = 1; start[ 1 ][ 22 ] = 1; start[ 1 ][ 23 ] = 1; start[ 1 ][ 24 ] = 1;
    end[ 1 ][ 25 ]   = 1; end[ 1 ][ 26 ]   = 1; end[ 1 ][ 27 ]   = 1; end[ 1 ][ 28 ]   = 1; end[ 1 ][ 29 ]   = 1;
    
    int main_start[ 52 ];
    int main_end[ 52 ];
    int main_res[ 3 ];
    memset( main_res, 0, sizeof( main_res ) );
    memset( main_start, 0, sizeof( main_start ) );
    memset( main_end, 0, sizeof( main_end ) );
    main_start[ 0 ]  = 1; main_start[ 1 ]  = 1; main_start[ 2 ]  = 1; main_start[ 3 ]  = 1; main_start[ 4 ]  = 1;
    main_end[ 25 ]   = 1; main_end[ 26 ]   = 1; main_end[ 27 ]   = 1; main_end[ 28 ]   = 1; main_end[ 29 ]   = 1;

    clock_t time_start, time_end;
    
    time_start = clock();

    std::vector< std::thread > threads;
    for ( int t = 0; t < 2; t++ ) {
        threads.emplace_back( std::thread( wr_threads, std::cref( p[ t ].cards ), start[ t ], end[ t ], res[ t ], std::cref( player_xsl[ t ][ 0 ].holecards ), std::cref( player_xsl[ t ][ 1 ].holecards ) ) );
    }
    for ( int i = 0; i < threads.size(); i++ ) {
        threads[ i ].join();
    }

    time_end = clock();
    printf( "Cost time of 2 threads: %lf seconds\n", ( double ) ( time_end - time_start ) / CLOCKS_PER_SEC );
    
    Poker main_p;

    Player_xsl main_pa( 1, "xsl", main_p.sA, main_p.cA );
    Player_xsl main_pb( 2, "yw",  main_p.s2, main_p.c2 );
    main_p.deal_card( main_p.sA );
    main_p.deal_card( main_p.cA );
    main_p.deal_card( main_p.s2 );
    main_p.deal_card( main_p.c2 );
    struct thread_data source_data_main;
    source_data_main.res   = main_res;
    source_data_main.start = main_start;
    source_data_main.end   = main_end;
    source_data_main.value = main_p.cards;
    source_data_main.ap    = main_pa.holecards;
    source_data_main.bp    = main_pb.holecards;

    time_start = clock();

    wr_pthreads( (void *)&( source_data_main ) );

    time_end = clock();
    printf( "Cost time of 1 threads: %lf seconds\n", ( double ) ( time_end - time_start ) / CLOCKS_PER_SEC );
}

void test_wr_pthreads() {
    printf( "system cpu num is %ld\n", sysconf( _SC_NPROCESSORS_CONF ) );
    printf( "system enable cpu num is %ld\n", sysconf(_SC_NPROCESSORS_ONLN ) );
    const int num_threads = 32;

    Poker p;

    Player_xsl pa( 1, "xsl", p.sA, p.cA );
    Player_xsl pb( 2, "yw",  p.s2, p.c2 );
    p.deal_card( p.sA );
    p.deal_card( p.cA );
    p.deal_card( p.s2 );
    p.deal_card( p.c2 );

    int start[ num_threads ][ 52 ];
    int end[ num_threads ][ 52 ];
    int res[ num_threads ][ 3 ];
    memset( res, 0, sizeof( res ) );
    memset( start, 0, sizeof( start ) );
    memset( end, 0, sizeof( end ) );

    start[ 0 ][ 0 ]  = 1; start[ 0 ][ 1 ]  = 1; start[ 0 ][ 2 ]  = 1; start[ 0 ][ 3 ]  = 1; start[ 0 ][ 4 ]  = 1;
    end[ 0 ][ 20 ]   = 1; end[ 0 ][ 21 ]   = 1; end[ 0 ][ 22 ]   = 1; end[ 0 ][ 23 ]   = 1; end[ 0 ][ 24 ]   = 1;
    start[ 1 ][ 20 ] = 1; start[ 1 ][ 21 ] = 1; start[ 1 ][ 22 ] = 1; start[ 1 ][ 23 ] = 1; start[ 1 ][ 24 ] = 1;
    end[ 1 ][ 25 ]   = 1; end[ 1 ][ 26 ]   = 1; end[ 1 ][ 27 ]   = 1; end[ 1 ][ 28 ]   = 1; end[ 1 ][ 29 ]   = 1;
    
    int main_start[ 52 ];
    int main_end[ 52 ];
    int main_res[ 3 ];
    memset( main_res, 0, sizeof( main_res ) );
    memset( main_start, 0, sizeof( main_start ) );
    memset( main_end, 0, sizeof( main_end ) );
    main_start[ 0 ]  = 1; main_start[ 1 ]  = 1; main_start[ 2 ]  = 1; main_start[ 3 ]  = 1; main_start[ 4 ]  = 1;
    main_end[ 25 ]   = 1; main_end[ 26 ]   = 1; main_end[ 27 ]   = 1; main_end[ 28 ]   = 1; main_end[ 29 ]   = 1;

    pthread_t tids[ num_threads ];
    // void *status;

    struct thread_data source_data_00;
    source_data_00.res   = res[ 0 ];
    source_data_00.start = start[ 0 ];
    source_data_00.end   = end[ 0 ];
    source_data_00.value = p.cards;
    source_data_00.ap    = pa.holecards;
    source_data_00.bp    = pb.holecards;
    struct thread_data source_data_01;
    source_data_01.res   = res[ 1 ];
    source_data_01.start = start[ 1 ];
    source_data_01.end   = end[ 1 ];
    source_data_01.value = p.cards;
    source_data_01.ap    = pa.holecards;
    source_data_01.bp    = pb.holecards;

    clock_t time_start, time_end;
    
    time_start = clock();

    int ret_0 = pthread_create( &tids[ 0 ], NULL, wr_pthreads, (void *)&( source_data_00 ) );
    if ( ret_0 != 0 ) {
        std::cout << "pthread_create error: error_code=" << ret_0 << std::endl;
        return;
    }
    int ret_1 = pthread_create( &tids[ 1 ], NULL, wr_pthreads, (void *)&( source_data_01 ) );
    if ( ret_1 != 0 ) {
        std::cout << "pthread_create error: error_code=" << ret_1 << std::endl;
        return;
    }

    pthread_join( tids[ 0 ], NULL );
    pthread_join( tids[ 1 ], NULL );

    time_end = clock();
    printf( "Cost time of 2 threads: %lf seconds\n", ( double ) ( time_end - time_start ) / CLOCKS_PER_SEC );
    
    struct thread_data source_data_main;
    source_data_main.res   = main_res;
    source_data_main.start = main_start;
    source_data_main.end   = main_end;
    source_data_main.value = p.cards;
    source_data_main.ap    = pa.holecards;
    source_data_main.bp    = pb.holecards;

    time_start = clock();

    wr_pthreads( (void *)&( source_data_main ) );

    time_end = clock();
    printf( "Cost time of 1 threads: %lf seconds\n", ( double ) ( time_end - time_start ) / CLOCKS_PER_SEC );

    /*
    for ( int i = 0; i < 2; ++ i ) {
        struct thread_data source_data;
        source_data.res   = res[ i ];
        source_data.start = start[ i ];
        source_data.end   = end[ i ];
        source_data.value = p.cards;
        source_data.ap    = pa.holecards;
        source_data.bp    = pb.holecards;

        // pthread_attr_t attr;
        // pthread_attr_init( &attr );
        // pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );

        int ret_1 = pthread_create( &tids[ i ], NULL, wr_pthreads, (void *)&( source_data ) );
        if ( ret_1 != 0 ) {
            std::cout << "pthread_create error: error_code=" << ret_1 << std::endl;
            return;
        }

        int rc = pthread_join( tids[ i ], &status );
        if ( rc != 0 ) {
            std::cout << "pthread_join error: error_code=" << rc << std::endl;
            return;
        }
        // pthread_attr_destroy(&attr);
        std::cout << i << ": greater: " << res[ i ][ 0 ] << std::endl;
        std::cout << i << ": smaller: " << res[ i ][ 1 ] << std::endl;
        std::cout << i << ": equal  : " << res[ i ][ 2 ] << std::endl;
    }
    for ( int i = 0; i < 2; ++ i ) {
        int rc = pthread_join( tids[ i ], &status );
        if ( rc != 0 ) {
            std::cout << "pthread_join error: error_code=" << rc << std::endl;
            return;
        }
    }
    */
    pthread_exit( NULL );
    // int wstatus;
    // wait( &wstatus );
    // double wr = wr_pthreads( start, end, p.cards, pa.holecards, pb.holecards );
    // printf( "%lf\n", wr );
}

void test_fork() {
    printf( "system cpu num is %ld\n", sysconf( _SC_NPROCESSORS_CONF ) );
    printf( "system enable cpu num is %ld\n", sysconf(_SC_NPROCESSORS_ONLN ) );
    const int num_threads = 32;

    Poker p;

    Player_xsl pa( 1, "xsl", p.sA, p.cA );
    Player_xsl pb( 2, "yw",  p.s2, p.c2 );
    p.deal_card( p.sA );
    p.deal_card( p.cA );
    p.deal_card( p.s2 );
    p.deal_card( p.c2 );

    int start[ num_threads ][ 52 ];
    int end[ num_threads ][ 52 ];
    int res[ num_threads ][ 3 ];
    memset( res, 0, sizeof( res ) );
    memset( start, 0, sizeof( start ) );
    memset( end, 0, sizeof( end ) );

    start[ 0 ][ 0 ]  = 1; start[ 0 ][ 1 ]  = 1; start[ 0 ][ 2 ]  = 1; start[ 0 ][ 3 ]  = 1; start[ 0 ][ 4 ]  = 1;
    end[ 0 ][ 20 ]   = 1; end[ 0 ][ 21 ]   = 1; end[ 0 ][ 22 ]   = 1; end[ 0 ][ 23 ]   = 1; end[ 0 ][ 24 ]   = 1;
    start[ 1 ][ 20 ] = 1; start[ 1 ][ 21 ] = 1; start[ 1 ][ 22 ] = 1; start[ 1 ][ 23 ] = 1; start[ 1 ][ 24 ] = 1;
    end[ 1 ][ 25 ]   = 1; end[ 1 ][ 26 ]   = 1; end[ 1 ][ 27 ]   = 1; end[ 1 ][ 28 ]   = 1; end[ 1 ][ 29 ]   = 1;
    
    int main_start[ 52 ];
    int main_end[ 52 ];
    int main_res[ 3 ];
    memset( main_res, 0, sizeof( main_res ) );
    memset( main_start, 0, sizeof( main_start ) );
    memset( main_end, 0, sizeof( main_end ) );
    main_start[ 0 ]  = 1; main_start[ 1 ]  = 1; main_start[ 2 ]  = 1; main_start[ 3 ]  = 1; main_start[ 4 ]  = 1;
    main_end[ 25 ]   = 1; main_end[ 26 ]   = 1; main_end[ 27 ]   = 1; main_end[ 28 ]   = 1; main_end[ 29 ]   = 1;

    // pthread_t tids[ num_threads ];
    // void *status;

    struct thread_data source_data_00;
    source_data_00.res   = res[ 0 ];
    source_data_00.start = start[ 0 ];
    source_data_00.end   = end[ 0 ];
    source_data_00.value = p.cards;
    source_data_00.ap    = pa.holecards;
    source_data_00.bp    = pb.holecards;
    struct thread_data source_data_01;
    source_data_01.res   = res[ 1 ];
    source_data_01.start = start[ 1 ];
    source_data_01.end   = end[ 1 ];
    source_data_01.value = p.cards;
    source_data_01.ap    = pa.holecards;
    source_data_01.bp    = pb.holecards;

    struct thread_data source_data_main;
    source_data_main.res   = main_res;
    source_data_main.start = main_start;
    source_data_main.end   = main_end;
    source_data_main.value = p.cards;
    source_data_main.ap    = pa.holecards;
    source_data_main.bp    = pb.holecards;
    
    auto startTime = std::chrono::system_clock::now();

    // wr_pthreads( (void *)&( source_data_main ) );

    auto endTime = std::chrono::system_clock::now();
    std::cout << "main process time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count() << std::endl;
    
    int fd[ 2 ];
    pipe( fd );
    char out[ 256 ] = { 0 };
    memset( out, 0, sizeof( out ) );
    startTime = std::chrono::system_clock::now();
    // ---------------------------------------------fork()
    pid_t fpid = fork();
    if ( fpid < 0 ) {
        exit( -1 );
    } else if ( fpid == 0 ) {
        wr_pthreads( (void *)&( source_data_00 ) );
        close( fd[ 1 ] );
        char buf[ 256 ] = { 0 };
        memset( buf, 0, sizeof( buf ) );
        int ret = read( fd[ 0 ], buf, sizeof( buf ) );
        if ( !ret ) {
            std::cerr << ret << std::endl;
        }
        std::cout << buf << std::endl;
    } else {
        wr_pthreads( (void *)&( source_data_01 ) );
        close( fd[ 0 ] );
        char buf[ 256 ] = { 0 };
        memset( buf, 0, sizeof( buf ) );
        sprintf( buf, "%s", std::to_string( res[ 1 ][ 0 ] ).c_str() );
        write( fd[ 1 ], buf, sizeof( buf ) );
        sleep( 1 );
    }

    endTime = std::chrono::system_clock::now();
    std::cout << getpid() << ": time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count() << std::endl;
    
}

void generate_fivecards() {
    Poker p;
    std::vector< Fivecards > all_5;
    generate_all_5( p, all_5 );
    std::cout << all_5.size() << std::endl;
    sort( all_5.begin(), all_5.end() );
    std::ofstream out( "all_5_order_by_num.csv" );
    int count = 0;
    
    if ( out.is_open() ) {
        out << std::to_string( all_5[ 0 ].get_cards_5() );
        out << ",";
        out << std::to_string( count );
        out << "\n";
        for ( int i = 1; i < all_5.size(); ++ i ) {
            out << std::to_string( all_5[ i ].get_cards_5() );
            out << ",";
            if ( all_5[ i ] == all_5[ i - 1 ] ) {
                out << std::to_string( count );
            } else {
                out << std::to_string( ++ count );
            }
            out << "\n";
        }
        out.close();
    } else {
        exit( -1 );
    }
}

std::unordered_map< uint64_t, int > read_all_5_csv();

void generate_sevencards() {
    std::cout << "Reading..." << std::endl;
    auto mp = read_all_5_csv();
    std::cout << "Read done." << std::endl;
    std::cout << "size of mp: " << mp.size() << std::endl;

    std::unordered_map< uint64_t, uint32_t > mp_7;
    std::cout << "Running..." << std::endl;
    generate_fast( mp, mp_7 );
    std::cout << mp_7.size() << std::endl;
    std::ofstream out( "all_7.csv" );
    
    if ( out.is_open() ) {
        for ( auto iter = mp_7.begin(); iter != mp_7.end(); ++ iter ) {
            out << std::to_string( iter->first );
            out << ",";
            out << std::to_string( iter->second );
            out << "\n";
        }
        out.close();
    } else {
        exit( -1 );
    }
}

std::vector< std::string > readlines( const std::string& filepath ) {
    std::vector< std::string > res;
    std::ifstream in;
    in.open( filepath.c_str() );
    if ( !in ) {
        std::cerr << "Unable to open file.";
        exit(1);   
    }
    std::string tmp;
    while ( in >> tmp ) {
        res.push_back( tmp );
    }
    in.close();
    return res;
}

std::vector< std::string > split( std::string str, std::string delim ) {
    std::vector< std::string > res;
    if ( str.size() == 0 ) return res;
    //先将要切割的字符串从string类型转换为char*类型
    char *strs = new char[ str.size() + 1 ]; //不要忘了
    for ( int i = 0; i < str.size(); ++ i ) {
        strs[ i ] = str[ i ];
    }
    strs[ str.size() ] = '\0';
    // strcpy( strs, str.c_str() );
  
    char *d = new char[ delim.size() + 1 ];
    for ( int i = 0; i < delim.size(); ++ i ) {
        d[ i ] = delim[ i ];
    }
    d[ delim.size() ] = '\0';
    // strcpy( d, delim.c_str() );
  
    char *p = strtok( strs, d );
    while ( p ) {
        std::string s = p; //分割得到的字符串转换为string类型
        res.push_back( s ); //存入结果数组
        p = strtok( NULL, d );
    }
    return res;
}

std::string strip( std::string s ) {
    int n = s.size();
    if ( s[ n - 1 ] == '\n' )
        return s.substr( 0, n - 1 );
    return s;
}

std::unordered_map< uint64_t, int > read_all_5_csv() {
    std::unordered_map< uint64_t, int > mp;
    std::string csv_path = "../src/all_5_order_by_num.csv";
    auto lines = readlines( csv_path );
    for ( auto line : lines ) {
        auto info = split( strip( line ), "," );
        char *p_end;
        uint64_t cards = strtoull( info[ 0 ].c_str(), &p_end, 10 );
        int rank = stoi( info[ 1 ] );
        mp[ cards ] = rank;
    }
    return mp;
}

std::unordered_map< uint64_t, uint32_t > read_all_7_csv() {
    std::unordered_map< uint64_t, uint32_t > mp;
    std::string csv_path = "../src/all_7.csv";
    auto lines = readlines( csv_path );
    for ( auto line : lines ) {
        auto info = split( strip( line ), "," );
        char *p_end;
        uint64_t key = strtoull( info[ 0 ].c_str(), &p_end, 10 );
        char *p_end_1;
        uint32_t rank = strtoul( info[ 1 ].c_str(), &p_end_1, 10 );
        mp[ key ] = rank;
    }
    return mp;
}

void test_wr_fast() {
    uint64_t hc_a = 0x11ULL;
    uint64_t hc_b = 0x1100ULL;
    assert( popcnt( hc_a ) == 2 );
    assert( popcnt( hc_b ) == 2 );
    std::cout << "Reading..." << std::endl;
    auto mp = read_all_5_csv();
    std::cout << "Read done." << std::endl;
    std::cout << "size of mp: " << mp.size() << std::endl;
    std::cout << "Running..." << std::endl;
    // wr_fast( hc_a, hc_b, mp );
    wr_fast( hc_a, hc_b, mp );
}

void test_wr_final() {
    uint64_t hc_a = 0x11ULL;
    uint64_t hc_b = 0x1100ULL;
    assert( popcnt( hc_a ) == 2 );
    assert( popcnt( hc_b ) == 2 );
    std::cout << "Reading..." << std::endl;
    auto startTime = std::chrono::system_clock::now();
    auto mp = read_all_5_csv();
    auto endTime = std::chrono::system_clock::now();
    std::cout << "read_all_5() function time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count() << std::endl;
    startTime = std::chrono::system_clock::now();
    auto mp_7 = read_all_7_csv();
    endTime = std::chrono::system_clock::now();
    std::cout << "read_all_7() function time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count() << std::endl;
    std::cout << "Read done." << std::endl;
    std::cout << "size of mp: " << mp.size() << std::endl;
    std::cout << "size of mp_7: " << mp_7.size() << std::endl;
    std::cout << "Running..." << std::endl;
    // wr_fast( hc_a, hc_b, mp );
    startTime = std::chrono::system_clock::now();
    wr_final( hc_a, hc_b, mp, mp_7 );
    // double wr = wr_montecado( hc_a, hc_b, mp );
    // std::cout << "wr: " << wr << std::endl;
    endTime = std::chrono::system_clock::now();
    std::cout << "wr_final() function time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count() << std::endl;
}

void test_max_fc_in_sc() {
    std::cout << "Reading..." << std::endl;
    auto mp = read_all_5_csv();
    std::cout << "Read done." << std::endl;
    std::cout << "size of mp: " << mp.size() << std::endl;
    std::cout << "Running..." << std::endl;

    uint64_t hc_a = 0b11ULL;
    uint64_t hc_b = 0b1100ULL;

    // uint64_t pc = 0xc046000000000ULL;
    uint64_t pc = 0x600310000ULL;

    uint64_t sc_a = hc_a ^ pc;
    uint64_t sc_b = hc_b ^ pc;

    uint64_t m_fc_a = max_fc_in_sc( sc_a, mp );
    uint64_t m_fc_b = max_fc_in_sc( sc_b, mp );
    std::cout << "m_fc_a: " << std::hex << m_fc_a << std::endl;
    std::cout << "m_fc_b: " << std::hex << m_fc_b << std::endl;
    std::cout << "mp_a: " << std::dec << mp[ m_fc_a ] << std::endl;
    std::cout << "mp_b: " << std::dec << mp[ m_fc_b ] << std::endl;
}

void test_max_five_in_seven() {
    Poker p;
    Sevencards sc_1( p.s4, p.s5, p.d3, p.d5, p.dK, p.cA, p.dA );
    Sevencards sc_2( p.s2, p.s3, p.d3, p.d5, p.dK, p.cA, p.dA );
    auto mfc_sc_1 = max_five_in_seven( sc_1.sevencards );
    auto mfc_sc_2 = max_five_in_seven( sc_2.sevencards );
    Fivecards fc_1( p.s5, p.d5, p.dK, p.cA, p.dA );
    std::cout << "mfc_1: " << mfc_sc_1 << std::endl;
    std::cout << "mfc_2: " << mfc_sc_2 << std::endl;
    std::cout << "fc_1: " << fc_1 << std::endl;
    if ( mfc_sc_1 < mfc_sc_2 ) {
        std::cout << "1 < 2" << std::endl;
    } else if ( mfc_sc_2 < mfc_sc_1 ) {
        std::cout << "2 < 1" << std::endl;
    } else if ( mfc_sc_1 == mfc_sc_2 ) {
        std::cout << "2 == 1" << std::endl;
    } else {
        std::cout << "omit..." << std::endl;
    }
    std::cout << "level mfc_1: " << mfc_sc_1.level << std::endl;
    std::cout << "level  fc_1: " << fc_1.level << std::endl;
    if ( mfc_sc_1 < fc_1 ) {
        std::cout << "1 < kk" << std::endl;
    } else if ( fc_1 < mfc_sc_1 ) {
        std::cout << "kk < 1" << std::endl;
    } else if ( mfc_sc_1 == fc_1 ) {
        std::cout << "kk == 1" << std::endl;
    } else {
        std::cout << "kk omit..." << std::endl;
    }
    /*
    std::cout << "Reading..." << std::endl;
    auto mp = read_all_5_csv();
    std::cout << "Read done." << std::endl;
    std::cout << "size of mp: " << mp.size() << std::endl;
    std::cout << "Running..." << std::endl;

    uint64_t hc_a = 0b11ULL;
    uint64_t hc_b = 0b1100ULL;

    // uint64_t pc = 0xc046000000000ULL;
    uint64_t pc = 0x600310000ULL;

    uint64_t sc_a = hc_a ^ pc;
    uint64_t sc_b = hc_b ^ pc;

    uint64_t m_fc_a = max_fc_in_sc( sc_a, mp );
    uint64_t m_fc_b = max_fc_in_sc( sc_b, mp );
    std::cout << "m_fc_a: " << std::hex << m_fc_a << std::endl;
    std::cout << "m_fc_b: " << std::hex << m_fc_b << std::endl;
    std::cout << "mp_a: " << std::dec << mp[ m_fc_a ] << std::endl;
    std::cout << "mp_b: " << std::dec << mp[ m_fc_b ] << std::endl;
    */
}

void test_level() {
    Poker p;
    Fivecards fc( p.cJ, p.cT, p.hT, p.h5, p.s5 );
    // auto mfc_sc = max_five_in_seven( sc.sevencards );
    std::cout << fc.level << std::endl;
}

void test_normal() {
    uint64_t sc_1 = 0x2000800a2a;
    uint32_t hash_su = hash_s( sc_1 );
    std::cout << hash_su << std::endl;
    uint32_t hash_num = hash_n( sc_1 );
    std::cout << hash_num << std::endl;
    bool ret = is_fc_flush_in_sc( sc_1 );
    if ( ret ) {
        std::cout << "flush" << std::endl;
    } else {
        std::cout << "not flush" << std::endl;
    }
}

void test_SK() {
    uint64_t hc_a = 0x1100000000000ULL;
    uint64_t hc_b = 0x11000000000ULL;

    auto startTime = std::chrono::system_clock::now();
    wr_SK( hc_a, hc_b );
    auto endTime = std::chrono::system_clock::now();
    std::cout << "GetRank() function time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count() << std::endl;

}

void cmd_wr( const std::vector< std::string >& cmd ) {
    uint64_t c1 = s_u64[ cmd[ 1 ] ];
    uint64_t c2 = s_u64[ cmd[ 2 ] ];
    uint64_t c3 = s_u64[ cmd[ 3 ] ];
    uint64_t c4 = s_u64[ cmd[ 4 ] ];
    assert( popcnt( c1 ) == 1 );
    assert( popcnt( c2 ) == 1 );
    assert( popcnt( c3 ) == 1 );
    assert( popcnt( c4 ) == 1 );
    uint64_t hc_a = c1 | c2;
    uint64_t hc_b = c3 | c4;
    assert( popcnt( hc_a ) == 2 );
    assert( popcnt( hc_b ) == 2 );
    double wr = wr_SK( hc_a, hc_b );
    std::cout << u64_s[ c1 ] << u64_s[ c2 ] << " vs " << u64_s[ c3 ] << u64_s[ c4 ] << std::endl;
    std::cout << "win rate of " << u64_s[ c1 ] << u64_s[ c2 ] << " : " << std::fixed << std::setprecision( 3 ) << 100 * wr << "%" << std::endl;
}

void cmd_mwr( const std::vector< std::string >& cmd ) {
    std::vector< uint64_t > hcs;
    int tmp_2 = 1;
    uint64_t card = 0ULL;
    for ( int i = 1; i < cmd.size(); ++ i ) {
        if ( tmp_2 == 1 ) {
            card = card ^ s_u64[ cmd[ i ] ];
            tmp_2 = 2;
        } else if ( tmp_2 == 2 ) {
            card = card ^ s_u64[ cmd[ i ] ];
            hcs.push_back( card );
            tmp_2 = 1;
            card = 0ULL;
        }
    }
    auto wrs = wr_preflop( hcs );
    for ( int i = 0; i < wrs.size(); ++ i ) {
        std::cout << wrs[ i ] << std::endl;
    }
}

void cmd_go( const std::vector< std::string >& cmd ) {
    int num_players = stoi( cmd[ 1 ] );
    assert( 1 < num_players && num_players < 24 );
    uint64_t poker = ( 1ULL << 52 ) - 1;
    std::vector< uint64_t > hcs;
    for ( int i = 0; i < num_players; ++ i ) {
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
    for ( int i = 0; i < wrs.size(); ++ i ) {
        uint64_t hc_tmp = hcs[ i ];
        uint64_t c1 = hc_tmp & ( -hc_tmp );
        hc_tmp = hc_tmp & ( hc_tmp - 1 );
        uint64_t c2 = hc_tmp & ( -hc_tmp );
        std::cout << u64_s[ c1 ] << u64_s[ c2 ] << " : ";
        std::cout << std::fixed << std::setprecision( 3 ) << 100 * wrs[ i ] << "%\n";
    }
    hcs.clear();
}

int global_id = 0;

class Player {
public:
    int id;
    const char* name;
    uint64_t holecards;
    uint64_t c1;
    uint64_t c2;
    bool is_on_table;
    int chips;
    Player() {}
    Player( const char* name, int buyin ) {
        this->id = global_id++;
        this->name = name;
        this->chips = buyin;
    }
    Player( const char* name, std::string c1, std::string c2 ) {
        this->id = global_id++;
        this->name = name;
        this->c1 = s_u64[ c1 ];
        assert( popcnt( this->c1 ) == 1 );
        this->c2 = s_u64[ c2 ];
        assert( popcnt( this->c2 ) == 1 );
        this->holecards = this->c1 | this->c2;
        assert( popcnt( holecards ) == 2 );
        this->is_on_table = true;
        this->chips = 0;
    }
    bool operator==( const Player& b ) {
        if ( *this == b )
            return true;
        if ( this->id == b.id && this->name == b.name ) {
            return true;
        }
        return false;
    }
};

class Game {
public:
    const char* game_place;
    std::vector< Player > players;
    uint64_t flop_cards;
    uint64_t turn_card;
    uint64_t river_card;
    uint64_t poker;
    int small_blind;
    int big_blind;
    int btn;
    int utg;
    int co;
    int pos_dealer;
    int pos_sb;
    int pos_bb;
    int straddle;
    int ante;
    int pot;
    int chip_rate;
    int buyin;
    bool is_dc;
    bool is_flop;
    bool is_turn;
    bool is_river;
    Game( const char* game_place, int sb, int bb, int ante, int straddle, int buyin, int chip_rate ) {
        this->game_place = game_place;
        if ( !strcmp( game_place, "la" ) ) {
            this->poker = ( 1ULL << 52 ) - 1;
            this->flop_cards = 0ULL;            
            this->small_blind = sb;
            this->big_blind = bb;
            this->ante = 0;
            this->straddle = 0;
            this->buyin = buyin;
            this->chip_rate = chip_rate;
            this->is_dc = false;
            this->is_flop = false;
            this->is_turn = false;
            this->is_river = false;
            this->pot = 0;
        }
    }
    void add_player( const Player& p ) {
        this->players.push_back( p );
    }
    void remove_player( Player p ) {
        for ( auto it = players.begin(); it != players.end(); ++ it ) {
            if ( p == *it ) {
                players.erase( it );
                break;
            }
        }
    }
    void discard_holecards() {
        this->poker = ( 1ULL << 52 ) - 1;
        for ( int i = 0; i < players.size(); ++ i ) {
            std::random_device rd;
            std::default_random_engine eng( rd() );
            std::uniform_int_distribution< int > distr( 0, 51 );

            uint64_t hc = 0ULL;
            while ( popcnt( hc ) != 2 ) {
                // std::cout << popcnt( hc ) << std::endl;
                int rand_a = distr( eng );
                // std::cout << "rand_a: " << rand_a << std::endl;
                uint64_t card = 1ULL << rand_a;
                if ( ( card & poker ) == card ) {
                    hc = hc ^ card;
                    poker = poker ^ card;
                }
            }
            assert( popcnt( hc ) == 2 );
            assert( ( hc & poker ) == 0ULL );
            players[ i ].holecards = hc;
            this->is_dc = true;
        }
    }
    void wr_cal_preflop() {
        std::vector< uint64_t > hcs;
        for ( int i = 0; i < players.size(); ++ i ) {
            hcs.push_back( players[ i ].holecards );
        }
        auto wrs = wr_preflop( hcs );
        for ( int i = 0; i < wrs.size(); ++ i ) {
            uint64_t hc_tmp = hcs[ i ];
            uint64_t c1 = hc_tmp & ( -hc_tmp );
            hc_tmp = hc_tmp & ( hc_tmp - 1 );
            uint64_t c2 = hc_tmp & ( -hc_tmp );
            std::cout << u64_s[ c1 ] << u64_s[ c2 ] << " : ";
            std::cout << std::fixed << std::setprecision( 3 ) << 100 * wrs[ i ] << "%\n";
        }
    }
    void wr_cal_flop() {
        std::vector< uint64_t > hcs;
        for ( int i = 0; i < players.size(); ++ i ) {
            hcs.push_back( players[ i ].holecards );
        }
        auto wrs = wr_flop( hcs, this->flop_cards );
        for ( int i = 0; i < wrs.size(); ++ i ) {
            uint64_t hc_tmp = hcs[ i ];
            uint64_t c1 = hc_tmp & ( -hc_tmp );
            hc_tmp = hc_tmp & ( hc_tmp - 1 );
            uint64_t c2 = hc_tmp & ( -hc_tmp );
            std::cout << u64_s[ c1 ] << u64_s[ c2 ] << " : ";
            std::cout << std::fixed << std::setprecision( 3 ) << 100 * wrs[ i ] << "%\n";
        }
    }
    void wr_cal_turn() {
        std::vector< uint64_t > hcs;
        for ( int i = 0; i < players.size(); ++ i ) {
            hcs.push_back( players[ i ].holecards );
        }
        auto wrs = wr_turn( hcs, this->flop_cards, this->turn_card );
        for ( int i = 0; i < wrs.size(); ++ i ) {
            uint64_t hc_tmp = hcs[ i ];
            uint64_t c1 = hc_tmp & ( -hc_tmp );
            hc_tmp = hc_tmp & ( hc_tmp - 1 );
            uint64_t c2 = hc_tmp & ( -hc_tmp );
            std::cout << u64_s[ c1 ] << u64_s[ c2 ] << " : ";
            std::cout << std::fixed << std::setprecision( 3 ) << 100 * wrs[ i ] << "%\n";
        }
    }
    void flop_round() {
        assert( is_dc );
        std::random_device rd;
        std::default_random_engine eng( rd() );
        std::uniform_int_distribution< int > distr( 0, 51 );

        uint64_t tmp_poker = this->poker;
        assert( popcnt( this->poker ) == 52 - 2 * this->players.size() );
        uint64_t flop_c = 0ULL;
        while ( popcnt( flop_c ) != 3 ) {
            // std::cout << popcnt( hc ) << std::endl;
            int rand_a = distr( eng );
            // std::cout << "rand_a: " << rand_a << std::endl;
            uint64_t card = 1ULL << rand_a;
            if ( ( card & tmp_poker ) == card ) {
                flop_c = flop_c ^ card;
                tmp_poker = tmp_poker ^ card;
            }
        }
        assert( popcnt( flop_c ) == 3 );
        assert( ( flop_c & tmp_poker ) == 0ULL );
        this->flop_cards = flop_c;
        std::cout << "flop cards: " << std::endl;
        for ( int i = 0; i < 3; ++ i ) {
            uint64_t c = flop_c & ( -flop_c );
            flop_c = flop_c & ( flop_c - 1 );
            std::cout << u64_s[ c ] << " ";
        }
        std::cout << std::endl;
        this->is_flop = true;
    }

    void turn_round() {
        assert( is_flop );
        std::random_device rd;
        std::default_random_engine eng( rd() );
        std::uniform_int_distribution< int > distr( 0, 51 );

        uint64_t tmp_poker = this->poker ^ this->flop_cards;
        assert( popcnt( this->poker ) == 52 - 2 * this->players.size() );
        assert( popcnt( tmp_poker ) == 52 - 2 * this->players.size() - 3 );
        uint64_t turn_c = 0ULL;
        while ( popcnt( turn_c ) != 1 ) {
            // std::cout << popcnt( hc ) << std::endl;
            int rand_a = distr( eng );
            // std::cout << "rand_a: " << rand_a << std::endl;
            uint64_t card = 1ULL << rand_a;
            if ( ( card & tmp_poker ) == card ) {
                turn_c = turn_c ^ card;
                tmp_poker = tmp_poker ^ card;
            }
        }
        assert( popcnt( turn_c ) == 1 );
        assert( ( turn_c & tmp_poker ) == 0ULL );
        this->turn_card = turn_c;
        std::cout << "boards card: " << std::endl;
        uint64_t flop_c = this->flop_cards;
        for ( int i = 0; i < 3; ++ i ) {
            uint64_t c = flop_c & ( -flop_c );
            flop_c = flop_c & ( flop_c - 1 );
            std::cout << u64_s[ c ] << " ";
        }
        std::cout << u64_s[ turn_c ] << " ";
        std::cout << std::endl;
        is_turn = true;
    }

    void river_round() {
        assert( is_turn );
        std::random_device rd;
        std::default_random_engine eng( rd() );
        std::uniform_int_distribution< int > distr( 0, 51 );

        uint64_t tmp_poker = this->poker ^ this->flop_cards ^ this->turn_card;
        assert( popcnt( this->poker ) == 52 - 2 * this->players.size() );
        assert( popcnt( tmp_poker ) == 52 - 2 * this->players.size() - 3 - 1 );
        uint64_t river_c = 0ULL;
        while ( popcnt( river_c ) != 1 ) {
            // std::cout << popcnt( hc ) << std::endl;
            int rand_a = distr( eng );
            // std::cout << "rand_a: " << rand_a << std::endl;
            uint64_t card = 1ULL << rand_a;
            if ( ( card & tmp_poker ) == card ) {
                river_c = river_c ^ card;
                tmp_poker = tmp_poker ^ card;
            }
        }
        assert( popcnt( river_c ) == 1 );
        assert( ( river_c & tmp_poker ) == 0ULL );
        this->river_card = river_c;
        std::cout << "boards card: " << std::endl;
        uint64_t flop_c = this->flop_cards;
        uint64_t turn_c = this->turn_card;
        for ( int i = 0; i < 3; ++ i ) {
            uint64_t c = flop_c & ( -flop_c );
            flop_c = flop_c & ( flop_c - 1 );
            std::cout << u64_s[ c ] << " ";
        }
        std::cout << u64_s[ turn_c ] << " ";               
        std::cout << u64_s[ river_c ] << " ";
        std::cout << std::endl;
        is_river = true;
    }
    void run() {
        int num_players = players.size();
        for ( int i = 0; i < num_players; ++ i ) {
            std::cout << "id: " << i << " name: " << players[ i ].name << std::endl;
        }
        std::cout << "plz select position of small blind: " << std::endl;
        std::cin >> this->pos_sb;
        this->pos_bb = ( this->pos_sb + 1 ) % num_players;
        this->pos_dealer = ( this->pos_sb - 1 + num_players ) % num_players;
        int token = ( this->pos_bb + 1 ) % num_players;
        this->discard_holecards();
        // players[ pos_sb ].small_blind();
        this->pot += 5;
        // players[ pos_bb ].big_blind();
        this->pot += 10;
        while ( true ) {
            if ( players[ token ].is_on_table ) {
                // int move_ret = players[ token ].move();
                int move_ret = 0;
                if ( move_ret == -1 ) {
                    players[ token ].is_on_table = false;
                } else if ( move_ret == 1 ) {
                    players[ token ].chips -= 10;
                    this->pot += 10;
                }
            }
            
        }
    }
};

void cmd_poker( const std::vector< std::string >& cmd ) {
    Game game( "la", 5, 10, 0, 0, 1000, 0.05 );
    Player jd( "jd", 1000 );
    Player sb( "sb", 1000 );
    Player la( "la", 1000 );
    Player yy( "yy", 1000 );
    Player lh( "lh", 1000 );
    Player xg( "xg", 1000 );
    game.add_player( jd );
    game.add_player( sb );
    game.add_player( la );
    game.add_player( yy );
    game.add_player( lh );
    game.add_player( xg );
    std::cout << "now the number of players: " << game.players.size() << std::endl;
    while ( true ) {
        std::string in;
        getline( std::cin, in );
        auto cmds = split( in, " " );
        if ( cmds.size() == 0 ) {
            continue;
        }
        if ( cmds[ 0 ] == "dc" ) { // dc for discard
            game.discard_holecards();
            std::cout << "dicard cards done." << std::endl;
        } else if ( cmds[ 0 ] == "wc" ) { // wc for wr_calculate
            if ( cmds.size() < 2 ) {
                continue;
            }
            std::cout << "win rate calculating..." << std::endl;
            if ( cmds[ 1 ] == "pr" && game.is_dc )
                game.wr_cal_preflop();
            else if ( cmds[ 1 ] == "fl" && game.is_flop )
                game.wr_cal_flop();
            else if ( cmds[ 1 ] == "tu" && game.is_turn )
                game.wr_cal_turn();
            std::cout << "win rate calculated done." << std::endl;
        } else if ( cmds[ 0 ] == "fl" ) { // fl for flop round
            game.flop_round();
        } else if ( cmds[ 0 ] == "tu" ) { // tu for turn round
            game.turn_round();
        } else if ( cmds[ 0 ] == "ri" ) { // ri for river round
            game.river_round();
        } else if ( cmds[ 0 ] == "ov" ) { // ov for game over
            std::cout << "game over." << std::endl;
            break;
        } else if ( cmds[ 0 ] == "run" ) {
            game.run();
        }
    }
}

void test_pipe() {
    init_one_c();

    int fd[ 2 ];
    pipe( fd );
    char out[ 256 ] = { 0 };
    memset( out, 0, sizeof( out ) );
    int status;
    // ---------------------------------------------fork()
    pid_t fpid = fork();
    if ( fpid < 0 ) {
        exit( -1 );
    } else if ( fpid == 0 ) {
        close( fd[ 1 ] );
        while ( true ) {
            char buf[ 256 ] = { 0 };
            memset( buf, 0, sizeof( buf ) );

            int ret = read( fd[ 0 ], buf, sizeof( buf ) );
            if ( !ret ) {
                std::cerr << ret << std::endl;
            }

            auto cmd = split( buf, " " );
            if ( cmd.size() == 0 ) {
                continue;
            }
            if ( cmd[ 0 ] == "wr" ) {
                cmd_wr( cmd );
            } else if ( cmd[ 0 ] == "mwr" ) {
                cmd_mwr( cmd );
            } else if ( cmd[ 0 ] == "go" ) {
                cmd_go( cmd );
            } else if ( cmd[ 0 ] == "play" ) {
                cmd_poker( cmd );   
            }
        }
    } else {
        close( fd[ 0 ] );
        while ( true ) {
            char buf[ 256 ] = { 0 };
            memset( buf, 0, sizeof( buf ) );

            std::string in;
            getline( std::cin, in );
            sprintf( buf, "%s", in.c_str() );
            write( fd[ 1 ], buf, sizeof( buf ) );
            sleep( 1 );
        }
    }
}

void shell() {
    init_one_c();
    while ( true ) {
        std::string in;
        getline( std::cin, in );
        auto cmd = split( in, " " );
        if ( cmd.size() == 0 ) {
            continue;
        }
        if ( cmd[ 0 ] == "wr" ) {
            cmd_wr( cmd );
        } else if ( cmd[ 0 ] == "mwr" ) {
            cmd_mwr( cmd );
        } else if ( cmd[ 0 ] == "go" ) {
            cmd_go( cmd );
        } else if ( cmd[ 0 ] == "play" ) {
            cmd_poker( cmd );   
        } else if ( cmd[ 0 ] == "over" ) {
            break;
        }
    }
}

void test_wr_hc_preflop() {
    uint64_t hc = 0x11ULL;
    int num_players = 2;
    double wr = wr_hc_preflop( hc, 2 );
    std::cout << wr << std::endl;
}

int main( int argc, char *argv[] ) {
    printf( "App starting...\n\n" );
    auto startTime = std::chrono::system_clock::now();

    // test_SK();
    // test_pipe();
    // shell();
    test_wr_hc_preflop();

    // test_wr_pthreads();
    // test_thread();
    // test_fork();
    // generate_fivecards();
    // generate_sevencards();
    // test_wr_final();
    // test_normal();
    // test_wr_fast();
    // test_level();
    // test_max_fc_in_sc();
    // test_max_five_in_seven();
    /*
    if ( argc > 4 ) {
        std::cout << "v1: " << argv[ 1 ] << std::endl;
        std::cout << "v2: " << argv[ 2 ] << std::endl;
        std::cout << "v3: " << argv[ 3 ] << std::endl;
        std::cout << "v4: " << argv[ 4 ] << std::endl;
        wr_2( argv[ 1 ], argv[ 2 ], argv[ 3 ], argv[ 4 ] );
    } else {
        wr_2();
    }
    */
    // app();
    // test_max_fc();
    // test_change_();
    // test_wr();
    // test_operator_s();
    // test_choose();
    /*
    printf( "argc: %d\n", argc );
    printf( "argv[ 0 ]: %s\n", argv[ 0 ] );
    if ( argc > 1 ) {
        printf( "argv[ 1 ]: %s\n", argv[ 1 ] );
        int level = atoi( argv[ 1 ] );
        assert( -1 < level && level < 10 );
        test_choose( level );
    } else {
        test_choose();
    }
    */
    auto endTime = std::chrono::system_clock::now();
    // std::cout << "time:" << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << std::endl;
    std::cout << "main() function time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count() << std::endl;
    printf( "\nApp end.\n" );
    return 0;
}
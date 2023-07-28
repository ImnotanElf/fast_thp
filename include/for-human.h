#ifndef __FOR_HUMAN_H__
#define __FOR_HUMAN_H__

#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map< std::string, uint64_t > s_u64;
std::map< uint64_t, std::string > u64_s;
std::vector< std::string > card_s { "As", "Ah", "Ac", "Ad", 
                                    "Ks", "Kh", "Kc", "Kd", 
                                    "Qs", "Qh", "Qc", "Qd", 
                                    "Js", "Jh", "Jc", "Jd", 
                                    "Ts", "Th", "Tc", "Td", 
                                    "9s", "9h", "9c", "9d", 
                                    "8s", "8h", "8c", "8d", 
                                    "7s", "7h", "7c", "7d", 
                                    "6s", "6h", "6c", "6d", 
                                    "5s", "5h", "5c", "5d", 
                                    "4s", "4h", "4c", "4d", 
                                    "3s", "3h", "3c", "3d", 
                                    "2s", "2h", "2c", "2d" };

void init_one_c() {
    for ( int i = 0; i < 52; ++ i ) {
        uint64_t u64 = 1ULL << i;
        u64_s[ u64 ] = card_s[ i ];
        s_u64[ card_s[ i ] ] = u64;
    }
}

#endif
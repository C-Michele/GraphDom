#ifndef GRAPHDOM_UTILITY_H
#define GRAPHDOM_UTILITY_H

#include <cstdint>

namespace graphdom::utility{}

namespace graphdom::utility {
    inline std::uintptr_t hash_pointer(const void* const input) {
        if constexpr ( sizeof(void*) == 8 ) {
            // See "SplitMix64" written in 2015 by Sebastiano Vigna ( https://prng.di.unimi.it/splitmix64.c )
            auto output = reinterpret_cast< std::uintptr_t >( input ) + 0x9e3779b97f4a7c15;
            output = (output ^ (output >> 30)) * 0xbf58476d1ce4e5b9;
            output = (output ^ (output >> 27)) * 0x94d049bb133111eb;
            return output ^ (output >> 31);
        }
        else if constexpr ( sizeof(void*) == 4 ) {
            // See "fmix32" function of "MurmurHash3" written by Austin Appleby ( https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp )
            auto output = reinterpret_cast< std::uintptr_t >( input );
            output ^= output >> 16;
            output *= 0x85ebca6b;
            output ^= output >> 13;
            output *= 0xc2b2ae35;
            output ^= output >> 16;
            return output;
        }
    }
}


#endif //GRAPHDOM_UTILITY_H
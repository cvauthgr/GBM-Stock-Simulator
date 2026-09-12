#pragma once

#include <random>

namespace prng
{

inline std::mt19937_64 generate()
{
    thread_local std::random_device rd ; //thread_local so each thread get a different seed

    thread_local std::seed_seq  ss { rd() , rd() , rd() , rd() , rd() , rd() , rd() } ;

    return std::mt19937_64 ( ss ) ;
}

inline thread_local std::mt19937_64  mt { generate() } ; //Can be called from any file ( stand-alone instance ) , thread local for the same reason
//otherwise all threads use the same random value at each respective simualation , mt19937_64 to avoid repetitiond in random number generations


inline double getReal(double min , double max)
{
    return std::uniform_real_distribution<double>{ min , max }(mt) ;
}

inline int getInt( int min , int max )
{
    return std::uniform_int_distribution<int>{ min , max }(mt) ;
}

template <typename T>
inline T fairChance( T variable )
{
    T fairProbability { 0.5 } ;
    T randomProbability { prng::getReal( 0.0 , 1.0 ) } ;

    if( randomProbability <= fairProbability )
        return variable ;

    return (-1)*variable ;
}

}
